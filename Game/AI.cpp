#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#include"car.h"
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
	//A_charaCon.RemoveRigidBoby();
	DeleteGO(work);
}
bool AI::Start()
{
	work = NewGO<AImove>(0, "AImove");
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	Car = FindGO<car>("car");
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
		0
	);
	ai_NPCAnimationClips[shiminidle].Load(L"animData/shiminidle.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminidle].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminwalk].Load(L"animData/shiminwalk.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminrun].Load(L"animData/shiminrun.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminrun].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminattack].Load(L"animData/playerattack.tka");//���B��œ����B
	ai_NPCAnimationClips[shiminattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiwalk].Load(L"animData/playerwalk.tka");//���B��œ����B
	ai_NPCAnimationClips[Zonbiwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiattack].Load(L"animData/playerattack.tka");//���B��œ����B
	ai_NPCAnimationClips[Zonbiattack].SetLoopFlag(true);
	
	//�A�j���[�V�����̏������B
	ai_NPCAnimation.Init(
		m_skinModel,			//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		ai_NPCAnimationClips,	//�A�j���[�V�����N���b�v�̔z��B

		animnum					//�A�j���[�V�����N���b�v�̐��B
	);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	work->Setkakudo(4.0f);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
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
	float min_Nagasa = 99999999.0f;
	for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
		if (this != (AI*)AIrest[0]) {															    //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			AI* ai = (AI*)AIrest[0];
			if (ai->GetZonbi() == false) {															//���ꂪ��ʎs����������
				if (ai->Raifu_f == false) {														    //���̐l�������Ă����
					float kyori = GetKyori(this->m_position, ai->m_position);						//�����Ƃ̋��������߂�B
					if (kyori < 1500.0f) {															//���������E�͈͈ȓ���������
						float angle = VectorAngleDeg(ai->m_position - this->m_position);		    //�����Ώۂ̍��W�������ɂ���B
						if (angle <= 60.0f) {														//�p�x�����E����������
							if (kyori < min_Nagasa) {												//�����Ɉ�ԋ߂��̂Ȃ�
								min_Nagasa = kyori;
								Tansaku = ai;
							}
						}
					}
				}
			}
		}
	}
	if (ForceFlag == true) {
		float len = takikennsau();
		if (len <= 1500) {
			pa = Zombie_Attack;
			kannkaku = true;
		}
	}
}
void AI::NPCNormal_Search()//NPC�̌x�������B
{
	CVector3 v2 = pl->Getposition() - m_position;
	float len1 = v2.Length();//����
	float hann = Siya(v2, len1);
	if (hann == 1) {
		da = 0;
		m_speed = 4.0f;
		nearestpas();
		Fardist_path(pl->Getposition());
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
		lam = nullptr;
		Chasefrag = 0;
		Raifu_f = false;
		SetZonbe();
		NPCHP = 100.0f;
		NPCMAXHP = 100.0f;
		m_speed = 1.5;
		pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
	}
	else {
		count++; //1�t���[���o�߂��J�E���g����B
	}

}
void AI::nearestpas()//�Ŋ��̃p�X����
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
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
	}
}

