
#pragma once

#include "MapChip.h"

	//���x���B
class Level
{
public:
	Level();
	~Level();
	/*!
	*@brief	���x���̍\�z�B
	*@param[in]	levelDataFilePath	�ǂݍ��ރ��x���f�[�^�̃t�@�C���p�X�B
	*/
	void Build(const wchar_t* levelDataFilePath);
	float X = 0.0f, Z = 0.0f;
	///////////////////////////////////////////////
	// �������烁���o�ϐ��B
	///////////////////////////////////////////////
	std::vector<MapChip*> m_mapChipList;		//�}�b�v�`�b�v�̃��X�g�B
private:
	std::vector<int> kaunto;
	std::list<CVector3> L_pos;
	std::list<CVector3>::iterator i_pos = L_pos.begin();
	std::list<CVector3> L_scale;
	std::list<CVector3>::iterator i_scale = L_scale.begin();
	std::list<CQuaternion> L_AI4;
	std::list<CQuaternion>::iterator i_AI4 = L_AI4.begin();
	std::wstring name;
	std::vector<std::wstring> nameNo;
	int hairetuNo = 0;
	int No=0;
};