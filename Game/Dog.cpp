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

