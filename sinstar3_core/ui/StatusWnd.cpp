#include "StdAfx.h"
#include "StatusWnd.h"
#include <helper/SMenuEx.h>
#include "ConfigDlg.h"
#include "../InputState.h"

#define SIZE_MAGNETIC	 5
#define MAX_SKINS	 80
namespace SOUI
{
	CStatusWnd::CStatusWnd(ICmdListener *pListener):CImeWnd(UIRES.LAYOUT.wnd_status_bar), m_pCmdListener(pListener)
	{
	}

	CStatusWnd::~CStatusWnd(void)
	{
	}

	int CStatusWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		int nRet = __super::OnCreate(lpCreateStruct);
		if(nRet != 0) return nRet;

		m_pBackGround = FindChildByID2<SStatusBackground>(R.id.status_bg);

		CRect rcWnd = GetWindowRect();
		CRect rcWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0);

		CPoint pt =CDataCenter::getSingletonPtr()->GetData().m_ptStatus;
		if(pt.x<0) pt.x = 0;
		if(pt.y<0) pt.y = 0;
		if(pt.x + rcWnd.Width() > rcWorkArea.right)
			pt.x = rcWorkArea.right - rcWnd.Width();
		if(pt.y + rcWnd.Height()> rcWorkArea.bottom)
			pt.y = rcWorkArea.bottom - rcWnd.Height();

		UpdateCompInfo();
		{
			SToggle * toggle = FindChildByID2<SToggle>(R.id.btn_charmode);
			if(toggle) toggle->SetToggle(g_SettingsL.bCharMode);
		}
		{
			SToggle * toggle = FindChildByID2<SToggle>(R.id.btn_sound);
			if(toggle) toggle->SetToggle(g_SettingsL.bSound);
		}
		{
			SToggle * toggle = FindChildByID2<SToggle>(R.id.btn_record);
			if(toggle) toggle->SetToggle(g_SettingsL.bSound);
		}


		SetWindowPos(HWND_TOPMOST,pt.x,pt.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
		return 0;
	}

	void CStatusWnd::OnRButtonUp(UINT nFlags,CPoint pt)
	{
		const MSG * pMsg = GetCurrentMessage();
		SHostWnd::OnMouseEvent(pMsg->message,pMsg->wParam,pMsg->lParam);

		SMenuEx menu;
		BOOL bLoad=menu.LoadMenu(UIRES.smenu.context);
		ClientToScreen(&pt);
		m_skinManager.ClearMap();
		SLOG_INFO("before trackpopupmenu");
		int nRet = menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_BOTTOMALIGN|TPM_RETURNCMD,pt.x,pt.y, m_hWnd);
		SLOG_INFO("after trackpopupmenu"<<" nRet:"<<nRet);
		if (nRet == R.id.config)
		{//system config
			CConfigDlg configDlg;
			configDlg.DoModal();
		}else if(nRet>=R.id.skin_def && nRet <= R.id.skin_def + MAX_SKINS)
		{//select menu
			m_skinManager.SetSkin(nRet);
		}
		else if (nRet >= R.id.comp_start && nRet < R.id.comp_start + 50)
		{//comps
			int iComp = nRet - R.id.comp_start;
			const SArray<CNameTypePair> & compList = CDataCenter::getSingleton().GetCompList();
			if (iComp < compList.GetCount())
			{
				ISComm_Comp_Open(compList[iComp].strName);
			}
		}
		else if (nRet > R.id.svr_showicon && nRet < R.id.svr_showicon + 50)
		{//svr page
			LPCSTR pszPages = ISComm_Svr_Pages();
			int uID = R.id.svr_showicon+1;
			while (uID<=nRet)
			{
				pszPages += strlen(pszPages) + 1;
				uID++;
			}
			ISComm_ShowServer(pszPages, strlen(pszPages));
		}
		else if (nRet == R.id.svr_showicon)
		{//show icon
			BOOL bTray = !ISComm_SvrTray_Get();
			ISComm_SvrTray_Set(bTray);
		}
		m_skinManager.ClearMap();
	}

	void CStatusWnd::OnInitMenuPopup(SMenuEx* menuPopup, UINT nIndex)
	{
		switch (menuPopup->GetContextHelpId())
		{
		case 2:
		{
			SMenuExItem *pdefSkin = menuPopup->GetMenuItem(R.id.skin_def);
			SStringT strCurSkin = CDataCenter::getSingletonPtr()->GetData().m_strSkin;
			if (strCurSkin.IsEmpty())
			{
				pdefSkin->SetAttribute(L"check", L"1");
			}
			m_skinManager.InitSkinMenu(menuPopup, theModule->GetDataPath() + _T("\\skins"), R.id.skin_def, strCurSkin);
			break;
		}
		case 3://dict
		{
			const SArray<CNameTypePair> & dis = CDataCenter::getSingleton().UpdateUserDict();
			int idStart = R.id.dict_close + 1;
			for (size_t i = 0; i < dis.GetCount(); i++)
			{
				SStringA strText = SStringA().Format("%s[%s]", dis[i].strName, dis[i].strType);
				menuPopup->InsertMenu(-1, MF_BYPOSITION, idStart + i, S_CA2T(strText));
			}
			//todo: select current item.
			break;
		}
		case 4://comp select
		{
			const SArray<CNameTypePair> &comps = CDataCenter::getSingleton().UpdateCompList();
			int idStart = R.id.comp_start;
			menuPopup->DeleteMenu(R.id.comp_start,MF_BYCOMMAND);
			int iSelComp = CDataCenter::getSingleton().GetSelectCompIndex();
			for (size_t i = 0; i < comps.GetCount(); i++)
			{
				SStringA strText = SStringA().Format("%s[%s]", comps[i].strName, comps[i].strType);
				UINT flag = MF_BYPOSITION;
				if (iSelComp == i) flag |= MF_CHECKED;
				menuPopup->InsertMenu(-1, flag, idStart + i, S_CA2T(strText));
			}
			//select comp
			break;
		}
		case 6://svr data manager
		{
			LPCSTR pszPages = ISComm_Svr_Pages();
			if (pszPages)
			{
				int nPos = 1;
				UINT uID = R.id.svr_showicon;
				while (*pszPages)
				{
					SStringA strName = pszPages;
					if (*pszPages == '\n')
						menuPopup->InsertMenu(nPos++, MF_BYPOSITION | MF_SEPARATOR, 0 , _T(""));
					else
						menuPopup->InsertMenu(nPos++, MF_BYPOSITION | MF_STRING, uID, S_CA2T(strName));
					uID++;
					pszPages += strName.GetLength() + 1;
				}
			}
			SMenuExItem *pItem = menuPopup->GetMenuItem(R.id.svr_showicon);
			if (pItem)
			{
				pItem->SetAttribute(L"check", L"1");
			}

			break;
		}
		}

	}

	void CStatusWnd::OnDragStatus(EventArgs *e)
	{
		EventDragMove *e2 = sobj_cast<EventDragMove>(e);
		CRect rcWnd;
		CSimpleWnd::GetWindowRect(&rcWnd);

		CPoint pt = rcWnd.TopLeft()+e2->ptMove;

		RECT rcWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0);

		if(pt.x-rcWorkArea.left<=SIZE_MAGNETIC) pt.x=rcWorkArea.left;
		if(pt.y-rcWorkArea.top<SIZE_MAGNETIC) pt.y=rcWorkArea.top;
		if(rcWorkArea.right-pt.x-rcWnd.Width()<SIZE_MAGNETIC) pt.x=rcWorkArea.right-rcWnd.Width();
		if(rcWorkArea.bottom-pt.y-rcWnd.Height()<SIZE_MAGNETIC) pt.y=rcWorkArea.bottom-rcWnd.Height();
		SetWindowPos(NULL,pt.x,pt.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);

		CDataCenter::getSingletonPtr()->GetData().m_ptStatus = pt;
	}

	void CStatusWnd::OnSetSkin(EventArgs *e)
	{
		OnDestroy();
		CREATESTRUCT cs;
		cs.cx=0;
		cs.cy=0;
		OnCreate(&cs);
	}


	void CStatusWnd::OnBtnExtend()
	{
		m_pBackGround->SetMode(SStatusBackground::MODE_EXTEND);

		FindChildByID(R.id.btn_status_extend)->SetVisible(TRUE,TRUE);
		FindChildByID(R.id.btn_status_shrink)->SetVisible(TRUE,TRUE);
		FindChildByID(R.id.btn_status_extend)->SetVisible(FALSE,TRUE);
		FindChildByID(R.id.status_extend)->SetVisible(TRUE,TRUE);
	}

	void CStatusWnd::OnBtnShrink()
	{
		m_pBackGround->SetMode(SStatusBackground::MODE_SHRINK);

		FindChildByID(R.id.btn_status_extend)->SetVisible(FALSE,TRUE);
		FindChildByID(R.id.btn_status_shrink)->SetVisible(FALSE,TRUE);
		FindChildByID(R.id.btn_status_extend)->SetVisible(TRUE,TRUE);
		FindChildByID(R.id.status_extend)->SetVisible(FALSE,TRUE);

	}

	void CStatusWnd::UpdateCompInfo()
	{
		FindChildByID(R.id.txt_comp)->SetWindowText(CDataCenter::getSingletonPtr()->GetData().m_compInfo.strCompName);
		SFlagView * pFlagView = FindChildByID2<SFlagView>(R.id.img_logo);
		if (pFlagView)
		{
			pFlagView->SetImeFlagData(ISComm_GetCompInfo()->pImeFlagData);
		}
	}

	void CStatusWnd::OnCompInfo(EventArgs *e)
	{
		if(!IsWindow())
			return;

		EventSvrNotify *e2 = sobj_cast<EventSvrNotify>(e);
		if(e2->wp == NT_COMPINFO)
		{
			UpdateCompInfo();
		}
	}

	void CStatusWnd::OnSwitchCharMode(EventArgs *e)
	{
		SToggle * toggle = sobj_cast<SToggle>(e->sender);
		if(toggle)
		{
			g_SettingsL.bCharMode = toggle->GetToggle();
		}
	}

	void CStatusWnd::OnSwitchRecord(EventArgs *e)
	{
		SToggle * toggle = sobj_cast<SToggle>(e->sender);
		if(toggle)
		{
			g_SettingsL.bRecord = toggle->GetToggle();
		}
	}

	void CStatusWnd::OnSwitchSound(EventArgs *e)
	{
		SToggle * toggle = sobj_cast<SToggle>(e->sender);
		if(toggle)
		{
			g_SettingsL.bSound = toggle->GetToggle();
		}

	}

	void CStatusWnd::OnBtnMakeWord()
	{
		m_pCmdListener->OnCommand(CMD_MAKEWORD,0);
	}

}

