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

};

