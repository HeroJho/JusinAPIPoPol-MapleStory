#pragma once
#include "Obj.h"
class CMouse : public CObj
{
public:
	enum MOUSE { IDLE, PICK, HOLD, END };

public:
	CMouse();
	virtual ~CMouse();

public:
	ITEM GetInfo() { return m_sInfo; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void OnCollision(CObj* _pOther);
	void SetItem(CObj* _pOther);


private:
	MOUSE	m_eState;
	ITEM	m_sInfo;
};

