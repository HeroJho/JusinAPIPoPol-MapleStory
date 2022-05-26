#pragma once
#include "Obj.h"
class CBossPotal :
    public CObj
{
public:
	CBossPotal();
	virtual ~CBossPotal();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;
};

