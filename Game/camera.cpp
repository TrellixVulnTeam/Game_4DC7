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
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");
	if (m_player != NULL){
		target = m_player->m_position;
		target.z = m_player->m_position.z + m_player->m_forward.z + 50.0f;
		target.y = m_player->m_position.y + m_player->m_forward.y + 50.0f;
		Ppos = m_player->m_position;
		Ppos.y += 50.0f;
	}
		
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetTarget(target);
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();
}