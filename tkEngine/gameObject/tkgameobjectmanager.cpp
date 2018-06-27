/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkgameobjectmanager.h"
#include <future>
#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	void CGameObjectManager::Execute()
	{
		ExecuteDeleteGameObjects();

		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreUpdateWrapper();
			}
		}
		CRenderContext& renderContext = GraphicsEngine().GetRenderContext();
		//�v�������_�����O�B
		GraphicsEngine().GetPreRender().Update();
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostUpdateWrapper();
			}
		}
		//�V�[���O���t���X�V�B
		UpdateSceneGraph();
		//���C�g���X�V�B
		LightManager().Update();
		//�G�t�F�N�g���X�V�B
		GraphicsEngine().GetEffectEngine().Update();

		//��ʂ��N���A
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
		CRenderTarget* renderTargets[] = {
			&GraphicsEngine().GetMainRenderTarget()
		};
		renderContext.OMSetRenderTargets(1, renderTargets);
		renderContext.ClearRenderTargetView(0, ClearColor);
		renderContext.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
		renderContext.RSSetState(RasterizerState::sceneRender);
		renderContext.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
		//�v�������_�����O�B
		GraphicsEngine().GetPreRender().Render(renderContext);
		BeginGPUEvent(L"enRenderStep_Render3DModelToScene");
		//�����_�����O�X�e�b�v��3D���f���̕`��ɁB
		renderContext.SetRenderStep(enRenderStep_Render3DModelToScene);

		//���C�g�̏���]���]���B
		LightManager().Render(renderContext);
		//�e�𗎂Ƃ����߂̏���]���B
		GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(renderContext);
		GraphicsEngine().GetGBufferRender().SendGBufferParamToGPU(renderContext);
		int no = 0;
		IGameObject* obj1;
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreRenderWrapper(renderContext);
				if (no++ == 2) {
					obj1 = obj;
				}
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->RenderWrapper(renderContext);
			}
		}

		EndGPUEvent();

		BeginGPUEvent(L"enRenderStep_Render3DModelToScene");
		renderContext.SetRenderStep(enRenderStep_Render3DModelToScene);
		for (int i = 0;i < 4;i++)
		{
			ClearColor[i] = 1.0f;
		}
		EnRenderStep renderStep = renderContext.GetRenderStep();
		renderContext.SetRenderStep(enRenderStep_ZPrepass);
		renderContext.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);
		for (int i = 0;i < 3;i++)
		{
			if (i == 1)
			{
				for (int i = 0;i < 4;i++)
				{
					ClearColor[i] = 0.0f;
				}
				renderContext.OMSetDepthStencilState(DepthStencilState::volumeLight, 0);
			}
			if(i == 2)
			{
				renderContext.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
				renderContext.SetRenderStep(enRenderStep_Render3DModelToScene);
			}
			unsigned int setTargetNum = 1;
			CRenderTarget* setRenderTarget[] = { &GraphicsEngine().GetVolumeLightTarget()[i] };
			renderContext.OMSetRenderTargets(1, setRenderTarget);
			if (i == 1)
			{
				renderContext.ClearRenderTargetView(0, ClearColor, true, true);
			}
			else
			{
				renderContext.ClearRenderTargetView(0, ClearColor);
			}
			LightManager().Render(renderContext);
			renderContext.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());

			for (GameObjectList objList : m_gameObjectListArray)
			{
				for (IGameObject* obj : objList)
				{
					obj->VolumeLightRenderWrapper(renderContext);
				}
			}
		}
		CRenderTarget* setRenderTarget[] = { &GraphicsEngine().GetMainRenderTarget() };
		renderContext.OMSetRenderTargets(1, setRenderTarget);
		renderContext.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
		renderContext.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);

		//EndGPUEvent();
		renderContext.SetRenderStep(renderStep);
		

		//�|�X�g�G�t�F�N�g�B
		GraphicsEngine().GetPostEffect().Render(renderContext);

		////2D�I�Ȃ��̂̕`��B
		BeginGPUEvent(L"enRenderStep_Render2DToScene");
		float blendFactor[4] = { 0.0f };
		renderContext.OMSetBlendState(AlphaBlendState::trans, blendFactor, 0xFFFFFFFF);
		renderContext.RSSetState(RasterizerState::spriteRender);
		renderContext.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
		renderContext.SetRenderStep(enRenderStep_Render2DToScene);
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostRenderWrapper(renderContext);
			}
		}
		EndGPUEvent();
	}
	void CGameObjectManager::UpdateSceneGraph()
	{
		//���[���h�s����X�V�B
		for (auto transform : m_childrenOfRootTransformList) {
			transform->UpdateWorldMatrixAll();
		}
	}
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//�o�b�t�@��؂�ւ��B
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for(GameObjectList& goList : m_deleteObjectArray[preBufferNo]){
			for(IGameObject* go : goList){
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find( goExecList.begin(),goExecList.end(),go );
				if (it != goExecList.end()) {
					//�폜���X�g���珜�O���ꂽ�B
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManager()) {
						delete (*it);
					}
				}
				goExecList.erase(it);
			}
			goList.clear();
		}
	}
	void CGameObjectManager::Init(int gameObjectPrioMax)
	{
		//psShader.Load("")
		TK_ASSERT( gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}
}