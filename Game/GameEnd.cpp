#include "stdafx.h"
#include "GameEnd.h"
#include"Geizi.h"
#include"Game.h"

GameEnd::GameEnd()
{
}


GameEnd::~GameEnd()
{
}
bool GameEnd::Start()
{
	Geizi* hama= FindGO<Geizi>("Geizi");
	if (hama->GatHPfurag() >= 1) {
		furgu++;
	}
	m_position = { 0.0,300.0,0.0 };
	switch (furgu)
	{
	case 0://プレイヤーの勝ち

		you.CreateFromDDSTextureFromFile(L"sprite/GameClear.dds");//ここに勝利時のリザルト画面を表示
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		break;
	case 1://プレイヤーの負け
		you.CreateFromDDSTextureFromFile(L"sprite/GameOver.dds");//ここに敗北時のリザルト画面を表示
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		break;
	default:
		break;
	}
	return true;
}
void GameEnd::Update()
{
	if (taim <= 300) {
		m_position.y -= 1.0;
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		taim++;
	}
	else {
		DeleteGO(FindGO<Game>("Game"));
		DeleteGO(this);
	}
}

void GameEnd::Render(CRenderContext& rc)
{
	syuuryou.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
