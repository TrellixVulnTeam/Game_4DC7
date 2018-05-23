#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#define REACH 300.0  //�]���r�̍U���͈́B���̋����܂ŋ߂Â�����U������B
#define PI 3.141592653589793 
//AI NPC;
//�����m�����p����NPC�̃n���h���Ƃ��āAj����ꕔ���̃n���h���Ƃ��đ�p����B����͌�ɒ����Ă����悤�ɁB
//NPC��NPC�]���r�̗�������������B
AI::AI()
{
	pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_speed = 1.0f; //�m�[�}����Ԃ̂Ƃ��̏�ɓ����ړ����x�i��{1�j�B
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
	game=FindGO<Game>("Game");
	tekip = FindGO<tekihei>("tekihei");
	iNo = game->incNo();
	m_position= game->pasu.m_pointList[game->da[iNo][0] - 1];
	m_position.y = 0.0f;
	//�L�����̃X�L�����f���̃��[�h�͊e���T�u�N���X�ōs���B
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	A_charaCon.Init(
		50.0,			//���a�B 
		100.0f,			//�����B
		m_position,		//�����ʒu�B
		0
	);

	////�A�j���[�V�����̏������B
	//ai_NPCAnimation.Init(
	//	m_skinModel,			//�A�j���[�V�����𗬂��X�L�����f���B
	//								//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
	//	ai_NPCAnimationClips,	//�A�j���[�V�����N���b�v�̔z��B
	//	6							//�A�j���[�V�����N���b�v�̐��B
	//);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();

	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->pasu.m_pointList[game->da[iNo][1] - 1]));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);
	if (game->GatNo() >= 4) {
		game->risetteNo();
	}
	return true;
}
void AI::NPCNormal()
{

	//CVector3 v = game->siminUI[iNo]->K - m_position; //K�����̖ړI�n
	//float len = v.Length();//����
	//if (30 <= len) {
	//	float angle = VectorAngleDeg(v);
	//	if (angle >= 3.0) {
	//		v.y = 0.0f;
	//		v.Normalize();
	//		CVector3 forward = this->m_forward;
	//		//��]�������߂�B
	//		CVector3 rotAxis;
	//		rotAxis.Cross(forward, v);
	//		rotAxis.Normalize();
	//		CQuaternion qBias1;
	//		qBias1.SetRotationDeg(rotAxis, 3.0f);
	//		m_rotation.Multiply(qBias1);
	//	}
	//	else {
	//	//	//if (angle >= 2.0f) {
	//	//	//	v.y = 0.0f;
	//	//	//	v.Normalize();
	//	//	//	CVector3 forward = this->m_forward;
	//	//	//	//��]�������߂�B
	//	//	//	CVector3 rotAxis;
	//	//	//	rotAxis.Cross(forward, v);
	//	//	//	rotAxis.Normalize();
	//	//	//	CQuaternion qBias1;
	//	//	//	qBias1.SetRotationDeg(rotAxis, angle);
	//	//	//	m_rotation.Multiply(qBias1);
	//	//	//}
	//	//	//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
	//	//	
	work->kyorikeisan(game->da[iNo][ima] - 1, m_position, m_forward,game->pasu.m_pointList);
	m_rotation.Multiply(work->Gatkaku());//��]
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*(work->Gatmuve()*m_speed));//�ړ�
	if (15.0f > work->Gatlen()) {
		if (ima >= 10) {//���̃|�W�V������6�Ȃ�
					  //0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
			ima = 0;
		}
		else {
			ima++;
		}
	}

	//FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//	if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
	//		AI* ai = (AI*)go;
	//		if (ai->Zonbe == 0) {  //���ꂪ�]���r�łȂ�������
	//			CVector3 kyori1 =   ai->m_position - this->m_position;//�����Ƃ̋��������߂�B
	//			float f = kyori1.Length();
	//			if (Siya(kyori1, f)) { //�������U���͈͈ȓ���������

	//				CQuaternion qBias1;
	//				qBias1.SetRotationDeg(CVector3::AxisY, 3.0f);
	//				m_rotation.Multiply(qBias1);

	//			}
	//		}
	//	}

	//});
	//if (len1 < 500.0f) {//�v���C���[����������
	//	if (fabsf(VectorAngleDeg(v2)) <= 45.0f) {
	//		Gaizi->point += 0.1f;
	//		pa = Escape;
	//		retu_position = m_position;
	//		m_speed = 3000.0f;
	//		//DamageFlag = true;
	//		//�v���C���[���瓦����B
	//	}
	//}
	//	/////////////////////////////////
	//	//���̃��[�g�����낤�낷�鏈���B
	//	/////////////////////////////////
	//
	//	FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
	//			AI* ai = (AI*)go;
	//			if (ai->Zonbe == 1) {                                        //���ꂪ�]���r��������
	//				float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
	//				if (kyori < 60.0f) {                                     //���������E�͈͈ȓ���������
	//					float angle = VectorAngleDeg(ai->m_position);        //�����Ώۂ̍��W�������ɂ���B
	//					if (angle <= 45.0f&&angle >= -45.0f) {                //�p�x�����E����������
	//																		  //�]���r���瓦����B
	//						muki.x = m_forward.x*(-1);
	//						muki.y = m_forward.y*(-1);
	//						muki.z = m_forward.z*(-1);//���΂̌����Ɍ����B
	//						pa = Escape_NPC;
	//						NPCEscapeNumber = MyNumber;
	//						Chase_Zombie = ai;   //NPC����̓����֐��Ɏg���B
	//					}
	//				}
	//			}
	//		}
	//
	//	});
	//	Player* pl = FindGO<Player>("Player");
	//	CVector3 v = m_position - pl->m_position;
	//	float len = v.Length();//����
	//	if (len < 60.0f) {//�v���C���[����������
	//		float angle = VectorAngleDeg(pl->m_position); //�����Ώۂ̍��W�������ɂ���B
	//		if (angle <= 45.0f&&angle >= -45.0f) { //�p�x�����E����������
	//											   //�v���C���[���瓦����B
	//
	//			muki.x = m_forward.x*(-1);
	//			muki.y = m_forward.y*(-1);
	//			muki.z = m_forward.z*(-1);
	//			NPCEscapeNumber = MyNumber;
	//			pa = Escape_Player;
	//		}
	//	}
	//	//if (len < REACH) {//�U�����󂯂�͈͂܂ŋ߂Â�����m���Ƀ_���[�W���󂯂�̂�
	//	//	DamageFlag = true;//�_���[�W�t���O��true�ɂ���B
	//	//}
	//	//if (DamageFlag == true) {//�v���C���[����̍U�����󂯂���
	//	//	static int i = 0; //30�t���[�����J�E���g����B
	//	//	if (i >= 30) {
	//	//		pa = Damage;//30�t���[���o�߂�����p�^�[�����_���[�W�ɕς���B
	//	//	}
	//	//	else {
	//	//		i++; //1�t���[���o�߂��J�E���g����B
	//	//	}
	//	//	
	//	//}
}
void AI::NPCNormal_Search()//NPC�̌x�������B
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//����
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.1);
		m_speed = 1.5f;
		pa = Escape;
	}
}

