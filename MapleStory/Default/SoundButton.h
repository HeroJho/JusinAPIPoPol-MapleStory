#pragma once
#include "Obj.h"
class CSoundButton :
    public CObj
{
public:
	CSoundButton();
	virtual ~CSoundButton();

public:
	void SetColBox(float fX, float fY);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void OnCollision(CObj* _pOther);
	virtual     void	ColRender(HDC hDC) override;
};

