#pragma once
#include "Obj.h"
class CPortal :
    public CObj
{
public:
	CPortal();
	virtual ~CPortal();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;
};

