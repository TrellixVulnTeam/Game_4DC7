#pragma once
#include"Human.h"
class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
};

