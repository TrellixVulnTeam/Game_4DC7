#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class taieki;
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
	CVector3 m_rite;						//�v���C���[�̉E����
	float rotY = 0.0f; //��]
	float rotX = 0.0f; //��]
	CQuaternion qBias;
	CQuaternion qBias1;
	CQuaternion qrot;
	CMatrix mRot;
	CQuaternion m_rotation = CQuaternion::Identity;//�L�����̉�]
	CQuaternion d_rotation = CQuaternion::Identity;//�_�~�[�̉�]�i�c�j
	CSkinModel m_taieki;
	CSkinModelData m_taiekiModelData;
	taieki* Tp = nullptr;
	prefab::CEffect* hakaba = nullptr;
	CVector3 landpos = CVector3::Zero;
	CVector3 land_to_player = CVector3::Zero;
	float land_to_player_vector = 0.0f;
	int landflag = 1;

};

