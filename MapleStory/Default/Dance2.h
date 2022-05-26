#pragma once
#include "Obj.h"

class CDance2 :
    public CObj
{
public:
	CDance2();
	~CDance2();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;

private:
	float m_fTime;
	float m_fOldTime;
};

