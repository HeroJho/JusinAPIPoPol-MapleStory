#pragma once
#include "Obj.h"
class CQSlotTemp_UI :
    public CObj
{
public:
	CQSlotTemp_UI();
	virtual ~CQSlotTemp_UI();

public:
	void SetInfo(ITEM _sInfo) { m_sInfo = _sInfo; };
	ITEM& GetInfo() { return m_sInfo; }

	void SetIndex(int _iIndex) { m_iIndex = _iIndex; }
	int GetIndex() { return m_iIndex; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void OnCollision(CObj* _pOther);
	virtual     void	ColRender(HDC hDC) override;

private:
	ITEM m_sInfo;
	int m_iIndex;

};

