#include "stdafx.h"
#include "taieki.h"
#include"math.h"
#include"camera.h"


taieki::taieki()
{
	effect = NewGO<prefab::CEffect>(0);
}
taieki::~taieki()
{
	effect->Release();
}
bool taieki::Start()
{
	for (int i = 0;i < teki;i++)
	{
		taieki_to_tekipos[i] = CVector3::Zero;
	}
	player = FindGO<Player>("Player");
	tekip = FindGO<tekihei>("tekihei");//�G���������炻�̃C���X�^���X���i�[����B
	/*m_taiekiModelData.Load(L"modelData/taieki.cmo");
	m_taieki.Init(m_taiekiModelData);*/
	CF = MainCamera().GetForward();
	CF.Normalize();
	tpos = player->GetPosition();//�̉t�̓v���C���[����o�����̂ŁA�̉t�̍��W�̓v���C���[�Ɠ������W�ɂ���B
	tpos.y += 120.0f;//�̉t�𓪂���o�����߂ɍ����𒲐��B

	PS = player->GetMoveSpeed();//�v���C���[�̈ړ����x���i�[�B

	//�G�t�F�N�g�̏������B
	effect->Play(L"effect/aura1.efk");
	effect->SetPosition(tpos);
	effect->SetScale({ 10.0f,10.0f,10.0f });

	return true;
}

void taieki::ThisDelete()
{
	if (effect->IsPlay() != 1) {
		DeleteGO(this);
	}
	if (teikonFrag == true && Taim++ >= 70) {
		DeleteGO(this);
	}
}
void taieki::Update()
{
	for (int i = 0; i < teki; i++)//10��J��Ԃ��B
	{
		if (tekip != NULL)//�G���̃C���X�^���X���i�[���Ă�����
		{
			tekipos2[i] = tekip->tekipos[i];                    //i�Ԗڂ̓G���̍��W���i�[�B
			tekipos2[i].y += 50.0f;                             //i�Ԗڂ̓G���̍��W��Y���W��50.0���v���X�B
			taieki_to_tekipos[i] = tekipos2[i] - tpos;          //i�Ԗڂ̓G���̍��W�Ƒ̉t�̍��W�Ƃ̍����i�[�B
			tekikyori[i] = sqrt(taieki_to_tekipos[i].x*taieki_to_tekipos[i].x + taieki_to_tekipos[i].y*taieki_to_tekipos[i].y + taieki_to_tekipos[i].z*taieki_to_tekipos[i].z);
			taieki_to_tekipos[i].Normalize();

			//i�Ԗڂ̓G���Ƃ̋�����50�ȉ����Ai�Ԗڂ̓G�����������Ă�����
			if (tekikyori[i] <= 50.0f&&tekip->tekiheiflag[i] == 1)
			{
				tekip->tekiHP[i] = 0.0f; //i�Ԗڂ̓G����HP��-1����B
				/*effect = NewGO<prefab::CEffect>(0);
				e_pos = tpos;
				effect->SetPosition(e_pos);
				effect->SetScale({ 100.0f,100.0f,100.0f });
				effect->Play(L"effect/aura.efk");*/
				DeleteGO(this);
			}

			//i�Ԗڂ̓G���Ƃ̋�����200�ȉ����A�̉t��Y���W��10.0�ȉ�(���e)��������
			if ((tekikyori[i] <= 300.0f)&&(tpos.y <= 10.0f))
			{
				tekip->tekiHP[i] -= 5.0f;//i�Ԗڂ̓G����HP�𖈃t���[�����Ƃ�0.01�����炷�B
			}
		}
	}

	if (tpos.y <= 10.0f)
	{
		if (teikonFrag ==false) {
			if (Lever >= 2) {
				effect->Release();
				effect->Play(L"effect/aura3.efk");
				effect->SetScale({ 100.0f,100.0f,100.0f });
			}
			else {
				Taim = 120;
			}

			
			
			/*effect = NewGO<prefab::CEffect>(0);
			e_pos = tpos;
			effect->SetPosition(e_pos);
			effect->SetScale({100.0f,100.0f,100.0f});
			effect->Play(L"effect/aura.efk");*/

			teikonFrag = true;
		}
	}
	else {
		tpos += (CF * 2000.0f*GameTime().GetFrameDeltaTime()) + PS * GameTime().GetFrameDeltaTime();
		TS.y -= 50.0f * GameTime().GetFrameDeltaTime();
		tpos.y += TS.y;
		effect->SetPosition(tpos);
	}
	ThisDelete();//�������g���폜���邩�ǂ����̏���������B
	effect->SetPosition(tpos);
}
void taieki::Render(CRenderContext& rc)
{
	m_taieki.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
