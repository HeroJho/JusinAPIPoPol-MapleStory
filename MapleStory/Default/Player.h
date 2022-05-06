#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Line.h"

class CPlayer : public CObj
{
	enum STATE { IDLE, MOVE, SKILL, BEND, HANG };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

	void	Update_Gravity(void);
	void	Update_Hang(void);

private:
	void		Key_Input(void);
	void		OffSet(void);

private:
	STATE					m_eState;
	bool					m_bDrop;

	CLine*					m_pDropLine;
	CLine*					m_pHangLine;
	float					m_fDropY;
};
