#pragma once
#include "Scene.h"
class CStage_Catoon :
    public CScene
{
public:
	CStage_Catoon();
	virtual ~CStage_Catoon();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void RenderBackGround(HDC hDC);
	void Move_Frame();

private:
	int m_iCount;

	float m_fStartTime;
	float m_fOldStartTime;

	float m_fChangTime;
	float m_fOldChangTime;
};

