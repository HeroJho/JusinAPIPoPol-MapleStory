#pragma once
#include "Scene.h"
class CStage_Boss :
    public CScene
{
public:
	CStage_Boss();
	virtual ~CStage_Boss();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void RenderBackGround(HDC hDC);

};

