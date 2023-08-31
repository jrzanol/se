
// se.h: arquivo de cabeçalho principal para o aplicativo PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "inclua 'pch.h' antes de incluir este arquivo para PCH"
#endif

#include "resource.h"		// símbolos principais


// CseApp:
// Consulte se.cpp para a implementação desta classe
//

class CseApp : public CWinApp
{
public:
	CseApp();

// Substitui
public:
	virtual BOOL InitInstance();

// Implementação

	DECLARE_MESSAGE_MAP()
};

extern CseApp theApp;
