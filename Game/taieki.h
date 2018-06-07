#pragma once
#include "Player.h"
#include "tekihei.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class taieki:public IGameObject
{
public:
	taieki();
	~taieki();
	bool Start();
	void Update();
	void ThisDelete();//�������g�̍폜������֐��B
	void Render(CRenderContext& rc);
	CVector3 tpos = CVector3::Zero;  //�̉t�̍��W�B
	CSkinModel m_taieki;             //�̉t�̃X�L�����f���B
	CSkinModelData m_taiekiModelData;
	int tf = 0;
	CVector3 PS = CVector3::Zero;   //�v���C���[�̈ړ����x(MoveSpeed)�B
	CVector3 CF = CVector3::Zero;	//�J�����̑O����
	CVector3 TS = CVector3::Zero;
	Player* player = nullptr;
	tekihei* tekip = nullptr;
	//CVector3 e_pos = CVector3::Zero;
	CVector3 taieki_to_tekipos[teki];//���ꂼ��̓G���̍��W�Ƒ̉t�̍��W�Ƃ̍��B
	CVector3 tekipos2[teki];//�G���́A���ꂼ��̍��W���i�[�B
	float tekikyori[teki];//���ꂼ��̓G���Ƒ̉t�Ƃ̋����B
private:
	int Lever = 2;
	int Taim = 0;
	bool teikonFrag = false;
	int counter = 0;
	prefab::CEffect* effect = nullptr;
};

