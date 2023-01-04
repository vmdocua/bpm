// BpmCounterCtl.cpp : Implementation of CBpmCounterCtl
#include "stdafx.h"
#include "BpmCounterCtl.h"
#include "AboutDlg.h"

////////////////////////////////////////////////////////////////////////////////
inline double CalculateBpm(int nBeats, long lDTime)
{
	ATLASSERT(nBeats>0);
	if( nBeats<1 )
		nBeats = 1;
	return (lDTime==0)?0:static_cast<double>((nBeats-1)*60*1000)/lDTime;
}

////////////////////////////////////////////////////////////////////////////////
// CBpmCounterCtl
COLORREF CBpmCounterCtl::LOG_ENTRY::clrTextBkDef = GetSysColor(COLOR_WINDOW);

CBpmCounterCtl::LOG_ENTRY::LOG_ENTRY(long _lTime, double _dBpm, int _nBeats, double _dCurBpm, bool _fOdd, int _nSeq)
{
	int nMin = _lTime/(1000*60);
	int nSec = (_lTime/1000) % 60;
	int nDSec = (_lTime/100) % 10;

	time.Format(IDS_FORMAT_TIME2, nMin, nSec, nDSec);
	lTime = _lTime;
	bpm.Format("%0.2f", _dBpm);
	beats.Format("%d", _nBeats);
	nBeats = _nBeats;
	curBpm.Format("%0.2f", _dCurBpm);
	clrText = _fOdd?RGB(0,0,127):RGB(0,127,0);
	clrTextBk = _fOdd?RGB(230, 230, 250):RGB(230, 250, 230);
	fOdd = _fOdd;
	nSeq = _nSeq;
}

CBpmCounterCtl::CBpmCounterCtl():m_wndBpm(this,ID_BPM_WND)
{
	m_dBpm = 0;
	m_nClick = 0;
	m_lStartTime = 0;
	m_lLastTime = 0;
	m_fRunning = false;
	m_nAutoTerminateDelay = 2000;
	m_nLogInterval = 15*1000;
	m_fShowHistory = true;
	SetRect(&m_rcClick,0,0,0,0);
	m_hFontBpm = NULL;
	m_lLastLogTime = NULL;
	m_nLastKeyClick = 0;
	m_fOddLog = false;
	m_nSeq = 0;

	//
	m_sizeExtent.cx = 4*2540;
	m_sizeExtent.cy = 2*2540;
	//m_sizeNatural = m_sizeExtent;
	m_bWindowOnly = true;
}

CBpmCounterCtl::~CBpmCounterCtl()
{
}

void CBpmCounterCtl::ClearHistoryInternal()
{
	if( m_wndHistory.IsWindow() )
		m_wndHistory.DeleteAllItems();

	for(int i=0; i<m_aHistory.GetSize(); i++)
		delete m_aHistory[i];
	m_aHistory.RemoveAll();
	m_fOddLog = false;
}

void CBpmCounterCtl::DoBeat()
{
	long lTime = timeGetTime();

	if( !m_fRunning )
	{
		// start timer
		Reset();
		m_fRunning = true;
		m_nTimerId = SetTimer(IDT_CLOCK, 100);
		m_nClick = 0;
		m_aKeys.RemoveAll();
		m_lStartTime = lTime;
		m_lLastLogTime = m_lStartTime;
		m_fOddLog = !m_fOddLog;
		m_nSeq++;
	}

	m_nClick++;
	if( (GetKeyState(VK_SHIFT) & 0x80) )
		m_nClick++;

	m_lLastTime = lTime;
	long lDTime = m_lLastTime - m_lStartTime;
	m_dBpm = CalculateBpm(m_nClick, lDTime);
	m_wndBpm.Invalidate();
}

void CBpmCounterCtl::DoKey()
{
	int nKey = m_nClick-m_nLastKeyClick;
	if( nKey>0 )
		m_aKeys.Add(nKey);
	m_nLastKeyClick = m_nClick;
}

HRESULT CBpmCounterCtl::FinalConstruct()
{
	m_hBrushText = GetSysColorBrush(COLOR_WINDOWTEXT);
	m_hBrushBk = GetSysColorBrush(COLOR_WINDOW);
	return S_OK;
}

void CBpmCounterCtl::FinalRelease() 
{
	ClearHistoryInternal();
}

