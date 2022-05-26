#pragma once
#include "Obj.h"
#include "StatS_UI.h"
class CStatUI :
    public CObj
{
public:
	CStatUI();
	virtual ~CStatUI();

public:
	CStatS_UI** GetStatUIList() { return m_aStatUIList; }
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };

public:

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	bool m_bIsOpen;
	CStatS_UI* m_aStatUIList[4];

	float m_fRePosX;
	float m_fRePosY;
};

