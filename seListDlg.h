#pragma once
#include "afxdialogex.h"


// caixa de diálogo de CFormView

class CseListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CseListDlg)

public:
	CseListDlg(CWnd* pParent = nullptr);   // construtor padrão
	virtual ~CseListDlg();

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

	std::list<std::string> m_StrList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Suporte DDX/DDV

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ValList;
};
