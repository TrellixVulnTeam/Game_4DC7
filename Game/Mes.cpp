#include "stdafx.h"
#include "Mes.h"


Mes::Mes()
{
}


Mes::~Mes()
{
}


bool Mes::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�����^������
	m_skinModel.Init(m_skinModelData);
	AI::Start();

	return true;
}

void Mes::NPCNormal_Search()
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//����
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.1);
		pa = Escape;
	}
}


void Mes::Start_Walk_Animation()//�L�����N�^�[�������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Mes::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{

}

void Mes::Start_Run_Animation()//�L�����N�^�[������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Mes::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
{

}

void Mes::Resistance_Animation()//�L�����N�^�[����R���Ă��鎞�̃A�j���[�V�����̏����B
{

}

void Mes::Zombie_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă���̃A�j���[�V�����̏����B
{

}
