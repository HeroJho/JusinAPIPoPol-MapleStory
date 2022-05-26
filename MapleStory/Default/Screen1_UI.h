#pragma once
#include "Obj.h"
#include "SoundMgr.h"
class CScreen1_UI :
    public CObj
{
public:
	CScreen1_UI();
	~CScreen1_UI();

public:
	void StartOpen() 
	{ 
		m_bStart = true; 
		m_tFrame.dwTime = (DWORD)GetTickCount64(); 
		Set_FrameKey(L"domiOpen"); m_tFrame.iFrameStart = 0; 
		m_tFrame.iFrameEnd = 20; 

		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"domiOpen.wav", SOUND_PEFFECT3, 1);
	}
	void StartClose() 
	{ 
		m_bStart = true; 
		m_tFrame.dwTime = (DWORD)GetTickCount64(); Set_FrameKey(L"domiClose");
		m_tFrame.iFrameStart = 0; 
		m_tFrame.iFrameEnd = 17; 
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"domiClose.wav", SOUND_PEFFECT3, 1);
	}
	void Reset() { m_bStart = false; m_tFrame.iFrameStart = 0; }


public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOther) override;

private:
	void Move_Frame(void);

private:
	bool m_bStart;

};

