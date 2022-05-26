#pragma once

#include "Scene.h"

class CStage_End :
    public CScene
{
public:
	CStage_End();
	virtual ~CStage_End();

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

	float m_fWhiteTime;
	float m_fOldWhiteTime;
	bool m_bWhite;

	float m_fWhiteEndTime;
	float m_fOldWhiteEndTime;
	bool m_bWhiteEnd;

	float m_fEggTime1;
	float m_fOldEggTime;
	bool m_bEggEnd1;

	float m_fEggTime2;
	bool m_bEggEnd2;

	float m_fEggTime3;
	bool m_bEggEnd3;

	float m_fEggTime4;
	bool m_bEggEnd4;
};

