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
	m_skinModelData.Load(L"modelData/unityChan.cmo");//女性型を書け
	m_skinModel.Init(m_skinModelData);
	AI::Start();

	return true;
}