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
private:
	enum animation {
		waon,
		animnum
	};
	CAnimation ai_NPCAnimation;				//�A�j���[�V�����B
	CAnimationClip ai_NPCAnimationClips[animnum];	//�A�j���[�V�����N���b�v�B
};

