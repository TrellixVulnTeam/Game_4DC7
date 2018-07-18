#include "stdafx.h"
#include "BGM.h"


BGM::BGM()
{
}


BGM::~BGM()
{
	m_bdm_Title->Stop();
	m_bdm_Sneak1->Stop();
	m_bdm_Sneak2->Stop();
	ZombieNPC_Number = 0;
}

bool BGM::Start()
{
	m_bdm_Title = NewGO<prefab::CSoundSource>(0);
	m_bdm_Title->Init("sound/Zombie_Title_Theme.wav");
	m_bdm_Title->SetVolume(bgm_volume);
	m_bdm_Sneak1 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak1->Init("sound/horror_zone1.wav");
	m_bdm_Sneak1->SetVolume(bgm_volume);
	m_bdm_Sneak2 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak2->Init("sound/n80.wav");
	m_bdm_Sneak2->SetVolume(0.3f);
	Scene = Title;
	ai_manager = FindGO<AI_manager>("AI_manager");//AI_manager�̃C���X�^���X���擾�B
	NPC_Goukei = ai_manager->Get_NPC_Number();//��������NPC�̍��v�l�������B
	
	return true;
}

void BGM::Play_Title() //�^�C�g����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	if (Startbutton_push_Flag == false ) {
		m_bdm_Title->Play(true);//�^�C�g������BGM�𗬂��B
	}
	else {//�X�^�[�g�{�^���������ꂽ��
		 //BGM�̃t�F�[�h�A�E�g
		if (bgm_volume > 0.01f) {
			bgm_volume = bgm_volume - 0.01f;
			m_bdm_Title->SetVolume(bgm_volume);
		}
		else {
			m_bdm_Title->Stop();
		}
	}
	
	Gauge = FindGO<Geizi>("Geizi");//�C���X�^���X����������Ă���������B
	if (Gauge != nullptr) {
		Scene = Sneak_First;//�Q�[�W���o��(���^�C�g����ʂ��玟���ֈڍs����)�̂ŗ���BGM���X�j�[�N�t�@�[�X�g�ɕς���B
		Startbutton_push_Flag = false;
		bgm_volume = 1.0f;
		//m_bdm_Title->Stop();//���֐؂�ւ��̂ō�����Ă���BGM���~�߂�B
	}
}

void BGM::Play_Sneak_First()//�X�j�[�N���̍ŏ��ɏ��������B
{
	game = FindGO<Game>("Game");//�^�C���v���Ɏg���B
	Scene = Sneak_Fewer_people;//�������I������̂Ŏ��̏�Ԃֈڍs����B
}
void BGM::Play_Sneak_Fewer_people()//�X�j�[�N��(�]���r��NPC��1/2�����̎�)��BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	m_bdm_Sneak1->Play(true);//�X�j�[�N����BGM�𗬂��B
	
	if (game->Gettimer_m()<=0)//�]���r��NPC��NPC�̍��v�l���̔����ȏ���߂���
	{
		//BGM�̃t�F�[�h�A�E�g
		if (bgm_volume > 0.01f) {
			bgm_volume = bgm_volume - 0.01f;
			m_bdm_Sneak1->SetVolume(bgm_volume);
		}
		else {
			m_bdm_Sneak1->Stop();
			Scene = Sneak_Many_persons;//�]���r��NPC�������ȏ���߂��ꍇ�̏����ɕς���B
			bgm_volume = 1.0f;
		}
	}
}

void BGM::Play_Sneak_Many_persons()//�X�j�[�N��(�]���r��NPC��1/2�ȏ�̎�)��BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	m_bdm_Sneak2->Play(true);//�X�j�[�N����BGM2�𗬂��B
	m_bdm_Sneak2->SetVolume(0.5f);
}

void BGM::Update()
{

	switch (Scene)//���A�ǂ�BGM�𗬂����𔻒f����B
	{
	case Title://�^�C�g��
		Play_Title();
		break;
	case Sneak_First://�X�j�[�N�̍ŏ��̏����B
		Play_Sneak_First();
		break;
	case Sneak_Fewer_people://�X�j�[�N���]���r��1/2�����B
		Play_Sneak_Fewer_people();
		break;
	case Sneak_Many_persons://�X�j�[�N���]���r��1/2�ȏ�B
		Play_Sneak_Many_persons();
		break;
	default:
		break;
	}
}

void BGM::Set_Startbutton_push()
{
	Startbutton_push_SE();//���ʉ��B
	Startbutton_push_Flag = true;
}

void BGM::Startbutton_push_SE()
{
	prefab::CSoundSource*m_SE_Startbutton=nullptr;
	m_SE_Startbutton = NewGO<prefab::CSoundSource>(0);
	m_SE_Startbutton->Init("sound/StartbuttonSE.wav", false);
	m_SE_Startbutton->SetVolume(0.7f);
	m_SE_Startbutton->Play(false);//��񂾂��Đ�����Ĕj�������B
}