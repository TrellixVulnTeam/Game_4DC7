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


	//////////////////////////////////////////////////
	// �������烁���o�ϐ��B
	//////////////////////////////////////////////////

	void Update();
#ifdef instansingu_katto
	void Getmama(const wchar_t* ja)
	{
		m_skinModelData.Load(ja);
	}
	void Render(CRenderContext& rc);
#endif
	CVector3 m_position;				//!<���W�B
	CVector3 m_scale;
	CQuaternion m_rotation;				//!<��]�B
private:

	CPhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	LevelRender* m_levelRender = nullptr;	//!<���x�������_���[�B
};

