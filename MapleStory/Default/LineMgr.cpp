#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);

	for (auto& iter : m_HangLineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	for_each(m_HangLineList.begin(), m_HangLineList.end(), CDeleteObj());
	m_HangLineList.clear();
}

CLine* CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY, bool _bGetSecond)
{
	// ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;
	CLine*		pSecondTarget = nullptr;

	float fMinY = 0.f;
	for (auto& iter : m_LineList)
	{
		// 1. �ش� ������ x�� ���� �ȿ� �ִ�.
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			// 2. L- P���� ���� ����, ���� ���� ���� ������ �����Ѵ�.
			float	x1 = iter->Get_Info().tLPoint.fX;
			float	x2 = iter->Get_Info().tRPoint.fX;

			float	y1 = iter->Get_Info().tLPoint.fY;
			float	y2 = iter->Get_Info().tRPoint.fY;

			float fTempY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
			
			// ������ ���� (���� �÷��̾� ���� �ִ�)
			fTempY = fTempY - _fY;
			if (-3.f > fTempY)
				continue;

			// ���� ������ ��
			if (fTempY < fMinY)
			{
				fMinY = fTempY;
				pSecondTarget = pTarget;
				pTarget = iter;
			}
			else if (!pTarget)
			{
				fMinY = fTempY;
				pTarget = iter;
			}
		}
		
	}

	if (!pSecondTarget)
		pSecondTarget = pTarget;

	if (_bGetSecond)
	{
		float	x1 = pSecondTarget->Get_Info().tLPoint.fX;
		float	x2 = pSecondTarget->Get_Info().tRPoint.fX;

		float	y1 = pSecondTarget->Get_Info().tLPoint.fY;
		float	y2 = pSecondTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}
	else
	{ 
   		float	x1 = pTarget->Get_Info().tLPoint.fX;
		float	x2 = pTarget->Get_Info().tRPoint.fX;

		float	y1 = pTarget->Get_Info().tLPoint.fY;
		float	y2 = pTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}

	return _bGetSecond ? pSecondTarget : pTarget;
}

CLine* CLineMgr::Collision_HangLine(float& _fX, float& _fY, float* pY)
{
	// ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_HangLineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_HangLineList)
	{
		// 1. �ش� ������ x��, y�� ���� �ȿ� �ִ�. >> ���� Ż �� �ִ�
		if (_fX >= iter->Get_Info().tLPoint.fX - 40.f &&
			_fX <= iter->Get_Info().tRPoint.fX + 40.f &&
			_fY >= iter->Get_Info().tLPoint.fY - 5.f &&
			_fY <= iter->Get_Info().tRPoint.fY)
		{
			pTarget = iter;
		}
	}

	if (pTarget)
	{
		float	x1 = pTarget->Get_Info().tLPoint.fX;
		float	x2 = pTarget->Get_Info().tRPoint.fX;

		float	y1 = pTarget->Get_Info().tLPoint.fY;
		float	y2 = pTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}

	return pTarget;
}


void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