void AI::NPCZombie_Normal()
{
	//	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	//	m_rotation.Multiply(work->Getkaku());//��]
	//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
	pasmove();
	m_rotation.Multiply(work->Getkaku());//��]
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {//�����_���p�j�̃p�X�ԍ�����
		int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
		mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num];
	}
	Retrieval_pasNo(mokuhyou);
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //�p�^�[�����]���r�`�F�C�X�ɕς���B
	}
}
void AI::NPCZombie_Attack()//vs���ꕔ��
{

	static int flame = 40;
	if (tekip != NULL) {
		float len = GetKyori(m_position, tekip->tamapos[No]);
		if (len > 2100.0f &&tekip->tekiheiflag[No] <= 0) {//����NPC����������(������2100�ȏ゠����)�A���邢�͎��񂾂�
														//���̈ʒu�ɖ߂�B
			// //�������ʂ�����������B
			kaiten = false;
			HitFlag = false;
			escapecaku = 30.0f;
			nearestpas();
		}
		else {//NPC���������Ă��炸�A�����Ă�����
			kannkaku=true;
			CVector3 n = tekip->tamapos[No] - m_position;
			NPCRunangle(n);
			if (len < atakkukyori) {//NPC�ɒǂ�������
									//�U������(�m���ɓ�����d�l)�B
				HitFlag = true;//�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
				if (flame >= 40) {
					tekip->tekiHP[No] -=3;
					flame = 0;
				}
				atakkukyori = 200.0f;
				//NPC_Attack_Animation();//�U���A�j���[�V�����𗬂��B
			}
			else {
				HitFlag = false;
				n.y = 0.0f;
				n.Normalize();
				m_movespeed = n * (m_speed*200.0 + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
				atakkukyori = 100.0f;
				/////////////////////////////////
				//�s��NPC��ǐՂ��鏈���B
				/////////////////////////////////
			}
		}
		flame++;
		//if (BattleFlag == false) {//�����Ɛ���Ă��炸�A�t���[�ȏ�ԂȂ�
		//	if (da >= jyunban.size()) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
		//		if (tekip->tekiheiflag[No] >= 1) {
		//			work->kyorikeisan(tekip->tekipos[No], m_position, m_forward);
		//		}
		//		else {
		//			takikennsau();
		//		}
		//	}
		//	else {
		//		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		//	}
		//	m_rotation.Multiply(work->Getkaku());
		//	CVector3 v = work->Getmokuteki() - m_position;  //��ԋ߂������Ɉړ�����B
		//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
		//	m_movespeed.y += gravity;
		//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
		//	if (15.0f > work->Getlen()) {
		//		if (da >= jyunban.size() - 1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
		//			if (tekip->tekiheiflag[No] >= 1) {
		//				da++;
		//			}
		//			else {
		//				takikennsau();
		//			}
		//		}
		//		else {
		//			da++;
		//		}
		//	}
		//	float h = 9999999999999.0f;
		//	for (int i = 0; i < 10; i++) {
		//		if (tekip->tekiheiflag[i] >= 1) {
		//			float max = GetKyori(m_position, tekip->tekipos[i]);
		//			if (max < REACH) {//�����ɋ߂Â�����
		//				BattleFlag = true;//�퓬���J�n����B
		//				if (h > max) {
		//					No = i;
		//					h = max;
		//				}
		//			}
		//		}
		//	}
		//}
		//if (BattleFlag == true) {//�퓬��ԂȂ�
		//	CVector3 bekutor = tekip->tekipos[No] - m_position;
		//	float len = GetKyori(m_position, tekip->tekipos[No]);
		//	float angle = VectorAngleDeg(bekutor);
		//	if (angle >= 3.0) {
		//		bekutor.y = 0.0f;
		//		bekutor.Normalize();
		//		//��]�������߂�B
		//		CVector3 rotAxis;
		//		rotAxis.Cross(m_forward, bekutor);
		//		rotAxis.Normalize();
		//		CQuaternion qBias1;
		//		qBias1.SetRotationDeg(rotAxis, 5.0f);
		//		m_rotation.Multiply(qBias1);
		//	}
		//	else if (150 < len) {
		//		m_movespeed = m_forward * (m_speed + mobe);
		//		m_movespeed.y += gravity;
		//		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
		//	}
		//	else {
		//		//����
		//		tekip->tekiHP[No] = tekip->tekiHP[No] - 5;
		//		//�����ɍU������B
		//		takikennsau();
		//		BattleFlag = false;
		//	}
		//}

		//if () {//������|������
		//	//�u�퓬���I�������v�Ƃ����t���O�����Ă�B
		//	BattleFlag = false;
		//}
	}
	
}
float AI::takikennsau()
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
	}
	return min;
}
void AI::NPCFade_Out()//��ʎs�����ޏꂷ��Ƃ��̏����B
{
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());
	m_movespeed = m_forward*(work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//�ړ�
	if (150.0f > work->Getlen()) {
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
float AI::VectorAngleDeg(CVector3 c)
{
	c.y = 0.0f;
	c.Normalize();//����Vector�ɂ���B
	float kaku = acosf(c.Dot(m_forward));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)

	float degree =CMath::RadToDeg(kaku);

	return degree;
}
float AI::VectorAngleDeg(CVector3 h,CVector3 c)
{
	c.y = 0.0f;
	c.Normalize();//����Vector�ɂ���B
	h.y = 0.0f;
	h.Normalize();
	float kaku = acosf(c.Dot(h));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)

	float degree = CMath::RadToDeg(kaku);

	return degree;
}
void AI::NPC_Search_Zonbi() //�S�Ẵ]���r�Ƌ����Ń_���[�W���������B
{
	AIrest++;
	if (Chasefrag <= 0) {
		for (; AIrest != Humans.end(); AIrest++) {
			if (this != (AI*)AIrest[0]) {
				AI* ai = (AI*)AIrest[0];
				float kyori = GetKyori(this->m_position, ai->m_position);
				if (kyori < 800) {
					float angle = VectorAngleDeg(ai->m_position - this->m_position);
					if (angle <= 60)
					{
						if (ai->GetZonbi() == true) {
							keikai_f = true;
							lam = ai;
							nearestpas();
							pa = Escape_NPC;
							m_speed = 3.0f;
							retu_position = m_position;
						}
					}
				}
				else {
					//�s�����m�̊m�F
				}
			}
		}
	}
	if (keikai_f==true) {
		for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
			if (this != (AI*)AIrest[0]) {
				AI* ai = (AI*)AIrest[0];
				if (ai->GetZonbi() != true) {
					if (1000.0 >= (ai->m_position - this->m_position).Length())
					{
						mikata++;
						mikatalest.push_back(ai);
					}
				}
			}
		}
		if (mikata >= 2) {
			Chasefrag = 1;
			pa = Chase;
			keikai_f = false;
			retu_position = m_position;
			for (int k = 0; k < mikatalest.size(); k++) {
				m_speed = 4.0f;
				mikatalest[k]->Chasefrag += 1;
				mikatalest[k]->retu_position = mikatalest[k]->m_position;
				mikatalest[k]->pa = Chase;
				mikatalest[k]->keikai_f = false;
				mikatalest[k]->lam = this->lam;
			}
		}
		mikatalest.clear();
		mikata = 0;
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
	if (pl->GetattackF() >= 1) {
		if ((pl->Getposition() - m_position).Length() <= 100.0f) {
			m_speed = 0.0;
			NPCHP -= 1000.0f;
			HitFlag = false;
		}
	}
}
void AI::NPCDeath()//���S�A���ŏ����B
{
	static int fureme = 0;
	if (Leftfrag <= 0) {
		game->SatRSaizon(iNo);
	}
	else {
		game->SatLSaizon(iNo);
	}
	if (fureme++ >= 30) {
		DeleteGO(this);//���ȏ��ŁB
	}
}

