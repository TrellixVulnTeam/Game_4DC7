#pragma once
#include"tekihei.h"
#define tekikazu 10
class item : public IGameObject
{
public:
	item();
	~item();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel itemModel[tekikazu];					//�X�L�����f���B
	CSkinModelData itemModelData;			//�X�L�����f���f�[�^�B
	CVector3 itempos[tekikazu];
	CQuaternion itemrot[tekikazu];
	int itemf[tekikazu];
	tekihei *tp;
	
};

