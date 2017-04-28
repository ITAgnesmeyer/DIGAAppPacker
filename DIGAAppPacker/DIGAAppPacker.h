
// DIGAAppPacker.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDIGAAppPackerApp:
// Siehe DIGAAppPacker.cpp für die Implementierung dieser Klasse
//

class CDIGAAppPackerApp : public CWinApp
{
public:
	CDIGAAppPackerApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDIGAAppPackerApp theApp;