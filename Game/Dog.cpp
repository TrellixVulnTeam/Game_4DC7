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

