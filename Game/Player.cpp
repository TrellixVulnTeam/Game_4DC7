#include "stdafx.h"
#include "Player.h"
#include"Human.h"
#include"taieki.h"
#include"tekihei.h"
#include"Geizi.h"
#define counter 10
#include <string>
#include<codecvt>


Player::Player()
{
	hakaba=NewGO<prefab::CEffect>(0);
}


Player::~Player()
{
	DeleteGO(FindGO<taieki>("taieki"));
	
}
bool Player::Start()
{
	
	m_animclip[0].Load(L"animData/shiminwalk.tka");

	/*animclip[1].Load(L"animData/demoanime/walk.tka");
	animclip[2].Load(L"animData/demoanime/run.tka");
	animclip[0].SetLoopFlag(true);
	animclip[1].SetLoopFlag(true);
	animclip[2].SetLoopFlag(true);*/
	/*std::string hoge("Character1_Head");
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring headbone = cv.from_bytes(hoge);*/
	const wchar_t name[20] = { 'h','e','a','d' };
	m_skinModelData.Load(L"modelData/liam.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);
	m_animclip[0].SetLoopFlag(true);
	m_animation.Init(
		m_skinModel,
		m_animclip,
		1
	);
	m_skinModel.SetShadowCasterFlag(true);
	m_position.x = -2910.12085;
	m_position.z = 3936.80713;
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		30.0,			//���a�B 
		100.0f,			//�����B
		m_position,		//�����ʒu�B
		0
	);
	landpos.x = 2000.0f;
	landpos.z = 0.0f;
	hakaba->Play(L"effect/aura2.efk");
	hakaba->SetPosition(landpos);
	hakaba->SetScale({ 40.0f,40.0f,40.0f });
	hakaba->Release();
	hakaba->Play(L"effect/aura1.efk");
	hakaba->SetScale({ 40.0f,40.0f,40.0f });
	
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
	
	return true;
}
void Player::Update()
{
	

	//m_animation.Play(idle,0.2);


	m_moveSpeed.z = 0.0f;
	m_moveSpeed.x = 0.0f;
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF()*1000.0f;
	float lStick_y = Pad(0).GetLStickYF()*1000.0f;
	//�E�X�e�B�b�N�̓��͗ʂ��󂯎��B
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	
	/*rotX += rStick_y * 5;*/
	rotY = rStick_x * 5;
	/*qBias.SetRotationDeg(CVector3::AxisX, rotX);*/
	qBias1.SetRotationDeg(CVector3::AxisY, rotY);
	m_rotation.Multiply(qBias1);
	if (hakaba != NULL)
	{
		land_to_player = landpos - m_position;
		land_to_player_vector = sqrt(land_to_player.x*land_to_player.x + land_to_player.y*land_to_player.y + land_to_player.z*land_to_player.z);
	}
	

	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
		m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
	}
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	if (Pad(0).IsTrigger(enButtonRB2)&& NULL == FindGO<taieki>("taieki"))
	{
		NewGO<taieki>(0,"taieki");
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
	m_moveSpeed += m_forward*lStick_y;
	m_moveSpeed += m_rite * lStick_x;
	if (lStick_y > 0.0f&&(lStick_y > lStick_x&&lStick_y > lStick_x*-1.0f))
	{
		m_animation.Play(0);
	}
	/*else {
		animation.Play(0, 0.2f);
	}*/
	
	if (hakaba->IsPlay()&&landflag == 1 && land_to_player_vector <= 50.0f)
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
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.x = 0.0f;
	if (m_position.y <= -100.0f) {
		m_position.y = -100.0f;
	}
	
	m_skinModel.Update(m_position, m_rotation, CVector3::One*20.0f);
	const CMatrix& boneM = m_skinModelData.GetSkeleton().GetBone(boneNo)->GetWorldMatrix();

	bonepos.x = boneM.m[3][0];
	bonepos.y = boneM.m[3][1];
	bonepos.z = boneM.m[3][2];
	/*FindGameObjectsWithTag(10, [&](IGameObject* go) {
		CVector3 diff;
		AI* ai = (AI*)go;
		diff = ai->position - m_position;
		if (diff.Length() < 100.0f) {

		}
	});*/
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
