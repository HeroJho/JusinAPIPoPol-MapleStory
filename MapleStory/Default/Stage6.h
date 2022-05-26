#pragma once
#include "Scene.h"
class CStage6 :
    public CScene
{
public:
	CStage6();
	virtual ~CStage6();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void RenderBackGround(HDC hDC);
	void MakeMap();

};