HRESULT CBpmCounterCtl::OnDraw(ATL_DRAWINFO& di)
{
	/*
	RECT& rc = *(RECT*)di.prcBounds;
	// Set Clip region to the rectangle specified by di.prcBounds
	HRGN hRgnOld = NULL;
	if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
		hRgnOld = NULL;
	bool bSelectOldRgn = false;

	HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

	if (hRgnNew != NULL)
	{
		bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
	}

	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
	LPCTSTR pszText = _T("ATL 7.0 : BpmCounterCtl");
	TextOut(di.hdcDraw, 
		(rc.left + rc.right) / 2, 
		(rc.top + rc.bottom) / 2, 
		pszText, 
		lstrlen(pszText));

	if (bSelectOldRgn)
		SelectClipRgn(di.hdcDraw, hRgnOld);

	*/
	return S_OK;
}

void CBpmCounterCtl::Log()
{
	int nLastClick = 0;
	long lLastTime = 0;
	if( m_aHistory.GetSize()>0 )
	{
		LOG_ENTRY *pLog = m_aHistory[m_aHistory.GetSize()-1];
		if( pLog->nSeq==m_nSeq )
		{
			nLastClick = pLog->nBeats;
			if(nLastClick>0)
				nLastClick--;
			lLastTime = pLog->lTime;
		}
	}

	double dCurBpm = CalculateBpm(m_nClick-nLastClick, m_lLastTime-m_lStartTime-lLastTime);

	LOG_ENTRY *pe = new LOG_ENTRY(m_lLastTime-m_lStartTime, m_dBpm, m_nClick, dCurBpm,	m_fOddLog, m_nSeq);
	m_aHistory.Add(pe);
	LV_ITEM item;
	item.mask = LVIF_PARAM | LVIF_TEXT;
	item.iItem = m_wndHistory.GetItemCount();
	item.iSubItem = 0;
	item.pszText = LPSTR_TEXTCALLBACK;
	item.cchTextMax = 64;
	item.lParam = m_aHistory.GetSize()-1;
	int nRes = m_wndHistory.InsertItem(&item);
	for(int i=1; i<eCol_Count; i++)
		m_wndHistory.SetItemText(item.iItem, i, LPSTR_TEXTCALLBACK);

	m_wndHistory.EnsureVisible(item.iItem, FALSE);
}

void CBpmCounterCtl::OnFinalMessage(HWND hWnd)
{
	if( m_hFontBpm!=NULL )
		DeleteObject(m_hFontBpm);
}

void CBpmCounterCtl::RedrawAll()
{
	if( IsWindow() )
		Invalidate();

	if( m_wndBpm.IsWindow() )
		m_wndBpm.Invalidate();

	if( m_wndHistory.IsWindow() )
		m_wndHistory.Invalidate();
}

void CBpmCounterCtl::Resize()
{
	if( IsWindow() )
	{
		RECT rc;
		GetClientRect(&rc);

		int d = 2;

		if( m_fShowHistory )
		{
			if( m_wndBpm.IsWindow() )
			{
				m_wndBpm.MoveWindow(
					rc.left+d, 
					rc.top+d, 
					(rc.right + rc.left)*2/3 - rc.left - 2*d,
					rc.bottom - rc.top - 2*d
				);
			}

			if( m_wndHistory.IsWindow() )
			{
				if( (m_wndHistory.GetStyle() & WS_VISIBLE)==0 )
					m_wndHistory.ShowWindow(SW_SHOW);

				int nLeft = (rc.right + rc.left)*2/3 - d;
				m_wndHistory.MoveWindow(
					nLeft + d,
					rc.top+d,
					rc.right - nLeft - 2*d,
					rc.bottom - rc.top - 2*d
					);
			}
		} else
		{
			if( m_wndBpm.IsWindow() )
			{
				m_wndBpm.MoveWindow(
					rc.left+d, 
					rc.top+d, 
					rc.right - rc.left - 2*d,
					rc.bottom - rc.top - 2*d
				);
			}

			if( m_wndHistory.IsWindow() && m_wndHistory.GetStyle() & WS_VISIBLE )
			{
				m_wndHistory.ShowWindow(SW_HIDE);
			}
		}
	}
}

