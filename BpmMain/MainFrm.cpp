// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "BpmMainView.h"
#include "MainFrm.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

void CMainFrame::OnFinalMessage(HWND hWnd)
{
	if( m_spCounterCtl )
		m_spCounterCtl.Release();
}

void  CMainFrame::UpdateShowHistory()
{
	if( m_spCounterCtl )
	{
		VARIANT_BOOL fShown = VARIANT_TRUE;
		m_spCounterCtl->get_ShowHistoryPanel(&fShown);
		UISetCheck(IDC_SHOWHISTORY, fShown==VARIANT_TRUE?1:0);
	}
}


LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();

	m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
	m_wndCounter = m_hWndClient;

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	m_wndCounter.CreateControl(OLESTR("BpmCounter.BpmCounterCtl.1"));
	m_wndCounter.QueryControl(&m_spCounterCtl);
	UpdateShowHistory();
	return 0;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
		m_spCounterCtl->About();
	return 0;
}

LRESULT CMainFrame::OnClearHistory(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
		m_spCounterCtl->ClearHistory();
	return 0;
}

LRESULT CMainFrame::OnShowHistory(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
	{
		VARIANT_BOOL fShown = VARIANT_FALSE;
		m_spCounterCtl->get_ShowHistoryPanel(&fShown);
		if( fShown==VARIANT_TRUE )
			m_spCounterCtl->put_ShowHistoryPanel(VARIANT_FALSE);
		else
			m_spCounterCtl->put_ShowHistoryPanel(VARIANT_TRUE);

		UpdateShowHistory();
	}
	return 0;
}

LRESULT CMainFrame::OnBeat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
		m_spCounterCtl->Beat();
	return 0;
}

LRESULT CMainFrame::OnKeyBeat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
		m_spCounterCtl->KeyBeat();
	return 0;
}

LRESULT CMainFrame::OnReset(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
	{
		m_spCounterCtl->Reset();
	}
	return 0;
}

LRESULT CMainFrame::OnResetAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( m_spCounterCtl )
	{
		m_spCounterCtl->ResetAll();
	}
	return 0;
}


LRESULT CMainFrame::OnHomepage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString sLink;
	sLink.LoadString(IDS_HOMEPAGE);
	::ShellExecute(0, _T("open"), sLink, 0, 0, SW_SHOWNORMAL);
	return 0;
}
