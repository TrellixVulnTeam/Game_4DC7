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

};

