#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start();
	//(�s�������p�X�̔ԍ�,�����̈ʒu,�O����)
	int kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward);
	//���������擾
	int Gatmuve() const
	{
		return muve;
	}
	//�ړI�n�擾
	CVector3 Gatmokuteki() const
	{
		return mokuteki;
	}
	//��]�p�x�擾
	CQuaternion Gatkaku() const
	{
		return qBias1;
	}
	float Gatlen() const
	{
		return len;
	}
private:
	CQuaternion qBias1= CQuaternion::Identity;
	int muve = 0;
	float len = 0.0;
	CVector3 bekutor=CVector3::Zero;
	Game* game;
	CVector3 mokuteki = CVector3::Zero;
};

