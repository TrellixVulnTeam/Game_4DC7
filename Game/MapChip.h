#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

class LevelRender;

class MapChip : public IGameObject
{
public:
	void OnDestroy() override;
	void Init(
		CVector3 pos,
		CQuaternion rotation,
		CVector3 scale
	);
	//���x�������_�[��������������ŌĂяo�����A�x���������B
	void PostInitAfterInitLevelRender(LevelRender* render);
	void Update();
	
	//////////////////////////////////////////////////
	// �������烁���o�ϐ��B
	//////////////////////////////////////////////////

	CPhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	CVector3 m_position;				//!<���W�B
	CVector3 m_scale;
	CQuaternion m_rotation;				//!<��]�B
private:
	LevelRender* m_levelRender = nullptr;	//!<���x�������_���[�B
};

