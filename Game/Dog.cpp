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
	m_skinModelData.Load(L"modelData/SimpleCorgi.cmo");//��������
	m_skinModel.Init(m_skinModelData);
	m_speed = 1.5f; //�m�[�}����Ԃ̂Ƃ��̈ړ����x�B
	//tka�t�@�C���̓ǂݍ��݁B6��ށB
	//ai_NPCAnimationClips[waon].Load(L"animData/waon.tka");//���B��œ����B
	//ai_NPCAnimationClips[waon].SetLoopFlag(true);

	//ai_NPCAnimation.Init(
	//	m_skinModel,			//�A�j���[�V�����𗬂��X�L�����f���B
	//							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
	//	ai_NPCAnimationClips,	//�A�j���[�V�����N���b�v�̔z��B

	//	animnum					//�A�j���[�V�����N���b�v�̐��B
	//);
	AI::Start();

	return true;
}

