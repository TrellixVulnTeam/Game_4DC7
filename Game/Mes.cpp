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

	//tka�t�@�C���̓ǂݍ��݁B6��ށB
	//ai_NPCAnimationClips[0].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[0].SetLoopFlag(true);

	//ai_NPCAnimationClips[1].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[1].SetLoopFlag(true);

	//ai_NPCAnimationClips[2].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[2].SetLoopFlag(true);

	//ai_NPCAnimationClips[3].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[3].SetLoopFlag(true);

	//ai_NPCAnimationClips[4].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[4].SetLoopFlag(true);

	//ai_NPCAnimationClips[5].Load(L"Assets/animData/walk.tka");//���B��œ����B
	//ai_NPCAnimationClips[5].SetLoopFlag(true);

	AI::Start();

	return true;
}

void Mes::NPCNormal_Search()
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//����
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.3);//�����������̃y�i���e�B���ʏ��3�{�B�V���A
		pa = Escape;
	}
}
