#include "stdafx.h"
#include "Dog.h"


Dog::Dog()
{
}


Dog::~Dog()
{
}

bool Dog::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//��������
	m_skinModel.Init(m_skinModelData);
	m_speed = 800.0f; //�m�[�}����Ԃ̂Ƃ��̈ړ����x�B
	AI::Start();

	return true;
}


void Dog::Start_Walk_Animation()//�L�����N�^�[�������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Dog::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{

}

void Dog::Start_Run_Animation()//�L�����N�^�[������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Dog::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
{

}

void Dog::Resistance_Animation()//�L�����N�^�[����R���Ă��鎞�̃A�j���[�V�����̏����B
{

}

void Dog::Zombie_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă���̃A�j���[�V�����̏����B
{

}

