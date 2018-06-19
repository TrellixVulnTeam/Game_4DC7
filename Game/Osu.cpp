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
	m_skinModelData.Load(L"modelData/liam.cmo");//�j���^������
	m_skinModel.Init(m_skinModelData);
	ai_NPCAnimationClips[shiminidle].Load(L"animData/shiminidle.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminidle].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminwalk].Load(L"animData/shiminwalk.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminrun].Load(L"animData/shiminrun.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminrun].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminattack].Load(L"animData/playerattack.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiwalk].Load(L"animData/playerwalk.tka");//���B��œ����B
	ai_NPCAnimationClips[Zonbiwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiattack].Load(L"animData/playerattack.tka");//���B��œ����B
	ai_NPCAnimationClips[Zonbiattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbi_zico].Load(L"animData/liam_ziko.tka");//���B��œ����B
	ai_NPCAnimationClips[Zonbi_zico].SetLoopFlag(false);
	
	//�A�j���[�V�����̏������B
	ai_NPCAnimation.Init(
		m_skinModel,			//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		ai_NPCAnimationClips,	//�A�j���[�V�����N���b�v�̔z��B

		animnum					//�A�j���[�V�����N���b�v�̐��B
	);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
	material->Setm_zonbi(zondi.GetBody());
	});
	AI::Start();

	return true;
}

//NPC�]���r�ɒ�R���Ă���Ƃ��̏����BAI�N���X�̓������\�b�h(�����o�֐�)���I�[�o�[���C�h����B
//void Osu::NPCResistance_NPC() 
//{
//	pa = Damage;
//}

//�v���C���[�]���r�ɒ�R���Ă���Ƃ��̏����BAI�N���X�̓������\�b�h(�����o�֐�)���I�[�o�[���C�h����B
//void Osu::NPCResistance_Player()
//{
//	static int count = 30;//�����l�B
//	static int i = 0;//���t���[���J�E���g����B
//
//	i++;//���t���[�����s�B
//	
//	//Resistance_Animation();
//		
//		if (i > 7) {//8�t���[���ȏ�ō쓮����B
//			count++;
//			i = 0;
//		}
//
//		if (Pad(0).IsTrigger(enButtonB)) { //B�{�^���������ꂽ��
//			count--;
//		}
//
//		if (count <= 0) {//count��0�ȉ��ɂȂ�����
//			count = 30;//�l���������B
//			i = 0;//�t���[���J�E���g�̒l���������B
//			pa = Damage;//�p�^�[�����_���[�W�ɕς���B
//		}
//
//		if (count >= 60) {//count��60�ȏ�ɂȂ�����
//			count = 30;//�l���������B
//			i = 0;//�t���[���J�E���g�̒l���������B
//		//	muteki_Flag = true;//���G�t���O�������āA���G������B
//			pa = Return;//�p�^�[�������^�[���ɕς���B
//		}
//	
//}

void Osu::Update()
{

	AI::Update();
	AI_Animation();
}
void Osu::AI_Animation()//AI�̃A�j���[�V��������
{
	/*if (m_speed <= 1.0) {
	Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
	Loop_Run_Animation();
	}*/
	if (GetZonbi() == false) {
		if (HitFlag == true)
		{
			NPC_Attack_Animation();

		}
		else if (m_speed < 0.5f) {
			Idle_Animation();
		}
		else if (m_speed <= 1.0) {
			Loop_Walk_Animation();
		}
		else if (m_speed > 1.0) {
			Loop_Run_Animation();
		}

	}
	else {
		if (pa == flyNPC) {
			Zombie_Ziko_Animation();
		}
		else if (HitFlag == true) {
			NPC_Attack_Animation();
		}
		else if (m_speed >= 0.5f) {
			Zombie_Walk_Animation();
		}
	}
}
void Osu::Idle_Animation() //�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(shiminidle, 0.7);
}


void Osu::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(shiminwalk, 0.7);
}
void Osu::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(shiminrun, 0.7);
}

void Osu::NPC_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă��鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(shiminattack, 0.2);
}


void Osu::Zombie_Walk_Animation()
{
	ai_NPCAnimation.Play(Zonbiwalk, 0.7);
}
void Osu::Zombie_Ziko_Animation()
{
	ai_NPCAnimation.Play(Zonbi_zico, 0.7);
	if (!ai_NPCAnimation.IsPlaying()) {
		pa = Zombie_Normal;
	}
}
