#pragma once
#include "Obj.h"
class CHpHp_UI :
    public CObj
{
public:
	CHpHp_UI();
	virtual ~CHpHp_UI();

public:
	void SetP(float _fP) { m_fP = _fP; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	float m_fP;
	float m_fPreP;
};

