#pragma once
#include "Obj.h"

class CMonster : public CObj
{
protected:
	enum STATE { IDLE, WALK, CHASE, HIT, DEAD, ATTACK, SKILL,  END };

public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	virtual void Motion_Change(void);

protected:
	STATE					m_ePreState;
	STATE					m_eCurState;

};

