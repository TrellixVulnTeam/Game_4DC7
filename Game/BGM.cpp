#include "stdafx.h"
#include "BGM.h"


BGM::BGM()
{
}


BGM::~BGM()
{
}

bool BGM::Start()
{
	/*m_bdm_Title = NewGO<prefab::CSoundSource>(0);
	m_bdm_Title->Init("sound/horror_zone1.wav", false);*/
	m_bdm_Sneak = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak->Init("sound/horror_zone1.wav");
	m_bdm_Sneak->Play(true);
	Scene = Title;
	/*m_bdm_Assault = NewGO<prefab::CSoundSource>(0);
	m_bdm_Assault->Init("sound/horror_zone1.wav", false);*/

	return true;
}

void BGM::Play_Title() //�^�C�g����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	//m_bdm_Title->Play(true);//	�^�C�g��������BGM�𗬂��B
	Gauge = FindGO<Geizi>("Geizi");//�C���X�^���X����������Ă���������B
	if (Gauge != nullptr) {
		Scene = Sneak;//�Q�[�W���o��(���^�C�g����ʂ��玟���ֈڍs����)�̂ŗ���BGM���X�j�[�N�ɕς���B
		//m_bdm_Title->Stop();//���֐؂�ւ��̂ō�����Ă���BGM���~�߂�B
	}
}

void BGM::Play_Sneak()//�X�j�[�N����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	m_bdm_Sneak->Play(true);//�X�j�[�N����BGM�𗬂��B
	if (Gauge->Get_keifou_saiz()>=0.95) {//�Q�[�W���G�����o�Ă��郉�C���𒴂�����
		Scene = Assault;//�Q�[�W�����C���𒴂���(���G���Ƃ̃o�g���Ɉڍs����)�̂ŗ���BGM���A�T���g�ɕς���B
		m_bdm_Sneak->Stop();//���֐؂�ւ��̂ō�����Ă���BGM���~�߂�B
	}
}

void BGM::Play_Assault()//�A�T���g(�G���Ɛ키)����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	//m_bdm_Assault->Play(true);//�G���Ɛ키����BGM�𗬂��B
}

void BGM::Update()
{

	m_bdm_Sneak->Play(true);

	switch (Scene)//���A�ǂ�BGM�𗬂����𔻒f����B
	{
	case Title://�^�C�g��
		Play_Title();
		break;
	case Sneak://�X�j�[�N
		Play_Sneak();
		break;
	case Assault://�A�T���g(�G���Ɛ키)
		Play_Assault();
		break;
		Play_Title();
	default:
		break;
	}
}
