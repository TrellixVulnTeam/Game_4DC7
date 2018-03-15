#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void StartFadeIn()
	{
		m_Fade= FadeIn;
	}
	void StartFadeOut()
	{
		m_Fade = FadeOut;
	}

	bool IsFade() const
	{
		return m_Fade != Idle;
	}
	float GetCurrentAlpha() const
	{
		return  toumeiodo;
	}

private:
	enum EnState {
		FadeIn,		//!<�t�F�[�h�C�����B
		FadeOut,		//!<�t�F�[�h�A�E�g���B
		Idle,		//!<�A�C�h�����B
	};
	CShaderResourceView m_texture;
	CSprite m_sprite;
	EnState m_Fade = Idle;
	float toumeiodo = 1.0f;//�����x
};

