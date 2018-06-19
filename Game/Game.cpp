#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
#include"Level.h"
#include "AI_manager.h"
#include"AImove.h"
#include"camera.h"
#include"Pasu.h"
#include"keiroK.h"
#include"carRender.h"
#include"tekihei.h"
#include"Geizi.h"
#include"item.h"
#include"car.h"
Game::Game()
{
	//�����Ɋ�{�I�Ȕ�����`��
	gaizi = NewGO<Geizi>(1, "Geizi");
	player = FindGO<Player>("Player");
	player->SetGame();
//	pasu2.clear();
	camera1 = NewGO<camera>(0, "camera");
	//m_level[1].X = 5.0f;
	//m_level[1].Z=  5.0f;
	//m_level[1].Build(L"lever/leval01.tks");
	//�����Ɋ�{�I�Ȕ�����`��
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	
}
void Game::OnDestroy()
{
	DeleteGO(player);
	//�����ōŏI�I�ɂc�����������f�n���΂�����B	
	DeleteGO(FindGO<AI_manager>("AI_manager"));
	DeleteGO(gaizi);
	DeleteGO(camera1);
	DeleteGO(FindGO<item>("item"));
	//�ċN���i�^�C�g���\���j
	NewGO<Taitor>(0, "Taitor");
	NewGO<AI_manager>(0, "AI_manager");
}
bool Game::Start()
{
	//�J������ݒ�B
	m_Fade = FindGO<Fade>("Fade");


	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//�N���A�֌W�H�H


	//if(i < loc.GetNumObject()) {
	//	CVector3 pos = loc.GetObjectPosition(i);
	//	//m_point.push_back(m_point);
	//}
	if (m_Fade != NULL&& m_Fade->toumeiodo >= 1.0f) {
		m_Fade->StartFadeIn();
	}

	//�T�E���h
	SoundEngine().SetListenerPosition(MainCamera().GetPosition());
	CVector3 frontXZ = MainCamera().GetForward();
	frontXZ.y = 0.0f;
	frontXZ.Normalize();
	SoundEngine().SetListenerFront(frontXZ);

	/*if (Pad(0).IsTrigger(enButtonB) && a >= 2) {
		m_Fade->StartFadeOut();
		a--;

	}
	if (Pad(0).IsTrigger(enButtonA)&&a==1) {
		m_Fade->StartFadeIn();
		a++;
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		g += 100.0;
	}
	if (Pad(0).IsTrigger(enButtonRight)) {

		f += 100.0;
	}*/
	/*MainCamera().SetTarget({ 0.0f, 10.0f, 0.5f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();*/
	//i++;
}
void Game::Render(CRenderContext& rc)
{

}