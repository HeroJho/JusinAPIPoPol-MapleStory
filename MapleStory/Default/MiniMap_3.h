#pragma once
#include "Obj.h"
class CMiniMap_3 :
    public CObj
{
public:
	CMiniMap_3();
	virtual ~CMiniMap_3();

public:
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
};