void AI::NPCResistance_NPC()//NPC�]���r�ւ̒�R�Ɋւ��鏈���B�I�[�o�[���C�h������B
{
	pa = Damage;
}

void AI::NPCResistance_Player()//�v���C���[�ւ̒�R�Ɋւ��鏈���B�I�[�o�[���C�h������B
{
	pa = Damage;
}

void AI::NPCDamage()
{
	static int i = 0; //30�t���[�����J�E���g����B
	if (i >= 30) {
		//30�t���[���o�߂�����]���r���B
		pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
		m_speed = 1.5;
		Zonbe = 1;
	}
	else {
		i++; //1�t���[���o�߂��J�E���g����B
	}

}
//void AI::NPCEscape_NPC() //NPC����̓�
//	static bool LostFlag = false;  //�����������ǂ����������t���O�B
//								   ///////////////////
//								   //�����Ɋւ��鏈���B
//								   ///////////////////
//
//	float len = GetKyori(this->m_position, Chase_Zombie->m_position);
//	if (len >= 60) { //������60�ȏ�󂢂���
//		LostFlag = true;
//	}
//	if (LostFlag == true) { //����������
//
//							/////////////////////
//							//���̈ʒu�ɖ߂鏈���B
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//���̈ʒu�̔ԍ��ɖ߂�����
//			pa = Normal; //�p�^�[�����m�[�}���ɕς���B
//			LostFlag = false;//�t���O�����ɖ߂��B
//		}
//
//	}
//}
//void AI::NPCEscape_Player() //�v���C���[����̓���
//{
//	///////////////////
//	//�����Ɋւ��鏈���B
//	///////////////////
//
//	static bool LostFlag = false;  //�����������ǂ����������t���O�B
//	Player* pl = FindGO<Player>("Player");
//	float len = GetKyori(this->m_position, pl->m_position);
//	if (len >= 120) { //������120�ȏ�󂢂���
//		LostFlag = true; //NPC�̓v���C���[���������B
//	}
//	if (LostFlag == true) { //����������
//
//							/////////////////////
//							//���̈ʒu�ɖ߂鏈���B
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//���̈ʒu�̔ԍ��ɖ߂�����
//			pa = Normal; //�p�^�[�����m�[�}���ɕς���B
//			LostFlag = false;//�t���O�����ɖ߂��B
//		}
//
//	}
void AI::NPCZombie_Normal()
{
	//CVector3 v = game->siminUI[iNo]->K - m_position; //K�����̖ړI�n
	//float len = v.Length();//����
	//if (30 <= len) {
	//	float angle = VectorAngleDeg(v);
	//	if (angle >= 3.0) {
	//		v.y = 0.0f;
	//		v.Normalize();
	//		CVector3 forward = this->m_forward;
	//		//��]�������߂�B
	//		CVector3 rotAxis;
	//		rotAxis.Cross(forward, v);
	//		rotAxis.Normalize();
	//		CQuaternion qBias1;
	//		qBias1.SetRotationDeg(rotAxis, 3.0f);
	//		m_rotation.Multiply(qBias1);
	//	}
	//	else {
	//		if (angle >= 2.0f) {
	//			v.y = 0.0f;
	//			v.Normalize();
	//			CVector3 forward = this->m_forward;
	//			//��]�������߂�B
	//			CVector3 rotAxis;
	//			rotAxis.Cross(forward, v);
	//			rotAxis.Normalize();
	//			CQuaternion qBias1;
	//			qBias1.SetRotationDeg(rotAxis, angle);
	//			m_rotation.Multiply(qBias1);
	//		}
	//		//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
	//		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);//�ړ��B
	//	}
	//}
	//else {
	//	if (ima >= 6)//���̃|�W�V������6�Ȃ�
	//				 //0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
	//		ima = 0;
	//	game->siminUI[iNo]->kyorikeisan(game->da[iNo][ima++] - 1);
	//}
	///////////////////////////////////
	////���̃��[�g�����낤�낷�鏈���B
	///////////////////////////////////
	NPCNormal();
	float min_Nagasa = 9999.0f;
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			AI* ai = (AI*)go;
			if (ai->Zonbe == 0) {   //���ꂪ��ʎs����������
				float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
				if (kyori < 60.0f) {  //���������E�͈͈ȓ���������
					float angle = VectorAngleDeg(ai->m_position); //�����Ώۂ̍��W�������ɂ���B
					if (angle <= 45.0f) { //�p�x�����E����������
						if (kyori < min_Nagasa) { //�����Ɉ�ԋ߂��̂Ȃ�
							min_Nagasa = kyori;
							Tansaku = ai;
						}
					}
				}
			}
		}
	});

	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //�p�^�[�����]���r�`�F�C�X�ɕς���B
	}
}
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len>80.0f||HitFlag == true) {//����NPC����������(������80�ȏ゠����)�A���邢�͍U����^������
		//���̈ʒu�ɖ߂�B
		if (ZombieChaseNumber == MyNumber) {//���̈ʒu�̔ԍ��ɖ߂�����
			Tansaku = nullptr; //�������ʂ�����������B
			pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
			HitFlag = false;
		}
	}else {//NPC���������Ă��炸�A�����Ă�����
		CVector3 n = m_position - Tansaku->m_position;
		n.Normalize();
		n.y = 0.0f;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), n*m_speed);
			/////////////////////////////////
			//�s��NPC��ǐՂ��鏈���B
			/////////////////////////////////
		if (len<REACH) {//NPC�ɒǂ�������
						//�U������(�m���ɓ�����d�l)�B
			//NPC_Attack_Animation();//�U���A�j���[�V�����𗬂��B
			HitFlag = true; //�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
		}
	}	
}
void AI::NPCZombie_Attack()//vs���ꕔ��
{
	if (BattleFlag == false) {//�����Ɛ���Ă��炸�A�t���[�ȏ�ԂȂ�
		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu.m_pointList);
		m_rotation.Multiply(work->Gatkaku());
		CVector3 v = work->Gatmokuteki() - m_position;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*(work->Gatmuve()*m_speed));
		if (15.0f > work->Gatlen()) {
			if (da >= jyunban.size() - 1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
				float min = 99999999999999999.0;
				for (int i = 0; i < 10; i++) {
					if (tekip->tekiheiflag[i] >= 1) {
						float max = GetKyori(m_position, tekip->tekipos[i]);
						if (min > max) {
							min = max;
							No = i;
						}
					}
					CVector3 posa = tekip->tekipos[No] - m_position;
					jyunban.erase(jyunban.begin(), jyunban.end());
					keiro.tansa(m_position, posa, &jyunban);
					da = 0;//������x����
				}
			}
			else {
				da++;
			}
		}			  //��ԋ߂������Ɉړ�����B
		for (int i = 0; i < 10; i++) {
			float max = GetKyori(m_position, tekip->tekipos[i]);
			if (max < REACH) {//�����ɋ߂Â�����
				BattleFlag == true;//�퓬���J�n����B
				No = i;
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
			m_rotation.SetRotationDeg(rotAxis, 5.0f);
		}
		else if(15<len){
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);
		}
		else {
			//����
     	 //�����ɍU������B
			BattleFlag = false;
		}
	}

	//if () {//������|������
	//	//�u�퓬���I�������v�Ƃ����t���O�����Ă�B
	//	BattleFlag = false;
	//}
	
}
void AI::NPCFade_Out()//��ʎs�����ޏꂷ��Ƃ��̏����B
{
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu.m_pointList);
	m_rotation.Multiply(work->Gatkaku());
	CVector3 v = work->Gatmokuteki() - m_position;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*(work->Gatmuve()*m_speed));
	if (float len = v.Length() < 100.0f) {
		if (da >= jyunban.size()-1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
			pa = Death;
			da = 1;
		}
		else {
			da++;
		}
	}
	//CVector3 v = game->siminUI[iNo]->K - m_position; //K�����̖ړI�n
	//float len = v.Length();//����
	//if (100 <= len) {
	//	float angle = VectorAngleDeg(v);
	//	if (angle >= 2.0) {//10�x����Ȃ��]
	//		//�p�X�܂Ńx�N�g����XZ���ʏ�ł̌����ɂ���B
	//		v.y = 0.0f;
	//		v.Normalize();
	//		CVector3 forward = this->m_forward;
	//		//��]�������߂�B
	//		CVector3 rotAxis;
	//		rotAxis.Cross(forward, v);
	//		rotAxis.Normalize();
	//		CQuaternion qBias1;
	//		qBias1.SetRotationDeg(rotAxis, 3.0);
	//		m_rotation.Multiply(qBias1);
	//	}
	//	else {//10�x�����ł���-10�x�ȏ�Ȃ�
	//		//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
	//		//if (angle != 0) {
	//		//	v.y = 0.0f;
	//		//	v.Normalize();
	//		//	CVector3 forward = this->m_forward;
	//		//	//��]�������߂�B
	//		//	CVector3 rotAxis;
	//		//	rotAxis.Cross(forward, v);
	//		//	rotAxis.Normalize();
	//		//	CQuaternion qBias1;
	//		//	qBias1.SetRotationDeg(rotAxis, angle);
	//		//	m_rotation.Multiply(qBias1);
	//		//}
	//		m_position =A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);//�ړ��B
	//	}
	//	//}
	//	//v.Normalize();
	//	//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), v*m_speed);//�ړ�
	//}
	//else {//�p�X�ɒ�������
	//	if (da >= jyunban.size()) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
	//		pa = Death;
	//		da = 1;
	//	}
	//	else {
	//		game->siminUI[iNo]->kyorikeisan(jyunban[da++] - 1);
	//	}
	//}
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
			retu_position = m_position;
			//m_speed = 1000.0f;
			//DamageFlag = true;
			//�v���C���[���瓦����B
			return 1;
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

