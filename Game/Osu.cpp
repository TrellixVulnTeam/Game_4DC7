#include "stdafx.h"
#include"Game.h"
#include "AIMove.h"
#include "Osu.h"



Osu::Osu()
{
}


Osu::~Osu()
{
}

bool Osu::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�j���^������
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

//NPC�]���r�ɒ�R���Ă���Ƃ��̏����BAI�N���X�̓������\�b�h(�����o�֐�)���I�[�o�[���C�h����B
void Osu::NPCResistance_NPC() 
{
	pa = Damage;
}

//�v���C���[�]���r�ɒ�R���Ă���Ƃ��̏����BAI�N���X�̓������\�b�h(�����o�֐�)���I�[�o�[���C�h����B
void Osu::NPCResistance_Player()
{
	static int count = 30;//�����l�B
	static int i = 0;//���t���[���J�E���g����B

	i++;//���t���[�����s�B
	
	//Resistance_Animation();
		
		if (i > 7) {//8�t���[���ȏ�ō쓮����B
			count++;
			i = 0;
		}

		if (Pad(0).IsTrigger(enButtonB)) { //B�{�^���������ꂽ��
			count--;
		}

		if (count <= 0) {//count��0�ȉ��ɂȂ�����
			count = 30;//�l���������B
			i = 0;//�t���[���J�E���g�̒l���������B
			pa = Damage;//�p�^�[�����_���[�W�ɕς���B
		}

		if (count >= 60) {//count��60�ȏ�ɂȂ�����
			count = 30;//�l���������B
			i = 0;//�t���[���J�E���g�̒l���������B
		//	muteki_Flag = true;//���G�t���O�������āA���G������B
			pa = Return;//�p�^�[�������^�[���ɕς���B
		}
	
}


