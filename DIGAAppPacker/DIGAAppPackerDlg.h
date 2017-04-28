
// DIGAAppPackerDlg.h: Headerdatei
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CDIGAAppPackerDlg-Dialogfeld
class CDIGAAppPackerDlg : public CDialogEx
{
// Konstruktion
public:
	CDIGAAppPackerDlg(CWnd* pParent = NULL);	// Standardkonstruktor
	~CDIGAAppPackerDlg();
// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGAAPPPACKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CString CombinePathAndFile(CString destFolder, CString packedFile);
	bool FileExists(CString assemblyPath);
	CString GetAppDir();
	bool PackAssembly(CString zifToolPath, CString assemblyPath, CString packedFile);
	void GetFileName(CString assemblyPath, CString& assemblyFileName);
	DECLARE_MESSAGE_MAP()
private:
	CString _NetExePath;
	CString _DestinationPath;
	CString _NameSpace;
	CListBox _LogListBox;
public:
	afx_msg void OnBnClickedButtoncreate();
private:
	CMFCEditBrowseCtrl _BrowsControl;
};
