#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#define REACH 200.0  //�]���r�̍U���͈́B���̋����܂ŋ߂Â�����U������B
#define PI 3.141592653589793 
//AI NPC;
//�����m�����p����NPC�̃n���h���Ƃ��āAj����ꕔ���̃n���h���Ƃ��đ�p����B����͌�ɒ����Ă����悤�ɁB
//NPC��NPC�]���r�̗�������������B
AI::AI()
{
	pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_speed = 0.5f; //�m�[�}����Ԃ̂Ƃ��̏�ɓ����ړ����x�i��{0.8�j�B1.5������B
	iNo = game1->incNo();
	Leftfrag = game1->GetLeft();
}
AI::~AI()
{
	//m_charaCon.RemoveRigidBoby();
	DeleteGO(work);
}
bool AI::Start()
{
	work = NewGO<AImove>(0, "AImove");
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	//�L�����̃X�L�����f���̃��[�h�͊e���T�u�N���X�ōs���B
	m_skinModelData.Load(L"modelData/liam.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);
	if (Leftfrag <= 0) {
		pasu = game->getAIDate(iNo);
	}
	else
	{
		pasu = game->getLAIDate(iNo);
	}
	m_position = game->pasu[Leftfrag].m_pointList[pasu[ima++] - 1];
	m_position.y = 100.0;
	//�t���X�^���J�����O���������B
	m_objectFrustumCulling.Init(MainCamera());
	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	A_charaCon.Init(
		40.0,			//���a�B 
		150.0f,			//�����B
		m_position,		//�����ʒu�B
		1
	);
	ai_NPCAnimationClips[0].Load(L"animData/shiminidle.tka");//���B��œ����B
	ai_NPCAnimationClips[0].SetLoopFlag(true);
	ai_NPCAnimationClips[1].Load(L"animData/shiminwalk.tka");//���B��œ����B
	ai_NPCAnimationClips[1].SetLoopFlag(true);
	ai_NPCAnimationClips[2].Load(L"animData/shiminrun.tka");//���B��œ����B
	ai_NPCAnimationClips[2].SetLoopFlag(true);

	//�A�j���[�V�����̏������B
	ai_NPCAnimation.Init(
		m_skinModel,			//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		ai_NPCAnimationClips,	//�A�j���[�V�����N���b�v�̔z��B
		4							//�A�j���[�V�����N���b�v�̐��B
	);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	work->Setkakudo(4.0f);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		material->Setm_zonbi(zondi.GetBody());
	});
	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->pasu[Leftfrag].m_pointList[pasu[ima] - 1]));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);


	return true;
}
void AI::NPCNormal()
{
	work->kyorikeisan(pasu[ima] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());//��]
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�

	if (160.0f > work->Getlen()) {
		if (Leftfrag <= 0) {
			if (ima >= game->gatsiz(iNo) - 1) {//���̃|�W�V������6�Ȃ�
						  //0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
				ima = 0;
			}
			else {
					ima++;
			}
		}
		else {
			if (ima >= game->gatLsiz(iNo) - 1) {//���̃|�W�V������6�Ȃ�
											   //0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
				ima = 0;

			}
			else {
				ima++;
			}
		}
	}
}
void AI::Zonbesiya()
{
	float min_Nagasa = 990099.0f;
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			AI* ai = (AI*)go;
			if (ai->GetZonbi()==false) {   //���ꂪ��ʎs����������
				float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
				if (kyori < 2.0f) {  //���������E�͈͈ȓ���������
					float angle = VectorAngleDeg(this->m_position - ai->m_position); //�����Ώۂ̍��W�������ɂ���B
					if (angle <= 100.0f) { //�p�x�����E����������
						if (kyori < min_Nagasa) { //�����Ɉ�ԋ߂��̂Ȃ�
							min_Nagasa = kyori;
							Tansaku = ai;
						}
					}
				}
			}
		}
	});

	min_Nagasa;
}
void AI::NPCNormal_Search()//NPC�̌x�������B
{
	CVector3 v2 = pl->Getposition() - m_position;
	float len1 = v2.Length();//����
	float hann = Siya(v2, len1);
	if (hann == 1) {
		Gaizi->Satpoint(0.1);
		da = 0;
		m_speed = 2.5f;
		pa = Escape;
	}
	if (hann >= 2) {
		kannkaku = true;
	}
}

void AI::NPCResistance_NPC()//NPC�]���r�ւ̒�R�Ɋւ��鏈���B�I�[�o�[���C�h������B
{
	m_speed = 0.0f;
	if (sinsoku < 1.0) {
		m_skinModel.Satburend(sinsoku);
		sinsoku += 0.01;
	}
	else {
		pa = Damage;
	}
}

