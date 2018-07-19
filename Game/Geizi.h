#pragma once
class tekihei;
class Player;
#define flash 0.4f
class Geizi : public IGameObject
{
public:
	Geizi();
	~Geizi();
	bool Start();
	void Update();
//	void Render(CRenderContext& rc);

	void PostRender(CRenderContext& rc);
	void satHP(float a)
	{
		HP -= a;
		HP_saiz = HP+ flash;
		Dame = UP; 
		time = 30;
	}
	void Satpoint(float a)
	{
		point += a;
	}
	float GatHP() 
	{
		return HP;
	}
	float GatFragu()
	{
		return furag;
	}
	void SatFragu()
	{
		furag++;
	}
	int GatHPfurag()
	{
		return HPfurag;
	}

	float Get_keifou_saiz()
	{
		return keifou_saiz;//���ꂪ0.95�ȏ�ɂȂ�ƓG�����o�Ă���B
	}
private:
	int time = 0;
	CSprite hy_sprite;				//�X�v���C�g(�Ə�)�B
	CShaderResourceView hy_texture;	//�e�N�X�`���B
	enum Damage
	{
		UP,
		Down,
		idor
	};
	Player* player;
	Damage Dame;
	CShaderResourceView HP_texture;	//�e�N�X�`���B
	CSprite hm_sprite;				//�X�v���C�gh(�g)�B
	tekihei* haus;
	float point = 0.0f;
	float HP = 0.95f;
	float  furag = 0.0f; //���ꕔ�����o����1�ɂȂ�B
	int HPfurag = 0;
	float keifou_saiz = 0.0f, HP_saiz = 1.0f;
};