void CBpmCounterCtl::Stop()
{
	if( m_fRunning )
	{
		m_fRunning = false;
		KillTimer(m_nTimerId);
	}
}


////////////////////////////////////////////////////////////////////////////////
// Message Handlers


LRESULT CBpmCounterCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	RECT rc = {0, 0, 0, 0};
	m_wndBpm.Create(_T("STATIC"), this, ID_BPM_WND, m_hWnd, rc, NULL, 
		WS_CHILD | WS_VISIBLE);

	m_wndHistory.Create(m_hWnd, rc, NULL, 
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL);

	m_wndHistory.SetExtendedListViewStyle(/*LVS_EX_FLATSB | */LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndHistory.InsertColumn(eCol_Time, _T("Time"), LVCFMT_LEFT, 50, -1);
	m_wndHistory.InsertColumn(eCol_Bpm, _T("BPM"), LVCFMT_LEFT, 50, -1);
	m_wndHistory.InsertColumn(eCol_CurBpm, _T("Current BPM"), LVCFMT_LEFT, 50, -1);
	m_wndHistory.InsertColumn(eCol_Beats, _T("Beats"), LVCFMT_LEFT, 50, -1);
	Resize();
	return 0;
}

LRESULT CBpmCounterCtl::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch( wParam )
	{
		case VK_SPACE:
		case VK_RETURN:
				DoBeat();
			break;

		case 'Q':
		case VK_TAB:
				DoKey();
				DoBeat();
			break;
	}
	return 0;
}

LRESULT CBpmCounterCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	Resize();
	return 0;
}

LRESULT CBpmCounterCtl::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( wParam==IDT_CLOCK && m_fRunning )
	{
		long lTime = timeGetTime();

		if( (m_lLastLogTime+m_nLogInterval)<=lTime )
		{
			Log();
			m_lLastLogTime += m_nLogInterval;
		}

		if( m_nAutoTerminateDelay>0 )
		{
			if( (lTime-m_lLastTime)>=m_nAutoTerminateDelay )
			{
				if( m_aKeys.GetSize()>0 )
					DoKey();
				Stop();
				Log();
			}
		}
		m_wndBpm.Invalidate(FALSE);

	}
	return 0;
}

LRESULT CBpmCounterCtl::OnNotify_LvnGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	NMLVDISPINFO *pdi = reinterpret_cast<NMLVDISPINFO*>(pnmh);
	int nIndex = static_cast<int>(pdi->item.lParam);
	if( nIndex>=0 && nIndex<m_aHistory.GetSize() )
	{
		LOG_ENTRY *pe = m_aHistory[nIndex];

		if( pe!=NULL )
		{
			switch(pdi->item.iSubItem)
			{
				case eCol_Time:
						pdi->item.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pe->time));
					break;

				case eCol_Bpm:
						pdi->item.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pe->bpm));
					break;

				case eCol_CurBpm:
						pdi->item.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pe->curBpm));
					break;

				case eCol_Beats:
						pdi->item.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pe->beats));
					break;
			}
		}
	} else
		ATLASSERT(false);
	return 0;
}

LRESULT CBpmCounterCtl::OnNotify_CustomDraw(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	if( pnmh->hwndFrom==m_wndHistory )
	{
		NMLVCUSTOMDRAW* p = reinterpret_cast<NMLVCUSTOMDRAW*>(pnmh);
		//ATLTRACE(_T("Stage: %d 0x%08x\n"), p->nmcd.dwDrawStage, p->nmcd.dwDrawStage);
		switch(p->nmcd.dwDrawStage)
		{
			case CDDS_PREPAINT:
				return CDRF_NOTIFYITEMDRAW;

			case CDDS_ITEMPREPAINT:
				return CDRF_NOTIFYSUBITEMDRAW;

			case (CDDS_ITEMPREPAINT | CDDS_SUBITEM):
				{
					int nIndex = static_cast<int>(p->nmcd.lItemlParam);
					if( nIndex>=0 && nIndex<m_aHistory.GetSize() )
					{
						p->clrText = m_aHistory[nIndex]->clrText;
						if( p->iSubItem==eCol_Bpm )
							p->clrTextBk = m_aHistory[nIndex]->clrTextBk;
						else
							p->clrTextBk = m_aHistory[nIndex]->clrTextBkDef;
					}
				}
				return CDRF_DODEFAULT;
		}
	}
	return CDRF_DODEFAULT;
}

