#pragma once
#define KOSUU 2

#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	void kyorikeisan(int bangou);
	//CSkinModel m_skinModel;					//�X�L�����f���B
	//CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CVector3 iin;
	float in;
	int Size;
	int j = 0;
	CVector3 bekutor=CVector3::Zero;
	Game* game;
	CVector3 K;
	int Fream;
	int Flag;
	int No[5] = { 0,0,0,0,0 };
	int hugo = 1;
	int g = 0;
};

