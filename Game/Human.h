#pragma once
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	CVector3 m_position = CVector3::Zero;		//���W�B
	CVector3 m_movespeed = CVector3::Zero;		//�ړ����x�B
	CQuaternion qBias_x;
	CQuaternion qBias_z;
	CQuaternion rotation(float a) {
		qBias_x.SetRotationDeg(CVector3::AxisY, 0.0f);
		qBias_z.SetRotationDeg(CVector3::AxisY, a);
		qBias_x.Multiply(qBias_z);
		return qBias_x;
	}
	void Muve(CVector3 X) {
		m_position += X;
		//return m_position;
	}
	CVector3 kakudai;
<<<<<<< HEAD
	int Zonbe = 0;//�]���r�������Ƃ���+1����B
=======
	int Zonbe = 0;

	


>>>>>>> a419c3131ef65b0e11cb7f5c01d1efbdc63ec9c8
};

