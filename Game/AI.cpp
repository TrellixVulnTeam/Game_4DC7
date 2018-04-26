#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#define REACH 100.0  //�]���r�̍U���͈́B���̋����܂ŋ߂Â�����U������B
#define PI 3.141592653589793 
AI NPC;
//�����m�����p����NPC�̃n���h���Ƃ��āAj����ꕔ���̃n���h���Ƃ��đ�p����B����͌�ɒ����Ă����悤�ɁB
//NPC��NPC�]���r�̗�������������B
AI::AI()
{
	pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_speed = 1000.0f; //�m�[�}����Ԃ̂Ƃ��̈ړ����x�B
}


AI::~AI()
{
}
bool AI::Start()
{
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	game=FindGO<Game>("Game");
	iNo = game->No++;
	m_position= game->pasu.m_pointList[game->da[iNo][0] - 1];
	m_position.y = 0.0f;
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	m_charaCon.Init(
		20.0,			//���a�B 
		100.0f,			//�����B
		m_position		//�����ʒu�B
	);
	game->siminUI[iNo]->kyorikeisan(game->da[iNo][1] - 1);
	SetTags(10);
	return true;
}
void AI::NPCNormal()
{

	CVector3 v = game->siminUI[iNo]->K - m_position; //K�����̖ړI�n
	float len = v.Length();//����
	if (50 <= len) {
		if (VectorAngleDeg2(v)>=10.0) {
			CQuaternion qBias1;
			qBias1.SetRotationDeg(CVector3::AxisY, 5.0f);
			m_rotation.Multiply(qBias1);
		}
		else if (VectorAngleDeg2(v) <= -10.0)
		{
			CQuaternion qBias1;
			qBias1.SetRotationDeg(CVector3::AxisY, -5.0f);
			m_rotation.Multiply(qBias1);
		}
		else {
			//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
			m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), game->siminUI[iNo]->bekutor*m_speed);
		}
	}
	else {
		if (ima >= 6)//���̃|�W�V������6�Ȃ�
			//0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
			ima = 0;
		game->siminUI[iNo]->kyorikeisan(game->da[iNo][ima++] - 1);
	}
	CVector3 v2 = pl->m_position-m_position;
	float len1 = v2.Length();//����

	if (len1 < 500.0f) {//�v���C���[����������
		if (fabsf(VectorAngleDeg(v2)) <= 45.0f) {
			Gaizi->point += 0.1f;
			pa = Escape;
			retu_position = m_position;
			m_speed = 3000.0f;
			//DamageFlag = true;
			//�v���C���[���瓦����B
		}
	}

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
}

void AI::NPCDamage()
{
	if (DamageFlag == true) {//�v���C���[����̍U�����󂯂���
		static int i = 0; //30�t���[�����J�E���g����B
		if (i >= 30) {
			//30�t���[���o�߂�����]���r���B
			pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
			m_movespeed = { 0.5f, 0.0f, 0.0f }; //�]���r�m�[�}����Ԃ̂Ƃ��̈ړ����x�ɕς���B
			Zonbe = 1;
			DamageFlag = false;
		}
		else {
			i++; //1�t���[���o�߂��J�E���g����B
		}
		
	}

}

//void AI::NPCEscape_NPC() //NPC����̓���
//{
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
//}

