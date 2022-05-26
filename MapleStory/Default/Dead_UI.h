#pragma once
#include "Obj.h"
#include "CommunityS_UI.h"
class CDead_UI :
    public CObj
{
public:
	CDead_UI();
	virtual ~CDead_UI();

public:
	CObj* GetCommunityS() { return m_pNextButton; }
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	bool m_bIsOpen;
	CCommunityS_UI* m_pNextButton;
};

