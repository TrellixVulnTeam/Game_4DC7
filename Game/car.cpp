#include "stdafx.h"
#include "car.h"
#include"AImove.h"
#include"AI.h"
#include"Game.h"
#include"Geizi.h"
#include"Human.h"
#include"Stage.h"
car::car()
{
}


car::~car()
{
	DeleteGO(ran);
}
bool car::Start()
{
	CLocData loc;
	loc.Load(L"lever/carLv001.tks");
	No.resize(loc.GetNumObject());
	for (int i = 0; i < loc.GetNumObject(); i++) {
		int ka=_wtoll(loc.GetObjectName(i));
		No[ka-1] = loc.GetObjectPosition(i);
	}
	Stage* stage =FindGO<Stage>("stage");
	Gaizi = FindGO<Geizi>("Geizi");
	fa = stage->incNo();//�Ԃ��ł����������J�E���g����֐��B
	saidaiNo = stage->Gatpasusaiz(fa);
	pasu = stage->getDate(fa);
	ran = NewGO<AImove>(0, "AImove");
	m_position = No[pasu[ima++]-1];
	m_position.y = 10.0f;
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	for (int u = 0; u < Humans.size(); u++) {
		Human* ai = Humans[u];
		HumanLest.push_back(ai);
	}

	
	m_noise = NewGO<prefab::CSoundSource>(0);
	m_noise->Init("sound/car_noise.wav", true);
	m_noise->AddSoundStopCallback([&]() {
		//�T�E���h����~�����炱�̊֐����Ă΂��
		
	});
	
	//m_noise->Play(false);//���߂Ď~�܂����̂ŁA�N���N�V������炷�B

	//�N���N�V�����̏������B
	//m_klaxon = NewGO<prefab::CSoundSource>(0);
	//m_klaxon->Init("sound/car-horn1.wav",true);
	CVector3 c = No[pasu[ima] - 1];
	CVector3 bekutor =  c-m_position;
	bekutor.y = 0.0f;
	bekutor.Normalize();
	//��]�������߂�B
	c.y = 0.0f;
	c.Normalize();//����Vector�ɂ���B
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, bekutor);
	CVector3 l = CVector3::Zero;
	if (rotAxis.x==0&& rotAxis.y==0&& rotAxis.z==0) {
		if (bekutor.z > 0) {
			m_rotation.SetRotationDeg(CVector3::AxisY,0.0f);
		}
		else {
			m_rotation.SetRotationDeg(CVector3::AxisY,-180.0);
		}
	}
	else {
		float kaku = acosf(c.Dot(m_forward));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)
		float degree = CMath::RadToDeg(kaku);
		rotAxis.Normalize();
		m_rotation.SetRotationDeg(rotAxis, degree);
	}
	//rotation.Multiply(rotation);
	ran->Setkakudo(0.1f);
	ran->Sethaba(1.0f);
	if (stage->GatNo() >= 23) {//car�𑝂₷�Ƃ��ɕς���B
		stage->risetteNo();
	}


	m_skinModelData.Load(L"modelData/Vehicle_SUV1.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);

	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass= 10.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	stopFlag = false;//stopFlag�̏������B

#ifdef instansingu_katto
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
#endif 
	SetTags(20);
	return true;
}

void car::Update()
{
	klaxonFlag = false;//���񏉊����B
	if (Gaizi->GatFragu() < 1.0f) {
		CarSound_SetPosition();//�����̍��W��ݒ�B

		m_tekirot.MakeRotationFromQuaternion(m_rotation);
		m_forward.x = m_tekirot.m[2][0];
		m_forward.y = m_tekirot.m[2][1];
		m_forward.z = m_tekirot.m[2][2];
		m_forward.y = 0.0f;
		m_forward.Normalize();
		frag = false;
		Humanfrag = false;
		Stop();
		//����������艺�́A��~���Ă������klaxonFlag��true�ɂȂ�B
		//if (frag <= 0) {
		Move();
		//}

		if (move != 0.0f) {//�����Ă�����
			if(m_noise->Get3DSoundFlag() ==true)
			m_noise->Play(true);//�Ԃ̑��s���𗬂��B
		}
		else {//�~�܂��Ă�����
			m_noise->Stop();//�Ԃ̑��s�����~�߂�B
		}
		//�N���N�V������炷���𔻒肷��B
		if (klaxonFlag == true) {//�N���N�V������炵���B
			SoundklaxonPlay();
		}

		if (klaxonFlag == false) {
			stopFlag = false;
		}
		m_position.y = 0.0f;
		if (Humanfrag != false) {

			ran->Setlen(0.0f);
		}

//	}

	if (move == 0.0f) {
		int i = 0;
	}
	//�N���N�V������炷���𔻒肷��B
	if (klaxonFlag == true) {//�N���N�V������炵���B
		SoundklaxonPlay();
	}

	if (klaxonFlag == false) {
		stopFlag = false;
	}


	btVector3 m_pos = m_rigidBody.GetBody()->getWorldTransform().getOrigin();
	if (0 >= m_pos.y()) {
		m_pos.setY(0.0f);
	}
	m_pos.setX(m_position.x);
	m_pos.setZ(m_position.z);
	m_rigidBody.GetBody()->getWorldTransform().setOrigin(m_pos);
	m_position.Set(m_pos);


#ifdef instansingu_katto
	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f });
