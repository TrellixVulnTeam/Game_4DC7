#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include"tkEngine/sound/tkSoundSource.h"
#define tama 20
class taieki;
class car;
class Player : public Human
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3& Getboneforward()
	{
		return boneforward;
	}

	CVector3& Getbonepos()
	{
		return bonepos;
	}
	void trueGame()
	{
		game = true;
	}
	void falseGame()
	{
		game = false;

	}
	CVector3& GetFoeward()
	{
		return m_forward;
	}

	CVector3& Getboneright()
	{
		return boneright;
	}

	CVector3& Getboneup()
	{
		return boneup;
	}

	CVector3 &GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	int GetattackF()
	{
		return attackF;
	}

	void Play_Respiration(CVector3 m_moveDecision);//�������̉����Đ������邩�𔻒f����B

	bool CVector_same_Decision(CVector3 a, CVector3 b);//��̃x�N�g��������Ȃ̂��𒲂ׂ�B
	
private:
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<�L�����N�^�p�̃��C�g�B
	CCharacterController m_charaCon;
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specMap;
			//�L�����N�^�R���g���[���B
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveDecision = CVector3::Zero;//�����Ă���̂��𔻒肷��B
				//�X�y�L�����}�b�v�B
	CVector3 m_forward=CVector3::Zero;						//�v���C���[�̑O���B
	CVector3 m_rite= CVector3::Zero;						//�v���C���[�̉E����
	float rotY = 0.0f; //��]
	float rotX = 0.0f; //��]
	CQuaternion qBias=CQuaternion::Identity;
	CQuaternion qBias1 = CQuaternion::Identity;
	CQuaternion qrot = CQuaternion::Identity;
	CMatrix mRot;
	CQuaternion m_rotation = CQuaternion::Identity;//�L�����̉�]
	CQuaternion d_rotation = CQuaternion::Identity;//�_�~�[�̉�]�i�c�j
	//CSkinModel m_taieki;
	//CSkinModelData m_taiekiModelData;
	taieki* Tp[20];
	int taieki_sum = 0;
	float taieki_timer = 0;
	int taieki_F = 0;
	prefab::CEffect* hakaba = nullptr;
	CVector3 landpos = CVector3::Zero;
	CVector3 land_to_player = CVector3::Zero;
	float land_to_player_vector = 0.0f;
	int landflag = 1;
	wchar_t bonename[50];
	int bonenum = 0;
	int boneNo = 0;
	CVector3 bonepos = CVector3::Zero;
	bool zikofrag = false;
	enum animation {
		idle,
		walk,
		attack,
		ziko,
		animnum
	};
	car* carpoint;
	CAnimation m_animation;
	CShaderResourceView zondi;
	CAnimationClip m_animclip[animnum];
	int attackF = 0;
	int attackcounter = 0;
	CQuaternion bonerot = CQuaternion::Identity;
	CVector3 boneforward = CVector3::Zero;
	CVector3 boneright = CVector3::Zero;
	CVector3 boneup = CVector3::Zero;
	CMatrix bonerot_M;
	bool game = false;
	//////////T.M////////////////////////////
	float Log_lStick_x = 0.0f;

	float Log_lStick_y = 0.0f;
	float muteki_count = 0;//���G���Ԃ̃J�E���g�B
	bool  muteki_Flag = false;
	bool collision_f = false;
	float blend = 0.0f;
	//CVector3 m_moveSpeed_log = CVector3::Zero;//moveSpeed��ێ�����B
	bool X_button_Flag = false;//X�{�^���������ꂽ���ǂ�����ێ�����t���O�B
	prefab::CSoundSource*m_Respiration = nullptr;//���g���̉��B�����Ƃ��ɗ����B
};

