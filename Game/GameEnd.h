#pragma once
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	int furgu = 0,taim=0;

	CSprite GameOuba;				//�X�v���C�g(�g)�B
	CShaderResourceView Ouba;	//�e�N�X�`���B

	CSprite GameKuria;				//�X�v���C�g(�g)�B
	CShaderResourceView kuria;	//�e�N�X�`���B
	CVector3 m_position;

};

