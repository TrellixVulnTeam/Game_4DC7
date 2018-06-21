#pragma once
#include"Geizi.h"
class BGM : public IGameObject
{
public:
	BGM();
	~BGM();
	bool Start();
	void Update();

	enum BGM_Scene //switch���Ɏg���B
	{
		Title,//�^�C�g��
		Sneak,//�X�j�[�N
		Assault//�A�T���g(�G���Ɛ키)
	};

	void Play_Title();//�^�C�g����BGM�𗬂��Ă���Ƃ��̏����B
	void Play_Sneak();//�X�j�[�N����BGM�𗬂��Ă���Ƃ��̏����B
	void Play_Assault();//�A�T���g(�G���Ɛ키)����BGM�𗬂��Ă���Ƃ��̏����B

private:
	Geizi * Gauge=nullptr;//nullptr�ŏ���������BGeizi�N���X�̃C���X�^���X����������Ȃ�����Gauge��nullptr�̂܂܁B
	enum BGM_Scene Scene; //switch���Ɏg���B
	prefab::CSoundSource*m_bdm_Title = nullptr;//�^�C�g���ŗ���BGM
	prefab::CSoundSource*m_bdm_Sneak = nullptr;//�s�������P����Ƃ��ɗ���BGM
	prefab::CSoundSource*m_bdm_Assault = nullptr;//�G���Ɛ키���ɗ���BGM
};

