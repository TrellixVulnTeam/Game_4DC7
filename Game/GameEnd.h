#pragma once
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	int furgu = 0;
	int taim = 0;
	CSprite syuuryou;				//�X�v���C�g(�g)�B
	CShaderResourceView you;	//�e�N�X�`���B
	CVector3 m_position;
};

