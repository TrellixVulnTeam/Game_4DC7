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
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath,L"modelData/stage%d.cmo", No);
	m_skinModelData.Load(moveFilePath);
	m_skinModel.Init(m_skinModelData);
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero;
	rbInfo.rot = CQuaternion::Identity;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	return true;
}
void Stage::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Stage::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}