void CLineMgr::Scene_1()
{
	Release();

	LINE		tf{ -5.f, 934.f, 797.f, 934.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(797.f, 934.f, 875.f, 996.f);
	m_LineList.push_back(new CLine(tf, true));
	tf.Init(875.f, 996.f, 975.f, 996.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(975.f, 996.f, 1056.f, 1056.f);
	m_LineList.push_back(new CLine(tf, true));
	tf.Init(1056.f, 1056.f, 2237.f, 1056.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(99.f, 784.f, 228.f, 784.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(546.f, 725.f, 680.f, 725.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(727.f, 723.f, 1667.f, 723.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1671.f, 785.f, 1755.f, 785.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1772.f, 843.f, 1845.f, 843.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1854.f, 905.f, 1937.f, 905.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1943.f, 963.f, 2028.f, 963.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2037.f, 1024.f, 2119.f, 1024.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1717.f, 604.f, 1843.f, 604.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1626.f, 663.f, 1757.f, 663.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1899.f, 544.f, 2239.f, 554.f);
	m_LineList.push_back(new CLine(tf));

	tf.Init(779, 720.f, 779.f, 928.f);
	m_HangLineList.push_back(new CLine(tf));

}

void CLineMgr::Scene_2()
{
	Release();

	LINE		tf{ 0.f, 1570.f, 2238.f, 1570.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(385.f, 1500.f, 475.f, 1500.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1547, 1387.f, 1705.f, 1387.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init( 1752.f, 1435.f, 1846.f, 1435.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1700.f, 1500.f, 1870.f, 1500.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(373.f, 1270.f, 1859.f, 1270.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(281.f, 1150.f, 417.f, 1150.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(281.f, 1090.f, 417.f, 1090.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(465.f, 1030.f, 1770.f, 1030.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init( 1641.f, 1202.f, 1814.f, 1202.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1694.f, 1136.f, 1786.f, 1136.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(456.f, 1205.f, 549.f, 1205.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(531.f, 963.f, 625.f, 963.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(375.f, 909.f, 507.f, 909.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(375.f, 850.f, 507.f, 850.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(552.f, 787.f, 1678.f, 787.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1559.f, 960.f, 1730.f, 960.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1615.f, 896.f, 1704.f, 896.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(613.f, 724.f, 704.f, 724.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(463.f, 670.f, 597.f, 670.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1457.f, 718.f, 1630.f, 718.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1515.f, 655.f, 1605.f, 655.f);
	m_LineList.push_back(new CLine(tf));


	// ��
	tf.Init(1768.f, 1264.f, 1768.f, 1387.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1164.f, 1264.f, 1164.f, 1473.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(419.f, 1264.f, 419.f, 1437.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(825.f, 1025.f, 825.f, 1025.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1645.f, 787.f, 1645.f, 845.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1200.f, 785.f, 1200.f, 957.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(825.f, 1025.f, 825.f, 1200.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1725.f, 1028.f, 1725.f, 1088.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1199.f, 783.f, 1199.f, 960.f);
	m_HangLineList.push_back(new CLine(tf));

}

void CLineMgr::Scene_3()
{
	Release();

	LINE		tf{ 0.f, 643.f, 1300.f, 643.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(1300.f, 643.f, 1388.f, 703.f);
	m_LineList.push_back(new CLine(tf, true));
	tf.Init(1388.f, 703.f, 1482.f, 703.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1482.f, 703.f, 1569.f, 766.f);
	m_LineList.push_back(new CLine(tf, true));
	tf.Init(1569.f, 766.f, 3546.f, 766.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(961.f, 495.f, 1089.f, 495.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1140.f, 436.f, 2173.f, 436.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2175.f, 494.f, 2261.f, 494.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2267.f, 554.f, 2351.f, 554.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2361.f, 613.f, 2442.f, 613.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2448.f, 675.f, 2531.f, 675.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2537.f, 735.f, 2622.f, 735.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2132.f, 376.f, 2260.f, 376.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2310.f, 315.f, 2440.f, 315.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2491.f, 254.f, 3160.f, 254.f);
	m_LineList.push_back(new CLine(tf));


	tf.Init(1035.f, 485.f, 1035.f, 603.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1447.f, 428.f, 1447.f, 626.f);
	m_HangLineList.push_back(new CLine(tf));

}

void CLineMgr::Scene_4()
{
	Release();

	LINE		tf{ 910.f, 1002.f, 2789.f, 1002.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(810.f, 942.f, 935.f, 942.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(540.f, 880.f, 860.f, 880.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(0.f, 823.f, 560.f, 823.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(477.f, 791.f, 1410.f, 791.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1424.f, 851.f, 1504.f, 851.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1515.f, 909.f, 1593.f, 909.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1606.f, 971.f, 1682.f, 971.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1466.f, 735.f, 1598.f, 735.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1647.f, 672.f, 1775.f, 672.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1647.f, 552.f, 1773.f, 552.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1464.f, 492.f, 1594.f, 492.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1825.f, 613.f, 2405.f, 613.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(659.f, 434.f, 1411.f, 434.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(2368.f, 374.f, 2767.f, 374.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1465.f, 375.f, 1594.f, 375.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1465.f, 314.f, 1594.f, 314.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1646.f, 252.f, 2314.f, 252.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(30.f, 372.f, 599.f, 372.f);
	m_LineList.push_back(new CLine(tf));


	tf.Init(822.f, 431.f, 822.f, 747.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1344.f, 783.f, 1344.f, 960.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(2194.f, 605.f, 2194.f, 929.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1918.f, 246.f, 1918.f, 571.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(2444.f, 368.f, 2444.f, 696.f);
	m_HangLineList.push_back(new CLine(tf));


}

void CLineMgr::Scene_5()
{
	Release();

	LINE		tf{ -5.f, 1035.f, 1420.f, 1035.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(867.f, 735.f, 1421.f, 735.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(-5.f, 734.f, 729.f, 734.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(774.f, 675.f, 823.f, 675.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(686.f, 615.f, 733.f, 615.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(755.f, 556.f, 818.f, 556.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(864.f, 496.f, 1419.f, 496.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(-5.f, 435.f, 821.f, 435.f);
	m_LineList.push_back(new CLine(tf));


	tf.Init(339.f, 728.f, 339.f, 968.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1076.f, 722.f, 1076.f, 969.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(962.f, 483.f, 962.f, 687.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(189.f, 424.f, 189.f, 669.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(484.f, 424.f, 484.f, 670.f);
	m_HangLineList.push_back(new CLine(tf));

}

void CLineMgr::Scene_6()
{
	Release();

	LINE		tf{ -5.f, 671.f, 1419.f, 671.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(261.f, 318.f, 1196.f, 318.f);
	m_LineList.push_back(new CLine(tf));

	tf.Init(528.f, 314.f, 528.f, 620.f);
	m_HangLineList.push_back(new CLine(tf));
}

void CLineMgr::Scene_7()
{
	Release();

	LINE		tf{ -5.f, 583.f, 1826.f, 583.f };
	m_LineList.push_back(new CLine(tf));
}

void CLineMgr::Scene_Boss()
{
	Release();

	LINE		tf{ 0.f, 700.f, 2100.f, 700.f };
	m_LineList.push_back(new CLine(tf));
}
