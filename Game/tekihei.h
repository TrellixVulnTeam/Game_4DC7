#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 33
#define path 99
class tekihei : public IGameObject
{
public:
	tekihei();
	~tekihei();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
	void Enemy_Discovery();
	enum enemyDiscoveryIcon
	{
		null,		//������Ȃ�����
		left,		//�v���C���[���猩�č����ɂ���
		right,		//�v���C���[���猩�ĉE���ɂ���
	};
	enemyDiscoveryIcon Icon_state = null;
	CFont m_font;



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
	CVector3 ppos = CVector3::Zero;//�v���C���[�̍��W�B
	CVector3 teki_to_player[teki];//�v���C���[��teki�Ԗڂ̓G���Ƃ̋������i�[����B
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];//�e�̃G�t�F�N�g�̔z��BCEffect�^
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





	//�|�C���g�ړ��v���O����

	
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
	float tekistop_counter[teki];
	CVector3 oldpos_to_tekipos_vector[teki];
	float oldpos_to_tekipos[teki];
	int stop_target_num[teki];
	int stop_f[teki];
	int min_f[teki];
	//
	bool bom_f[teki];
	CVector3 Scale[teki];
	prefab::CEffect* bomEF[teki];//�e�̃G�t�F�N�g�̔z��BCEffect�^�B
	//
	float minDist = FLT_MAX;//��ԒZ�������𒲂ׂ鎞�Ɏg���B
	int nearPathNo[teki];//teki�Ԗڂ̓G���ɂ����΂�Z�������̃p�X�ԍ����i�[����B
	CVector3 teki_to_teki_vector[teki];
	float teki_to_teki_dist[teki];
	float collide_siya[teki];
	void SetOnDestoryCb(std::function<void()> cb)
	{
		m_onDestroyCb = cb;
	}
private:
	CSprite kikenn_sprite[teki];		//�X�v���C�g�i���g�j�B


	struct enemyDiscovery
	{
		bool discovery = false;		//���������Ƃ�true
		float alpha = 0.0f;		//���������Ƃ��̉摜�̓����x
	};
	enemyDiscovery m_enemyDiscovery[teki];

	CShaderResourceView kikenn_texture;	//�e�N�X�`���B*/
	std::function<void()> m_onDestroyCb;		//���S�����Ƃ��ɌĂ΂��R�[���o�b�N�B
	bool deth_player = false;



	
};