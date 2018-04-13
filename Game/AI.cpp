#include "stdafx.h"
#include "AI.h"
#include "Player.h"
#define REACH 5.0  //�]���r�̍U���͈́B���̋����܂ŋ߂Â�����U������B
AI NPC;
//�����m�����p����NPC�̃n���h���Ƃ��āAj����ꕔ���̃n���h���Ƃ��đ�p����B����͌�ɒ����Ă����悤�ɁB
//NPC��NPC�]���r�̗�������������B
AI::AI()
{
	pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_speed = 5.0f; //�m�[�}����Ԃ̂Ƃ��̈ړ����x�B
}


AI::~AI()
{
}
bool AI::Start()
{
	m_position -= {30.0f,10.0f, 0.0f};
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();

	return true;
}

void AI::NPCNormal()
{
	Player* pl=FindGO<Player>("Player");
	CVector3 v = m_position - pl->m_position;
	float len = v.Length();//����
	if (len<50.0f) {//�v���C���[����������
		v.Normalize();//���K�����Č����x�N�g���ɂ���B
		//�v���C���[���瓦����B
	}
	if (len < REACH) {//�U�����󂯂�͈͂܂ŋ߂Â�����m���Ƀ_���[�W���󂯂�̂�
		DamageFlag = true;//�_���[�W�t���O��true�ɂ���B
	}
	if (DamageFlag == true) {//�v���C���[����̍U�����󂯂���
		static int i = 0; //30�t���[�����J�E���g����B
		if (i >= 30) {
			pa = Damage;//30�t���[���o�߂�����p�^�[�����_���[�W�ɕς���B
		}
		else {
			i++; //1�t���[���o�߂��J�E���g����B
		}
		
	}
}

void AI::NPCDamage()
{
	pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
	m_movespeed = { 0.5f, 0.0f, 0.0f }; //�]���r�m�[�}����Ԃ̂Ƃ��̈ړ����x�ɕς���B
	Zonbe = 1;
}

void AI::NPCZombie_Normal()
{
	//���͈͂�p�j����B

	//���͈͓��ɑ���NPC����������
	//float len;
	//if (len) {
	//	if (m->Zonbe == 0) {//���ꂪ�]���r�ł͂Ȃ�������
	//		//���E�����A�p�x���Ƃ��Ē��ׂ�B

	//		if () {//�p�x��(���E��)��������
	//			ZombieChaseNumber = MyNumber; //�����������Ă����p�X�̔ԍ����L������B
	//			pa = Zombie_Chase; //�p�^�[����ǐՂɕς���B
	//		}
	//	}
	//}
}

void AI::NPCZombie_Chase()
{
	//float len = GetKyori(m_position, m->m_position);
	//if (len>80.0f||HitFlag == true) {//����NPC����������(������80�ȏ゠����)�A���邢�͍U����^������
	//	//���̈ʒu�ɖ߂�B

	//	if (ZombieChaseNumber = MyNumber) {//���̈ʒu�̔ԍ��ɖ߂�����
	//		pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
	//		HitFlag == false;
	//	}
	//}
	//if (len<REACH) {//NPC�ɒǂ�������
	//	//�U������(�m���ɓ�����d�l)�B

	//		HitFlag = true; //�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
	//	}
	
}

void AI::NPCZombie_Attack()//vs���ꕔ��
{
	//if (BattleFlag == false) {//�����Ɛ���Ă��炸�A�t���[�ȏ�ԂȂ�
	//	//��ԋ߂������Ɉړ�����B
	//	float len = GetKyori(m_position,j->m_position );
	//	if (len<REACH) {//�����ɋ߂Â�����
	//		BattleFlag == true;//�퓬���J�n����B
	//	}
	//}

	if (BattleFlag == true) {//�퓬��ԂȂ�
     	 //�����ɍU������B
	}

	//if () {//������|������
	//	//�u�퓬���I�������v�Ƃ����t���O�����Ă�B
	//	BattleFlag = false;
	//}
	
}

float AI::GetKyori(CVector3 a, CVector3 b) //2�̃I�u�W�F�N�g�̍��W���󂯎��B
{
	CVector3 v = a - b;
	float len = v.Length();//����
	return len;  //2�̃I�u�W�F�N�g�̋�����Ԃ��B
}

void AI::Turn()//����
{
	if (fabsf(m_movespeed.x) < 0.001f
		&& fabsf(m_movespeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void AI::NPCRuet()//NPC���[�g
{

}

float AI::VectorAngleDeg(CVector3 c)
{
	float a = 0.0f;
	return a;
}
void AI::Update()
{
	//pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	
	if (ForceFlag==true) {//���ꕔ�����o��������
		pa = Zombie_Attack; //�p�^�[�����]���r�A�^�b�N�ɐ؂�ւ���B
	}

	CQuaternion qBias;
	qBias = rotation(270);

	switch (pa) {
	case Normal:
		//NPC�̓����������B
		NPCNormal();
		break;
	case Damage:
		NPCDamage();
		break;
	case Zombie_Normal:
		//NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//����NPC�����������̏����������B
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	}

	
	//Muve(m_movespeed);//���[���X�s�[�h�����Ɠ���
	//m_movespeed.x += 0.001;
	// //qRot��]�ƃL�����̉�]����Z���č�������B
	//qBias.Multiply(m_rotation, qBias);

	//NPC�̑O�������v�Z

	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	m_rite.x = mRot.m[0][0];
	m_rite.y = mRot.m[0][1];
	m_rite.z = mRot.m[0][2];
	m_rite.Normalize();
	m_position += m_forward *  m_speed;
	m_position += m_rite * 10 * m_speed;
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