void AI::NPCResistance_Player()//�v���C���[�ւ̒�R�Ɋւ��鏈���B�I�[�o�[���C�h������B
{
	m_speed = 0.0f;
	if (sinsoku < 1.0) {
		m_skinModel.Satburend(sinsoku);
		sinsoku += 0.01;
	}
	else {
		pa = Damage;
	}
}

void AI::NPCDamage()
{
	static int count = 0; //30�t���[�����J�E���g����B
	if (count >= 30) {
		//30�t���[���o�߂�����]���r���B
		nearestpas();
		SetZonbe();
	}
	else {
		count++; //1�t���[���o�߂��J�E���g����B
	}

}
void AI::nearestpas()
{

	float sa = 99999999999999.0;
	for (int h = 0; h < game->pasu[Leftfrag].GetresutoSaiz()-1; h++) {
		CVector3 k = game->pasu[Leftfrag].Getresuto(h)->m_position[0] - m_position;
		float saa = k.Length();
		if (sa > saa) {
			sa = saa;
			mokuhyou = game->pasu[Leftfrag].Getresuto(h)->No[0];
		}
	}
	m_speed = 1.5;
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
	}
	pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
}

void AI::NPCZombie_Normal()
{
	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());//��]
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�


	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {
		int furag = 0;
		do {
			int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
			if (mokuhyou != game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num]) {
				furag++;
				mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[num];
			}
		} while (furag == 0);
		for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
			if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
				mokuhyouNo = ka;
				break;
			}
		}
	}
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //�p�^�[�����]���r�`�F�C�X�ɕς���B
	}
}
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len>2100.0f||HitFlag == true) {//����NPC����������(������80�ȏ゠����)�A���邢�͍U����^������
		//���̈ʒu�ɖ߂�B
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
			Tansaku = nullptr; //�������ʂ�����������B
			kaiten = false;
			nearestpas();
			HitFlag = false;
		
	}else {//NPC���������Ă��炸�A�����Ă�����
		CVector3 n =  Tansaku->m_position-m_position;
		NPCRunangle(n);
		n.y = 0.0f;
		n.Normalize();
		m_movespeed = n * (m_speed*200.0 + mobe);
		m_movespeed.y+=gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//�ړ�
			/////////////////////////////////
			//�s��NPC��ǐՂ��鏈���B
			/////////////////////////////////
		if (len<REACH) {//NPC�ɒǂ�������
						//�U������(�m���ɓ�����d�l)�B
			Tansaku->pa = Resistance_NPC;
			//NPC_Attack_Animation();//�U���A�j���[�V�����𗬂��B
			HitFlag = true; //�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
		}
	}	
}
void AI::NPCZombie_Attack()//vs���ꕔ��
{
	if (tekip != NULL) {
		if (BattleFlag == false) {//�����Ɛ���Ă��炸�A�t���[�ȏ�ԂȂ�
			if (da >= jyunban.size()) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
				if (tekip->tekiheiflag[No] >= 1) {
					work->kyorikeisan(tekip->tekipos[No], m_position, m_forward);
				}
				else {
					takikennsau();
				}
			}
			else {
				work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
			}
			m_rotation.Multiply(work->Getkaku());
			CVector3 v = work->Getmokuteki() - m_position;  //��ԋ߂������Ɉړ�����B
			m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
			m_movespeed.y += gravity;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
			if (15.0f > work->Getlen()) {
				if (da >= jyunban.size() - 1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
					if (tekip->tekiheiflag[No] >= 1) {
						da++;
					}
					else {
						takikennsau();
					}
				}
				else {
					da++;
				}
			}
			float h = 9999999999999.0f;
			for (int i = 0; i < 10; i++) {
				if (tekip->tekiheiflag[i] >= 1) {
					float max = GetKyori(m_position, tekip->tekipos[i]);
					if (max < REACH) {//�����ɋ߂Â�����
						BattleFlag = true;//�퓬���J�n����B
						if (h > max) {
							No = i;
							h = max;
						}
					}
				}
			}
		}
		if (BattleFlag == true) {//�퓬��ԂȂ�
			CVector3 bekutor = tekip->tekipos[No] - m_position;
			float len = GetKyori(m_position, tekip->tekipos[No]);
			float angle = VectorAngleDeg(bekutor);
			if (angle >= 3.0) {
				bekutor.y = 0.0f;
				bekutor.Normalize();
				//��]�������߂�B
				CVector3 rotAxis;
				rotAxis.Cross(m_forward, bekutor);
				rotAxis.Normalize();
				CQuaternion qBias1;
				qBias1.SetRotationDeg(rotAxis, 5.0f);
				m_rotation.Multiply(qBias1);
			}
			else if (150 < len) {
				m_movespeed = m_forward * (m_speed + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
			}
			else {
				//����
				tekip->tekiHP[No] = tekip->tekiHP[No] - 5;
				//�����ɍU������B
				takikennsau();
				BattleFlag = false;
			}
		}

		//if () {//������|������
		//	//�u�퓬���I�������v�Ƃ����t���O�����Ă�B
		//	BattleFlag = false;
		//}
	}
	
}
void AI::takikennsau()
{
	float min = 99999999999999999.0;
	No = -1;
	if (tekip != NULL) {
		for (int i = 0; i < 10; i++) {
			if (tekip->tekiheiflag[i] >= 1) {
				float max = GetKyori(m_position, tekip->tekipos[i]);
				if (min > max) {
					min = max;
					No = i;
				}
			}
		}
		if (No >= 0) {
			CVector3 posa = tekip->tekipos[No] - m_position;
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, tekip->tekipos[No], &jyunban, Leftfrag);
			da = 0;//������x����
		}
	}
}
void AI::NPCFade_Out()//��ʎs�����ޏꂷ��Ƃ��̏����B
{
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());
	m_movespeed = m_forward*(work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//�ړ�
	if (200.0f > work->Getlen()) {
		if (da >= jyunban.size()-1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
			pa = Death;
			da = 1;
		}
		else {
			da++;
		}
	}
}

