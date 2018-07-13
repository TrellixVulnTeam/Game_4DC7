#pragma once
#include"AI.h"
#include"Game.h"
/*NPC�̒j���^�N���X(AI�N���X����p��)�B

*/
class Osu : public AI
{
public:
	Osu();
	~Osu();
	bool Start();
	void AI_Animation();//AI�̃A�j���[�V�����̈ڍs����������B
	void Update();
	//void NPCResistance_NPC();  //NPC�]���r�ɒ�R���Ă���Ƃ��̏����B
	//void NPCResistance_Player();  //�v���C���[�]���r�ɒ�R���Ă���Ƃ��̏����B
	void death_Animation();
	void Idle_Animation();

	void Loop_Walk_Animation();//����������Ƃ��̏����B

	void Loop_Run_Animation();//���葱����Ƃ��̏����B

	void Zombie_Walk_Animation();//�]���r��NPC������������Ƃ��̏����B
								 //void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void NPC_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B
	void Zombie_Ziko_Animation();
private:

	enum animation {
		shiminidle,
		shiminwalk,
		shiminrun,
		shiminattack,
		shimindeath,
		shiminkai,
		shiminoki,
		Zonbiwalk,
		Zonbiattack,
		Zonbi_zico,
		animnum
	};
	bool okiagari = false;
	CAnimation ai_NPCAnimation;				//�A�j���[�V�����B
	CAnimationClip ai_NPCAnimationClips[animnum];	//�A�j���[�V�����N���b�v�B
	static CShaderResourceView* zondi ;
};

