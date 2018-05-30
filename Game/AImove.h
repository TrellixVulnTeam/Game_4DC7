#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	//(�s�������p�X�̔ԍ�,�����̈ʒu,�O����)
	int kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward, std::vector<CVector3> pasu);
	//(�s�������ꏊ,�����̈ʒu,�O����)
	int kyorikeisan(CVector3 mokuteki , CVector3 m_pos, CVector3 m_forward);
	//���������擾
	float Getmuve() const
	{
		return muve;
	}
	//�ړI�n�擾
	CVector3 Getmokuteki() const
	{
		return mokuteki;
	}
	//��]�s��擾
	CQuaternion Getkaku() const
	{
		return qBias1;
	}
	//��]���Ă��邩�ǂ����i0�F��]���Ă��Ȃ��A����ȊO�F��]�����j
	float Getkaiten() const
	{
		return kaku;
	}
	//��]���������p�x�i1�t���[��������j
	void Setkakudo(float kku) 
	{
		kakudo = kku;
	}
	//�ړI�n�܂ł̋���
	float Getlen() const
	{
		return len;
	}
	//�ړI�n�Ƃ̊p�x�̌덷�ւ�
	void Sethaba(float kakudo) 
	{
		haba = kakudo;
	}
private:
	CQuaternion qBias1 = CQuaternion::Identity; //��]�s��
	float muve = 1.0;								//����
	float len = 0.0;							//�ړI�n�܂ł̂̋���
	CVector3 bekutor=CVector3::Zero;			
	Game* game;									
	CVector3 mokuteki = CVector3::Zero;			//�ړI�n�̍��W
	float kaku = 0.0f;							//��]�p�x
	float haba = 3.0f;							//�ړI�n�̊p�x�̂���
	float kakudo = 3.0f;						//�Ȃ���p�x
};

