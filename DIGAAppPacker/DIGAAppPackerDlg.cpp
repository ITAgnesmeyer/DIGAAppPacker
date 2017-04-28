
// DIGAAppPackerDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DIGAAppPacker.h"
#include "DIGAAppPackerDlg.h"
#include "afxdialogex.h"
#include <winuser.h>
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void addRTString(LPCTSTR lpFileName, WORD id, WORD wLanguage, LPCWSTR lpStr)
{
	DWORD dwResSize;
	WORD wStrLen, wStrIndex;
	WCHAR *pRes;
	HANDLE hHeap;
	HANDLE hUpdateRes;
	//HMODULE hModule;
	//HRSRC hResInfo;

	wStrIndex = id & 0xF;
	wStrLen = (WORD)lstrlenW(lpStr);
	dwResSize = sizeof(WORD) * 16 + sizeof(WCHAR)*wStrLen;
	hHeap = GetProcessHeap();
	pRes = (LPWSTR)HeapAlloc(hHeap, 0, dwResSize);
	lstrcpyW(pRes, lpStr);
	dwResSize = sizeof(WORD) * 16 + sizeof(WCHAR)*wStrLen;
	pRes = (LPWSTR)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, dwResSize);
	pRes[wStrIndex] = wStrLen;
	lstrcpyW(&pRes[wStrIndex + 1], lpStr);
	hUpdateRes = BeginUpdateResource(lpFileName, FALSE);
	
	UpdateResource(hUpdateRes, RT_STRING, MAKEINTRESOURCE(id), MAKELANGID(LANG_GERMAN, SUBLANG_DEFAULT), pRes, dwResSize);
	EndUpdateResource(hUpdateRes, FALSE);
	HeapFree(hHeap, 0, pRes);
}



LPWSTR ConvertToUnicode(CString cString)
{
	int nBufSize = cString.GetLength() + 1;
	LPWSTR lpws = new wchar_t[nBufSize];

	if (lpws != NULL)
	{
#if defined(_UNICODE)
		lstrcpy(lpws, cString); // If Unicode is defined, just copy the string.
#else
		// mbstowcs() would work here as well...
		MultiByteToWideChar(CP_ACP, 0, cString, nBufSize, lpws, nBufSize * 2);
#endif // _UNICODE
	}

	return lpws; // Caller must delete!
}

// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	::CoInitialize(nullptr);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDIGAAppPackerDlg-Dialogfeld



CDIGAAppPackerDlg::CDIGAAppPackerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIGAAPPPACKER_DIALOG, pParent)
	, _NetExePath(_T(""))
	, _DestinationPath(_T(""))
	, _NameSpace(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDIGAAppPackerDlg::~CDIGAAppPackerDlg()
{
	::CoUninitialize();
}

void CDIGAAppPackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TXTNETEXEPATH, _NetExePath);
	DDX_Text(pDX, IDC_DESTFOLDER, _DestinationPath);
	DDX_Text(pDX, IDC_NAMESPACE, _NameSpace);
	DDX_Control(pDX, IDC_LIST1, _LogListBox);
	DDX_Control(pDX, IDC_TXTNETEXEPATH, _BrowsControl);
}

BEGIN_MESSAGE_MAP(CDIGAAppPackerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONCREATE, &CDIGAAppPackerDlg::OnBnClickedButtoncreate)
END_MESSAGE_MAP()


// CDIGAAppPackerDlg-Meldungshandler

BOOL CDIGAAppPackerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	_BrowsControl.EnableFileBrowseButton(_T("EXE"), _T("Exe|*.exe|All files|*.*||"));

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CDIGAAppPackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDIGAAppPackerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDIGAAppPackerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CDIGAAppPackerDlg::CombinePathAndFile(CString destFolder, CString packedFile)
{
	CString destFileHelper;
	PathCombine(destFileHelper.GetBufferSetLength(MAX_PATH), destFolder, packedFile);
	destFileHelper.ReleaseBuffer();
	return  destFileHelper;
}

