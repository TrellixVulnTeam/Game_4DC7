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
	case 0://�v���C���[�̏���

		you.CreateFromDDSTextureFromFile(L"sprite/GameClear.dds");//�����ɏ������̃��U���g��ʂ�\��
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
		break;
	case 1://�v���C���[�̕���
		you.CreateFromDDSTextureFromFile(L"sprite/GameOver.dds");//�����ɔs�k���̃��U���g��ʂ�\��
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
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
		syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
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
