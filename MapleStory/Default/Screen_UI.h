#pragma once
#include "Obj.h"

class CScreen_UI :
    public CObj
{
public:
	CScreen_UI();
	~CScreen_UI();

public:
	void Start() { m_bStart = true; m_tFrame.dwTime = (DWORD)GetTickCount64();}
	void Reset() { m_bStart = false; m_tFrame.iFrameStart = 0; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;

private:
	void Move_Frame(void);
	
private:
	bool m_bStart;

};

