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
			muteki_Flag = true;//���G�t���O�������āA���G������B
			pa = Return;//�p�^�[�������^�[���ɕς���B
		}
	
}


void Osu::Start_Walk_Animation()//�L�����N�^�[�������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Osu::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{

}

void Osu::Start_Run_Animation()//�L�����N�^�[������n�߂鎞�̃A�j���[�V�����̏����B
{

}

void Osu::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
{

}

void Osu::Resistance_Animation()//�L�����N�^�[����R���Ă��鎞�̃A�j���[�V�����̏����B
{

}

void Osu::Zombie_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă���̃A�j���[�V�����̏����B
{

}