void AI::DamageHantei() //�S�Ẵ]���r�Ƌ����Ń_���[�W���������B
{
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			AI* ai = (AI*)go;
			if (ai->Zonbe == 1) {   //���ꂪ�]���r��������
				float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
				if (kyori < REACH) {  //�������U���͈͈ȓ���������
					pa = Resistance_NPC; //�p�^�[�����R�ɂ�����B
				}
			}
		}
	});

	float kyori = GetKyori(this->m_position, pl->GetPosition());//�����Ƃ̋��������߂�B
	if (kyori < REACH) {  //�������U���͈͈ȓ���������
		pa = Resistance_Player; //�p�^�[�����R�ɂ�����B
	}
}

void AI::NPCDeath()//���S�A���ŏ����B
{
//	DeleteGO(this);//���ȏ��ŁB
}

void AI::Animation_Walk()//�����n�߂ƕ��������̈�A�̃A�j���[�V�����̏����B
{
	static int walk_count = 0;//�����n�߂Ă���̃J�E���g
	if (work->Gatmuve()!=0) {
		//�����Ă�����
		if (walk_count<50) {
			Start_Walk_Animation();
		}
		else {
			Loop_Walk_Animation();
		}
		walk_count++;
	}
	else {//�~�܂�����
		walk_count = 0;
	}
	
}
void AI::Animation_Run()//����n�߂Ƒ��葱���̈�A�̃A�j���[�V�����̏����B
{
	static int run_count = 0;//����n�߂Ă���̃J�E���g
	if (work->Gatmuve() != 0) {
		//�����Ă�����
		if (run_count<50) {
			Start_Run_Animation();
		}
		else {
			Loop_Run_Animation();
		}
		run_count++;
	}
	else {//�~�܂�����
		run_count = 0;
	}
}

