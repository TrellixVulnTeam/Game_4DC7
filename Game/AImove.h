#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start() override;
	void kyorikeisan(int bangou);
	//CSkinModel m_skinModel;					//�X�L�����f���B
	//CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CVector3 bekutor=CVector3::Zero;
	Game* game;
	CVector3 K;
	int g = 0;
};

