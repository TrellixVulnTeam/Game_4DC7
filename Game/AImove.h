#pragma once
class Level;
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	Level* Level;
	CVector3 iin;
	float in;
	int Size = 0;
	CVector3 bekutor = CVector3::Zero;
	float K = 0.0f;
	int Fream = 0;
	int Flag = 0;
	int No = 0;
	int hugo = 1;
};

