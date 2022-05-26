#pragma once

#include "HpHp_UI.h"
#include "Inven_UI.h"
#include "Skill_UI.h"
#include "QSlot_UI.h"
#include "Shop_UI.h"
#include "Community_UI.h"
#include "Quest_UI.h"
#include "Screen_UI.h"
#include "Screen1_UI.h"
#include "Boss_UI.h"
#include "StatUI.h"
#include "Equip_UI.h"
#include "Dead_UI.h"
#include "MiniMap_1.h"
#include "MiniMap_2.h"
#include "MiniMap_3.h"
#include "MiniMap_4.h"
#include "MiniMap_5.h"
#include "MiniMap_6.h"
#include "MiniMap_7.h"
#include "MiniMap_Boss.h"
#include "Option_UI.h"


class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

#pragma region Ins
public:
	static		CUIMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
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
	static CUIMgr* m_pInstance;
#pragma endregion

public: 
	CObj* Get_InvenUI() { return m_pInven; }
	CObj* Get_SkillUI() { return m_pSkill; }
	CObj* Get_SlotUI() { return m_pSlot; }
	CObj* Get_ShopUI() { return m_pShop; }
	CObj* Get_StatUI() { return m_pStat; }
	CObj* Get_EquipUI() { return m_pEquip; }
	CObj* Get_CommunityUI() { return m_pCommunity; }
	CObj* Get_QuestUI() { return m_pQuest; }
	CObj* Get_BossUI() { return m_pBoss; }
	CObj* Get_DeadUI() { return m_pDead; }
	CObj* Get_OptionUI() { return m_pOption; }

	int Get_PomDamage() { return m_iDamageEffect; }
	void Set_PomDamage(int iValue) { m_iDamageEffect = iValue; }
	int Get_DamageSkin() { return m_iDamageSkin; }
	void Set_DamageSkin(int iValue) { m_iDamageSkin = iValue; }
	
public:
	void OpenShop();
	void CloseShop();

	void OpenCommunity();
	void CloseCommunity();

	void OpenDead();
	void CloseDead();

	void ScreenStart() { m_pScreen->Start(); }
	void ScreenReset() { m_pScreen->Reset(); }
	void DomiOpen()	 { m_pDomi->StartOpen(); }
	void DomiClose() { m_pDomi->StartClose(); }
	void DomiReset() { m_pDomi->Reset(); }
	void StartWriteDarkedMage();
	void WriteDarkedMage(HDC hDC);
	void WriteDarkedMageReset() { m_bStartDarkedMage = false; }

	void UpdateMiniMap();
	void RenderMiniMap(HDC hDC);


public:
	void		Initialize(void);
	void		Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	void ChangePlayerHp(int _iHp, int _iMaxHp);
	void ChangePlayerMp(int _iMp, int _iMaxMp);
	void ChangePlayerExp(int _iExp, int _iMaxExp);
	void MakeDamge(int _iHitCount, float _fHitTime, int _iStart, int _iEnd, float _fMeX, float _fMeY, float _fPivot, float _fTempPivot);

	void ShowBossHP(float _fHp, float _fMaxHp, float _fMp, float _fMaxMp);
	void ChangeBossHp(int _iHp, int _iMaxHp);
	void ChangeBossMp(int _iMp, int _iMaxMp);

private:
	CHpHp_UI* m_pHpHpUI;

	CInven_UI* m_pInven;
	CSkill_UI* m_pSkill;
	CQSlot_UI* m_pSlot;
	CShop_UI* m_pShop;
	COption_UI* m_pOption;
	CCommunity_UI* m_pCommunity;
	CStatUI* m_pStat;
	CEquip_UI* m_pEquip;
	CDead_UI* m_pDead;

	CQuest_UI* m_pQuest;
	CScreen_UI* m_pScreen;
	CScreen1_UI* m_pDomi;
	CBoss_UI* m_pBoss;

	CMiniMap_1* m_pMiniMap_1;
	CMiniMap_2* m_pMiniMap_2;
	CMiniMap_3* m_pMiniMap_3;
	CMiniMap_4* m_pMiniMap_4;
	CMiniMap_5* m_pMiniMap_5;
	CMiniMap_6* m_pMiniMap_6;
	CMiniMap_7* m_pMiniMap_7;
	CMiniMap_Boss* m_pMiniMap_Boss;

private:
	bool m_bStartDarkedMage;
	bool m_bFontFadeOut;
	float m_fFontTime;
	float m_fOldFontTime;
	int	  m_iFontCount;

	bool m_bShop;
	bool m_bCom;
	bool m_bDead;

	int m_iDamageEffect;
	int m_iDamageSkin;
};
