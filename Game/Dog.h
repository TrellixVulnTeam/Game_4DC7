#pragma once
#include "AI.h"
/*NPCの犬型クラス(AIクラスから継承)。
他よりも移動速度が速い。
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
	CAnimation ai_NPCAnimation;				//アニメーション。
	CAnimationClip ai_NPCAnimationClips[animnum];	//アニメーションクリップ。
};

