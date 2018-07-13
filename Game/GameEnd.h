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
	CSprite syuuryou;				//�X�v���C�g(�g)�B
	CShaderResourceView you;	//�e�N�X�`���B
	CVector3 m_position;
	CFont m_font;
	CVector2 font_pos = { 0.0f,0.0f };
	CVector2 fomt_pivot = { 0.0f,0.0f };	
	std::wstring inputwstr = L"ABCDEFG";
};

