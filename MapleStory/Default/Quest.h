#pragma once
#include "Obj.h"

class CQuest :
    public CObj
{
public:
	enum STATE { IDLE, MOVE, END };

public:
	CQuest();
	virtual ~CQuest();

public:
	void SetCurState(STATE _eState, DIRECTION _eDir);
	void SetIdle() { SetCurState(IDLE, DIR_LEFT); }
	void SetMove() { SetCurState(MOVE, DIR_LEFT); }
	void SetEnd() { SetCurState(END, DIR_LEFT); }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	virtual void OnCollision(CObj* _pOther) override;


protected:
	void Motion_Change(void);

private:
	STATE m_eCurState;
	STATE m_ePreState;

};

