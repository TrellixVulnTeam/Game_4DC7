#pragma once
#include"AImove.h"
#include"tkEngine/sound/tkSoundSource.h"
#include"carRender.h"
class car : public IGameObject
{
public:
	car();
	~car();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void gatcarRender(carRender& ka)
	{
		m_Render = &ka;
	}
	void CarSound();//Car�N���X�̃T�E���h�������֐��B
	void SoundklaxonPlay();//�N���N�V������炷�����B
	CVector3 Getposition()
	{
		return m_position;//���݂̍��W
	}
	CVector3 Getforward()
	{
		return m_forward;
	}
	void GetGeizi(Geizi* naka)
	{
		Gaizi = naka;
	}
private:

	//CMeshCollider m_meshCollider;	//���b�V���R���C�_�[�B
	//CRigidBody m_rigidBody;			//����
	//CPhysicsStaticObject m_physicsStaticObject;
	void Move();
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	AImove* ran;
	std::vector<Human*> HumanLest;
	Geizi* Gaizi= nullptr;
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
	bool frag = false;
	float siya = 100.0f;
	bool Humanfrag = false;
	carRender* m_Render;
	
	bool stopFlag = false;//���~�܂��Ă��邩�������t���O���̃t���O��true�̂Ƃ��́A�O�̃t���[���Ŋ��Ɏ~�܂��Ă���B
	bool loodflag = false;//���[�h�������������t���O�B
	bool klaxonFlag = false;//�N���N�V������炷���Ƃ������t���O�B
};

