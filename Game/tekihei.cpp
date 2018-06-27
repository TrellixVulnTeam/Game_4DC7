#include "stdafx.h"
#include "tekihei.h"
#include"AI.h"
#include"Player.h"
#include"math.h"
#include"Geizi.h"
#include"GameEnd.h"
//#include"item.h"
tekihei::tekihei()
{
}


tekihei::~tekihei()
{
	for (int i = 0;i < teki;i++)
	{
		if (tamaEF[i] != NULL) {
			DeleteGO(tamaEF[i]);
		}
	}
	for (auto human : Humans) {
		AI* pointa = (AI*)human;
		pointa->Gettekihei(NULL);
	}
}

bool tekihei::Start()
{
	
	gaizi = FindGO<Geizi>("Geizi");
	/*animclip[0].Load(L"animData/tekiidle.tka");
	animclip[0].SetLoopFlag(true);*/


	//�p�X�̏�����
	EnemyPath[0] = { 0.0f,0.0f,0.0f };
	EnemyPath[1] = { 0.0f,0.0f,1950.0f };
	EnemyPath[2] = { 0.0f,0.0f,4000.0f };
	EnemyPath[3] = { 0.0f,0.0f,6030.0f };
	EnemyPath[4] = { 0.0f,0.0f,8000.0f };
	EnemyPath[5] = { 0.0f,0.0f,-2010.0f };
	EnemyPath[6] = { 0.0f,0.0f,-4000.0f };
	EnemyPath[7] = { 0.0f,0.0f,-6100.0f };
	EnemyPath[8] = { 0.0f,0.0f,-8000.0f };
	EnemyPath[9] = { -8000.0f,0.0f,0.0f };
	EnemyPath[10] = { -6010.0f,0.0f,0.0f };
	EnemyPath[11] = { -4000.0f,0.0f,0.0f };
	EnemyPath[12] = { -2000.0f,0.0f,0.0f };
	EnemyPath[13] = { 2010.0f,0.0f,0.0f };
	EnemyPath[14] = { 4000.0f,0.0f,0.0f };
	EnemyPath[15] = { 6200.0f,0.0f,0.0f };
	EnemyPath[16] = { 8000.0f,0.0f,0.0f };
	EnemyPath[17] = { -8000.0f,0.0f,-8000.0f };
	EnemyPath[18] = { -8000.0f,0.0f,-6100.0f };
	EnemyPath[19] = { -8000.0f,0.0f,-4000.0f };
	EnemyPath[20] = { -8000.0f,0.0f,-2010.0f };
	EnemyPath[21] = { -8000.0f,0.0f,2050.0f };
	EnemyPath[22] = { -8000.0f,0.0f,4000.0f };
	EnemyPath[23] = { -8000.0f,0.0f,6030.0f };
	EnemyPath[24] = { -8000.0f,0.0f,8000.0f };
	EnemyPath[25] = { 8000.0f,0.0f,-8000.0f };
	EnemyPath[26] = { 8000.0f,0.0f,-6100.0f };
	EnemyPath[27] = { 8000.0f,0.0f,-4000.0f };
	EnemyPath[28] = { 8000.0f,0.0f,-2010.0f };
	EnemyPath[29] = { 8000.0f,0.0f,1950.0f };
	EnemyPath[30] = { 8000.0f,0.0f,4000.0f };
	EnemyPath[31] = { 8000.0f,0.0f,6030.0f };
	EnemyPath[32] = { 8000.0f,0.0f,8000.0f };
	EnemyPath[33] = { -6010.0f,0.0f,8000.0f };
	EnemyPath[34] = { -4000.0f,0.0f,8000.0f };
	EnemyPath[35] = { -2020.0f,0.0f,8000.0f };
	EnemyPath[36] = { 2010.0f,0.0f,8000.0f };
	EnemyPath[37] = { 4000.0f,0.0f,8000.0f };
	EnemyPath[38] = { 6200.0f,0.0f,8000.0f };
	EnemyPath[39] = { -6010.0f,0.0f,-8000.0f };
	EnemyPath[40] = { -4000.0f,0.0f,-8000.0f };
	EnemyPath[41] = { -2020.0f,0.0f,-8000.0f };
	EnemyPath[42] = { 2010.0f,0.0f,-8000.0f };
	EnemyPath[43] = { 4000.0f,0.0f,-8000.0f };
	EnemyPath[44] = { 6200.0f,0.0f,-8000.0f };

	

	for (int i = 0;i < teki;i++)//�G���̐���������������B
	{	
		collide_siya[i] = 0.0f;
		teki_to_teki_dist[i] = 0.0f;
		teki_to_teki_vector[i] = CVector3::Zero;	                        
		nearPathNo[i] = 0;													
		tekipos[i] = EnemyPath[i];	//���W�̏������B										
		stop_target_num[i] = 999;												
		stop_f[i] = 0;														
		for (int j = 0;j < path;j++)										
		{																	
			teki_to_path[i][j]= FLT_MAX;
			teki_to_path_vector[i][j] = CVector3::Zero;
		}
		oldpos_to_tekipos_vector[i] = CVector3::Zero;
		tekistop_counter[i] = 0;

		old_old_target_num[i] = 100;
		target_num[i] = 100;
		old_target_num[i] = 100;
		old_old_old_target_num[i] = 100;
		moving[i] = 0;
		find_f[i] = 0;
		path_f[i] = 0;


		Dtekiangle[i] = 0.0f;
		tekianglecompF[i] = 0;
		tekiHP[i] = 5.0f;
		tekiheiflag[i] = 1;
		damageflag[i] = 0;
		time[i] = 0;
		tama_to_player[i] = CVector3::Zero;
		tama_to_player_vector[i] = 0.0f;
		teki_to_tama_vector[i] = 0.0f;
		teki_to_tama[i] = CVector3::Zero;
		tamamuki[i] = CVector3::Zero;
		tamaEF[i] = nullptr;
		tamaflag[i] = 0;
		tamapos[i] = CVector3::Zero;
		tekispeed[i] = CVector3::Zero;
		teki_angle[i] = 0.0f;
		trot[i] = CQuaternion::Identity;
		tekirot[i] = CQuaternion::Identity;
		tekiskinModelData[i].Load(L"modelData/teki.cmo");//�v���C���[������
		tekiskinModel[i].Init(tekiskinModelData[i]);
		trot[i].SetRotationDeg(CVector3::AxisY, -90.0f);//��]
		tekirot[i].Multiply(trot[i]);
		tekipos[i].y += 2000.0f;            //�󂩂�~���Ă���悤�ɂ��邽��
		/*tekiskinModel[i].SetShadowCasterFlag(true);

		tekianimation[i].Init(
			tekiskinModel[i],
			animclip,
			1
		);*/
		
		/*tekipos[i].y += 1000.0f;
		tekipos[i].z += i * 150;*/
		m_charaCon[i].Init(
			40.0,			//���a�B
			100.0f,			//�����B
			tekipos[i], 	//�����ʒu�B
			0
		);

	}//���������[�v���������܂�
	
	gaizi->SatFragu();//�t���O���Z�b�g���āA����ȏ�G���̃C���X�^���X����������Ȃ��悤�ɂ���B
	Pp = FindGO<Player>("Player");//�v���C���[�̃C���X�^���X�����B
	auto human = Humans.begin();
	human++;
	for (; human < Humans.end(); human++) {
		AI* pointa = (AI*)human[0];
		pointa->Gettekihei(this);
	}
	return true;
}
float tekihei::length(CVector3 vector)
{
	float leng = sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
	return leng;

}
void tekihei::Update()
{
	for (int i = 0;i < teki;i++)//�G���̐������J��Ԃ��B
	{

		//tekianimation[i].Play(0);
		
		if (tekiheiflag[i] == 1)//i�Ԗڂ̓G����tekiheiflag��1(i�Ԗڂ̓G����HP���܂�����)�̂Ƃ��̃��[�v
		{

			//�G�p�X
			if (find_f[i] == 0)
			{
				tekispeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();//i�Ԗڂ̓G���̗�������

				if (m_charaCon[i].IsOnGround())//i�Ԗڂ̓G�����n�ʂɂ���Ƃ�
				{
					tekispeed[i].y = 0.0f;//�������~�߂�(�n�ʂɒ��n��������)


					//target_num[i] = 0;

					for (int j = 0; j < path; j++)//path�̓p�X�̐��Bi�Ԗڂ̓G���ƑS�Ẵp�X�Ƃ̋����𒲂ׂ�B
					{
						teki_to_path_vector[i][j] = EnemyPath[j] - tekipos[i];//j�Ԗڂ̃p�X(���W)���玩���̍��W�������B
						teki_to_path[i][j] = length(teki_to_path_vector[i][j]);//������j�Ԗڂ̃p�X�Ƃ̋������Ƃ�B
					}
					if (moving[i] == 0)//moving[i]��0�̂Ƃ��ɂ����΂�Z�������̃p�X�ԍ���nearPathNo[i]�ɕۑ�����B
					{

						minDist = FLT_MAX;
						//nearPathNo = target_num[i];
						for (int c = 0; c < path; c++)
						{

							if (c == old_target_num[i])//�ЂƂO�̃p�X��������
							{
								continue;
							}
							if (c == old_old_target_num[i])//�ӂ��O�̃p�X��������
							{
								continue;
							}
							if (c == old_old_old_target_num[i]/* && c<path - 1*/)//�݂��O�̃p�X��������
							{
								continue;
							}
							if (minDist > teki_to_path[i][c])//��ԒZ�������Ƃ��ׂ�B
							{
								//���̃p�X�̕����߂��B
								minDist = teki_to_path[i][c];
								//��ԋ߂��p�X�̔ԍ����X�V�B
								nearPathNo[i] = c;
							}
						}
						moving[i] = 1;//
						target_num[i] = nearPathNo[i];//���ɍs���p�X���i�[����B
					}



					//for (int j = 0;j < 20;j++)
					//{
					//	for (int c = 1;c < 21;c++)
					//	{
					//		if (j == old_target_num[i] || j == old_old_target_num[i])
					//		{
					//			j++;
					//		}
					//		if (c == old_target_num[i] || c == old_old_target_num[i]||j==c)
					//		{
					//			c++;
					//		}
					//		teki_to_path_vector[i] = EnemyPath[j] - tekipos[i];
					//		teki_to_path[i][j] = length(teki_to_path_vector[i]);

					//		teki_to_path_vector[i] = EnemyPath[c] - tekipos[i];
					//		teki_to_path[i][c] = length(teki_to_path_vector[i]);

					//		if (teki_to_path[i][j] < teki_to_path[i][c])
					//		{
					//			target_num[i] = j;
					//			//if (j != old_target_num[i] && j != old_old_target_num[i])
					//			//{
					//			//	teki_to_path[i][j] = length(teki_to_path_vector[i]);//teki_to_path_vector[i].Length();
					//			//	target_num[i] = j;
					//			//}

					//		}
					//		else
					//		{
					//			target_num[i] = c;
					//		}
					//	}
					//	
					//	

					//}

					if (length(teki_to_path_vector[i][target_num[i]]) < 300.0f)//i�Ԗڂ̓G���ƈ�ԋ߂��p�X�Ƃ̋�����300������������(�ړI�n�ɒ�������)
					{
						old_old_old_target_num[i] = old_old_target_num[i];//��O�̃p�X���O�O�̃p�X�ɂ���B
						old_old_target_num[i] = old_target_num[i];//��O�̃p�X���O�̃p�X�ɂ���B

						old_target_num[i] = target_num[i];//�ړI�n�������p�X����O�̃p�X�ɂ���B



						stop_f[i] = 0;
						moving[i] = 0;//moving��0�ɂ��āAi�Ԗڂ̓G���ɂ����΂�Z�������̃p�X�ԍ��𒲂ׂ�悤�ɂ���B
					}


					m_tekirot[i].MakeRotationFromQuaternion(tekirot[i]);
					tekiright[i].x = m_tekirot[i].m[0][0];
					tekiright[i].y = m_tekirot[i].m[0][1];
					tekiright[i].z = m_tekirot[i].m[0][2];
					tekiright[i].Normalize();

					tekifoward[i].x = m_tekirot[i].m[2][0];
					tekifoward[i].y = m_tekirot[i].m[2][1];
					tekifoward[i].z = m_tekirot[i].m[2][2];
					tekifoward[i].Normalize();

					for (int j = 0; j < path; j++)
					{
						teki_to_path_vector[i][j] = EnemyPath[j] + tekiright[i] * 100.0f - tekipos[i];
						teki_to_path[i][j] = length(teki_to_path_vector[i][j]);
					}

					teki_to_path_vector[i][target_num[i]].Normalize();

					ppos = Pp->GetPosition();
					teki_to_player[i] = ppos - tekipos[i];

					teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);

					teki_to_player[i].Normalize();//�v���C���[��i�Ԗڂ̓G���Ƃ̋����𐳋K�����Č����x�N�g���ɂ���B

					teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//����̌v�Z

					teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
					if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i] < 1000.0f)
					{
						find_f[i] = 1;
						moving[i] = 0;//moving��0�ɂ��āAi�Ԗڂ̓G���ɂ����΂�Z�������̃p�X�ԍ��𒲂ׂ�悤�ɂ���B
					}



					teki_angle[i] = atanf(tekiright[i].Dot(teki_to_path_vector[i][target_num[i]]));
					teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];
					trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);//��]
					tekirot[i].Multiply(trot[i]);

					if (teki_to_path[i][target_num[i]] > 1.0f)//i�Ԗڂ̓G���̎��̖ړI�n�̃p�X�Ƃ̋�����1.0f�ȏ�̂Ƃ�
					{
						tekispeed[i] = teki_to_path_vector[i][target_num[i]] * 300.0f;
					}
					//�Փ˂��Ȃ��łق����ȁ`�B
					for (int j = 0; j < teki; j++)
					{
						if (j == i)
						{
							continue;
						}
						teki_to_teki_vector[j] = tekipos[j] - tekipos[i];
						teki_to_teki_dist[j] = length(teki_to_teki_vector[j]);
						teki_to_teki_vector[j].Normalize();
						if (teki_to_teki_dist[j] < 100.0f)
						{
							collide_siya[j] = acosf(tekifoward[i].Dot(teki_to_teki_vector[j]));
							collide_siya[j] = (180.0 / 3.14159)*collide_siya[j];
							if (collide_siya[j] <= 30.0f)
							{
								tekispeed[i] += tekiright[i] * 300.0f;
							}
						}


					}

					if (tamaflag[i] == 1)
					{
						playerpos = Pp->GetPosition();
						playerpos.y += 50.0f;
						tama_to_player[i] = playerpos - tamapos[i];
						tama_to_player_vector[i] = sqrt(tama_to_player[i].x*tama_to_player[i].x + tama_to_player[i].y*tama_to_player[i].y + tama_to_player[i].z*tama_to_player[i].z);

						teki_to_tama[i] = tamapos[i] - tekipos[i];
						teki_to_tama_vector[i] = sqrt(teki_to_tama[i].x*teki_to_tama[i].x + teki_to_tama[i].y*teki_to_tama[i].y + teki_to_tama[i].z*teki_to_tama[i].z);
						if (tama_to_player_vector[i] > 50.0f && damageflag[i] == 0)
						{
							tamapos[i] += tamamuki[i] * 1000.0f*GameTime().GetFrameDeltaTime();
							tamaEF[i]->SetPosition(tamapos[i]);//i�Ԗڂ̓G���̒e�̃G�t�F�N�g�̍��W���A�����e�̍��W�Ɠ������W�ɐݒ肷��B
						}


						if (tama_to_player_vector[i] <= 50.0f&& damageflag[i] == 0)
						{
							damageflag[i] = 1;
							gaizi->satHP(0.1);
						}
						if (damageflag[i] == 1)
						{
							tamaEF[i]->SetScale({ 100.0f,100.0f,100.0f });//i�Ԗڂ̓G���̒e�̃G�t�F�N�g�̊g�嗦��ݒ肷��B
							time[i]++;

							if (time[i] >= 10)
							{

								tamaEF[i]->Release();
								tamaEF[i] = NULL;
								tamaflag[i] = 0;
								time[i] = 0;
								damageflag[i] = 0;
							}
						}
						if (teki_to_tama_vector[i] >= 1000)
						{
							tamaEF[i]->Release();
							tamaEF[i] = NULL;
							tamaflag[i] = 0;
						}

					}
				}//�������Ă���Ƃ��͂��̃J�b�R���̏����͂���Ȃ��B

				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });

			}//find_f�����܂�


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////



			if (find_f[i] == 1) {
				//	tekianimation[i].Play(0);

				m_tekirot[i].MakeRotationFromQuaternion(tekirot[i]);
				tekiright[i].x = m_tekirot[i].m[0][0];
				tekiright[i].y = m_tekirot[i].m[0][1];
				tekiright[i].z = m_tekirot[i].m[0][2];
				tekiright[i].Normalize();

				tekifoward[i].x = m_tekirot[i].m[2][0];
				tekifoward[i].y = m_tekirot[i].m[2][1];
				tekifoward[i].z = m_tekirot[i].m[2][2];
				tekifoward[i].Normalize();

				ppos = Pp->GetPosition();
				teki_to_player[i] = ppos - tekipos[i];

				teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);//teki_to_player??

				teki_to_player[i].Normalize();
				teki_angle[i] = atanf(tekiright[i].Dot(teki_to_player[i]));//�v���C���[�Ɍ�����v�Z
				teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];

				teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//����̌v�Z
				teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
				if (teki_siya[i] > 45.0f)
				{
					find_f[i] = 0;
				}
				if (teki_to_player_vector[i] >= 1000.0f)
				{
					find_f[i] = 0;
				}
				if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i] < 1000.0f&&tekianglecompF[i] == 0)
				{
					if (Dtekiangle[i] < 1.0f)
					{
						Dtekiangle[i] += 0.01f;
					}
					if (Dtekiangle[i] >= 1.0f&&teki_siya[i] == 0.0f) {
						tekianglecompF[i] = 1;
					}
					teki_angle[i] *= Dtekiangle[i];
					trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);//��]

					tekirot[i].Multiply(trot[i]);
				}

				if (teki_to_tama_vector[i] >= 300.0f&&tekianglecompF[i] == 1)
				{
					Dtekiangle[i] = 0.0f;
					tekianglecompF[i] = 0;
				}
				if (teki_siya[i] <= 0.0f)
				{
					Dtekiangle[i] = 0.0f;
					tekianglecompF[i] = 0;
				}


				tekispeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();
				if (m_charaCon[i].IsOnGround()) {
					//�n�ʂɂ����B
					tekispeed[i].y = 0.0f;


					if (teki_siya[i] <= 45.0f)
					{
						if (teki_to_player_vector[i] < 1000.0f&&teki_to_player_vector[i] >= 500.0f)
						{
							tekispeed[i] = teki_to_player[i] * 300.0f;
						}
						else {
							tekispeed[i] = CVector3::Zero;
						}

						if (teki_to_player_vector[i] < 510)
						{
							if (tamaflag[i] == 0)
							{
								tamamuki[i] = teki_to_player[i];
								tamaEF[i] = NewGO<prefab::CEffect>(0);
								tamapos[i] = tekipos[i];
								tamapos[i].y += 85.0f;
								tamaEF[i]->Play(L"effect/aura.efk");
								tamaEF[i]->SetPosition(tamapos[i]);
								tamaEF[i]->SetScale({ 10.0f,10.0f,10.0f });
								tamaflag[i] = 1;
							}
						}
					}

				}
				if (tamaflag[i] == 1)
				{
					playerpos = Pp->GetPosition();
					playerpos.y += 50.0f;
					tama_to_player[i] = playerpos - tamapos[i];
					tama_to_player_vector[i] = sqrt(tama_to_player[i].x*tama_to_player[i].x + tama_to_player[i].y*tama_to_player[i].y + tama_to_player[i].z*tama_to_player[i].z);

					teki_to_tama[i] = tamapos[i] - tekipos[i];
					teki_to_tama_vector[i] = sqrt(teki_to_tama[i].x*teki_to_tama[i].x + teki_to_tama[i].y*teki_to_tama[i].y + teki_to_tama[i].z*teki_to_tama[i].z);
					if (tama_to_player_vector[i] > 50.0f && damageflag[i] == 0)
					{
						tamapos[i] += tamamuki[i] * 1000.0f*GameTime().GetFrameDeltaTime();
						tamaEF[i]->SetPosition(tamapos[i]);//i�Ԗڂ̓G���̒e�̃G�t�F�N�g�̍��W���A�����e�̍��W�Ɠ������W�ɐݒ肷��B
					}
					if (tama_to_player_vector[i] <= 50.0f&& damageflag[i] == 0)
					{
						damageflag[i] = 1;
						gaizi->satHP(0.1);
					}
					if (damageflag[i] == 1)
					{
						tamaEF[i]->SetScale({ 100.0f,100.0f,100.0f });
						time[i]++;
						if (time[i] >= 10)
						{
							tamaEF[i]->Release();
							tamaEF[i] = NULL;
							tamaflag[i] = 0;
							time[i] = 0;
							damageflag[i] = 0;
						}
					}
					if (teki_to_tama_vector[i] >= 1000)
					{
						tamaEF[i]->Release();
						tamaEF[i] = NULL;
						tamaflag[i] = 0;
					}

				}

				if (tekiHP[i] <= 0.0f)//i�Ԗڂ̓G����HP��0�ȉ��ɂȂ�����
				{
					tekiheiflag[i] = 0;//i�Ԗڂ�tekiheiflag��0�ɂ���B

				}
				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });
			}
		}
		//i�Ԗڂ̓G����HP���܂�����Ƃ��̃��[�v�͂����܂�

		if (tekiheiflag[i] == 0)//i�Ԗڂ�tekiheiflag��0(i�Ԗڂ̓G����HP��0�ȉ��ɂȂ���)�Ƃ�
		{
			m_charaCon[i].RemoveRigidBoby();//i�Ԗڂ̓G���̍��̂����̂̃��X�g����폜����B
			clearcount++;
		}
		if (clearcount >= teki)
		{
			soma = clearcount;
		}
		if (i == teki - 1)
		{
			clearcount = 0;
		}
		if (tekiheiflag[i]==0)
		{
			if (tamaEF[i] != NULL) {//NULL����Ȃ����������(�����ŃN���b�V�����Ă���BNULL���������Ă��Ȃ�)�B
				//DeleteGO(tamaEF[i]);
				tamaflag[i] = 0;
			}
		}

	}//�G���̐������J��Ԃ����[�v�͂����܂�
	if (soma >= teki) {
		NewGO<GameEnd>(0, "End");
		DeleteGO(this);
	}
}

void tekihei::Render(CRenderContext& rc)
{
	for (int i = 0;i < teki;i++)
	{
		if(tekiheiflag[i]==1)
		tekiskinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}