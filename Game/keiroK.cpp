#include "stdafx.h"
#include "keiroK.h"
#include"AI.h"
#include"Game.h"
#include"math.h"
#include <map>
#include <tchar.h>
#include "AI_manager.h"
#include "kanren.h"
keiroK::keiroK()
{
}
keiroK::~keiroK()
{
}
int keiroK::Kans(int currentCost)
{
	return -1000;
}
void keiroK::tansa(CVector3 i, CVector3 Ta, std::vector<int> *a,int Leftfrag)
{
	//�J�n
	auto& kanrenList = AI_ado->pasu[Leftfrag].Pasuresuto;
	//�J�n�m�[�h����������B
	auto minDist = FLT_MAX;
	kanren* startNode = nullptr;
	for (auto& kanren : kanrenList) {
		auto vDist = i - kanren.m_position[0];
		if (minDist > vDist.Length()) {
			//���������߂��B
			minDist = vDist.Length();
			startNode = &kanren;
		}
	}
	//�I���m�[�h����������B
	minDist = FLT_MAX;
	kanren* endNode = nullptr;
	for (auto& kanren : kanrenList) {
		auto vDist = Ta - kanren.m_position[0];
		if (minDist > vDist.Length()) {
			//���������߂��B
			minDist = vDist.Length();
			endNode = &kanren;
		}
	}

	auto currentNode = startNode;
	//�I�[�m�[�h�ɓ��B����܂Ń��[�v����B
	std::vector<int> openNodeNos;
	std::vector<int> closeNodeNos;
	kanren* parentNode = nullptr;
	//�J�n�m�[�h���I�[�v�����X�g�ɐςށB
	openNodeNos.push_back(currentNode->No[0]-1);
	float moveCost = 0.0f;
	while (currentNode != endNode && openNodeNos.empty() == false) {
		//�I�[�v������Ă��郊�X�g�ւ̈ړ��R�X�g���v�Z����B
		//���ɊJ���m�[�h��I�ԁB
		minDist = FLT_MAX;
		auto nextNodeNo = -1;
		for (auto nodeNo : openNodeNos) {
			//�I���n�_�܂ł̋������v�Z����B
			//�����͗v���P�B
			auto vDist = kanrenList[nodeNo].m_position[0] - Ta;
			if (minDist > vDist.Length()) {
				//������̂ق����߂��B
				minDist = vDist.Length();
				nextNodeNo = nodeNo;
			}
		}
		//�J�����g�m�[�h�����������m�[�h�ɂ���B
		currentNode = &kanrenList[nextNodeNo];
		currentNode->SetParentNode(parentNode);
		parentNode = currentNode;
		//���̃m�[�h���N���[�Y�B
		closeNodeNos.push_back(nextNodeNo);
		//�I�[�v�����X�g����폜�B
		auto itFind = std::find(openNodeNos.begin(), openNodeNos.end(), nextNodeNo);
		openNodeNos.erase(itFind);
		//�I�[�v�����X�g���쐬�B
		for (int i = 1; i < currentNode->No.size(); i++) {
			//�N���[�Y����Ă��Ȃ������ׂ�B
			itFind = std::find(closeNodeNos.begin(), closeNodeNos.end(), currentNode->No[i]);
			if (itFind == closeNodeNos.end()) {
				//�N���[�Y����Ă��Ȃ��B
				openNodeNos.push_back(currentNode->No[i]-1);
			}
		}
	}
	
	while (currentNode != startNode) {
		a->push_back(currentNode->No[0]);
		currentNode = currentNode->GetParentNode();
	}
	//�ڕW�n�_����̋t���ɂȂ��Ă���̂Ń��o�[�X�B
	std::reverse(a->begin(), a->end());
}