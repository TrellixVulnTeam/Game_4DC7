#pragma once
class tekihei;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	void Setposition(CVector3 position)
	{
		H_position = position;
	}
	CVector3 Getposition()
	{
		return H_position;
	}
	void SetZonbe()
	{
		Zonbe =true;
	}
	bool GetZonbi()
	{
		return Zonbe;
	}	
	void Gettekihei(tekihei* pointa)
	{
		tekip = pointa;
	}
protected:
	tekihei* tekip;
private:	
	CVector3 H_position = CVector3::Zero;		//���W�B
	CVector3 kakudai;
	bool Zonbe =false;//�]���r�������Ƃ���+1����B
};
extern std::vector<Human*> Humans;

