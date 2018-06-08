#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 10
class tekihei : public IGameObject
{
public:
	tekihei();
	~tekihei();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

	CSkinModel tekiskinModel[teki];					//スキンモデル。
	CSkinModelData tekiskinModelData[teki];
	CCharacterController m_charaCon[teki];		//キャラクタコントローラ。
	CVector3 tekipos[teki];//敵のポジション
	CVector3 tekispeed[teki];//移動速度
	CQuaternion tekirot[teki];
	CMatrix m_tekirot[teki];
	CVector3 tekiright[teki];
	CVector3 tekifoward[teki];
	Geizi *gaizi;
	Player *Pp = nullptr;
	CVector3 ppos = CVector3::Zero;
	CVector3 teki_to_player[teki];
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];
	CVector3 tamapos[teki];
	int tamaflag[teki];
	CVector3 tamamuki[teki];
	CVector3 teki_to_tama[teki];
	float teki_to_tama_vector[teki];
	CVector3 playerpos = CVector3::Zero;
	int time[teki];
	int damageflag[teki];
	int tekiheiflag[teki];
	float tekiHP[teki];
	int clearcount = 0;
	int soma = 0;
	CAnimation tekianimation[teki];
	CAnimationClip animclip[1];
	float Dtekiangle[teki];
	int tekianglecompF[teki];						//敵が向ききったフラグ






	//経路探査用プログラム



	CVector3 EnemyPath[21];
	int path_f[teki][21];
	int find_f[teki];
	CVector3 teki_to_path_vector[teki][21];
	float teki_to_path[teki][21];
	int target_num = 0;


};