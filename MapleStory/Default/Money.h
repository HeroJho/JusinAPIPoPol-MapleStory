#pragma once
#include "Item.h"
class CMoney :
    public CItem
{
public:
	CMoney();
	~CMoney();

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

	virtual		void	OnCollision(CObj* _pOther)	override;
	virtual void	OnHit(CObj* _pOther) override;
public:
	bool	m_bEat;

	float	m_fUpTime;
	float	m_fDownTime;
	float	m_fOldUpTime;

	float m_iMove;
	bool m_bUpDown;
};

