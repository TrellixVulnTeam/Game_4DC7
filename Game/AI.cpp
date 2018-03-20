#include "stdafx.h"
#include "AI.h"
#include "Player.h"

AI NPC;
//�����m�����p����NPC�̃n���h���Ƃ��đ�p����B����͌�ɒ����Ă����悤�ɁB
//NPC��NPC�]���r�̗�������������B
AI::AI()
{
	pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_movespeed = { 0.0f, 0.0f, -0.1f }; //�m�[�}����Ԃ̂Ƃ��̈ړ����x�B
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
	if () {//����NPC����������
		if (m->Zonbe == 0) {//���ꂪ�]���r�ł͂Ȃ�������
			pa = Zombie_Chase; //�p�^�[����ǐՂɕς���B
		}
	}
}

void AI::NPCZombie_Chase()
{
	if () {//����NPC������������
		//���̈ʒu�ɖ߂��B

		if () {//���̈ʒu�ɖ߂�����
			pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
		}
	}
	if () {//NPC�ɒǂ�������
		//�U������B

		if (m->DamageFlag == true) {//������������
			HitFlag = true; //�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
		}
		
	}
	if (HitFlag == true) {//�U���𓖂Ă�����
		if () {//���̈ʒu�ɖ߂��Ă���
			pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
			HitFlag == false;
		}
	}
}

void AI::NPCZombie_Attack()//vs���ꕔ��
{
	if () {//�����ɋ߂Â�����
		HitFlag = true; //�����ɍU������B
	}
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

void AI::NPCRuet()
{

}
void AI::Update()
{
	//pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	
	if () {//���ꕔ����������
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
		NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//����NPC�����������̏����������B
		NPCZombie_Chase();
		break;
	case Zombie_Attack:
		NPCZombie_Attack();
		break;
	}
	Turn();
	Muve(m_movespeed);//���[���X�s�[�h�����Ɠ���
	m_movespeed.x += 0.001;
	 //qRot��]�ƃL�����̉�]����Z���č�������B
	qBias.Multiply(m_rotation, qBias);
	m_skinModel.Update(m_position, qBias, { 0.5f,0.5f,0.5f });
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
