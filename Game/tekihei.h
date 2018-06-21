#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 45
#define path 45
class tekihei : public IGameObject
{
public:
	tekihei();
	~tekihei();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

	CSkinModel tekiskinModel[teki];					//�X�L�����f���B
	CSkinModelData tekiskinModelData[teki];
	CCharacterController m_charaCon[teki];		//�L�����N�^�R���g���[���B
	CVector3 tekipos[teki];//�G�̃|�W�V����
	CVector3 tekispeed[teki];//�ړ����x
	CQuaternion tekirot[teki];//�G�̉�]
	CMatrix m_tekirot[teki];
	CVector3 tekiright[teki];//�G���̉E�����B
	CVector3 tekifoward[teki];//�G���̑O�������B
	Geizi *gaizi;//�Q�[�W�̃C���X�^���X������|�C���^�B
	Player *Pp;//�v���C���[�̃C���X�^���X������|�C���^�B
	CVector3 ppos = CVector3::Zero;
	CVector3 teki_to_player[teki];
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];//�e�̃G�t�F�N�g�̔z��BCEffect�^�B
	CVector3 tamapos[teki];
	int tamaflag[teki];
	CVector3 tamamuki[teki];
	CVector3 teki_to_tama[teki];
	float teki_to_tama_vector[teki];
	CVector3 playerpos = CVector3::Zero;
	int time[teki];
	int damageflag[teki];
	int tekiheiflag[teki];
	float tekiHP[teki];
	int clearcount = 0;
	int soma = 0;
	CAnimation tekianimation[teki];
	CAnimationClip animclip[1];
	float Dtekiangle[teki];
	int tekianglecompF[teki];





	//�o�H�T���p�v���O����

	
	float length(CVector3 vector);

	CVector3 EnemyPath[path];//���ꂼ��̓G���̏����ʒu���i�[����B
	int path_f[teki];
	int find_f[teki];
	CVector3 teki_to_path_vector[teki][path];
	float teki_to_path[teki][path];//teki�Ԗڂ̓G����path�Ԗڂ̃p�X�Ƃ̋������i�[����B
	int target_num[teki];//teki�Ԗڂ̓G���̎��̖ړI�n�̃p�X���i�[����B
	int old_target_num[teki];
	int old_old_target_num[teki];
	int old_old_old_target_num[teki];
	int moving[teki];
	CVector3 old_pos[teki];
	int tekistop_counter[teki];
	CVector3 oldpos_to_tekipos_vector[teki];
	float oldpos_to_tekipos[teki];
	int stop_target_num[teki];
	int stop_f[teki];
	int min_f[teki];
	float minDist = FLT_MAX;//��ԒZ�������𒲂ׂ鎞�Ɏg���B
	int nearPathNo[teki];//teki�Ԗڂ̓G���ɂ����΂�Z�������̃p�X�ԍ����i�[����B
	CVector3 teki_to_teki_vector[teki];
	float teki_to_teki_dist[teki];
	float collide_siya[teki];
};