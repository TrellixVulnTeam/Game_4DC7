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