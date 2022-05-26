#include "stdafx.h"
#include "UIMgr.h"
#include "AbstractFactory.h"

#include "ObjMgr.h"

#include "HpHp_UI.h"
#include "BmpMgr.h"
#include "DamageGen.h"
#include "Effect.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CUIMgr* CUIMgr::m_pInstance = nullptr;
CUIMgr::CUIMgr()
	: m_pHpHpUI(nullptr)
	, m_pInven(nullptr)
	, m_pSkill(nullptr)
	, m_pSlot(nullptr)
	, m_pShop(nullptr)
	, m_pCommunity(nullptr)
	, m_pQuest(nullptr)
	, m_pStat(nullptr)
	, m_pEquip(nullptr)
	, m_pScreen(nullptr)
	, m_pDomi(nullptr)
	, m_pBoss(nullptr)
	, m_pDead(nullptr)
	, m_pMiniMap_1(nullptr)
	, m_pMiniMap_2(nullptr)
	, m_pMiniMap_3(nullptr)
	, m_pMiniMap_4(nullptr)
	, m_pMiniMap_5(nullptr)
	, m_pMiniMap_6(nullptr)
	, m_pMiniMap_7(nullptr)
	, m_pMiniMap_Boss(nullptr)
	, m_pOption(nullptr)
	, m_fFontTime(0.f)
	, m_fOldFontTime(0.f)
	, m_iFontCount(1)
	, m_bStartDarkedMage(false)
	, m_bFontFadeOut(false)
	, m_bShop(false)
	, m_bCom(false)
	, m_iDamageEffect(0)
	, m_iDamageSkin(0)
	, m_bDead(false)
{

}

CUIMgr::~CUIMgr()
{
	Release();
}


