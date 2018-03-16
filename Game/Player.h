#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
class Player : public Human
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CAnimation m_animation;
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<�L�����N�^�p�̃��C�g�B
	CCharacterController m_charaCon;		//�L�����N�^�R���g���[���B
	CVector3 m_moveSpeed = CVector3::Zero;
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specMap;			//�X�y�L�����}�b�v�B
	CVector3 m_forward;						//�v���C���[�̑O���B
	float rotY=0.0f; //��]
	CQuaternion qBias;
	CMatrix mRot;
};

