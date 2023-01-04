// BpmCounterCtl.h : Declaration of the CBpmCounterCtl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "BpmCounter.h"
#include "_IBpmCounterCtlEvents_CP.h"

#define ID_BPM_WND    101
#define IDT_CLOCK     201



// CBpmCounterCtl
class ATL_NO_VTABLE CBpmCounterCtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IBpmCounterCtl, &IID_IBpmCounterCtl, &LIBID_BpmCounterLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CBpmCounterCtl>,
	public IOleControlImpl<CBpmCounterCtl>,
	public IOleObjectImpl<CBpmCounterCtl>,
	public IOleInPlaceActiveObjectImpl<CBpmCounterCtl>,
	public IViewObjectExImpl<CBpmCounterCtl>,
	public IOleInPlaceObjectWindowlessImpl<CBpmCounterCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CBpmCounterCtl>,
	public CProxy_IBpmCounterCtlEvents<CBpmCounterCtl>, 
	public IPersistStorageImpl<CBpmCounterCtl>,
	public ISpecifyPropertyPagesImpl<CBpmCounterCtl>,
	public IQuickActivateImpl<CBpmCounterCtl>,
	public IDataObjectImpl<CBpmCounterCtl>,
	public IProvideClassInfo2Impl<&CLSID_BpmCounterCtl, &__uuidof(_IBpmCounterCtlEvents), &LIBID_BpmCounterLib>,
	public CComCoClass<CBpmCounterCtl, &CLSID_BpmCounterCtl>,
	public CComControl<CBpmCounterCtl>
{
private:
	enum 
	{
		eCol_Time  = 0,
		eCol_Bpm   = 1,
		eCol_CurBpm= 2,
		eCol_Beats = 3,
		//
		eCol_Count = 4
	};

	struct LOG_ENTRY
	{
		LOG_ENTRY(long _lTime=0, double _dBpm=0, int _nBeats=0, double _dCurBpm=0, bool _fOdd=false, int nSeq=0);
		//
		CString  time;
		long     lTime;
		CString  bpm;
		CString  beats;
		int      nBeats;
		CString  curBpm;
		COLORREF clrText;
		COLORREF clrTextBk;
		bool     fOdd;
		int      nSeq;
		static COLORREF clrTextBkDef;
	};


private:
	double                   m_dBpm;
	int                      m_nClick;
	long                     m_lStartTime;
	long                     m_lLastTime;
	bool                     m_fRunning;
	UINT_PTR                 m_nTimerId;
	int                      m_nAutoTerminateDelay;
	int                      m_nLogInterval;
	long                     m_lLastLogTime;
	bool                     m_fShowHistory;
	RECT                     m_rcClick;
	CSimpleArray<LOG_ENTRY*> m_aHistory;
	CSimpleArray<int>        m_aKeys;
	int                      m_nLastKeyClick;
	bool                     m_fOddLog;
	int                      m_nSeq;

	//
	CContainedWindow  m_wndBpm;
	CListViewCtrl     m_wndHistory;
	HBRUSH            m_hBrushText;
	HBRUSH            m_hBrushBk;
	HFONT             m_hFontBpm;

public:
	DECLARE_PROTECT_FINAL_CONSTRUCT()

public:

	CBpmCounterCtl();
	~CBpmCounterCtl();

	void    ClearHistoryInternal();
	void    DoBeat();
	void    DoKey();
	HRESULT FinalConstruct();
	void    FinalRelease();
	void    Log();
	HRESULT OnDraw(ATL_DRAWINFO& di);
	void    OnFinalMessage(HWND hWnd);
	void    RedrawAll();
	void    Resize();
	void    Stop();


DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_BPMCOUNTERCTL)

BEGIN_COM_MAP(CBpmCounterCtl)
	COM_INTERFACE_ENTRY(IBpmCounterCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CBpmCounterCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CBpmCounterCtl)
	CONNECTION_POINT_ENTRY(__uuidof(_IBpmCounterCtlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CBpmCounterCtl)
	MESSAGE_HANDLER(WM_CREATE,        OnCreate)
	MESSAGE_HANDLER(WM_KEYDOWN,       OnKeyDown)
	MESSAGE_HANDLER(WM_SIZE,          OnSize)
	MESSAGE_HANDLER(WM_TIMER,         OnTimer)
	NOTIFY_CODE_HANDLER(LVN_GETDISPINFO, OnNotify_LvnGetDispInfo)
	NOTIFY_CODE_HANDLER(NM_CUSTOMDRAW,   OnNotify_CustomDraw)
	CHAIN_MSG_MAP(CComControl<CBpmCounterCtl>)
	DEFAULT_REFLECTION_HANDLER()
ALT_MSG_MAP(ID_BPM_WND)
	MESSAGE_HANDLER(WM_ERASEBKGND,    Bpm_OnEraseBk)
	MESSAGE_HANDLER(WM_KEYDOWN,       OnKeyDown)
	MESSAGE_HANDLER(WM_LBUTTONDOWN,   Bpm_OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, Bpm_OnLButtonDblClick)
	MESSAGE_HANDLER(WM_RBUTTONDOWN,   Bpm_OnRButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONDBLCLK, Bpm_OnRButtonDblClick)
	MESSAGE_HANDLER(WM_MOUSEMOVE,     Bpm_OnMouseMove)
	MESSAGE_HANDLER(WM_NCHITTEST,     Bpm_OnNcHitTest)
	MESSAGE_HANDLER(WM_PAINT,         Bpm_OnPaint)
	MESSAGE_HANDLER(WM_SETCURSOR,     Bpm_OnSetCursor)
	MESSAGE_HANDLER(WM_SIZE,          Bpm_OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNotify_LvnGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnNotify_CustomDraw(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT Bpm_OnEraseBk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnLButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnRButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT Bpm_OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);




// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IBpmCounterCtl
public:
	STDMETHOD(ClearHistory)(void);
	STDMETHOD(get_ShowHistoryPanel)(VARIANT_BOOL* pVal);
	STDMETHOD(put_ShowHistoryPanel)(VARIANT_BOOL newVal);
	STDMETHOD(About)(void);
	STDMETHOD(ResetAll)(void);
	STDMETHOD(Reset)(void);
	STDMETHOD(Beat)(void);
	STDMETHOD(KeyBeat)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(BpmCounterCtl), CBpmCounterCtl)
