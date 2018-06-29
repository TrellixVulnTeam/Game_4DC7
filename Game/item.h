#pragma once
#include "Player.h"
class item : public IGameObject
{
public:
	item();
	~item();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void Set_itempos(CVector3 pos)
	{
		itempos = pos;
	}
private:
	float item_to_player_dist(CVector3 playerpos,CVector3 itemposition);
	CSkinModel itemModel;					//�X�L�����f���B
	CSkinModelData itemModelData;			//�X�L�����f���f�[�^�B
	CVector3 itempos = CVector3::Zero;		//�A�C�e���̃|�W�V����
	CQuaternion itemrot=CQuaternion::Identity;//�A�C�e���̉�]
	int itemf = 0;							//�C�ɂ��Ȃ�
	Player *Pp;
	CQuaternion itemQrot = CQuaternion::Identity;
};

