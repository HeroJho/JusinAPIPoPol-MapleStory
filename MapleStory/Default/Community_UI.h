#pragma once
#include "Obj.h"

#include "CommunityS_UI.h"

class CCommunity_UI :
    public CObj
{
public:
	CCommunity_UI();
	virtual ~CCommunity_UI();

public:
	CObj* GetCommunityS() { return m_pNextButton; }
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };

public:
	void QuestTalk_1(HDC hDC);
	void QuestQ_1(HDC hDC);
	void QuestCQ_1(HDC hDC);
	void QuestTalk_2(HDC hDC);
	void QuestQ_2(HDC hDC);
	void QuestCQ_2(HDC hDC);
	void QuestTalk_3(HDC hDC);
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
	CCommunityS_UI* m_pNextButton;
};

