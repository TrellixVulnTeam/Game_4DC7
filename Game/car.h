#pragma once
#include"AImove.h"
class car : public IGameObject
{
public:
	car();
	~car();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	void Move();
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	AImove* ran;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CVector3 m_position = CVector3::Zero;				//���݂̍��W
	CMatrix m_tekirot;									//�s��
	CVector3 m_forward;									//�L�����̑O���B
	float  move = 1.0f;									//�ړ����x�i�{���A1.0�����ʁj
	std::vector<CVector3> No;
	float speed = 1000;									//��ɑ���X�s�[�h
	std::vector<int>::iterator pasu;
	int saidaiNo = 0;
	int ima = 0;
	void Stop();
	int fa = 0;
	int frag = 0;
};

