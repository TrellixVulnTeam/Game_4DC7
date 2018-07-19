#include "stdafx.h"
#include "Player.h"
#include"Human.h"
#include"taieki.h"
#include"tekihei.h"
#include"Geizi.h"
#include"car.h"
#define counter 10
#define taime 15.0f*30.0f
#include<string>
#include<codecvt>
Player::Player()
{
	hakaba=NewGO<prefab::CEffect>(0);
}
Player::~Player()
{
	DeleteGO(FindGO<taieki>("taieki"));
	m_Respiration->Stop();//�ċz�����~�߂�B
}
bool Player::Start()
{
	swprintf_s(test_font,L"%d", bullet_sum);
	////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	m_animclip[idle].Load(L"animData/playeridle.tka");
	m_animclip[walk].Load(L"animData/playerwalk.tka");
	m_animclip[attack].Load(L"animData/playerattack.tka");
	m_animclip[ziko].Load(L"animData/liam_ziko.tka");	
	m_animclip[koke].Load(L"animData/shiminkoke.tka");//���B��œ����B
	m_animclip[oki].Load(L"animData/shiminokiagari2.tka");//���B��œ����B
	/*animclip[1].Load(L"animData/demoanime/walk.tka");
	animclip[2].Load(L"animData/demoanime/run.tka");

	/*std::string hoge("Character1_Head");
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> c
	v;
	std::wstring headbone = cv.from_bytes(hoge);*/
	const wchar_t name[20] = { 'h','e','a','d' };
	m_skinModelData.Load(L"modelData/liam.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		material->Setm_zonbi(zondi.GetBody());

	});

	m_skinModel.Satburend(1.0f);
	m_animclip[idle].SetLoopFlag(true);
	m_animclip[walk].SetLoopFlag(true);
	m_animclip[attack].SetLoopFlag(false);
	m_animclip[ziko].SetLoopFlag(false);
	m_animclip[oki].SetLoopFlag(false);
	m_animclip[koke].SetLoopFlag(false);
	m_animation.Init(
		m_skinModel,
		m_animclip,
		animnum
	);
	m_skinModel.SetShadowCasterFlag(true);
	m_position.x = 2910.12085;
	m_position.z = -3936.80713;
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		30.0,			//���a�B 
		100.0f,			//�����B
		m_position,		//�����ʒu�B
		0
	);
	landpos.x = 2000.0f;
	landpos.z = 0.0f;
	hakaba->Play(L"effect/aura3.efk");
	hakaba->SetPosition(landpos);
	hakaba->SetScale({ 40.0f,40.0f,40.0f });
	hakaba->Release();
	hakaba->Play(L"effect/aura1.efk");
	hakaba->SetScale({ 40.0f,40.0f,40.0f });
	hakaba->Release();
	bonenum = m_skinModelData.GetSkeleton().GetNumBones();
	for (int i = 1;i < bonenum;i++)
	{
		swprintf_s(bonename, m_skinModelData.GetSkeleton().GetBone(i)->GetName());
		int result = wcscmp(bonename, name);
		if (result == 0)
		{
			boneNo = i;
			break;
		}
	}
	/*m_animclip[walk].SetLoopFlag(true);
	m_animation.Init(
		m_skinModel,
		m_animclip,
		animnum
	);*/
	SetZonbe();
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	m_animation.Play(idle, 0.2f);
	m_skinModel.Update(m_position, m_rotation, { 20.0f,20.0f,20.0f });// CVector3::One*20.0f);
	//�v���C���[�̌ċz���̏������B
	m_Respiration = NewGO<prefab::CSoundSource>(0);
	m_Respiration->Init("sound/iki.wav", false);
	controller_end = false;
	return true;
}
void Player::Update()
{
	//������font
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	
	if ((game != false)&&(controller_end==false)) {
		
		//m_animation.Play(idle,0.2);

		m_moveDecision = CVector3::Zero;//����Ɏg�p����̂ŏ������B

		// ��y //NewGO<prefab::CVolumeLight>(0)->Init(&m_position);

		m_moveSpeed.z = 0.0f;
		m_moveSpeed.x = 0.0f;

		


		if ((Pad(0).IsTrigger(enButtonLB3))|| (Pad(0).IsTrigger(enButtonA))) //A�{�^���������ꂽ��
		{
			switch (L3_button_Flag)
			{
			case false://�܂�A�{�^����������Ă��Ȃ�������
				L3_button_Flag = true;//X�{�^����������āA���b�N���ꂽ
				break;
			case true://����A�{�^����������Ă�����
				L3_button_Flag = false;//�ēxA�{�^���������ꂽ�̂ŁA���b�N������
			default:
				L3_button_Flag = false;//�ēxA�{�^���������ꂽ�̂ŁA���b�N������
				break;
			}
		}


		//float lStick_x;
		//float lStick_y;
		if (L3_button_Flag == false) //��X�j�[�N���[�h��
		{
			//���X�e�B�b�N�̓��͗ʂ��󂯎��B
			lStick_x = Pad(0).GetLStickXF()*500.0f;
			lStick_y = Pad(0).GetLStickYF()*600.0f;
		}
		else //�X�j�[�N���[�h��
		{
			//���X�e�B�b�N�̓��͗ʂ��󂯎��B
			lStick_x = Pad(0).GetLStickXF()*200.0f;
			lStick_y = Pad(0).GetLStickYF()*240.0f;
		}
		
		//�E�X�e�B�b�N�̓��͗ʂ��󂯎��B
		float rStick_x = Pad(0).GetRStickXF();
		float rStick_y = Pad(0).GetRStickYF();

		/*rotX += rStick_y * 5;*/
		rotY = rStick_x * 3;
		/*qBias.SetRotationDeg(CVector3::AxisX, rotX);*/
		qBias1.SetRotationDeg(CVector3::AxisY, rotY);
		m_rotation.Multiply(qBias1);
		if (hakaba != NULL)
		{
			land_to_player = landpos - m_position;
			land_to_player_vector = sqrt(land_to_player.x*land_to_player.x + land_to_player.y*land_to_player.y + land_to_player.z*land_to_player.z);
		}


		//if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		//	&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		//	) {
		//	//�W�����v����B
		//	m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
		//	m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
		//}
		//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
		if (m_charaCon.IsOnGround()) {
			//�n�ʂɂ����B
			m_moveSpeed.y = 0.0f;
		}
		if (Pad(0).IsTrigger(enButtonRB1)&&taieki_F==0&&bullet_sum>0)
		{
			
			Tp[taieki_sum]=NewGO<taieki>(0, "taieki");
			taieki_sum++;
			taieki_F++;
			if (taieki_sum == 20)
			{
				taieki_sum = 0;
			}
			bullet_sum--;
			swprintf_s(test_font, L"%d", bullet_sum);
		}
		if (taieki_F == 1)
		{
			taieki_timer += 1.0f*GameTime().GetFrameDeltaTime();
		}
		if (taieki_timer >= 0.5f)
		{
			taieki_timer = 0.0f;
			taieki_F = 0;
		}
		//�v���C���[�̑O�������v�Z

		mRot.MakeRotationFromQuaternion(m_rotation);
		m_forward.x = mRot.m[2][0];
		m_forward.y = mRot.m[2][1];
		m_forward.z = mRot.m[2][2];
		m_forward.Normalize();
		//�E����
		m_rite.x = mRot.m[0][0];
		m_rite.y = mRot.m[0][1];
		m_rite.z = mRot.m[0][2];
		m_rite.Normalize();
		m_moveSpeed += m_forward * lStick_y;
		m_moveSpeed += m_rite * lStick_x;
		m_moveDecision = m_moveSpeed;//�����ł������Ă������������B

		Play_Respiration(m_moveDecision);

		if (hakaba->IsPlay() && landflag == 1 && land_to_player_vector <= 50.0f)
		{
			m_moveSpeed = CVector3::Zero;
			if (Pad(0).IsTrigger(enButtonA))
			{
				DeleteGO(hakaba);
				FindGO<Geizi>("Geizi")->Satpoint(1.0f);
			}
			if (Pad(0).IsTrigger(enButtonB))
			{
				landflag = 0;
			}
		}
		if (land_to_player_vector > 50.0f)
		{
			landflag = 1;
		}
		if (Pad(0).IsTrigger(enButtonB) && attackF == 0)
		{
			m_animation.Play(attack, 0.1f);
			Play_Attack();//�U������SE���Đ�����B
			attackF = 1;
		}
		if (!(m_animation.IsPlaying()) && attackF == 1)//�A�j���[�V�����Đ������U���s�\��Ԃ̂Ƃ�
		{
			/*		if (Pad(0).IsTrigger(enButtonB))
					{
						m_animation.Play(attack2, 0.3);
					}*/

			//attackcounter��10��J�E���g�����ƍU���\�ɂȂ�B
			if (attackcounter >= 10)
			{
				attackF = 0;//�U���\�ɂ���B
				attackcounter = 0;//�J�E���^�[���������B
			}
			attackcounter++;
		}
		if (m_moveSpeed.x == 0.0f&&m_moveSpeed.z == 0.0f&& m_charaCon.IsOnGround() && attackF == 0)//�v���C���[���~�܂��Ă���Ƃ�
		{
			m_animation.Play(idle, 0.2f);
		}
		if (m_moveSpeed.x != 0.0f&&m_moveSpeed.z != 0.0f&& m_charaCon.IsOnGround() && attackF == 0)//�v���C���[�������Ă���Ƃ�
		{
			m_animation.Play(walk, 0.2f);	
		}
		if (muteki_Flag == false) {
			FindGameObjectsWithTag(20, [&](IGameObject* go) {
				if (go != this) {            //��������̋������v�����邽�߁A�������ʂ��玩�������O����B
					car* ai = (car*)go;
					if (ai->GetmoveStop() == false) {//�Ԃ��~�܂��Ă�����
						CVector3 kyori1 = this->m_position - ai->Getposition();//�����Ƃ̋��������߂�B
						float f = kyori1.Length();
						if (f <= 300) { //�������Ԋԋ��������Z���Ȃ��Ă�����
							kyori1.Normalize();
							float kaku = acosf(kyori1.Dot(ai->Getforward()));//�Q�̂׃N�g���̓��ς̃A�[�N�R�T�C�������߂�B(���W�A��)
							float degree = CMath::RadToDeg(kaku);
							if (degree <= 30) {
								game = false;
								carpoint = ai;
								carpoint->SoundklaxonPlay();
								m_moveSpeed = (m_forward*-1 * m_moveSpeed.Length()) + carpoint->Getforward()*1000.0f;
								m_moveSpeed.y = 450.0f;
								zikofrag = true;
								muteki_Flag = true;

							}

						}
					}
				}
			});
		}
	}
	if (muteki_Flag == true) {
		muteki_count++;
		/*//���m�N��	float taim= taime;
		if ((muteki_count / taim) >= (4.0f / 5.0f)) {
			if (blend >= 0) {
				GraphicsEngine().GetMonochrome().SetAlpha(blend);
				blend -= 0.1f;
			}
		}*/
		if (muteki_count >= taime) {//���G�����Ă���5�b���o�߂�����
		//	GraphicsEngine().GetMonochrome().SetAlpha(0.0f);
			muteki_Flag = false;
			muteki_count = 0;
		}
	}
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);//�ړ��B

	//�ԂƂ̏Փ˔���
	if (zikofrag == true)
	{

		m_animation.Play(ziko, 0.4f);
		/*//���m�N��	if (blend <= 1.0f) {
							GraphicsEngine().GetMonochrome().SetAlpha(blend);
							blend += 0.1f;
						}*/
		if (!m_animation.IsPlaying()) {
			zikofrag = false;
			//	blend = 1.0f;
			game = true;
			//m_animation.Play(idle, 0.2f);
		}
		if (m_charaCon.IsOnGround()) {
			m_moveSpeed = CVector3::Zero;
		}
	}

	
	Setposition(m_position);
	m_skinModel.Update(m_position, m_rotation, { 20.0f,20.0f,20.0f });// CVector3::One*20.0f);
	const CMatrix& boneM = m_skinModelData.GetSkeleton().GetBone(boneNo)->GetWorldMatrix();
	
	bonepos.x = boneM.m[3][0];
	bonepos.y = boneM.m[3][1];
	bonepos.z = boneM.m[3][2];
	boneforward.x = boneM.m[2][0];
	boneforward.y = boneM.m[2][1];
	boneforward.z = boneM.m[2][2];
	boneright.x = boneM.m[0][0];
	boneright.y = boneM.m[0][1];
	boneright.z = boneM.m[0][2];
	boneup.x = boneM.m[1][0];
	boneup.y = boneM.m[1][1];
	boneup.z = boneM.m[1][2];
	boneforward.Normalize();
	boneright.Normalize();
	boneup.Normalize();
	/*FindGameObjectsWithTag(10, [&](IGameObject* go) {
		CVector3 diff;
		AI* ai = (AI*)go;
		diff = ai->position - m_position;
		if (diff.Length() < 100.0f) {

		}
	});*/
}
void Player::Play_Respiration(CVector3 m_moveDecision)
{
	if (CVector_same_Decision(m_moveDecision, CVector3::Zero) != true) {//�v���C���[���~�܂��Ă��Ȃ�������
		m_Respiration->Play(true);//�ċz�����Đ�����B
	}
	else {
		m_Respiration->Stop();//�ċz�����~�߂�B
	}

	if (camera_f == false) {
		if (m_Respiration->IsPlaying() == true) {
			m_Respiration->Stop();//�ċz�����~�߂�B
		}
	}
}
//�v���C���[���U���������̌��ʉ����Đ�����B
void Player::Play_Attack()
{
	m_AttackSE = NewGO<prefab::CSoundSource>(0);
	m_AttackSE->Init("sound/swing2.wav", false);
	m_AttackSE->Play(false);//��񂾂��Đ�����Ĕj�������B
}
bool Player::CVector_same_Decision(CVector3 a, CVector3 b) //2�̃x�N�g�������ꂩ�ǂ����𒲂ׂ�B
{
	bool Hantei = false;
	if (a.x == b.x) {
		if (a.y == b.y) {
			if (a.z == b.z) {//�S���ꏏ��������
				Hantei = true;//Hantei��true�ɂ���B
			}
		}
	}

	if (Hantei == true) {
		return true;//2�̃x�N�g������v�����̂�true��Ԃ��B
	}
	else {
		return false;//2�̃x�N�g������v���Ȃ������̂�false��Ԃ��B
	}
}
void Player::Playoki()
{
	m_animation.Play(oki, 0.2f);
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
void Player::PostRender(CRenderContext& renderContext)
{

	if (camera_f == true)
	{
		m_font.Begin(renderContext);
		m_font.Draw(test_font, font_pos, { 0.0f,255.0f,0.0f,1.0f }, 0.0f, 4.0f, fomt_pivot);
		m_font.End(renderContext);
	}
}
