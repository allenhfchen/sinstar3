// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

class CompBuilderLoader;

class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

protected:
	void OnBroweComp();
	void OnBroweCit();
	void OnBroweLogo();
	void OnBroweKeymap();

	void UpdateLogo();

	void OnBuildComp();
	void OnExportComp();

	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_ID_COMMAND(R.id.btn_browse_comp,OnBroweComp)
		EVENT_ID_COMMAND(R.id.btn_browse_save, OnBroweCit)
		EVENT_ID_COMMAND(R.id.btn_browse_logo, OnBroweLogo)
		EVENT_ID_COMMAND(R.id.btn_browse_keymap, OnBroweKeymap)
		EVENT_ID_COMMAND(R.id.btn_build,OnBuildComp)
		EVENT_ID_COMMAND(R.id.btn_export,OnExportComp)
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	CompBuilderLoader * m_pLoader;
};
