// CFormView.cpp : arquivo de implementação
//

#include "pch.h"
#include "se.h"
#include "afxdialogex.h"
#include "seListDlg.h"


// caixa de diálogo de CseListDlg

IMPLEMENT_DYNAMIC(CseListDlg, CDialogEx)

CseListDlg::CseListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORMVIEW, pParent)
{

}

CseListDlg::~CseListDlg()
{
}

void CseListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ValList);
}


BEGIN_MESSAGE_MAP(CseListDlg, CDialogEx)
END_MESSAGE_MAP()


// manipuladores de mensagens de CseListDlg

BOOL CseListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int counter = 0;

	for (const auto& it : m_StrList)
		m_ValList.InsertString(counter++, it.c_str());

	return TRUE;
}

void CseListDlg::AddStrListString(const char* str, ...)
{
	char buf[1024];

	va_list arglist;
	va_start(arglist, str);
	vsprintf(buf, str, arglist);
	va_end(arglist);

	m_StrList.push_back(buf);
}
