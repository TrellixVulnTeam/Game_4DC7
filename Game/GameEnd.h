#pragma once
class Fade;
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
//	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
private:
	int furgu = 0;
	Fade* fade;
	int taim = 0;
	CSprite syuuryou;				//スプライト(枠)。
	CShaderResourceView you;	//テクスチャ。
	CVector3 m_position;
};

