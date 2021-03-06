#pragma once

#include "Obj.h"

class CBoss_UI :
	public CObj
{
public:
	CBoss_UI();
	virtual ~CBoss_UI();

public:
	void SetPH(float _fP) { m_fPH = _fP; }
	void SetPM(float _fP) { m_fPM = _fP; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	float m_fPH;
	float m_fPrePH;
	float m_fPM;
	float m_fPrePM;
};