LRESULT CBpmCounterCtl::Bpm_OnEraseBk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	HDC hDC = (HDC)wParam;
	RECT rc;
	m_wndBpm.GetClientRect(&rc);
	FillRect(hDC, &rc, GetSysColorBrush(COLOR_WINDOWTEXT));
	*/
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoBeat();
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnLButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoBeat();
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoKey();
	DoBeat();
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnRButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoKey();
	DoBeat();
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	/*
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	if( PtInRect(&m_rcClick, pt) )
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
	else
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
		*/
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return HTCLIENT;
}

LRESULT CBpmCounterCtl::Bpm_OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = m_wndBpm.BeginPaint(&ps);
	RECT rc, rcText;
	m_wndBpm.GetClientRect(&rc);

	CString sBpm;
	sBpm.Format("%0.2f bpm", m_dBpm);

	//
	CString sTimer;
	long lTime = 0;
	if( m_fRunning )
		lTime = timeGetTime()-m_lStartTime;

	int nMin = lTime/(1000*60);
	int nSec = (lTime/1000) % 60;
	int nDSec = (lTime/100) % 10;

	sTimer.Format(IDS_FORMAT_TIME, nMin, nSec, nDSec);

	//
	CString sClickTimer;
	long lClickTime = m_lLastTime-m_lStartTime;

	nMin = lClickTime/(1000*60);
	nSec = (lClickTime/1000) % 60;
	nDSec = (lClickTime/100) % 10;

	sClickTimer.Format(IDS_FORMAT_LASTTIME, nMin, nSec, nDSec);

	//
	CString sClick;
	sClick.Format("%d", m_nClick);

	RECT rcBpm = { rc.left, rc.top, rc.right, (rc.top+rc.bottom)/2};
	RECT rcClick = { rc.left, rcBpm.bottom-1, rc.right, rc.bottom };
	RECT rcTimer = { rcClick.left, rcClick.top, (rcClick.left+rcClick.right)/2, rcClick.top+25 };
	RECT rcClickTimer = { rcTimer.right-1, rcClick.top, rcClick.right, rcClick.top+25 };
	
	if( rcTimer.bottom>rcClick.bottom )
		rcTimer.bottom = rcClick.bottom;

	//

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = ::CreateCompatibleBitmap(hMemDC, rc.right, rc.bottom);
	HBITMAP hStockBmp = reinterpret_cast<HBITMAP>(::SelectObject(hMemDC, hMemBmp));
	HFONT hStockFont = NULL;

	// 
	::SetTextColor(hMemDC, GetSysColor(COLOR_WINDOWTEXT));
	::SetBkColor(hMemDC, GetSysColor(COLOR_WINDOW));

	// draw XXX bpm
	FillRect(hMemDC, &rc, m_hBrushBk);
	FrameRect(hMemDC, &rcBpm, m_hBrushText);
	hStockFont = reinterpret_cast<HFONT>(::SelectObject(hMemDC, m_hFontBpm));
	rcText = rcBpm; OffsetRect(&rcText, 1, 1);	InflateRect(&rcText, -2, -2);
	DrawText(hMemDC, sBpm, -1, &rcText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


	// draw clicks
	FrameRect(hMemDC, &rcClick, m_hBrushText);
	rcText = rcClick; OffsetRect(&rcText, 1, 1);	InflateRect(&rcText, -2, -2);
	if( m_nClick==0 )
	{
		sClick.LoadString(IDS_CLICK);
		RECT rcClick2 = rcText;
		rcClick2.top = rcTimer.bottom;
		::SelectObject(hMemDC, hStockFont);
		DrawText(hMemDC, sClick, -1, &rcClick2, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
		int h = (rcClick2.bottom - rcClick2.top)/2;
		int y = (rcText.bottom + rcText.top)/2;
		rcClick2.left = rcText.left;
		rcClick2.top = y - h;
		rcClick2.right = rcText.right;
		rcClick2.bottom = y + h + 1;
		DrawText(hMemDC, sClick, -1, &rcClick2, DT_CENTER | DT_WORDBREAK);
	} else
	{
		DrawText(hMemDC, sClick, -1, &rcClick, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		::SelectObject(hMemDC, hStockFont);
	}

	
	// draw timer
	FrameRect(hMemDC, &rcTimer, m_hBrushText);
	if( m_fRunning )
	{
		rcText = rcTimer;	OffsetRect(&rcText, 1, 1); InflateRect(&rcText, -2, -2);
		DrawText(hMemDC, sTimer, -1, &rcText, DT_SINGLELINE | DT_VCENTER);
	}

	// draw last click time
	FrameRect(hMemDC, &rcClickTimer, m_hBrushText);
	rcText = rcClickTimer; OffsetRect(&rcText, 1, 1);	InflateRect(&rcText, -2, -2);
	DrawText(hMemDC, sClickTimer, -1, &rcText, DT_SINGLELINE | DT_VCENTER);

	// draw keys
	CString sKey = "";
	for(int i=0; i<m_aKeys.GetSize(); ++i)
	{
		CString s;
		s.Format(_T("%d"), m_aKeys[i]);
		if( sKey.GetLength()>0 )
			sKey +="|";
		sKey += s;
	}

	if( sKey.GetLength()>0 )
	{
		sKey = "Keys: "+sKey;
		RECT rcKey = rcTimer;
		OffsetRect(&rcKey, 0, rcKey.bottom-rcKey.top);
		rcKey.left += 3;
		rcKey.right = rcClickTimer.right-3;
		DrawText(hMemDC, sKey, -1, &rcKey, DT_SINGLELINE);
	}


	BitBlt(hDC, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
		hMemDC, rc.left, rc.top, SRCCOPY);

	::SelectObject(hMemDC, hStockBmp);
	::DeleteObject(hMemBmp);
	::DeleteDC(hMemDC);

	m_wndBpm.EndPaint(&ps);
	return 1;
}

LRESULT CBpmCounterCtl::Bpm_OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DWORD dwPos = GetMessagePos();
	POINT pt = { GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos) };

	m_wndBpm.ScreenToClient(&pt);

	if( PtInRect(&m_rcClick, pt) )
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
	else
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));

	return TRUE;
}

