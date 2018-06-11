#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/animation/tkAnimation.h" //�A�j���[�V����
#include"Human.h"
#include"Game.h"
#include"Geizi.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"

#define REACH 500.0  //�]���r�̍U���͈́B���̋����܂ŋ߂Â�����U������B
#define PI 3.141592653589793 
class Player;
class keiroK;
class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();
	void GetGame(Game* ka)
	{
		game = ka;
	}
	void NPCNormal();//�s���̒ʏ�s���̏����B
	void NPCNormal_Search();//�s�����x�����鏈���B
	void NPCEscape_NPC();//�s�����]���rNPC���瓦����Ƃ��̏����B
	void NPCChase();
	//void NPCEscape_Player();//�s�����]���r�v���C���[���瓦����Ƃ��̏����B
	void Gathered();				//�]���r��....�W������I�I�I�I�I�I
	void NPCResistance_NPC();  //�]���r�ɒ�R���Ă���Ƃ��̏����B
	void NPCResistance_Player();  //�]���r�ɒ�R���Ă���Ƃ��̏����B
	void NPCDamage();//����Ă���]���rNPC�ɂȂ�܂ł̏����B
	void NPCFade_Out();//��ʎs�����X�e�[�W����o�Ă����܂ł̏����B
	void NPCZombie_Normal();//�]���rNPC�̒ʏ�s���̏����B
	void NPCZombie_Chase();//�]���rNPC���s����ǐՂ���Ƃ��̏����B
	void NPCZombie_Attack();//���ꕔ���ƃ]���r���키���̏����B//vs���ꕔ��
	void NPCzombie_Return();//��������A��i�����j
	void nearestpas();//�����_���̏�����
//	void NPCzombie_Escape();
	void NPCescape();//�s�����]���r�v���C���[���瓦����Ƃ��̏����B
	void NPCReturn();//�߂�Ƃ�
	void NPCDeath();//���S�A���ŏ����B
	void Zonbesiya();
	void NPCRunangle(CVector3 kyori);
	void Render(CRenderContext& rc);
	void Turn();
	void DamageHantei();//�_���[�W����B
	void NPCRuet(); //NPC�̈ړ����[�g���i�[����B
	float GetKyori(CVector3 a, CVector3 b);  //2�̃I�u�W�F�N�g�̋������v������B
	float VectorAngleDeg(CVector3 c);  //2�̃x�N�g���̊p�x���p�x�\�L(degree)�ŕԂ��B
	float Siya(CVector3 h, float g);
	float VectorAngleDeg2(CVector3 c);
	void takikennsau();
	void Animation_Walk();//�����n�߂ƕ��������̈�A�̃A�j���[�V�����̏����B
	void Animation_Run();//����n�߂Ƒ��葱���̈�A�̃A�j���[�V�����̏����B

	////////////////////////////////////////////////////////////////////////
	////�A�j���[�V�����֘A�̃����o�֐�(���\�b�h)�B                      ////
	////�e�T�u�N���X�ł̃I�[�o�[���C�h��O��Ƃ��邽�߁A���g�͏����Ȃ��B////
	//////////////////////////////////////////////////////////////////////////
	void AI_Animation();//AI�̃A�j���[�V�����̈ڍs����������B

	void Idle_Animation();
	
	void Loop_Walk_Animation();//����������Ƃ��̏����B

	void Loop_Run_Animation();//���葱����Ƃ��̏����B

	void Zombie_Walk_Animation();//�]���r��NPC������������Ƃ��̏����B
	//void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void NPC_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