float AI::GetKyori(CVector3 a, CVector3 b) //2�̃I�u�W�F�N�g�̍��W���󂯎��A�I�u�W�F�N�g�Ԃ̋�����Ԃ��B
{
	CVector3 v = a - b;
	float len = v.Length();//����
	return len;  //2�̃I�u�W�F�N�g�̋�����Ԃ��B
}

void AI::Turn()//����
{
	if (fabsf(m_movespeed.x) < 0.001f
		&& fabsf(m_movespeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void AI::NPCRuet()//NPC���[�g
{

}

float AI::VectorAngleDeg2(CVector3 c)
{
	c.Normalize();//����Vector�ɂ���B
	float kaku = atanf(c.Dot(m_rite));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)

	float degree = CMath::RadToDeg(kaku);//���߂����W�A����x�ɕς���B

	return degree;
}

float AI::Siya(CVector3 h, float g)
{

	if (g < 500.0f) {
		if (fabsf(VectorAngleDeg(h)) <= 45.0f) {//��������
			if (pa == Normal)
				retu_position = m_position;
			//m_speed = 1000.0f;
			//DamageFlag = true;
			//�v���C���[���瓦����B
			return 1;
		}
		else {
			if (pl->GetMoveSpeed().Length() >= 500.0f)
			{
				CQuaternion kaku;
				kaku.SetRotationDeg(CVector3::AxisY, 30.0f);
				m_rotation.Multiply(kaku);
				return 2;
			}
		}
	}
	return 0;
}
void AI::NPCChase()
{
	m_speed = 2.5f;
	CVector3 mokuteki = lam->m_position-m_position  ;
	NPCRunangle(mokuteki);
	if (mokuteki.Length()<=200.0f&&lam->muteki_Flag==false) {
		m_speed = 1.1f;
		lam->NPCHP -= 10.0f;
		muteki_Flag = true;
	}
	else {
		mokuteki.y = 0.0f;
		mokuteki.Normalize();//���K�����Č����x�N�g���ɂ���B
		m_movespeed = mokuteki * (150 * m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
	}
}
float AI::VectorAngleDeg(CVector3 c)
{
	c.y = 0.0f;
	c.Normalize();//����Vector�ɂ���B
	float kaku = acosf(c.Dot(m_forward));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)

	float degree =CMath::RadToDeg(kaku);

	return degree;
}

void AI::DamageHantei() //�S�Ẵ]���r�Ƌ����Ń_���[�W���������B
{
	AIrest++;

	for (; AIrest != Humans.end(); AIrest++) {
		if (this != (AI*)AIrest[0]) {
			AI* ai = (AI*)AIrest[0];

			float kyori = GetKyori(this->m_position, ai->m_position);
			if (kyori < 1000) {
				float angle = VectorAngleDeg(ai->m_position - this->m_position);
				if (angle <= 60)
				{
					if (ai->GetZonbi() == true) {
						lam = ai;
						for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
							if (this != (AI*)AIrest[0]) {
								AI* ai = (AI*)AIrest[0];
								if (ai->GetZonbi() != true) {
									if (10000.0 >= (ai->m_position - m_position).Length())
									{
										mikata++;
										mikatalest.push_back(ai);

									}
								}
							}
						}
						if (mikata <= 2) {
							m_speed = 2.5f;
							retu_position = m_position;
							pa = Escape_NPC;
							mikatalest.clear();
						}
						else {
							for (int k = 0; k < mikatalest.size(); k++) {
								m_speed = 2.5f;
								mikatalest[k]->Chasefrag = 1;
								mikatalest[k]->pa = Chase;
								mikatalest[k]->lam = this->lam;
							}
						}
						break;
					}
					else {
						//�s�����m�̊m�F
					}
				}
			}
		}
	}
	
	
	//FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//	if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
	//		AI* ai = (AI*)go;
	//		if (ai->Zonbe == 1) {   //���ꂪ�]���r��������
	//			float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
	//			if (kyori < 1000) {
	//				float angle = VectorAngleDeg(this->m_position - ai->m_position);
	//				if (angle <= 60)
	//				{
	//					CVector3 j = this->m_position - ai->m_position;
	//					j.y = 0.0f;
	//					j.Normalize();
	//					m_movespeed = j * (m_speed *(mobe + 1000));
	//					m_movespeed.y += gravity;
	//					m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
	//					kannkaku = true;
	//				}
	//			}
	//		}
	//	}
	//});

	float kyori = GetKyori(this->m_position, pl->GetPosition());//�����Ƃ̋��������߂�B
	if (kyori < 100) {  //�������U���͈͈ȓ���������
		pa = Resistance_Player; //�p�^�[�����R�ɂ�����B
	}
}

void AI::NPCDeath()//���S�A���ŏ����B
{
	if (Leftfrag <= 0) {
		game->SatRSaizon(iNo);
	}
	else {
		game->SatLSaizon(iNo);
	}
	DeleteGO(this);//���ȏ��ŁB
}

void AI::AI_Animation()//AI�̃A�j���[�V��������
{
	if (m_speed<=1.0) {
		Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
		Loop_Run_Animation();
	}
}
void AI::Idle_Animation() //�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(0, 0.2);
}


