#pragma once
#include"Human.h"
class Player;
class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();
	void NPCNormal();
	void NPCDamage();
	void NPCZombie_Normal();
	void NPCZombie_Chase();
	void NPCZombie_Attack();

	void Render(CRenderContext& rc);
	void Turn();
	void NPCRuet(); //NPC�̈ړ����[�g���i�[����B
	float GetKyori(CVector3 a, CVector3 b);  //2�̃I�u�W�F�N�g�̋������v������B
	float VectorAngleDeg(CVector3 c);  //2�̃x�N�g���̊p�x���p�x�\�L(degree)�ŕԂ��B

	//�����o�ϐ�
	enum npcpattern { //switch���Ɏg���B
		Normal,             //�s���̒ʏ��ԁB
		Damage,             //�_���[�W���󂯂��Ƃ��B
		Zombie_Normal,      //�]���r��NPC�̒ʏ��ԁB
		Zombie_Chase,       //�]���r��NPC�̒ǐՏ�ԁB
		Zombie_Attack       //�]���r��NPC�̍U����ԁB
	};
	enum npcpattern pa;
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CVector3 m_forward;						//�L�����̑O���B
	CVector3 m_rite;						//�L�����̉E�����B
	CMatrix mRot;
	bool DamageFlag = false;      //�_���[�W���󂯂����������t���O�B
	bool HitFlag = false;      //�_���[�W��^�������������t���O�B
	bool BattleFlag = false;     //���ꕔ���Ɛ퓬�����Ă��邩�������t���O�B
	bool ForceFlag = false;     //���ꕔ���̏o����\���t���O�B
	int MyNumber = 0;               //�����������݂��Ă���p�X�̔ԍ��B
	int ZombieChaseNumber = 0;      //�]���r���ǐՂ��n�߂����ɗ����Ă����p�X�̔ԍ��B
	float m_speed;
};

