#pragma once
class kanren 
{
public:

	kanren();
	~kanren();
	std::vector<CVector3> m_position;
	std::vector<int> No;
	
	void kanrenz(std::vector<int> &a, std::vector<CVector3> &b);
	//�e�̃m�[�h��ݒ肷��B
	void SetParentNode(kanren* node)
	{
		m_parentNode = node;
	}
	kanren* GetParentNode()
	{
		return m_parentNode;
	}
	std::vector<float> moveCosts;		//�אڃm�[�h�Ɉړ�����R�X�g�B
private:
	
	float costFromStart = 0;			//�X�^�[�g�n�_����̈ړ��R�X�g�BA*�A���S���Y�������s���ꂽ�Ƃ��ɐݒ肳���B					
	kanren* m_parentNode = nullptr;		//�e�̃m�[�h�BA*�A���S���Y�������s���ꂽ�Ƃ��ɐݒ肳���B
};

