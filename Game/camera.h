#pragma once

#include "Player.h"
class camera:public IGameObject
{
public:
	camera();
	~camera();
	bool Start();
	void Update();

	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Player* m_player;	//�v���C���[�B
	CVector3 target = CVector3::Zero;
	CVector3 Ppos = CVector3::Zero;
	float d = 0.0f;
};

