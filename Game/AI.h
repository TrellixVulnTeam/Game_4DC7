#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/animation/tkAnimation.h" //�A�j���[�V����
#include"Human.h"
#include "AI_manager.h"
#include"Geizi.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"
#include"Game.h"
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
	void GetGame(AI_manager* ka)
	{
		game = ka;
	}
	void GetGaizi(Geizi*ka)
	{
		Gaizi = ka;
	}
	void NPCNormal();							//���̎��͂܂��m��Ȃ������c���̊X�Ƀ]���r������Ȃ�āc�i�s���̒ʏ�s���̏����j
	void NPCNormal_Search();				    //����H����́H�H�H�H�H�i�s���̎��쏈���j
	void NPCEscape_NPC();						//�Ɂ`����񂾂�`�`�`�i�s�����]���rNPC���瓦����Ƃ��̏����B�j
	void NPCChase();							//�����O�ɎE�����܂��`�`�`�[�[�[�[�i�]���r�����鏈���j
	//void NPCEscape_Player();					//�s�����]���r�v���C���[���瓦����Ƃ��̏����B
	void Gathered();							//��l�l�`�`���܂����܁`�`���i�]���r���W�����鏈���j
	void NPCResistance_NPC();					//���́c����ȓz�Ȃ񂩂Ɂc�i�s���]���r�ɂ��ꂽ�Ƃ��̏����j
	void NPCResistance_Player();				//�䂪�l���ɁA��Ђ̉����Ȃ��I�I�I�I�i�v���C���[�]���r�ɂ��ꂽ���̏����j
	void NPCDamage();							//���͐l�Ԃ���߂邼�`�`�`�`�`�i�]���r�������B�j
	void NPCFade_Out();							//����Ȓ��c����������΂��i�s����������o�Ă����܂ł̏����j
	void NPCZombie_Normal();					//�����́c�ǂ����i�]���rNPC�����_���p�j�̏����j
	void NPCZombie_Chase();						//���O���A���ʂ܂ŁA����̂���߂Ȃ��I�I�I�i�]���rNPC���s��������̏����j
	void NPCZombie_Attack();					//��l�l�ɂ��Ă��z�͋����ˁ`�`�`�i���ꕔ���ƃ]���r���키���̏����j//vs���ꕔ��
	void NPCzombie_Return();					//��������A��i�����j
	void nearestpas();			//�h�`�R�s�������ȁ`�`�`�i�����_���p�j�����̏������j
	void Retrieval_pasNo(int mokuhyou);
	void death_Animation();
	void again_move();
	void NPCGetaway();