bool CDIGAAppPackerDlg::FileExists(CString assemblyPath)
{
	CFileStatus fs;
	if(!CFile::GetStatus(assemblyPath,fs))
	{
		//AfxMessageBox(_T("Der Pfad ist ungültig\n") + assemblyPath, MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

CString CDIGAAppPackerDlg::GetAppDir()
{
	CString curDir;
	GetCurrentDirectory(MAX_PATH, curDir.GetBufferSetLength(MAX_PATH)); 
	curDir.ReleaseBuffer();
	return curDir;
}

bool CDIGAAppPackerDlg::PackAssembly(CString zifToolPath, CString assemblyPath, CString packedFile)
{
	CString command = _T("-f ") + assemblyPath + _T(" -o ") + packedFile + _T(" -c");
	int retVAl = reinterpret_cast<int>(ShellExecute(this->m_hWnd, nullptr, zifToolPath, command, nullptr, SW_SHOWNORMAL));
	Sleep(500);
	if(retVAl < 33)
	{

		AfxMessageBox(_T("Die Datei konnte nicht gepackt werden!\nFile:") + zifToolPath + _T("\nParameter:") + command,MB_OK | MB_ICONERROR);
		return true;
	}
	return false;
}

void CDIGAAppPackerDlg::GetFileName(CString assemblyPath, CString& assemblyFileName)
{
	CFile assFile(assemblyPath, CFile::OpenFlags::modeRead);
	assemblyFileName = assFile.GetFileName();
	assFile.Close();
}

void CDIGAAppPackerDlg::OnBnClickedButtoncreate()
{
	UpdateData(TRUE);
	CString nameSpace = this->_NameSpace;
	CString assemblyFileName = _T("");
	CString assemblyPath = this->_NetExePath;
	CString destFolder = this->_DestinationPath;
	CString packedFile = CombinePathAndFile(destFolder, _T("application.bin"));
	CString defaultDestinationFileName = _T("WinAppLauncher_x86.exe");
	if (!FileExists(assemblyPath)) 
		return;

	GetFileName(assemblyPath, assemblyFileName);


	if (FileExists(packedFile))
			CFile::Remove(packedFile);
	
	CString curDir = GetAppDir();

	CString zifToolPath = CombinePathAndFile(curDir, _T("DIGAZip.exe"));
	

	if (PackAssembly(zifToolPath, assemblyPath, packedFile)) return;

	


	CFile file;
	CFileException cfe;
	if(!file.Open(packedFile, CFile::OpenFlags::modeRead, &cfe))
	{
		AfxMessageBox(_T("Die Datei konnte nicht geöffnet werden!\n") + assemblyPath, MB_OK | MB_ICONERROR);
		return;
	}

	CString sourceFile = CombinePathAndFile(curDir, defaultDestinationFileName);
	CString destFile = CombinePathAndFile(destFolder, defaultDestinationFileName);
	if(!CopyFile(sourceFile, destFile, FALSE))
	{
		AfxMessageBox(_T("Der Wrapperfile konnte nicht kopiert werden"), MB_OK | MB_ICONERROR);
		return;
	}

	UINT fileLen = file.GetLength();
	auto buffer = new BYTE[fileLen];
	auto anzahlBytes = file.Read(buffer, fileLen);
	file.Close();
	
	HANDLE hResouce = BeginUpdateResource(destFile, FALSE);
	if(hResouce != nullptr)
	{
		BOOL changed = UpdateResource(hResouce, _T("BINARY"), MAKEINTRESOURCE(108), MAKELANGID(LANG_GERMAN, SUBLANG_DEFAULT), static_cast<LPVOID>(buffer), anzahlBytes);
		if (!changed)
		{
			AfxMessageBox(_T("Die BINARY Resource der EXE konnte nicht in die Wrapperdatei geschrieben werden!"), MB_OK | MB_ICONERROR);
			return;
		}
		else
			EndUpdateResource(hResouce, FALSE);
		
		addRTString(destFile, 7, MAKELANGID(LANG_GERMAN, LANG_GERMAN), _NameSpace);
	}
	else
	{
		AfxMessageBox(_T("Die Resoource des Exe konnte nicht geöffnet werden!"), MB_OK | MB_ICONERROR);
		return;
	}
	
	if(assemblyFileName.GetLength() > 0)
	{
		CString newFileName = CombinePathAndFile(destFolder, assemblyFileName);

		if(FileExists(newFileName))
		{
			CFile::Remove(newFileName);
		}
		try
		{
			CFile::Rename(destFile, newFileName);
		}
		catch(CFileException * ex)
		{
			CString errMessage;

			ex->GetErrorMessage(errMessage.GetBuffer(1024), 1024);
			errMessage.ReleaseBuffer();
			AfxMessageBox(errMessage, MB_OK | MB_ICONERROR);
			ex->Delete();
		}
		
		if(FileExists(newFileName))
		{
			AfxMessageBox(_T("Die Zieldatei wurde erstellt\n") + newFileName, MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("Die Zieldatei wurde nicht erstellt\n") + newFileName, MB_OK | MB_ICONERROR);
		}
	}
	
	

	delete[] buffer;


}
