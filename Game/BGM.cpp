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
	m_bdm_Sneak1 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak1->Init("sound/horror_zone1.wav");
	m_bdm_Sneak2 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak2->Init("sound/n80.wav");
	Scene = Title;
	ai_manager = FindGO<AI_manager>("AI_manager");//AI_manager�̃C���X�^���X���擾�B
	/*m_bdm_Assault = NewGO<prefab::CSoundSource>(0);
	m_bdm_Assault->Init("sound/horror_zone1.wav", false);*/
	NPC_Goukei = ai_manager->Get_NPC_Number();//��������NPC�̍��v�l�������B
	return true;
}

void BGM::Play_Title() //�^�C�g����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	//m_bdm_Title->Play(true);//	�^�C�g��������BGM�𗬂��B
	Gauge = FindGO<Geizi>("Geizi");//�C���X�^���X����������Ă���������B
	if (Gauge != nullptr) {
		Scene = Sneak_First;//�Q�[�W���o��(���^�C�g����ʂ��玟���ֈڍs����)�̂ŗ���BGM���X�j�[�N�t�@�[�X�g�ɕς���B
		//m_bdm_Title->Stop();//���֐؂�ւ��̂ō�����Ă���BGM���~�߂�B
	}
}

void BGM::Play_Sneak_First()//�X�j�[�N���̍ŏ��ɏ��������B
{
	Scene = Sneak_Fewer_people;//�������I������̂Ŏ��̏�Ԃֈڍs����B
}
void BGM::Play_Sneak_Fewer_people()//�X�j�[�N��(�]���r��NPC��1/2�����̎�)��BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	m_bdm_Sneak1->Play(true);//�X�j�[�N����BGM�𗬂��B
	if (ZombieNPC_Number>=(NPC_Goukei/2))//�]���r��NPC��NPC�̍��v�l���̔����ȏ���߂���
	{
		Scene = Sneak_Many_persons;//�]���r��NPC�������ȏ���߂��ꍇ�̏����ɕς���B
	}
	if (Gauge->Get_keifou_saiz()>=0.95) //�Q�[�W���G�����o�Ă��郉�C���𒴂�����
	{
		Scene = Assault;//�Q�[�W�����C���𒴂���(���G���Ƃ̃o�g���Ɉڍs����)�̂ŗ���BGM���A�T���g�ɕς���B
		m_bdm_Sneak1->Stop();//���֐؂�ւ��̂ō�����Ă���BGM���~�߂�B
	}
}

void BGM::Play_Sneak_Many_persons()//�X�j�[�N��(�]���r��NPC��1/2�ȏ�̎�)��BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	m_bdm_Sneak1->Play(true);//�X�j�[�N����BGM1�𗬂��B
	m_bdm_Sneak2->Play(true);//�X�j�[�N����BGM2�𗬂��B
	if (Gauge->Get_keifou_saiz() >= 0.95) //�Q�[�W���G�����o�Ă��郉�C���𒴂�����
	{
		Scene = Assault;//�Q�[�W�����C���𒴂���(���G���Ƃ̃o�g���Ɉڍs����)�̂ŗ���BGM���A�T���g�ɕς���B
		m_bdm_Sneak1->Stop();//���֐؂�ւ��̂ō�����Ă���BGM1���~�߂�B
		m_bdm_Sneak2->Stop();//���֐؂�ւ��̂ō�����Ă���BGM2���~�߂�B
	}
}

void BGM::Play_Assault()//�A�T���g(�G���Ɛ키)����BGM�𗬂��Ă���Ƃ��ɓ����֐��B
{
	//m_bdm_Assault->Play(true);//�G���Ɛ키����BGM�𗬂��B
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
	case Assault://�A�T���g(�G���Ɛ키)
		Play_Assault();
		break;
		Play_Title();
	default:
		break;
	}
}
