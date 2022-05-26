#pragma once

#include "Logo.h"
#include "MyMenu.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	CScene* Get_CurScene(void) { return m_pScene; }
	SCENEID Get_CurSceneId(void) { return m_eCurScene; }
	void		Scene_Change(SCENEID eID);
	
	bool Get_Scene3First() { return m_bScene3First; }
	void Set_Scene3First() { m_bScene3First = false; }

	void Start_FadeIn();
	void Start_FadeOut();
	void Start_WhiteIn();
	void End_WhiteIn();

public:
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	float GetBgmSound() { return m_fBgmSound * 0.1; }
	float GetEffectSound() { return m_fEffectSound * 0.1; }

	void IncreaseBgmSound();
	void DecreaseBgmSound();
	void IncreaseEffectSound();
	void DecreaseEffectSound();

	void Fade_Update();
	void FadeOut_Update();
	void WhiteIn_Update();


#pragma region Ins
public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*		m_pInstance;
#pragma	endregion


private:
	CScene*					m_pScene;
	WCHAR*					m_pKey;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

	bool m_bScene3First;

	float m_fBgmSound;
	float m_fEffectSound;

	int m_iAlpha;
	bool m_bFade;
	bool m_bFadeOut;
	bool m_bWhiteIn;
	float m_fAlphaTime;
	float m_fOldAlphaTime;

	float m_fSceneChange;
	float m_fOldSceneChange;

	bool m_bSceneTick;
};

