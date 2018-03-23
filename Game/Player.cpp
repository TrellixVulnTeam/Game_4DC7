#include "stdafx.h"
#include "Player.h"
#include"Human.h"
#include"taieki.h"



Player::Player()
{
	
}


Player::~Player()
{
	DeleteGO(FindGO<taieki>("taieki"));
}
bool Player::Start()
{
	
	effect = NewGO<prefab::CEffect>(0);
	effect->Play(L"effect/aura.efk");
	m_skinModelData.Load(L"modelData/unityChan.cmo");//�v���C���[������
	m_skinModel.Init(m_skinModelData);
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		100.0f,			//�����B
		m_position		//�����ʒu�B
	);
	return true;
}
void Player::Update()
{

	m_moveSpeed.z = 0.0f;
	m_moveSpeed.x = 0.0f;
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF()*500.0f;
	float lStick_y = Pad(0).GetLStickYF()*500.0f;
	//�E�X�e�B�b�N�̓��͗ʂ��󂯎��B
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	
	/*rotX += rStick_y * 5;*/
	rotY = rStick_x * 5;
	/*qBias.SetRotationDeg(CVector3::AxisX, rotX);*/
	qBias1.SetRotationDeg(CVector3::AxisY, rotY);
	m_rotation.Multiply(qBias1);

	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = 600.0f;	//������ɑ��x��ݒ肵�āA
		m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
	}
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	if (Pad(0).IsTrigger(enButtonB)&& NULL == FindGO<taieki>("taieki"))
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
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