void CUIMgr::Initialize(void)
{
	CObjMgr::Get_Instance()->PetReset();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerDead.bmp", L"PlayerDead");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/PetL.bmp", L"PetL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/PetR.bmp", L"PetR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/VetL.bmp", L"VetL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/VetR.bmp", L"VetR");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/cursor.bmp", L"Cursor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Screen.bmp", L"Screen");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/domiOpen.bmp", L"domiOpen");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/domiClose.bmp", L"domiClose");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HpMp.bmp", L"HpMp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/hp.bmp", L"hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/mp.bmp", L"mp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/exp.bmp", L"exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/expGage.bmp", L"expGage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inventory_Consum.bmp", L"Inventory_Consum");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inventory_Equip.bmp", L"Inventory_Equip");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/SkillInven.bmp", L"SkillInven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_content.bmp", L"Skill_content");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/store.bmp", L"store");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill1_Icon.bmp", L"Skill1_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill2_Icon.bmp", L"Skill2_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill3_Icon.bmp", L"Skill3_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill4_Icon.bmp", L"Skill4_Icon");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill1_Cool.bmp", L"Skill1_Cool");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill2_Cool.bmp", L"Skill2_Cool");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill3_Cool.bmp", L"Skill3_Cool");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill4_Cool.bmp", L"Skill4_Cool");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/quickslot.bmp", L"quickslot");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Damage.bmp", L"Damage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Damage2.bmp", L"Damage2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Damage3.bmp", L"Damage3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Damage4.bmp", L"Damage4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Damaged.bmp", L"Damaged");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Effect.bmp", L"Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clri.bmp", L"Clri");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Community.bmp", L"Community");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/stat.bmp", L"stat");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/StatButton.bmp", L"StatButton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Dead_UI.bmp", L"Dead_UI");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/EquipCon.bmp", L"EquipCon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Equip.bmp", L"Equip");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_1.bmp", L"MiniMap_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_2.bmp", L"MiniMap_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_3.bmp", L"MiniMap_3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_4.bmp", L"MiniMap_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_5.bmp", L"MiniMap_5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_6.bmp", L"MiniMap_6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_7.bmp", L"MiniMap_7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniMap_Boss.bmp", L"MiniMap_Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MiniPlayer.bmp", L"MiniPlayer");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/QuestUI.bmp", L"QuestUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Option.bmp", L"Option");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Alpha.bmp", L"Alpha");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MesoBig.bmp", L"MesoBig");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Meso.bmp", L"Meso");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RedPotion.bmp", L"RedPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BluePotion.bmp", L"BluePotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Equip.bmp", L"Equip");

	if (!m_pHpHpUI)
	{
		m_pHpHpUI = new CHpHp_UI;
		m_pHpHpUI->Initialize();
	}
	if (!m_pInven)
	{
		m_pInven = new CInven_UI;
		m_pInven->Initialize();
	}
	if (!m_pSkill)
	{
		m_pSkill = new CSkill_UI;
		m_pSkill->Initialize();
	}
	if (!m_pSlot)
	{
		m_pSlot = new CQSlot_UI;
		m_pSlot->Initialize();
	}
	if (!m_pShop)
	{
		m_pShop = new CShop_UI;
		m_pShop->Initialize();
	}
	if (!m_pCommunity)
	{
		m_pCommunity = new CCommunity_UI;
		m_pCommunity->Initialize();
	}
	if (!m_pQuest)
	{
		m_pQuest = new CQuest_UI;
		m_pQuest->Initialize();
	}
	if (!m_pScreen)
	{
		m_pScreen = new CScreen_UI;
		m_pScreen->Initialize();
	}
	if (!m_pDomi)
	{
		m_pDomi = new CScreen1_UI;
		m_pDomi->Initialize();
	}
	if (!m_pStat)
	{
		m_pStat = new CStatUI;
		m_pStat->Initialize();
	}
	if (!m_pEquip)
	{
		m_pEquip = new CEquip_UI;
		m_pEquip->Initialize();
	}
	if (!m_pDead)
	{
		m_pDead = new CDead_UI();
		m_pDead->Initialize();
	}
	if (!m_pOption)
	{
		m_pOption = new COption_UI();
		m_pOption->Initialize();
	}


	if (!m_pMiniMap_1)
	{
		m_pMiniMap_1 = new CMiniMap_1();
		m_pMiniMap_1->Initialize();
	}
	if (!m_pMiniMap_2)
	{
		m_pMiniMap_2 = new CMiniMap_2();
		m_pMiniMap_2->Initialize();
	}
	if (!m_pMiniMap_3)
	{
		m_pMiniMap_3 = new CMiniMap_3();
		m_pMiniMap_3->Initialize();
	}
	if (!m_pMiniMap_4)
	{
		m_pMiniMap_4 = new CMiniMap_4();
		m_pMiniMap_4->Initialize();
	}
	if (!m_pMiniMap_5)
	{
		m_pMiniMap_5 = new CMiniMap_5();
		m_pMiniMap_5->Initialize();
	}
	if (!m_pMiniMap_6)
	{
		m_pMiniMap_6 = new CMiniMap_6();
		m_pMiniMap_6->Initialize();
	}
	if (!m_pMiniMap_7)
	{
		m_pMiniMap_7 = new CMiniMap_7();
		m_pMiniMap_7->Initialize();
	}
	if (!m_pMiniMap_Boss)
	{
		m_pMiniMap_Boss = new CMiniMap_Boss();
		m_pMiniMap_Boss->Initialize();
	}

	ChangePlayerHp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iHp, CStatMgr::Get_Instance()->Get_PlayerMaxHP());
	ChangePlayerMp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMp, CStatMgr::Get_Instance()->Get_PlayerMaxMP());
	ChangePlayerExp(CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iExp, CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMaxExp);

	m_bStartDarkedMage = false;

}

void CUIMgr::Update(void)
{
	m_pHpHpUI->Update();
	m_pInven->Update();
	m_pSkill->Update();
	m_pSlot->Update();
	m_pShop->Update();
	m_pCommunity->Update();
	m_pQuest->Update();
	m_pOption->Update();
	m_pScreen->Update();
	m_pDomi->Update();
	m_pStat->Update();
	m_pEquip->Update();
	m_pDead->Update();

	UpdateMiniMap();

	if (m_pBoss)
		m_pBoss->Update();
}

void CUIMgr::Render(HDC hDC)
{
	m_pHpHpUI->Render(hDC);
	m_pInven->Render(hDC);
	m_pSkill->Render(hDC);
	m_pSlot->Render(hDC);
	m_pShop->Render(hDC);
	m_pCommunity->Render(hDC);
	m_pQuest->Render(hDC);
	m_pOption->Render(hDC);
	m_pStat->Render(hDC);
	m_pEquip->Render(hDC);
	m_pDead->Render(hDC);

	RenderMiniMap(hDC);


	m_pScreen->Render(hDC);

	if (m_pBoss)
		m_pBoss->Render(hDC);

	m_pDomi->Render(hDC);

	if (m_bStartDarkedMage)
		WriteDarkedMage(hDC);
}


void CUIMgr::StartWriteDarkedMage()
{
	m_bStartDarkedMage = true;
	m_fOldFontTime = GetTickCount64();
	m_fFontTime = 90.f;

	CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
	CSoundMgr::Get_Instance()->PlaySound(L"DarkTalk.wav", SOUND_NPC, 1);
}

