#pragma once
#include"AI.h"
#include"Game.h"
/*NPC�̒j���^�N���X(AI�N���X����p��)�B

*/
class Osu: public AI
{
public:
	Osu();
	~Osu();
	bool Start();
	void NPCResistance_NPC();  //NPC�]���r�ɒ�R���Ă���Ƃ��̏����B
	void NPCResistance_Player();  //�v���C���[�]���r�ɒ�R���Ă���Ƃ��̏����B

	void Start_Walk_Animation();//�����n�߂̏����B
	void Loop_Walk_Animation();//����������Ƃ��̏����B
	void Start_Run_Animation();//����n�߂̏����B
	void Loop_Run_Animation();//���葱����Ƃ��̏����B
	void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void Zombie_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B
};