void AI::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(1,0.2);
}


void AI::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(2,0.2);
}

//void AI::Resistance_Animation()//�L�����N�^�[����R���Ă��鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Resistance);
//}
//
//void AI::NPC_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă��鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(NPC_Attack);
//}


void AI::Update()
{

	AIrest = Humans.begin();
	m_movespeed = CVector3::Zero;
	//pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	kannkaku = false;
	if (muteki_Flag == true) {
		muteki_count++;
		if (muteki_count > 300) {//���G�����Ă���300�t���[�����o�߂�����
			muteki_Flag = false;
		}
	}

	if (GetZonbi()==false) { //�������]���r�ł͂Ȃ�������
		if (muteki_Flag == false) {//���G�ł͂Ȃ�������
			if (pa != Damage)
				DamageHantei(); //�]���r�Ƃ̓����蔻����Ƃ�B
			if (pl->GetattackF() >= 1) {
				if ((pl->Getposition() - m_position).Length() <= 100.0f) {
					if (atekfrag > -90.0) {
						CQuaternion qBias1;
						qBias1.SetRotationDeg(CVector3::AxisX, -10.0f);
						m_rotation.Multiply(qBias1);
						m_speed = 0.0;
						atekfrag -= 10.0;
					}
					kannkaku = true;
				}
			}
		}
	}

	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//���ꕔ�����o��������A
		ForceFlag = true;//�o���t���O�𗧂Ă�B
		if (GetZonbi()==true) {//�������]���r��������
			tekip = FindGO<tekihei>("tekihei");
			takikennsau();
			pa = Zombie_Attack; //�p�^�[�����]���r�A�^�b�N�ɐ؂�ւ���B
		}
		else {//�����A�������]���r�ł͂Ȃ�������
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
			da = 0;
			m_speed = 2.5f;
			work->Setkakudo(3.0f);
			pa = Fade_Out; //�p�^�[�����t�F�[�h�A�E�g�ɐ؂�ւ���B
		}
	}
	if (NPCHP <= 0.0) {
		m_speed = 0.0f;
		CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisX, 10.0f);
		m_rotation.Multiply(qBias1);
		kannkaku = true;
	}
	if (atekfrag < 0.0&&kannkaku == false) {
		
		CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisX, 10.0f);
		m_rotation.Multiply(qBias1);
		atekfrag += 10.0;
		kannkaku = true;
	}

	if (kannkaku== false) {
		switch (pa) {
		case Normal:
			//NPC�̓����������B
			NPCNormal_Search();
			if (kannkaku != true) {
			//	m_speed = 1.0;
				NPCNormal();
			}
			break;
		case Escape:
			NPCescape();
			break;
		case Escape_NPC:
			NPCEscape_NPC();
			break;
		case Return:
			NPCNormal_Search();
			if (kannkaku != true)
				NPCReturn();
			break;
		case Chase:
			NPCChase();
			break;
		case Fade_Out:
			NPCFade_Out();
			break;
		case Resistance_NPC:
			NPCResistance_NPC();
			break;
		case Resistance_Player:
			NPCResistance_Player();
			break;
		case Damage:
			NPCDamage();
			break;
		case Zombie_Normal:
			Zonbesiya();
			NPCZombie_Normal();
			break;
		case Zombie_Chase:
			//����NPC�����������̏����������B
			NPCZombie_Chase();
			break;
		case Zombie_Attack:
			NPCZombie_Attack();
			break;
		case Zombie_Return:
			Zonbesiya();
			NPCzombie_Return();
			break;
		case Death:
			NPCDeath();
			break;
		default:
			break;
		}
	}

	
	if (pa != Zombie_Chase) {
		FindGameObjectsWithTag(10, [&](IGameObject* go) {
			if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
				AI* ai = (AI*)go;
				CVector3 kyori1 = ai->m_position - this->m_position;//�����Ƃ̋��������߂�B
				float f = kyori1.Length();
				if (f<100.0f) { //������
					kyori1 /= 3.0f;
					kyori1.y = 0.0f;
					m_movespeed = kyori1 * m_speed*-1;
					m_movespeed.y += gravity;
					m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//�ړ�

				}
			}
		});
	}
	Setposition(m_position);

	if (!m_objectFrustumCulling.IsCulling()) {
		m_skinModel.Update(m_position, m_rotation, { 20.0f, 20.0f,20.0f });
	}

	AI_Animation();
	m_skinModel.UpdateBoundingBox();
	m_objectFrustumCulling.Execute(m_skinModel.GetBoundingBox());
}
void AI::NPCReturn()
{
	int Size = jyunban.size();
	if (Size > 0) {
		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		m_rotation.Multiply(work->Getkaku());
		CVector3 v = work->Getmokuteki() - m_position;
		m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//�ړ�
		if (15.0f > work->Getlen()) {
			if (da >= jyunban.size() - 1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
				pa = Normal;//�p�^�[�����m�[�}���ɂ�����B
				m_speed = 1.0f;
				da = 0;
			}
			else {
				da++;
			}
		}
	}
	else
	{
		m_speed = 1.0f;
		pa = Normal;
	}

}
void AI::NPCzombie_Return()
{
	NPCReturn();
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //�p�^�[�����]���r�`�F�C�X�ɕς���B
	}
	if (pa == Normal) {
		pa = Zombie_Normal;
	}
}
void AI::NPCRunangle(CVector3 kyori)
{
	kyori.y = 0.0f;
	float angle = VectorAngleDeg(kyori);
	kyori.Normalize();//���K�����Č����x�N�g���ɂ���B
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, kyori);
	rotAxis.Normalize();
	CQuaternion qBias1;
	if (angle >= escapecaku) {
		qBias1.SetRotationDeg(rotAxis, escapecaku);
		m_rotation.Multiply(qBias1);
		kaiten = false;
	}
	else if (kaiten != true) {
		qBias1.SetRotationDeg(rotAxis, angle);
		escapecaku = 2;
		m_rotation.Multiply(qBias1);
		kaiten = true;
	}
}
void AI::NPCescape()//�]���r���瓦����
{

	CVector3 v = m_position - pl->GetPosition();
	float len = v.Length();//����
	if (len < 2000.0) {
		NPCRunangle(v);
		//m_position += v * m_speed;
		v.y = 0.0f;
		v.Normalize();
		m_movespeed = v * (150*m_speed +mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
		m_speed = 2.5f;
		escapecaku = 30.0f;
		mobe = 50.0f;
		work->Setkakudo(5.0f);
		kaiten = false;
		pa = Fade_Out;
	}
}
void AI::NPCEscape_NPC()
{
	CVector3 j = this->m_position - lam->m_position;
	NPCRunangle(j);
	if (j.Length() >= 1500) {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		escapecaku = 30.0f;
		pa = Return;
	}
	else {
		j.y = 0.0f;
		j.Normalize();//���K�����Č����x�N�g���ɂ���B
		m_movespeed = j * (300 * m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
	}
}
void AI::Render(CRenderContext& rc)
{
	if (m_objectFrustumCulling.IsCulling()) {
		//�`�悵�Ȃ����S�B
		return;
	}
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
