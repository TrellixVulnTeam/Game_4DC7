#pragma once
#include"Fade.h"
#include"Player.h"
#include"BGM.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	float siya();
	void PostRender(CRenderContext& rc) override;
	void kaiten();
	void Transparency();
	void Update();
private:
	enum fade
	{
		Up,
		Down,
		Idor
	};
	enum kaiten {
		steat,
		push,
		suii,
		tyoku
	};
	enum kakudo
	{
		kaiton,
		idor
	};
	enum kaiten furag;
	enum kakudo kakudu;
	enum fade FADE= Up;
	Fade * fase;
	BGM* bgm;
		CSprite n_sprite;				//�X�v���C�g�i���g�j�B
		CShaderResourceView n_texture;	//�e�N�X�`���B*/
		CQuaternion Quaternion = CQuaternion::Identity; //��]
		CSprite Abotan_sprite;				//�X�v���C�g�iA�{�^���j�B
		CShaderResourceView Abotan_texture;	//�e�N�X�`���iA�{�^���j�B
		CSprite Pusu_sprite;				//�X�v���C�g�iPress�j�B
		CShaderResourceView Pusu_texture;	//�e�N�X�`���iPress�j
		CSprite start_sprite;				//�X�v���C�g�istart�j�B
		CShaderResourceView start_texture;	//�e�N�X�`���istart�j

	CVector3 n_position = { 0.0f ,180.0f,0.0f };
	Player* player = nullptr;
	CVector3 target = CVector3::Zero;
	float toumei = 1.0f;
	CVector3 nowkmtarget = CVector3::Zero;
	CVector3 Ppos = CVector3::Zero;
	float d = 0.0f;
	CVector3 player_Foeward= CVector3::Zero;
	CVector3 UP = CVector3::AxisY;
	CQuaternion Crot = CQuaternion::Identity;
	CVector3 BasisVector = CVector3::Zero;
	CVector3 nowkmVector = CVector3::Zero;
	int Triggeer = 0;
	float kakudo = 10.0f;
	float speed = 900.0f;
	int kaunto = 0;
	int taime = 0;
	CVector3 ka = CVector3::Zero;
	int hyouji = 11;
	int taim = 11;
	int Target = 3;
	CVector3 camera_to_player_vector = CVector3::Zero;
	float camera_to_player_dist = 0.0f;
	float cm_near = 2000.0f;
	CVector3 kakakakak = target - nowkmtarget;
	
};

