#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
<<<<<<< HEAD
#include"Level.h"
#include"AImove.h"
=======
#include"camera.h"
>>>>>>> 2d17ab8e8be7b1d97574d3fd2aba03b4fc0ce85e
Game::Game()
{
	//�����Ɋ�{�I�Ȕ�����`��
	NewGO<Taitor>(0,"Taitor");
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	
}
void Game::OnDestroy()
{
	//�����ōŏI�I�ɂc�����������f�n���΂�����B




	//�ċN���i�^�C�g���\���j
	NewGO<Game>(0, nullptr);
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.5f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();
	//�����Ɋ�{�I�Ȕ�����`��
	{
		NewGO<Taitor>(0, "Taitor");
		NewGO<Player>(0, "Player");
		//NewGO<AI>(0, "AI");
		NewGO<Stage>(0, "stage");
<<<<<<< HEAD
		m_level.Build(L"lever/leval01.tks");
		NewGO<AImove>(0, "na");
=======
		NewGO<camera>(0, "camera");
>>>>>>> 2d17ab8e8be7b1d97574d3fd2aba03b4fc0ce85e
	}

	m_Fade=FindGO<Fade>("Fade");
	if (m_Fade != NULL) {
		m_Fade->StartFadeOut();
		a++;
	}
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//�N���A�֌W�H�H
	
	if (Pad(0).IsTrigger(enButtonB) && a >= 2) {
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
	}
}
void Game::Render(CRenderContext& rc)
{
}