void AI::AI_Animation()//AI�̃A�j���[�V��������
{
	/*if (m_speed <= 1.0) {
		Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
		Loop_Run_Animation();
	}*/
	if (GetZonbi()==false) {
		if (HitFlag == true)
		{
				NPC_Attack_Animation();
			
		}else if (m_speed < 0.5f) {
			Idle_Animation();
		}
		else if (m_speed <= 1.0) {
			Loop_Walk_Animation();
		}
		else if (m_speed > 1.0) {
			Loop_Run_Animation();
		}

	}
	else {
		if (HitFlag == true)
		{
				NPC_Attack_Animation();
		}
		else if (m_speed >= 1.0f) {
			Zombie_Walk_Animation();
		}
	}
}

//void AI::Resistance_Animation()//�L�����N�^�[����R���Ă��鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Resistance);
//}
//
void AI::NPC_Attack_Animation()//�]���r���L�����N�^�[���U�����Ă��鎞�̃A�j���[�V�����̏����B
{
	ai_NPCAnimation.Play(shiminattack, 0.2);
}


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
	if (GetZonbi() == false) { //�������]���r�ł͂Ȃ�������
		if (muteki_Flag == false) {//���G�ł͂Ȃ�������
			if (Raifu_f == false) {
				NPC_Search_Zonbi(); //�]���r�Ƃ̓����蔻����Ƃ�B
			}
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonY))
		{
			pa = Zonbie_Gathered;
		}
	}

	if (muteki_Flag == true) {
		muteki_count++;
		/*CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisY, 10.0f);
		m_rotation.Multiply(qBias1);*/
		//kannkaku = true;
		if (muteki_count > 30) {//���G�����Ă���300�t���[�����o�߂�����
			muteki_Flag = false;
			muteki_count = 0;
		}
	}
	else {
		if (NPCHP != NPCMAXHP) {
			muteki_Flag = true;
			NPCMAXHP = NPCHP;
		}
	}

	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			car* ai = (car*)go;
			CVector3 kyori1 = ai->Getposition() - this->m_position;//�����Ƃ̋��������߂�B
			float f = kyori1.Length();
			if (f <= 1000000) { //�������Ԋԋ��������Z���Ȃ��Ă�����
				float kaku = acosf(kyori1.Dot(ai->Getforward()));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)
				float degree = CMath::RadToDeg(kaku);
				if (degree <= 90) {
					nearestpas();
					m_movespeed.y = 1000.0f;
					pa = flyNPC;
				}
			}
		}

	});
	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//���ꕔ�����o��������A
		ForceFlag = true;//�o���t���O�𗧂Ă�B
		if (GetZonbi() == true) {//�������]���r��������
			tekip = FindGO<tekihei>("tekihei");
			takikennsau(); //�p�^�[�����]���r�A�^�b�N�ɐ؂�ւ���B
		}
		else {//�����A�������]���r�ł͂Ȃ�������
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
			da = 0;
			m_speed = 4.0f;
			work->Setkakudo(3.0f);
			pa = Fade_Out; //�p�^�[�����t�F�[�h�A�E�g�ɐ؂�ւ���B
		}
	}
	if (NPCHP <= 0.0&&Raifu_f==false) {//�g�o���Ȃ��Ȃ��Ă��܂�����
		Raifu_f = true;							//����ł��܂��Ƃ͂Ȃ����Ȃ��I�I
		if (GetZonbi() == false) {				//�]���r�ł͂Ȃ��Ȃ�
			pa = Resistance_NPC;				//������x�`�����X����낤�I�I�I�I
			escapecaku = 30.0f;
			m_speed = 0.0f;
			HitFlag = false;
		}
		else {
			NPCHP = 10.0f;//�]���r�Ȃ�......
			pa = Death;
		}
	//	kannkaku = true;
		//DeleteGO(this);
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
		case flyNPC:
			FlyNPC();
			break;
		case Fade_Out:
			NPCNormal_Search();
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
		case Zonbie_Gathered:
			Gathered();
			break;
		case Zombie_Normal:
			Zonbesiya();
			if (kannkaku != true) {
				NPCZombie_Normal();
			}
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
					kyori1 /= 5.0f;
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
void AI::FlyNPC()
{
	work->kyorikeisan(mokuhyou - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	CQuaternion kak;
	kak.SetRotationDeg(CVector3::AxisX, 30.0f);
	m_rotation.Multiply(kak);
	m_movespeed+=work->Getbekutor();
	CharaConUpdate();
	if (m_position.y <= 0.0f) {
		pa = Zombie_Normal;
	}
}
void AI::CharaConUpdate()
{
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
}
void AI::Gathered()                       //��l�̂Ƃ���ɂ������`�`�`
{
	jyunban.erase(jyunban.begin(), jyunban.end());
	keiro.tansa(m_position, pl->Getposition(), &jyunban, Leftfrag);
	
	pa = Zombie_Return;
}
void AI::NPCzombie_Return()               //�ړI�n�ɂ����񂾁`�`�`
{
	NPCReturn();

	if (Tansaku != nullptr) {
		pa = Zombie_Chase;					//�l�����`�`�`�`�i�l���������j
	}
	if (pa == Normal) {
		nearestpas();
		m_speed = 1.2;
		pa = Zombie_Normal;					//�����`�`�`�i�����_���p�j�J�n�j
	}
}
void AI::NPCRunangle(CVector3 kyori)//�����x�N�g�������̂܂܎g�����ړ��̍ۂ́A��]�֐�
{
	kyori.y = 0.0f;
	float angle = VectorAngleDeg(kyori);
	kyori.Normalize();//���K�����Č����x�N�g���ɂ���B
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, kyori);
	rotAxis.Normalize();
	CQuaternion qBias1;
	if (angle >= 30) {
		escapecaku = 30.0f;
	}
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
void AI::pasmove()
{
	work->kyorikeisan(mokuhyou - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
}
void AI::Fardist_path(CVector3 m_position)//����t�������N��p�X����
{
	CVector3 minkore = { 0.0f,0.0f,0.0f };
	for (int Linknum = 0; Linknum < game->pasu[Leftfrag].GetresutoSaiz(mokuhyouNo); Linknum++) {
		CVector3 ma = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[Linknum] - m_position;
		if (minkore.Length() < ma.Length()) {
			if (90 <= VectorAngleDeg(ma, m_position - this->m_position)) {
				minkore = ma;
				mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[Linknum];
			}
		}
	}
	Retrieval_pasNo(mokuhyou);
}
void AI::hinannpas(CVector3 m_position)
{
	pasmove();
	NPCRunangle(work->Getbekutor());
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - this->m_position).Length() < 200.0f) {
		Fardist_path(m_position);
	}
}
void AI::NPCescape()//�]���r���瓦����
{
	CVector3 v = m_position - pl->Getposition();
	v.y = 0.0f;
	float len = v.Length();//����
	if (len < 10000.0) {
		hinannpas(pl->Getposition());
	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());     //�����؂������`�`�`�`
		keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
		m_speed = 4.0f;
		escapecaku = 30.0f;
		mobe = 50.0f;
		Gaizi->Satpoint(0.1);
		work->Setkakudo(5.0f);
		kaiten = false;
		pa = Fade_Out;										//����Ȓ�......����������΂��I�I
	}
	//CVector3 v = m_position - pl->GetPosition();
	//float len = v.Length();//����
	//if (len < 2000.0) {
	//	NPCRunangle(v);							
	//	//m_position += v * m_speed;
	//	v.y = 0.0f;
	//	v.Normalize();			//�Ɂ`����񂾂�`�`�`�`
	//	m_movespeed = v * (150*m_speed +mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
	//}


}
void AI::NPCEscape_NPC()
{
	CVector3 j = this->m_position - lam->m_position;
	if (j.Length() >= 3000) {
		jyunban.erase(jyunban.begin(), jyunban.end());				//�����]���r���Ȃ����I�I�I
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		escapecaku = 30.0f;											//���̈ʒu�ɁA���`�`�ǂ�
		pa = Return;
	}
	else {
		hinannpas(lam->m_position);
		//1�l�ł͐킦�Ȃ��I�I�I//�Ɂ`����񂾂�`�`�`�`
	}
}
void AI::search()
{
	jyunban.erase(jyunban.begin(), jyunban.end());     //�����؂������`�`�`�`
	keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
}
void AI::Retrieval_pasNo(int mokuhyou)
{
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
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
