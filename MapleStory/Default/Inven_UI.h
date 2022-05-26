#pragma once
#include "Obj.h"

#include "Item_UI.h"
#include "InvenButton_UI.h"

class CInven_UI :
    public CObj
{
public:
	CInven_UI();
	virtual ~CInven_UI();

public:
	CItem_UI** GetItemUIList() { return m_aItemUIList; }
	CInvenButton_UI** GetInvenButton() { return m_pInvenButton_UI; }

	void SetChange(bool _bValue) { m_bChange = _bValue; }

	bool GetChange() { return m_bChange; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;


private:
	CItem_UI* m_aItemUIList[24];
	CInvenButton_UI* m_pInvenButton_UI[2];
	bool m_bIsOpen;

	float m_fRePosX;
	float m_fRePosY;

	bool m_bChange;

};

