#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
class Fade;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CAnimationClip m_animClip[1];							//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
	Fade* m_Fade;
	int a=0;
private:
	void InitSceneLight();
};

