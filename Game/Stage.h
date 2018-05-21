#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CMeshCollider m_meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody m_rigidBody;			//����
	int No = 0;
private:

	CSkinModel s_skinModel;					//�X�L�����f���B
	CSkinModelData s_skinModelData;			//�X�L�����f���f�[�^�B
};