//	void NPCzombie_Escape();					
	void NPCescape();							//���A����Ȃ̏��Ă�͂����˂��A�����邵���˂��i�]���r�v���C���[���瓦����Ƃ��̏����j
	void NPCReturn();							//�������ɂ́A��������͂����I�I�I�i�w�肵���p�X�܂ňڍs���鏈���j
	void FlyNPC();
	void NPCDeath();							//���́A�A����A�ȂƂ���ŁA�A�A�i���S�A���ŏ����j
	void Zonbesiya();							//�l���͂ǂ����`�`�`�i�]���r�̎��씻��j
	void NPCRunangle(CVector3 kyori);
	void Render(CRenderContext& rc);
	void pasmove(int mokuhyou);		                       //�p�X�𗘗p���čœK�ȃp�X�Ɉړ�����B
	void CharaConUpdate();
	void Chasepas(CVector3 m_position);		    //�ǂ������鎞���̊�{�ړ�����
	void hinannpas(CVector3 m_position);		//�����鎞�̊�{�ړ�����
	void Turn();
	void NPC_Search_Zonbi();					//���A�|���Ȃ񂩂˂���(�s�����]���r��T������)
	void NPCRuet();							    //NPC�̈ړ����[�g���i�[����B
	float GetKyori(CVector3 a, CVector3 b);     //2�̃I�u�W�F�N�g�̋������v������B
	float VectorAngleDeg(CVector3 c);           //2�̃x�N�g���̊p�x���p�x�\�L(degree)�ŕԂ��B
	float VectorAngleDeg(CVector3 h, CVector3 c);
	void search(CVector3 mokutekipos);								//�o�H�T���Ăяo���֐�
	void Fardist_path(CVector3 m_position);
	float Siya(CVector3 h, float g);
	float takikennsau();
	void AI_Animation();
	////////////////////////////////////////////////////////////////////////
	////�A�j���[�V�����֘A�̃����o�֐�(���\�b�h)�B                      ////
	////�e�T�u�N���X�ł̃I�[�o�[���C�h��O��Ƃ��邽�߁A���g�͏����Ȃ��B////
	//////////////////////////////////////////////////////////////////////////
	void Animation_Walk();					    //�����n�߂ƕ��������̈�A�̃A�j���[�V�����̏����B
	void Animation_Run();						//����n�߂Ƒ��葱���̈�A�̃A�j���[�V�����̏����B

	void Idle_Animation();
	
	void Loop_Walk_Animation();//����������Ƃ��̏����B

	void Loop_Run_Animation();//���葱����Ƃ��̏����B

	void Zombie_Walk_Animation();//�]���r��NPC������������Ƃ��̏����B
	//void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void NPC_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B
	void Zombie_Ziko_Animation();
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CVector3 Getposition()
	{
		return m_position;
	}
	void Gettekihei(tekihei* pointa)
	{
		tekip = pointa;
	}
	CVector3 Getforward()
	{
		return m_forward;
	}
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
		flyNPC,
		//Escape_Player,       //�s���̃v���C���[����̓�����ԁB
		Return,				//�߂�Ƃ��B
		Fade_Out,           //���ꕔ�����o�����āA��ʎs�����ޏꂷ��Ƃ��B
		Zombie_Normal,      //�]���r��NPC�̒ʏ��ԁB
		Zonbie_Gathered,    //�]���r�̏W���i�v���C���[�̈ʒu�j
		Zombie_Chase,       //�]���r��NPC�̒ǐՏ�ԁB
		Zombie_Attack,      //�]���r��NPC�̍U����ԁB
		Zombie_Return,		//�]���r��NPC�̌��̈ʒu�ɖ߂�
		Death,               //NPC�̎��S�B
		Getaway,
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
	enum animation {
		shiminidle,
		shiminwalk,
		shiminrun,
		shiminattack,
		Zonbiwalk,
		Zonbiattack,
		Zonbi_zico,
		animnum
	};
	CAnimation ai_NPCAnimation;				//�A�j���[�V�����B
	CAnimationClip ai_NPCAnimationClips[animnum];	//�A�j���[�V�����N���b�v�B
	CShaderResourceView zondi;

	enum npcpattern pa;
	int satForceFlag()
	{
		 ForceFlag = true;     //���ꕔ���̏o����\���t���O�B
	}

	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	AI_manager* game;
	float m_speed;
	bool ziko_frag = false;
	car* Car;
	Geizi* Gaizi;
	Player* pl;
	CVector3 previous_position=CVector3::Zero;
	int taime = 0;
	bool HitFlag = false;      //�_���[�W��^�������������t���O�B
private:
	bool muteki_Flag = false;//���G�ɂȂ��Ă��邩�ǂ�����\���t���O�B
	bool DamageFlag = false;      //�_���[�W���󂯂����������t���O�B
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
	int stoptaim = 0;
	//CVector3 m_movespeed=CVector3::Zero;
	float gravity = -3*(980.0f * GameTime().GetFrameDeltaTime());
	int No = 0;
	int no = 0;
	float sinsoku = 0.0f;
	AI* Tansaku = nullptr;  //�T�����ʂ̃I�u�W�F�N�g���i�[����Bo
	AI* lam;
	CVector3 m_movespeed = CVector3::Zero;		//�ړ����x�B
	AImove* work;
	CVector3 m_position = CVector3::Zero;
	float atekfrag = 0;
	float escapecaku = 30.0f;
	int radam = 0;
	int mokuhyouNo = 0;			//�ړI�n�̃p�X�ԍ��̓����Ă��遃�z��ԍ���
	tekihei* tekip;
	int mokuhyou=1;					//�ړI�n�̃p�X�ԍ�
	std::vector<AI*> mikatalest;
	bool keikai_f = false;
	CVector3 retu_position = CVector3::Zero;
	int mobe = 500;
	std::vector<Human*>::iterator AIrest;

	float atakkukyori = 200.0f;
	int furag = 0;
	bool kannkaku = false;
	int Leftfrag = 0;
	int destination_Leftfrag = 0;
	bool kaiten = false;
	CObjectFrustumCulling m_objectFrustumCulling;
	float angle = 0.0f;
	CVector3 Pboneforward = CVector3::Zero;
	CQuaternion Crot = CQuaternion::Identity;
	CCharacterController A_charaCon;
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CQuaternion front = CQuaternion::Identity;
	CVector3 m_forward;						//�L�����̑O���B
	CVector3 m_rite;						//�L�����̉E�����B
	CMatrix mRot;
	CMatrix m_tekirot;
	CMatrix k_tekirot;
	car* ziko_car;
	CVector3 before_m_position = CVector3::Zero;		//��O�̍��W�B
	std::vector<int> jyunban;
	int counta = 0;
	CVector3 flydist=CVector3::Zero;
	AI* Chawse_Zombie;  //�ǐՂ��Ă���L�������i�[����B
};

