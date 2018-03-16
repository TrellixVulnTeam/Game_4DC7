#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
#include"camera.h"
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
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 100.0f, 0.0f });
	MainCamera().Update();
	//�����Ɋ�{�I�Ȕ�����`��
	{
		NewGO<Taitor>(0, "Taitor");
		NewGO<Player>(0, "Player");
		//NewGO<AI>(0, "AI");
		NewGO<Stage>(0, "stage");
		NewGO<camera>(0, "camera");
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
	
}
void Game::Render(CRenderContext& rc)
{
}