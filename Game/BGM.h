#pragma once
#include"Geizi.h"
#include"AI_manager.h"
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
		Sneak_First,//�X�j�[�N�̍ŏ��̈�񂾂��������B
		Sneak_Fewer_people,//�]���r��NPC�̐l�������Ȃ��Ƃ�(NPC�����̓񕪂̈ꖢ���̐l��)�̏����B
		Sneak_Many_persons,//�]���r��NPC�̐l���������Ƃ�(NPC�����̓񕪂̈�ȏ�̐l��)�̏���(�񕪂̈ꂿ�傤�ǂ��܂�)�B
		Assault//�A�T���g(�G���Ɛ키)
	};

	//NPC���]���r�������������J�E���g����B
	void SetZombie()
	{
		ZombieNPC_Number+=1.0f;
	}
	void Play_Title();//�^�C�g����BGM�𗬂��Ă���Ƃ��̏����B
	void Play_Sneak_First();//�X�j�[�N����BGM�𗬂��Ă���Ƃ��̏����B
	void Play_Sneak_Fewer_people();
	void Play_Sneak_Many_persons();
	void Play_Assault();//�A�T���g(�G���Ɛ키)����BGM�𗬂��Ă���Ƃ��̏����B

private:
	AI_manager * ai_manager = nullptr;//�o�^���ꂽNPC�̍��v�l���𒲂ׂ邽�߂Ɏg�p����B
	Geizi * Gauge=nullptr;//nullptr�ŏ���������BGeizi�N���X�̃C���X�^���X����������Ȃ�����Gauge��nullptr�̂܂܁B
	enum BGM_Scene Scene; //switch���Ɏg���B
	prefab::CSoundSource*m_bdm_Title = nullptr;//�^�C�g���ŗ���BGM
	prefab::CSoundSource*m_bdm_Sneak1 = nullptr;//�s�������P����Ƃ��ɗ���BGM1
	prefab::CSoundSource*m_bdm_Sneak2 = nullptr;	 //�s�������P����Ƃ��ɗ���BGM2
	prefab::CSoundSource*m_bdm_Assault = nullptr;//�G���Ɛ키���ɗ���BGM
	float ZombieNPC_Number = 0.0f;//�]���r��NPC�̐l�����i�[����B
	float NPC_Goukei = 0.0f;//NPC�̍��v�l�����L�^����B
};

