#pragma once
#include"Fade.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	Fade* fase;
	CSprite n_sprite;				//�X�v���C�g�i���g�j�B
	CShaderResourceView n_texture;	//�e�N�X�`���B*/
	CQuaternion Quaternion = CQuaternion::Identity; //��]
	CSprite y_sprite;				//�X�v���C�g�i���j�B
	CShaderResourceView y_texture;	//�e�N�X�`���B*/
	CVector3 n_position = CVector3::Zero;
private:
	int Triggeer = 0;
	int hyouji = 11;
	int taim = 11;
	int Target = 3;
};