LRESULT CBpmCounterCtl::Bpm_OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	m_wndBpm.GetClientRect(&m_rcClick);
	m_rcClick.top = (m_rcClick.bottom+m_rcClick.top)/2;

	if( m_hFontBpm!=NULL )
	{
		DeleteObject(m_hFontBpm);
		m_hFontBpm = NULL;
	}

	int w = (m_rcClick.right-m_rcClick.left)/20;
	int h = (m_rcClick.bottom-m_rcClick.top)/3;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	HDC hDC = m_wndBpm.GetWindowDC();
	lf.lfHeight = -MulDiv(h, GetDeviceCaps (hDC, LOGPIXELSY), 72);
	lf.lfWidth = -MulDiv(w, GetDeviceCaps (hDC, LOGPIXELSX), 72);
	m_wndBpm.ReleaseDC(hDC);
	_tcscpy(lf.lfFaceName, _T("Arial"));
	m_hFontBpm = CreateFontIndirect(&lf);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
STDMETHODIMP CBpmCounterCtl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBpmCounterCtl,
	};

	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBpmCounterCtl::ClearHistory(void)
{
	Stop();
	ClearHistoryInternal();
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::get_ShowHistoryPanel(VARIANT_BOOL* pVal)
{
	if( pVal==NULL )	
		return E_INVALIDARG;

	*pVal = m_fShowHistory?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::put_ShowHistoryPanel(VARIANT_BOOL newVal)
{
	m_fShowHistory = newVal==VARIANT_TRUE?true:false;
	Resize();

	RedrawAll();
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::About(void)
{
	CAboutDlg dlg;
	dlg.DoModal(m_hWnd);
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::ResetAll(void)
{
	ClearHistory();
	Reset();
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::Reset(void)
{
	Stop();
	m_dBpm = 0;
	m_nClick = 0;
	m_lStartTime = 0;
	m_lLastTime = 0;
	m_lLastLogTime = 0;
	m_nLastKeyClick = 0;
	m_aKeys.RemoveAll();
	RedrawAll();
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::Beat(void)
{
	DoBeat();
	return S_OK;
}

STDMETHODIMP CBpmCounterCtl::KeyBeat(void)
{
	DoKey();
	DoBeat();
	return S_OK;
}
