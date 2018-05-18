#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

bool camera::Start()
{
	
	return true;
}
void camera::Update()
{
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");
	if (m_player != NULL){

		position_of_player = m_player->GetPosition();
		target = position_of_player + m_player->GetFoeward() * 100.0f;
		target.y = position_of_player.y + 70.0f;
		
		d += rStick_y*5.0f;
		d = max(d, -50.0f);
		d = min(d, 50.0f);
		target.y = target.y + d;
		/*target.z = m_player->m_position.z + m_player->m_forward.z + 50.0f;
		target.y = m_player->m_position.y + m_player->m_forward.y + 50.0f;*/
		Ppos = m_player->GetPosition() + m_player->GetFoeward() * 10.0f;
		Ppos.y = position_of_player.y + 70.0f;
	}
		
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetTarget(target);
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();
}