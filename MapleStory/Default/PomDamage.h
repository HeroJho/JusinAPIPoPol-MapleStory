#pragma once
#include "Obj.h"
class CPomDamage :
	public CObj
{
public:
	CPomDamage();
	~CPomDamage();

public:
	void Init(int _iStart, int _iEnd, int _iDamageSkin = 1);

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

private:
	float m_fUpTime;
	float m_fOldUpTime;

	int m_iStart;
	int m_iEnd;
	int m_iCount;
	string m_sDamage;

	int m_iDisX;
};


