#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
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
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();
	//�����Ɋ�{�I�Ȕ�����`��
	{
		NewGO<Taitor>(0, "Taitor");

	}

	m_Fade=FindGO<Fade>("Fade");
	m_Fade->StartFadeOut();
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//�N���A�֌W�H�H
	if (Pad(0).IsTrigger(enButtonB) && a >= 1) {
		m_Fade->StartFadeOut();
		a--;
	}
	if (Pad(0).IsTrigger(enButtonA)&&a==0) {
		m_Fade->StartFadeIn();
		a++;
	}
	
}
void Game::Render(CRenderContext& rc)
{
}