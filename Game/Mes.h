#pragma once
#include"AI.h"
/*NPC�̏����^�N���X(AI�N���X����p��)�B

*/
class Mes: public AI
{
public:
	Mes();
	~Mes();
	bool Start();

	void NPCNormal_Search();//�����^�̌x�������B

	void Start_Walk_Animation();//�����n�߂̏����B
	void Loop_Walk_Animation();//����������Ƃ��̏����B
	void Start_Run_Animation();//����n�߂̏����B
	void Loop_Run_Animation();//���葱����Ƃ��̏����B
	void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void Zombie_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B
};

