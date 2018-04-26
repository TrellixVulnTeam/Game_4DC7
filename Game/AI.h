#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include"Human.h"
#include"Game.h"
#include"Geizi.h"
class Player;
class keiroK;

class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();

	void NPCNormal();//�s���̒ʏ�s���̏����B
	//void NPCEscape_NPC();//�s�����]���rNPC���瓦����Ƃ��̏����B
	//void NPCEscape_Player();//�s�����]���r�v���C���[���瓦����Ƃ��̏����B
	void NPCDamage();//�U�����󂯂Ă���]���rNPC�ɂȂ�܂ł̏����B
	void NPCZombie_Normal();//�]���rNPC�̒ʏ�s���̏����B
	void NPCZombie_Chase();//�]���rNPC���s����ǐՂ���Ƃ��̏����B
	void NPCZombie_Attack();//���ꕔ���ƃ]���r���키���̏����B
	void NPCescape();//�s�����]���r�v���C���[���瓦����Ƃ��̏����B
	void NPCReturn();//�߂�Ƃ�

	void Render(CRenderContext& rc);
	void Turn();
	void DamageHantei();//�_���[�W����B
	void NPCRuet(); //NPC�̈ړ����[�g���i�[����B
	float GetKyori(CVector3 a, CVector3 b);  //2�̃I�u�W�F�N�g�̋������v������B
	float VectorAngleDeg(CVector3 c);  //2�̃x�N�g���̊p�x���p�x�\�L(degree)�ŕԂ��B

	float VectorAngleDeg2(CVector3 c);
	//�����o�ϐ�
	enum npcpattern { //switch���Ɏg���B
		Normal,             //�s���̒ʏ��ԁB
		Damage,             //�_���[�W���󂯂��Ƃ��B
		Escape,				//�����Ă�Ƃ��B
		//Escape_NPC,             //�s����NPC����̓�����ԁB
		//Escape_Player,       //�s���̃v���C���[����̓�����ԁB
		Return,				//�߂�Ƃ��B
		Zombie_Normal,      //�]���r��NPC�̒ʏ��ԁB
		Zombie_Chase,       //�]���r��NPC�̒ǐՏ�ԁB
		Zombie_Attack       //�]���r��NPC�̍U����ԁB
	};
	enum npcpattern pa;
	CCharacterController m_charaCon;
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
	bool DamageFlag = false;      //�_���[�W���󂯂����������t���O�B
	bool HitFlag = false;      //�_���[�W��^�������������t���O�B
	bool BattleFlag = false;     //���ꕔ���Ɛ퓬�����Ă��邩�������t���O�B
	bool ForceFlag = false;     //���ꕔ���̏o����\���t���O�B
	int MyNumber = 0;               //�����������݂��Ă���p�X�̔ԍ��B
	int ZombieChaseNumber = 0;      //�]���r���ǐՂ��n�߂����ɗ����Ă����p�X�̔ԍ��B
	float m_speed;
	int iNo = 0;
	int ima = 2;
	int kore = 0;
	int modori = 0;
	int da = 1;
	std::vector<int> jyunban;
	AI* Tansaku = nullptr;  //�T�����ʂ̃I�u�W�F�N�g���i�[����B
	AI*Chase_Zombie;  //�ǐՂ��Ă���L�������i�[����B
};