//void AI::Start_Walk_Animation()//�L�����N�^�[�������n�߂鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Start_Walk);
//}
//
//void AI::Loop_Walk_Animation()//�L�����N�^�[�����������鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Loop_Walk);
//}
//
//void AI::Start_Run_Animation()//�L�����N�^�[������n�߂鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Start_Run);
//}
//
//void AI::Loop_Run_Animation()//�L�����N�^�[�����葱���鎞�̃A�j���[�V�����̏����B
//{
//	ai_NPCAnimation.Play(Loop_Run);
//}
//
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
	//pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	k_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_rite.x = k_tekirot.m[0][0];
	m_rite.y = k_tekirot.m[0][1];
	m_rite.z = k_tekirot.m[0][2];
	m_rite.Normalize();
	
	if (muteki_Flag == true) {
		muteki_count++;
		if (muteki_count > 300) {//���G�����Ă���300�t���[�����o�߂�����
			muteki_Flag = false;
		}
	}

	if (Zonbe == 0) { //�������]���r�ł͂Ȃ�������
		if (muteki_Flag == false) {//���G�ł͂Ȃ�������
			DamageHantei(); //�]���r�Ƃ̓����蔻����Ƃ�B
		}
	}
	
	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == 0) {//���ꕔ�����o��������A
		ForceFlag = 1;//�o���t���O�𗧂Ă�B
		if (Zonbe == 1) {//�������]���r��������
			float min = 99999999999999999.0;
			int no = 0;
			for (int i = 0; i < 10; i++) {
				float max = GetKyori(m_position, tekip->tekipos[i]);
				if (min > max) {
					min= max;
					no = i;
				}
			}
			CVector3 posa = tekip->tekipos[no]-m_position;
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, posa, &jyunban);
			m_speed = 1.5;
			da = 0;
			pa = Zombie_Attack; //�p�^�[�����]���r�A�^�b�N�ɐ؂�ւ���B
		}
		else {//�����A�������]���r�ł͂Ȃ�������
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu.m_pointList[0], &jyunban);
			jyunban[0] - 1;
			da = 0;
			m_speed = 1.2;
			pa = Fade_Out; //�p�^�[�����t�F�[�h�A�E�g�ɐ؂�ւ���B
		}
	}
	if (ForceFlag == 1) {//���ꕔ�����o��������
		ForceFlag = 1;//1�񂵂����s�������Ȃ��̂Ńt���O��������B
	}

	switch (pa) {
	case Normal:
		//NPC�̓����������B
		NPCNormal();
		NPCNormal_Search();
		break;
	//case Escape_NPC:
	//	NPCEscape_NPC();
	//	break;
	//case Escape_Player:
	//	NPCEscape_Player();
	//	break;
	case Escape:
		NPCescape();
		break;
	case Return:
		NPCReturn();
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
		NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//����NPC�����������̏����������B
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	case Death:
		NPCDeath();
		break;
	default:
		NPCZombie_Normal();
		break;
	}

	if (pa != Escape) {//NPC�������Ă��Ȃ�������
		Animation_Walk();//�����A�j���[�V�����B
	}
	else {//NPC�������Ă�����
		Animation_Run();//����A�j���[�V�����B
	}

	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::NPCReturn()
{
	int Size = jyunban.size();
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu.m_pointList);
	m_rotation.Multiply(work->Gatkaku());
	CVector3 v = work->Gatmokuteki() - m_position;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*(work->Gatmuve()*m_speed));
	if (15.0f > work->Gatlen()) {
		if (da >= jyunban.size()-1) {//�w�肳�ꂽ�p�X�̍Ō�܂Œ�������
			pa = Normal;//�p�^�[�����m�[�}���ɂ�����B
			da = 1;
		}
		else {
			da++;
		}
	}
	//CVector3 v = game->siminUI[iNo]->K - m_position;
	//float len = v.Length();//����
	//if (300 <= len) {
	//	float angle = VectorAngleDeg(v);
	//	if (angle >= 2.0) {//10�x����Ȃ��]
	//		v.y = 0.0f; //�p�X�܂Ńx�N�g����XZ���ʏ�ł̌����ɂ���B
	//		v.Normalize();
	//		CVector3 forward = this->m_forward;
	//		//��]�������߂�B
	//		CVector3 rotAxis;
	//		rotAxis.Cross(forward, v);
	//		rotAxis.Normalize();
	//		CQuaternion qBias1;
	//		qBias1.SetRotationDeg(rotAxis, 3.0);
	//		m_rotation.Multiply(qBias1);
	//	}
	//	else {
	//		//m_position += game->siminUI[iNo]->bekutor*m_speed;
	//		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);
	//	}
	//}
	//else {
	//	if (da >= Size) {//���̈ʒu�ɂ��ǂ���
	//		ima--;
	//		da = 1;
	//	}
	//	else {
	//		game->siminUI[iNo]->kyorikeisan(jyunban[da++] - 1);
	//		modori = 0;
	//	}
	//}
}
void AI::NPCescape()
{

	CVector3 v = m_position - pl->GetPosition();
	float len = v.Length();//����
	if (len < 2000.0) {
		v.Normalize();//���K�����Č����x�N�g���ɂ���B
		v.y = 0.0f;
		//m_position += v * m_speed;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), v*(work->Gatmuve()*m_speed));

	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position,&jyunban);
		m_speed = 1.0;
		pa = Return;
	}
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
