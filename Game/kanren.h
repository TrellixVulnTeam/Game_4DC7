#pragma once
class kanren : public IGameObject
{
public:
	kanren();
	~kanren();
	void kanrenz(int a,std::vector<CVector3> &b);
	std::vector<CVector3> m_position;
	std::vector<int> No;
	int ka = 0;
};

