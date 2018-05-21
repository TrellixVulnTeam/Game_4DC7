#pragma once
#include "Level.h"
#include"Pasu.h"
#include"keiroK.h"
#include"Geizi.h"
#include"Player.h"
#include"Stage.h"
#include"camera.h"
#include"item.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class Fade;
class AI;
class AImove;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CAnimationClip m_animClip[1];							//アニメーションクリップ。
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
	std::vector<AI*> simin;
	Fade* m_Fade;
	Geizi* gaizi;
	Player* player;
	Stage* stge;
	camera* camera1;
	Level m_level[10];
	Pasu  pasu;
	keiroK* keiro;
	int No = 0;
	int da[2][11] = { {26,25,17,16,15,14,19,18,24,28,27},{1,1,1,1,1,1,1,1,1,1,1} };
	int a=2;		
	int stag = 0;					//レベル。
private:
	void InitSceneLight();
	float g = 0.0f, f = 0.0;
	prefab::CDirectionLight* m_sunLig = nullptr;	//	太陽ライト。
};

