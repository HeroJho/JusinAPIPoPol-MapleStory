#include "stdafx.h"
#include "StatMgr.h"
#include "AbstractFactory.h"

#include "ObjMgr.h"

#include "BladeFury.h"
#include "KarmaFury.h"
#include "PhantomBlow.h"
#include "BladeStorm.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "SkillMgr.h"
#include "InvenMgr.h"
#include "UIMgr.h"


CStatMgr* CStatMgr::m_pInstance = nullptr;

CStatMgr::CStatMgr()
	: m_pPlayer(nullptr)
	, m_iPlusAT(0)
	, m_iPlusHP(0)
	, m_iPlusMP(0)
	, m_iPlusSP(0)
	, m_iPlusSTR(0)
	, m_iPlusDEX(0)
	, m_iPlusINT(0)
	, m_iPlusLUK(0)
	, m_iStatPoint(0)
	, m_iSkillPoint(0)
{
	m_tPlayerState.iSTR = 10;
	m_tPlayerState.iDEX = 10;
	m_tPlayerState.iINT = 10;
	m_tPlayerState.iLUK = 10;

	m_tWeapon = {};
	m_tShute = {};
	m_tShose = {};
	m_tGyenjong = {};
	m_tCave = {};
	m_tHet = {};
	m_tGlove = {};

}

CStatMgr::~CStatMgr()
{
	Release();
}


int CStatMgr::Get_PlayerAT()
{
	return m_pPlayer->Get_Stat().iAt + Get_TotalAT();
}
int CStatMgr::Get_PlayerMaxHP()
{
	return m_pPlayer->Get_Stat().iMaxHp + Get_PlusMaxHp();
}
int CStatMgr::Get_PlayerMaxMP()
{
	return m_pPlayer->Get_Stat().iMaxMp + Get_PlusMaxMp();
}
float CStatMgr::Get_PlayerMaxSP()
{
	return m_pPlayer->GetSpeed() + m_iPlusSP;
}

int CStatMgr::Get_TotalAT()
{
	return  Get_PlusAT() + m_tPlayerState.iLUK + Get_PlusLUK() + m_tPlayerState.iDEX + (Get_PlusDEX() / 2) + m_tPlayerState.iSTR + (Get_PlusSTR() / 2) + m_tPlayerState.iINT + (Get_PlusINT() / 2);
}

int CStatMgr::Get_PlusAT()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iAt;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iAt;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iAt;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iAt;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iAt;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iAt;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iAt;

	return total;
}
int CStatMgr::Get_PlusMaxHp()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iHp;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iHp;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iHp;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iHp;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iHp;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iHp;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iHp;

	return total;
}
int CStatMgr::Get_PlusMaxMp()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iMp;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iMp;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iMp;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iMp;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iMp;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iMp;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iMp;

	return total;
}
int CStatMgr::Get_PlusSTR()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iSTR;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iSTR;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iSTR;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iSTR;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iSTR;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iSTR;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iSTR;

	return total;
}
int CStatMgr::Get_PlusDEX()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iDEX;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iDEX;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iDEX;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iDEX;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iDEX;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iDEX;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iDEX;

	return total;
}
int CStatMgr::Get_PlusINT()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iINT;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iINT;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iINT;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iINT;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iINT;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iINT;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iINT;

	return total;
}
int CStatMgr::Get_PlusLUK()
{
	int total = 0;
	if (m_tWeapon.InvenID != 100)
		total += m_tWeapon.iLUK;
	if (m_tShute.InvenID != 100)
		total += m_tShute.iLUK;
	if (m_tShose.InvenID != 100)
		total += m_tShose.iLUK;
	if (m_tGyenjong.InvenID != 100)
		total += m_tGyenjong.iLUK;
	if (m_tCave.InvenID != 100)
		total += m_tCave.iLUK;
	if (m_tHet.InvenID != 100)
		total += m_tHet.iLUK;
	if (m_tGlove.InvenID != 100)
		total += m_tGlove.iLUK;

	return total;
}


void CStatMgr::Increase_STR()
{
	if (!AddStatPoint(-1))
		return;

	++m_tPlayerState.iSTR;
}
void CStatMgr::Increase_DEX()
{
	if (!AddStatPoint(-1))
		return;

	++m_tPlayerState.iDEX;
}
void CStatMgr::Increase_INT()
{
	if (!AddStatPoint(-1))
		return;

	++m_tPlayerState.iINT;
}
void CStatMgr::Increase_LUK()
{
	if (!AddStatPoint(-1))
		return;

	++m_tPlayerState.iLUK;
}

void CStatMgr::Increase_Skill_1()
{
	if (!AddSkillPoint(-1))
		return;

	CSkillMgr::Get_Instance()->UpSKill_1();
}
void CStatMgr::Increase_Skill_2()
{
	if (!AddSkillPoint(-1))
		return;

	CSkillMgr::Get_Instance()->UpSKill_2();
}
void CStatMgr::Increase_Skill_3()
{
	if (!AddSkillPoint(-1))
		return;

	CSkillMgr::Get_Instance()->UpSKill_3();
}
void CStatMgr::Increase_Skill_4()
{
	if (!AddSkillPoint(-1))
		return;

	CSkillMgr::Get_Instance()->UpSKill_4();
}


void CStatMgr::Set_Weapon(ITEM _tInfo)
{
	if (_tInfo.sTag != "Weapon")
		return;

	m_tWeapon = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tWeapon.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Shute(ITEM _tInfo)
{
	if (_tInfo.sTag != "Shute")
		return;

	m_tShute = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tShute.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Shose(ITEM _tInfo)
{
	if (_tInfo.sTag != "Shose")
		return;

	m_tShose = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tShose.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Gyenjong(ITEM _tInfo)
{
	if (_tInfo.sTag != "Gyenjong")
		return;

	m_tGyenjong = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tGyenjong.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Cave(ITEM _tInfo)
{
	if (_tInfo.sTag != "Cave")
		return;

	m_tCave = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tCave.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Het(ITEM _tInfo)
{
	if (_tInfo.sTag != "Het")
		return;

	m_tHet = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tHet.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Set_Glove(ITEM _tInfo)
{
	if (_tInfo.sTag != "Glove")
		return;

	m_tGlove = _tInfo;
	CInvenMgr::Get_Instance()->Remove_EquipInfo(m_tGlove.InvenID);

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}


void CStatMgr::Initialize(void)
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
}

int CStatMgr::Update(void)
{


	return 0;
}

void CStatMgr::Release(void)
{
}

void CStatMgr::Remove_Weapon()
{
	m_tWeapon.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Shute()
{
	m_tShute.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Shose()
{
	m_tShose.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Gyenjong()
{
	m_tGyenjong.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Cave()
{
	m_tCave.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Het()
{
	m_tHet.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
void CStatMgr::Remove_Glove()
{
	m_tGlove.InvenID = 100;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_pPlayer->Get_Stat().iHp, Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->ChangePlayerMp(m_pPlayer->Get_Stat().iMp, Get_PlayerMaxMP());
}
