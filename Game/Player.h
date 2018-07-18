#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include"tkEngine/sound/tkSoundSource.h"
#include<string>
//Font�̃e�X�g
///////////////////////////////////////////////////////
#include "tkEngine/graphics/font/tkFont.h"
///////////////////////////////////////////////////////
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
	void PostRender(CRenderContext& renderContext);
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
		m_moveSpeed = CVector3::Zero;

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
	void Playkoke()
	{
		m_animation.Play(koke, 0.2f);
	}
	void Playoki();

	bool anine_Playing()
	{
		return m_animation.IsPlaying();
	}
	int GetattackF()
	{
		return attackF;
	}
	void set_itemcounter()
	{
		itemcounter++;
	}


	//���X�e�B�b�N��X���̓��͗ʂ�Ԃ��B
	float GetlStick_x()
	{
		return lStick_x;
	}
	//���X�e�B�b�N��Y���̓��͗ʂ�Ԃ��B
	float GetlStick_y()
	{
		return lStick_y;
	}


	void set_camera_f()
	{
		camera_f = true;
	}
	void false_camera_f()
	{
		camera_f = false;
	}
	void set_bullet_sum()
	{

		bullet_sum += 5;
		swprintf_s(test_font, L"%d", bullet_sum);
	}
	bool getcamera_f()
	{
		return camera_f;
	}
	void SetController_end()
	{
		controller_end = true;
	}

	void Play_Respiration(CVector3 m_moveDecision);//�������̉����Đ������邩�𔻒f����B
	void Play_Attack();//�U���U���������̌��ʉ����Đ�����B
	bool CVector_same_Decision(CVector3 a, CVector3 b);//��̃x�N�g��������Ȃ̂��𒲂ׂ�B

	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
private:
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<�L�����N�^�p�̃��C�g�B
	CCharacterController m_charaCon;
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specMap;
	//�L�����N�^�R���g���[���B
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveDecision = CVector3::Zero;//�����Ă���̂��𔻒肷��B
				//�X�y�L�����}�b�v�B
	CVector3 m_forward = CVector3::Zero;						//�v���C���[�̑O���B
	CVector3 m_rite = CVector3::Zero;						//�v���C���[�̉E����
	float rotY = 0.0f; //��]
	float rotX = 0.0f; //��]
	CQuaternion qBias = CQuaternion::Identity;
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
	bool zikofrag = false;//�͂˂�ꂽ���ǂ�����ێ�����B�͂˂�ꂽ��true�ɂȂ�B
	enum animation {
		idle,
		walk,
		attack,
		ziko,
		oki,
		koke,
		animnum
	};
	car* carpoint;
	CAnimation m_animation;
	CShaderResourceView zondi;
	CAnimationClip m_animclip[animnum];
	int attackF = 0;//�A�^�b�N�t���O�B���ꂪ0�̂Ƃ��ɍU������B1�̂Ƃ��ɂ͏o���Ȃ��B
	int attackcounter = 0;
	CQuaternion bonerot = CQuaternion::Identity;
	CVector3 boneforward = CVector3::Zero;
	CVector3 boneright = CVector3::Zero;
	CVector3 boneup = CVector3::Zero;
	CMatrix bonerot_M;
	bool game = false;
	//////////T.M////////////////////////////

	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x;
	float lStick_y;

	float muteki_count = 0;//���G���Ԃ̃J�E���g�B
	bool  muteki_Flag = false;
	bool collision_f = false;
	float blend = 0.0f;
	//CVector3 m_moveSpeed_log = CVector3::Zero;//moveSpeed��ێ�����B
	bool L3_button_Flag = false;//L3�{�^���������ꂽ���ǂ�����ێ�����t���O�B
	prefab::CSoundSource*m_Respiration = nullptr;//���g���̉��B�����Ƃ��ɗ����B

	prefab::CSoundSource*m_AttackSE = nullptr;//���g���̉��B�����Ƃ��ɗ����B

	int itemcounter = 0;

	bool controller_end ;//�v���C���[�̃R���g���[���ł�����Ԃ��I���������Ƃ��󂯎��B
	bool camera_f = false;
	////////////////////////////////////////////////////
	std::wstring inputwstr = L"ABCDEFG";
	CFont m_font;
	wchar_t test_font[255];
	CVector2 font_pos = { 700.0f,400.0f };
	CVector2 fomt_pivot = { 0.0f,0.0f };
	int bullet_sum = 5;
	
	
};