void CUIMgr::WriteDarkedMage(HDC hDC)
{
	if (m_fOldFontTime + m_fFontTime < GetTickCount64())
	{
		++m_iFontCount;
		m_fOldFontTime = GetTickCount64();
	}

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 30;
	m_labelFontInfo.lfWidth = 12;
	m_labelFontInfo.lfCharSet = RUSSIAN_CHARSET;
	m_labelFontInfo.lfWeight = 700;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR lpOut[1024];

	if (!m_bFontFadeOut)
	{
		switch (m_iFontCount)
		{
		case 1:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 2:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 3:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라,"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라,"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 4:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 5:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 6:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, "));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 7:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 8:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 9:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 10:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 11:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 12:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 13:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. "));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. "));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 14:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 15:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 16:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 17:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 18:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 19:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 20:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 21:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다"));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다"));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 22:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 49:
			m_bFontFadeOut = true;
			m_fFontTime = 30.f;
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		default:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		}
	}
	else
	{
		switch (m_iFontCount)
		{
		case 49:
			SetTextColor(hDC, RGB(255, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(255, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 50:
			SetTextColor(hDC, RGB(220, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(220, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 51:
			SetTextColor(hDC, RGB(200, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(200, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 52:
			SetTextColor(hDC, RGB(180, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(180, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 53:
			SetTextColor(hDC, RGB(160, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(160, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 54:
			SetTextColor(hDC, RGB(140, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(140, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 55:
			SetTextColor(hDC, RGB(120, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(120, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 56:
			SetTextColor(hDC, RGB(100, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(100, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 57:
			SetTextColor(hDC, RGB(80, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(80, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 58:
			SetTextColor(hDC, RGB(60, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(60, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 59:
			SetTextColor(hDC, RGB(40, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(40, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		case 60:
			SetTextColor(hDC, RGB(20, 10, 10));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(20, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		default:
			SetTextColor(hDC, RGB(0, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470 - 1, 300 - 1, lpOut, lstrlen(lpOut));
			SetTextColor(hDC, RGB(0, 0, 0));
			wsprintf(lpOut, TEXT("오라, 대적자여. 운명을 완성할 때다."));
			TextOut(hDC, 470, 300, lpOut, lstrlen(lpOut));
			break;
		}
	}

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}


void CUIMgr::UpdateMiniMap()
{
	switch (CSceneMgr::Get_Instance()->Get_CurSceneId())
	{
	case SC_STAGE_1:
		m_pMiniMap_1->Update();
		break;
	case SC_STAGE_2:
		m_pMiniMap_2->Update();
		break;
	case SC_STAGE_3:
		m_pMiniMap_3->Update();
		break;
	case SC_STAGE_4:
		m_pMiniMap_4->Update();
		break;
	case SC_STAGE_5:
		m_pMiniMap_5->Update();
		break;
	case SC_STAGE_6:
		m_pMiniMap_6->Update();
		break;
	case SC_STAGE_7:
		m_pMiniMap_7->Update();
		break;
	case SC_STAGE_BOSS:
		m_pMiniMap_Boss->Update();
		break;
	}
}
void CUIMgr::RenderMiniMap(HDC hDC)
{
	switch (CSceneMgr::Get_Instance()->Get_CurSceneId())
	{
	case SC_STAGE_1:
		m_pMiniMap_1->Render(hDC);
		break;
	case SC_STAGE_2:
		m_pMiniMap_2->Render(hDC);
		break;
	case SC_STAGE_3:
		m_pMiniMap_3->Render(hDC);
		break;
	case SC_STAGE_4:
		m_pMiniMap_4->Render(hDC);
		break;
	case SC_STAGE_5:
		m_pMiniMap_5->Render(hDC);
		break;
	case SC_STAGE_6:
		m_pMiniMap_6->Render(hDC);
		break;
	case SC_STAGE_7:
		m_pMiniMap_7->Render(hDC);
		break;
	case SC_STAGE_BOSS:
		m_pMiniMap_Boss->Render(hDC);
		break;
	}
}


void CUIMgr::ChangePlayerHp(int _iHp, int _iMaxHp)
{
	if (_iHp > _iMaxHp)
	{
		_iHp = _iMaxHp;
		CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iHp = _iMaxHp;
	}
		
	float fP = _iHp / (float)_iMaxHp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPH(fP);
}

void CUIMgr::ChangePlayerMp(int _iMp, int _iMaxMp)
{
	if (_iMp > _iMaxMp)
	{
		_iMp = _iMaxMp;
		CObjMgr::Get_Instance()->Get_Player()->Get_Stat().iMp = _iMaxMp;
	}
		
	float fP = _iMp / (float)_iMaxMp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPM(fP);
}

void CUIMgr::ChangePlayerExp(int _iExp, int _iMaxExp)
{
	float fP = _iExp / (float)_iMaxExp;

	if (fP < 0.f)
		fP = 0.f;

	m_pHpHpUI->SetPE(fP);
}


void CUIMgr::MakeDamge(int _iHitCount, float _fHitTime, int _iStart, int _iEnd, float _fMeX, float _fMeY, float _fPivot, float _fTempPivot)
{
	CDamageGen* pGen = (CDamageGen*)CAbstractFactory<CDamageGen>::Create();
	pGen->Init(_iHitCount, _fHitTime, _iStart, _iEnd, _fMeX, _fMeY, _fPivot , _fTempPivot);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLE, pGen);
}


void CUIMgr::ShowBossHP(float _fHp, float _fMaxHp, float _fMp, float _fMaxMp)
{
	if (!m_pBoss)
	{
		m_pBoss = new CBoss_UI;
		m_pBoss->Initialize();
	}
	ChangeBossHp(_fHp, _fMaxHp);
	ChangeBossMp(_fMp, _fMaxMp);
}


void CUIMgr::ChangeBossHp(int _iHp, int _iMaxHp)
{
	float fP = _iHp / (float)_iMaxHp;

	if (fP < 0.f)
		fP = 0.f;

	m_pBoss->SetPH(fP);
}

void CUIMgr::ChangeBossMp(int _iMp, int _iMaxMp)
{
	float fP = _iMp / (float)_iMaxMp;

	if (fP < 0.f)
		fP = 0.f;

	m_pBoss->SetPM(fP);
}


void CUIMgr::Release(void)
{
	if (m_pHpHpUI != nullptr)
		Safe_Delete(m_pHpHpUI);
	if (m_pInven != nullptr)
		Safe_Delete(m_pInven);
	if (m_pSkill != nullptr)
		Safe_Delete(m_pSkill);
	if (m_pSlot != nullptr)
		Safe_Delete(m_pSlot);
	if (m_pShop != nullptr)
		Safe_Delete(m_pShop);
	if (m_pCommunity != nullptr)
		Safe_Delete(m_pCommunity);
	if (m_pQuest != nullptr)
		Safe_Delete(m_pQuest);
	if (m_pScreen != nullptr)
		Safe_Delete(m_pScreen);
	if (m_pDomi != nullptr)
		Safe_Delete(m_pDomi);
	if (m_pBoss != nullptr)
		Safe_Delete(m_pBoss);
	if (m_pStat != nullptr)
		Safe_Delete(m_pStat);
	if (m_pEquip != nullptr)
		Safe_Delete(m_pEquip); 
	if (m_pDead != nullptr)
		Safe_Delete(m_pDead);
	if (m_pMiniMap_1 != nullptr)
		Safe_Delete(m_pMiniMap_1);
	if (m_pMiniMap_2 != nullptr)
		Safe_Delete(m_pMiniMap_2);
	if (m_pMiniMap_3 != nullptr)
		Safe_Delete(m_pMiniMap_3);
	if (m_pMiniMap_4 != nullptr)
		Safe_Delete(m_pMiniMap_4);
	if (m_pMiniMap_5 != nullptr)
		Safe_Delete(m_pMiniMap_5);
	if (m_pMiniMap_6 != nullptr)
		Safe_Delete(m_pMiniMap_6);
	if (m_pMiniMap_7 != nullptr)
		Safe_Delete(m_pMiniMap_7);
	if (m_pMiniMap_Boss != nullptr)
		Safe_Delete(m_pMiniMap_Boss);
	if (m_pOption != nullptr)
		Safe_Delete(m_pOption);
}




void CUIMgr::OpenShop()
{
	if (!m_bShop)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);
		m_bShop = true;
	}

	m_pShop->Open();
}
void CUIMgr::CloseShop()
{
	if (m_bShop)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuDown.wav", SOUND_UI, 1);
		m_bShop = false;
	}

	m_pShop->Close();
}

void CUIMgr::OpenCommunity()
{
	if (!m_bCom)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);
		m_bCom = true;
	}
	m_pCommunity->Open();
}
void CUIMgr::CloseCommunity()
{
	if (m_bCom)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);
		m_bCom = false;
	}
	m_pCommunity->Close();
}

void CUIMgr::OpenDead()
{
	if (!m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);
		m_bDead = true;
	}
	m_pDead->Open();
}

void CUIMgr::CloseDead()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_UI);
		CSoundMgr::Get_Instance()->PlaySound(L"MenuUp.wav", SOUND_UI, 1);
		m_bDead = false;
	}
	m_pDead->Close();
}
