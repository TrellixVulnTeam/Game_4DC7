#pragma once
class tekihei;
class Geizi : public IGameObject
{
public:
	Geizi();
	~Geizi();
	bool Start();
	void Update();

	void Render(CRenderContext& rc);
	CSprite m_sprite;				//�X�v���C�g(�g)�B
	CShaderResourceView m_texture;	//�e�N�X�`���B
	CVector3 m_position = CVector3::Zero;

	CSprite hm_sprite;				//�X�v���C�gh(�g)�B

	CVector3 hm_position = CVector3::Zero;

	CSprite n_sprite;				//�X�v���C�g�i���g�j�B
	CShaderResourceView n_texture;	//�e�N�X�`���B*/
	CVector3 n_position = CVector3::Zero;

	CSprite hn_sprite;				//�X�v���C�gh�i���g�j�B
	CVector3 hn_position = CVector3::Zero;
	tekihei* haus;

	CSprite hy_sprite;				//�X�v���C�g(�g)�B
	CShaderResourceView hy_texture;	//�e�N�X�`���B
	float point = 0.0f;
	float HP = 0.0;
	int  furag = 0;
	int HPfurag = 0;
};

