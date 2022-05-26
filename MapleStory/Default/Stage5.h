#pragma once
#include "Scene.h"
class CStage5 :
    public CScene
{
public:
	CStage5();
	virtual ~CStage5();

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

