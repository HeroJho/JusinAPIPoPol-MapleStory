#pragma once
#include "Obj.h"

class CQuest_UI :
    public CObj
{
public:
	CQuest_UI();
	virtual ~CQuest_UI();

public:
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };

public:
	void QuestQ_1(HDC hDC);
	void QuestQ_2(HDC hDC);
	void QuestQ_3(HDC hDC);

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