#else
	m_Render->UpdateWorldMatrix(m_position, m_rotation, {1.0f,1.0f,1.0f});
#endif // Mizuki_baka
}
void car::Move()
{
	ran->kyorikeisan(pasu[ima] - 1, m_position, m_forward, No);

	if (ran->Getkaiten() != 0.0f) {
		m_rotation.Multiply(ran->Getkaku());//��]������
		if (move > 0.5) {
			move -= 0.05;
		}
		else {
			//if (frag <= 0) {
			//	//	�ł����炢���Ȃ��`�`
			//	CVector3 k = No[pasu[ima] - 1] - m_position;
			//	k.x = k.x*m_forward.x;
			//	k.y = k.y*m_forward.y;
			//	k.z = k.z*m_forward.z;
			//	float K = 90.0f / ((((k * 2)*3.14159) / 4).Length() / (move*speed*GameTime().GetFrameDeltaTime()));
			ran->Setkakudo(3.0f);
			ran->Sethaba(1.5f);
			//frag++;
			if (move < 0.4) {
				move += 0.3;

			}
		}
	}
	else {
		if (move < 1.0) {
			move += 0.1;
		}else{	
			ran->Setkakudo(0.5f);
			ran->Sethaba(1.0f);

			siya = 100.0f;
			//frag = 0;
			move = 1.0;
		}
	}
	m_position += m_forward * ((move*speed)*(GameTime().GetFrameDeltaTime()));

	if (300.0f > ran->Getlen()) {

		if (ima >= saidaiNo-1) {//���̃|�W�V������6�Ȃ�
						//0�Ƀ��Z�b�g����B0,1,2,3,4,5�̏��ԁB
			ima = 0;
			//ran->Setkakudo(0.3f);
			//ran->Sethaba(1.0f);
		}
		else {
			ima++;
			//ran->Setkakudo(0.3f);
			//ran->Sethaba(1.0f);
		}
	}
}
void car::Stop()
{
	for (auto& Humanlest : HumanLest) {
		if (Humanfrag != true) {
			CVector3 kyori1 = Humanlest->Getposition() - this->m_position;//�����Ƃ̋��������߂�B
			float f = kyori1.Length();
			if(!Humanlest->GetZonbi()){
				if (f <= 800) { //�������������������
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= 30)
					{
						//���̈�A�̏����𑱂��Ă���Ƃ��͎~�܂��Ă���B
						move = -0.1;
						Humanfrag = true;
						klaxonFlag = true;//�N���N�V������炷�B�~�܂葱�������true�̂܂܂ɂȂ�B
					}
				}
			}
		}
	}

	int ha = 0;
	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this && ha == 0) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
			car* ai = (car*)go;
			CVector3 kyori1 = ai->m_position - this->m_position;//�����Ƃ̋��������߂�B
			float f = kyori1.Length();
			if (f <= 1000) { //�������Ԋԋ��������Z���Ȃ��Ă�����
				float kaku1 = acosf(ai->m_forward.Dot(this->m_forward));
				float degree1 = CMath::RadToDeg(kaku1);
				if (degree1 <160) {
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= siya) {
						if (ai->ran->Getlen() <= this->ran->Getlen())
						{
							if (ai->Humanfrag == true) {
								move = -0.1;

								siya = 10.0f;
								Humanfrag = true;
							}

							else {
								if (move <= 0.2) {
									move = -0.1;
								}
								else {
									move -= 0.31;
								}
								ha++;
							}
						}
					}

				}
			}
		}
	});
}

void car::CarSound_SetPosition()//��A�̂�����ǂ̏���������B
{
	//	//�N���N�V������炷���𔻒肷��B
	//	SoundklaxonPlay();
	//�T�E���h�̃|�W�V������ݒ肷��B
	m_noise->SetPosition(m_position);
}

void car::SoundklaxonPlay()//�N���N�V�����̃T�E���h��炳�ꂽ���Ɉ�񂾂������B
{
	if (stopFlag == false) {
		prefab::CSoundSource*m_klaxon = nullptr;
		m_klaxon = NewGO<prefab::CSoundSource>(0);
		m_klaxon->Init("sound/klaxon.wav", true);
		m_klaxon->AddSoundStopCallback([&]() {
			//�T�E���h����~�����炱�̊֐����Ă΂��
			stopFlag = true;//�X�g�b�v�����B
		});
		//�T�E���h�̃|�W�V������ݒ肷��B
		m_klaxon->SetPosition(m_position);
		m_klaxon->Play(false);//���߂Ď~�܂����̂ŁA�N���N�V������炷�B
	//if (Humanfrag == false) {//�Ԃ������o�����B
	//	stopFlag = false;//�u�X�g�b�v�����v�Ƃ����t���O�����ɖ߂��Ă����B
	//}
		stopFlag = true;//�X�g�b�v�����B
	}
}
void car::Render(CRenderContext& rc)
{

#ifdef instansingu_katto
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
#endif 
}