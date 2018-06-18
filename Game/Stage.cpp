#include "stdafx.h"
#include "Stage.h"
#include"Game.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}
void Stage::OnDestroy()
{
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
bool Stage::Start()
{
	No = FindGO<Game>("Game")->stag;
	wchar_t moveFilePath[256];//�t�@�C���p�X�B
	swprintf_s(moveFilePath, L"modelData/stage%d.cmo", No);//�X�e�[�W�B
	m_skinModelData.Load(moveFilePath);
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	s_skinModelData.Load(L"modelData/sora.cmo");//��B�w�i�B
	s_skinModel.Init(s_skinModelData);
	////���b�V���R���C�_�[���쐬�B
	m_physicsStaticObject.CreateMeshObject( m_skinModel,CVector3::Zero,CQuaternion::Identity);
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);

	return true;
}
void Stage::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	s_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Stage::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	s_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}