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
void AI::NPCZombie_Normal()
{
	//	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	//	m_rotation.Multiply(work->Getkaku());//��]
	//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�
	pasmove(mokuhyou);
	m_rotation.Multiply(work->Getkaku());//��]
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {//�����_���p�j�̃p�X�ԍ�����
		int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
		mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num];
		Retrieval_pasNo(mokuhyou);
	}
	if (Tansaku != nullptr) {
		search(Tansaku->m_position);
		mokuhyou=jyunban[0];
		Retrieval_pasNo(mokuhyou);
		pa = Zombie_Chase; //�p�^�[�����]���r�`�F�C�X�ɕς���B
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
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len > 2100.0f || Tansaku->Raifu_f == true) {//����NPC����������(������2100�ȏ゠����)�A���邢�͎��񂾂�
													//���̈ʒu�ɖ߂�B
		search(retu_position);
		Tansaku = nullptr; //�������ʂ�����������B
		kaiten = false;
		angle = 0;
		HitFlag = false;
		nearestpas();
		pa = Zombie_Normal;
	}
	else {//NPC���������Ă��炸�A�����Ă�����
		CVector3 n = Tansaku->m_position- m_position;
		float kou = VectorAngleDeg((Tansaku->m_forward), n);
		NPCRunangle(n);
		if (n.Length()>=2000.0f)
		{
			Chasepas(Tansaku->m_position);
		}
		else if (kou <= 120) {
			if (len < atakkukyori) {//NPC�ɒǂ�������
									//�U������(�m���ɓ�����d�l)�B
				HitFlag = true;//�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
				if (Tansaku->muteki_Flag == false) {
					Tansaku->NPCHP -= 40.0f;
				}
				atakkukyori = 200.0f;
				//NPC_Attack_Animation();//�U���A�j���[�V�����𗬂��B
			}
			else {
				HitFlag = false;
				n.y = 0.0f;
				n.Normalize();
				NPCRunangle(n);
				m_movespeed = n * (m_speed*200.0 + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//�ړ�

				//Chasepas(Tansaku->m_position);
				atakkukyori = 100.0f;
				/////////////////////////////////
				//�s��NPC��ǐՂ��鏈���B
				/////////////////////////////////
			}
		}
		else {
			Pboneforward = Tansaku->m_forward;
			CVector3 rotAxis;
			rotAxis.Cross(this->m_forward, Pboneforward);
			rotAxis.Normalize();
			angle = 3.0f;
			n.Normalize();
			Crot.SetRotationDeg(rotAxis, angle);
			Crot.Multiply(n);
			CVector3 Destination = (n * len) + Tansaku->m_position;
			Destination = Destination - m_position;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), Destination);

			/*	Pboneforward = Tansaku->m_forward;
				CVector3 rotAxis;
				rotAxis.Cross(this->m_forward, Pboneforward);
				rotAxis.Normalize();
				angle += 3.0f;
				Crot.SetRotationDeg(rotAxis, angle);
				Crot.Multiply(Pboneforward);
				CVector3 baka = (Pboneforward * len) + Tansaku->m_position;
				baka = baka - m_position;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), baka);*/
		}

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
			kannkaku = true;
			CVector3 n = tekip->tamapos[No] - m_position;
			NPCRunangle(n);
			if (len < atakkukyori) {//NPC�ɒǂ�������
									//�U������(�m���ɓ�����d�l)�B
				HitFlag = true;//�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
				if (flame >= 40) {
					tekip->tekiHP[No] -= 3;
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