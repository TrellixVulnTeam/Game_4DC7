
#pragma once

#include "MapChip.h"

	//���x���B
class Level:IGameObject
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
private:
	std::vector<int> kaunto;
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B

	std::vector<LevelRender*> render;
	std::wstring name;
	int renderNo = 0;
	std::vector<MapChip*> m_mapChipList;		//�}�b�v�`�b�v�̃��X�g�B
	std::vector<std::wstring> nameNo;
	int hairetuNo = 0;
	int No=0;
};