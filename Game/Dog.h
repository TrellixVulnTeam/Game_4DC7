#pragma once
#include "AI.h"
/*NPC�̌��^�N���X(AI�N���X����p��)�B
�������ړ����x�������B
*/
class Dog:public AI
{
public:
	Dog();
	~Dog();
	bool Start();

	void Start_Walk_Animation();//�����n�߂̏����B
	void Loop_Walk_Animation();//����������Ƃ��̏����B
	void Start_Run_Animation();//����n�߂̏����B
	void Loop_Run_Animation();//���葱����Ƃ��̏����B
	void Resistance_Animation();//��R���Ă���Ƃ��̏����B
	void Zombie_Attack_Animation();//�]���r��NPC���U������Ƃ��̏����B

};

