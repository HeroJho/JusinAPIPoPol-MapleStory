#pragma once
#include "Obj.h"
class CStatS_UI
	: public CObj
{
public:
	CStatS_UI();
	virtual ~CStatS_UI();

public:
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
	int m_iIndex;

};