protected:
	//�����o�ϐ�
	enum npcpattern { //switch���Ɏg���B
		Normal,             //�s���̒ʏ��ԁB
		Damage,             //�_���[�W���󂯂��Ƃ��B
		Resistance_NPC, //�]���r�ɕ߂܂��āA��R���Ă���Ƃ��B
		Resistance_Player,
		Escape,				//�����Ă�Ƃ��B
		Escape_NPC,             //�s����NPC����̓�����ԁB
		Chase,
		//Escape_Player,       //�s���̃v���C���[����̓�����ԁB
		Return,				//�߂�Ƃ��B
		Fade_Out,           //���ꕔ�����o�����āA��ʎs�����ޏꂷ��Ƃ��B
		Zombie_Normal,      //�]���r��NPC�̒ʏ��ԁB
		Zonbie_Gathered,    //�]���r�̏W���i�v���C���[�̈ʒu�j
		Zombie_Chase,       //�]���r��NPC�̒ǐՏ�ԁB
		Zombie_Attack,      //�]���r��NPC�̍U����ԁB
		Zombie_Return,		//�]���r��NPC�̌��̈ʒu�ɖ߂�
		Death,               //NPC�̎��S�B
		pa_num				//pa�̐�
	};

	enum AnimationClip {//�e�A�j���[�V�����̃N���b�v�B
		Idle,              //�������
		Loop_Walk,         //��������
		Loop_Run,          //���葱��
		Zombie_Walk,       //�]���r��NPC�̕���           
		//Resistance,        //��R
		//NPC_Attack      //�]���r��NPC�̍U��
		Animnum           //AnimationClip�̑���
	};

	enum npcpattern pa;
	CCharacterController A_charaCon;
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CQuaternion front = CQuaternion::Identity;
	CVector3 m_forward;						//�L�����̑O���B
	CVector3 m_rite;						//�L�����̉E�����B
	CMatrix mRot;
	keiroK keiro;
	Geizi* Gaizi;
	Player* pl;
	CMatrix m_tekirot;

	CMatrix k_tekirot;
	CVector3 retu_position;

	Game* game;
	
	CVector3 before_m_position = CVector3::Zero;		//��O�̍��W�B
	std::vector<int> jyunban;

	AI*Chawse_Zombie;  //�ǐՂ��Ă���L�������i�[����B
	int satForceFlag()
	{
		 ForceFlag = true;     //���ꕔ���̏o����\���t���O�B
	}
	float m_speed;
private:
	bool muteki_Flag = false;//���G�ɂȂ��Ă��邩�ǂ�����\���t���O�B
	bool DamageFlag = false;      //�_���[�W���󂯂����������t���O�B
	bool HitFlag = false;      //�_���[�W��^�������������t���O�B
	bool BattleFlag = false;     //���ꕔ���Ɛ퓬�����Ă��邩�������t���O�B
	bool Raifu_f = false;
	int MyNumber = 0;               //�����������݂��Ă���p�X�̔ԍ��B
	int ZombieChaseNumber = 0;      //�]���r���ǐՂ��n�߂����ɗ����Ă����p�X�̔ԍ��B
	float NPCHP=100.0f;
	float NPCMAXHP = 100.0f;
	int iNo = 0;
	int ima = 0;
	int kore = 0;
	int modori = 0;
	int da = 0;
	int mikata = 0;
	int muteki_count = 0;//���G���Ԃ̃J�E���g�B
	int Chasefrag = 0;
	bool ForceFlag = false;     //���ꕔ���̏o����\���t���O�B
	std::vector<int>::iterator pasu;
	//CVector3 m_movespeed=CVector3::Zero;
	float gravity = -3*(980.0f * GameTime().GetFrameDeltaTime());
	int No = 0;
	int no = 0;
	float sinsoku = 0.0f;
	AI* Tansaku = nullptr;  //�T�����ʂ̃I�u�W�F�N�g���i�[����Bo
	CVector3 m_movespeed = CVector3::Zero;		//�ړ����x�B
	AImove* work;
	CVector3 m_position = CVector3::Zero;
	AI* lam;
	float atekfrag = 0;
	float escapecaku = 30.0f;
	int radam = 0;
	int mokuhyouNo = 0;
	tekihei* tekip;
	int mokuhyou=1;
	std::vector<AI*> mikatalest;
	int mobe = 50;
	std::vector<Human*>::iterator AIrest;
	enum animation {
		shiminidle,
		shiminwalk,
		shiminrun,
		shiminattack,
		Zonbiwalk,
		Zonbiattack,
		animnum
	};
	float atakkukyori = 100.0f;
	int furag = 0;
	CAnimation ai_NPCAnimation;				//�A�j���[�V�����B
	CAnimationClip ai_NPCAnimationClips[animnum];	//�A�j���[�V�����N���b�v�B
	bool kannkaku = false;
	int Leftfrag = 0;
	bool kaiten = false;
	CShaderResourceView zondi;
	CObjectFrustumCulling m_objectFrustumCulling;
};

