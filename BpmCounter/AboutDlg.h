#if !defined(AFX_ABOUTDLG_H__5F497A0B_4B4F_423C_99FD_8554828E50DE__INCLUDED_)
#define AFX_ABOUTDLG_H__5F497A0B_4B4F_423C_99FD_8554828E50DE__INCLUDED_

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
	CAxWindow  m_wndWB;
public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
		m_wndWB = GetDlgItem(IDC_WB);
		m_wndWB.CreateControl(IDR_HTML_ABOUT);
		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif // !defined(AFX_ABOUTDLG_H__5F497A0B_4B4F_423C_99FD_8554828E50DE__INCLUDED_)