void AI::NPCZombie_Normal()
{
	/////////////////////////////////
	//���̃��[�g�����낤�낷�鏈���B
	/////////////////////////////////
	float min_Nagasa = 9999.0f;
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			AI* ai = (AI*)go;
			if (ai->Zonbe == 0) {   //���ꂪ��ʎs����������
				float kyori = GetKyori(this->m_position, ai->m_position);//�����Ƃ̋��������߂�B
				if (kyori < 60.0f) {  //���������E�͈͈ȓ���������
					float angle = VectorAngleDeg(ai->m_position); //�����Ώۂ̍��W�������ɂ���B
					if (angle <= 45.0f&&angle >= -45.0f) { //�p�x�����E����������
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
	//float len = GetKyori(m_position, m->m_position);
	//if (len>80.0f||HitFlag == true) {//����NPC����������(������80�ȏ゠����)�A���邢�͍U����^������
	//	//���̈ʒu�ɖ߂�B

	//	if (ZombieChaseNumber = MyNumber) {//���̈ʒu�̔ԍ��ɖ߂�����
	//		pa = Zombie_Normal; //�p�^�[�����]���r�m�[�}���ɕς���B
	//		HitFlag == false;
	//	}
	//}
		//else {
		//	/////////////////////////////////
		//	//�s��NPC��ǐՂ��鏈���B
		//	/////////////////////////////////
		//}
	//if (len<REACH) {//NPC�ɒǂ�������
	//	//�U������(�m���ɓ�����d�l)�B

	//		HitFlag = true; //�uNPC�ɍU���𓖂Ă��v�Ƃ����t���O�����Ă�B
	//	}
	
}

void AI::NPCZombie_Attack()//vs���ꕔ��
{
	//if (BattleFlag == false) {//�����Ɛ���Ă��炸�A�t���[�ȏ�ԂȂ�
	//	//��ԋ߂������Ɉړ�����B
	//	float len = GetKyori(m_position,j->m_position );
	//	if (len<REACH) {//�����ɋ߂Â�����
	//		BattleFlag == true;//�퓬���J�n����B
	//	}
	//}

	if (BattleFlag == true) {//�퓬��ԂȂ�
     	 //�����ɍU������B
	}

	//if () {//������|������
	//	//�u�퓬���I�������v�Ƃ����t���O�����Ă�B
	//	BattleFlag = false;
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

	float degree = CMath::RadToDeg(kaku);

	return degree;
}

float AI::VectorAngleDeg(CVector3 c)
{
	

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
					pa = Damage; //�p�^�[�����_���[�W�ɂ�����B
				}
			}
		}
	});

	Player* pl = FindGO<Player>("Player");
	float kyori = GetKyori(this->m_position, pl->m_position);//�����Ƃ̋��������߂�B
	if (kyori < REACH) {  //�������U���͈͈ȓ���������
		pa = Damage; //�p�^�[�����_���[�W�ɂ�����B
	}
}
void AI::Update()
{
	//pa = Normal; //�����̓v���C���[�̍s���ɂ���ĕω�����悤�ɂ���B
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	k_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_rite.x = k_tekirot.m[0][0];
	m_rite.y = k_tekirot.m[0][1];
	m_rite.z = k_tekirot.m[0][2];
	m_rite.Normalize();

	if (ForceFlag==true) {//���ꕔ�����o��������
		pa = Zombie_Attack; //�p�^�[�����]���r�A�^�b�N�ɐ؂�ւ���B
	}

	CQuaternion qBias;
	qBias = rotation(270);

	switch (pa) {
	case Normal:
		//NPC�̓����������B
		NPCNormal();
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
	case Damage:
		NPCDamage();
		break;
	case Zombie_Normal:
		//NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//����NPC�����������̏����������B
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	default:
		NPCZombie_Normal();
		break;
	}

	if (Zonbe == 0) { //�������]���r�ł͂Ȃ�������
		DamageHantei(); //�]���r�Ƃ̓����蔻����Ƃ�B
	}
	
	//Muve(m_movespeed);//���[���X�s�[�h�����Ɠ���
	//m_movespeed.x += 0.001;
	// //qRot��]�ƃL�����̉�]����Z���č�������B
	//qBias.Multiply(m_rotation, qBias);

	//NPC�̑O�������v�Z

	//mRot.MakeRotationFromQuaternion(m_rotation);
	//m_forward.x = mRot.m[2][0];
	//m_forward.y = mRot.m[2][1];
	//m_forward.z = mRot.m[2][2];
	//m_forward.Normalize();
	//m_rite.x = mRot.m[0][0];
	//m_rite.y = mRot.m[0][1];
	//m_rite.z = mRot.m[0][2];
	//m_rite.Normalize();
	//m_position += m_forward *  m_speed;
	//m_position += m_rite * 10 * m_speed;		
	//CVector3 k = { 8881.04883
	//		,- 221.356491
	//		,9464.60547 };
	//	CVector3 b = {
	//		4190.29980
	//		,- 221.356491
	//		,4564.60596 };
	//	keiro=NewGO<keiroK>(0);

	//	keiro->tansa(k, b);
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::NPCReturn()
{
	int Size= jyunban.size();

	CVector3 v = game->siminUI[iNo]->K - m_position;
	float len = v.Length();//����
	if (50 <= len) {
		//m_position += game->siminUI[iNo]->bekutor*m_speed;
		m_position=	m_charaCon.Execute(GameTime().GetFrameDeltaTime(), (game->siminUI[iNo]->bekutor)*m_speed);
	}
	else {
		if (da >= Size) {//���̈ʒu�ɂ��ǂ���
			ima--;
			pa = Normal;//�p�^�[�����m�[�}���ɂ�����B
			da = 1;
		}
		else {
			game->siminUI[iNo]->kyorikeisan(jyunban[da++] - 1);
			modori = 0;
		}
	}
}
void AI::NPCescape()
{

	CVector3 v = m_position - pl->m_position;
	float len = v.Length();//����
	if (len < 1000.0) {
		v.Normalize();//���K�����Č����x�N�g���ɂ���B
		v.y = 0.0f;
		//m_position += v * m_speed;
		m_position =m_charaCon.Execute(GameTime().GetFrameDeltaTime(),v*m_speed);
	}

	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position,&jyunban);
		game->siminUI[iNo]->kyorikeisan(jyunban[0]-1);
		pa = Return;
		m_speed = 1000.0f;
	}
}

void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
