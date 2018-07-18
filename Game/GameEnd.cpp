#include "stdafx.h"
#include "GameEnd.h"
#include"Geizi.h"
#include"AI_manager.h"
#include"Game.h"
#include"Fade.h"
#include"tekihei.h"

GameEnd::GameEnd()
{
}


GameEnd::~GameEnd()
{
}

bool GameEnd::Start()
{
	fade = FindGO<Fade>("Fade");
	Geizi* hama= FindGO<Geizi>("Geizi");
	player = FindGO<Player>("Player");
	tekihei* Tekhei = FindGO<tekihei>("tekihei");
	if (hama->GatHPfurag() >= 1) {
		furgu++;
	}
	m_position = { 0.0,300.0,0.0 };
	//switch (furgu)
	//{
	//case 0://�v���C���[�̏���
		you.CreateFromDDSTextureFromFile(L"sprite/White.dds");//�����ɏ������̃��U���g��ʂ�\��
		syuuryou.Init(you, 1280, 780);
		//syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
	//	break;
	//case 1://�v���C���[�̕���
	//	you.CreateFromDDSTextureFromFile(L"sprite/GameOver.dds");//�����ɔs�k���̃��U���g��ʂ�\��
	//	syuuryou.Init(you, 110, 100);
	//	syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
	//	break;
	//default:
	//	break;
	//}
		player->falseGame();

	int isa = AI_ado->Get_NPC_Number();
	int zonbisuu = 0;
	int hinansuu = 0;
	for (int i = 0; i<AI_ado->Getsize(); i++)
	{
		if (AI_ado->RAIseizon[i] <= 0&& AI_ado->RAIseizon[i] >= -4)
		{
			zonbisuu++;
		}if (AI_ado->RAIseizon[i] <=-5)
		{
			hinansuu++;
		}
	}	for (int i = 0; i<AI_ado->Get2size(); i++)
	{
		if (AI_ado->LAIseizon[i] <= 0&& AI_ado->LAIseizon[i] >= -4)
		{
			zonbisuu++;
		}if (AI_ado->LAIseizon[i] <=-5)
		{
			hinansuu++;
		}
	}
	float wariai = 0.00f;
	wariai = ((float)zonbisuu / (float)AI_ado->Get_NPC_Number())*50;
	wariai +=((float)Tekhei->soma / (float)teki)*50;
	swprintf_s( inputscore, L"���_�F%d�_", (int)wariai);
	swprintf_s(inputsubscore, L"�]���r�����F%d��,�G�����j��:%d��,������ꂽ��:%d�l", zonbisuu, Tekhei->soma, hinansuu);
	return true;
}
void GameEnd::Update()
{
	switch (flag)
	{
	case White_fade:
		toumeiodo += 00.1;
		if (toumeiodo >= 1.0f)
		{
			toumeiodo = 1.0f;
			player->SetController_end();//�v���C���[�̃R���g���[�����~�B
			flag = UP;
		}
		break;
	case UP:
		result_pos.y += 30.0f;
		if (result_pos.y >= 300.0f)
		{
			result_pos.y = 300.0f;
			flag = slide;
		}
		break;
	case slide:
		score_pos.y += 30.0f;
		if (score_pos.y >= 100.0f)
		{
			score_pos.y = 100.0f;
			subscore_pos.y = -300.0f;
			flag = idle;
		}
		break;
	case idle:
		if (Pad(0).IsTrigger(enButtonA))
		{
			DeleteGO(FindGO<Game>("Game"));
			DeleteGO(this);
		}
		break;
	default:
		break;
	}
	//if (taim <= 300) {
	//	m_position.y -= 1.0;
	//	syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
	//	taim++;
	//}
	//else {
	//	fade->StartFadeOut();
	//	if (fade->toumeiodo >= 1.0f) {
	//		DeleteGO(FindGO<Game>("Game"));
	//		DeleteGO(this);
	//	}
	//}
	//if (Pad(0).IsTrigger(enButtonA)) //A�{�^���������ꂽ��
	//{
	//	taim += 300;//�{�^�����͂ɂ�鋭���I��
	//}
}

void GameEnd::PostRender(CRenderContext& rc)
{
	syuuryou.SetMulColor({ 1.0f, 1.0f, 1.0f, toumeiodo });
	syuuryou.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);
	m_font.Draw(L"�ŏI����", result_pos, { 0.0f,0.0f,0.0f,255.0f }, 0.0f, 5.0f, result_pivot);
	m_font.Draw(inputscore, score_pos, { 0.0f,0.0f,0.0f,255.0f }, 0.0f,5.0f, score_pivot);
	m_font.Draw(inputsubscore, subscore_pos, { 0.0f,0.0f,0.0f,255.0f }, 0.0f, 1.0f, score_pivot);
	m_font.End(rc);
}
