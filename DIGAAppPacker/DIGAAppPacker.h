
// DIGAAppPacker.h: Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CDIGAAppPackerApp:
// Siehe DIGAAppPacker.cpp f�r die Implementierung dieser Klasse
//

class CDIGAAppPackerApp : public CWinApp
{
public:
	CDIGAAppPackerApp();

// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDIGAAppPackerApp theApp;