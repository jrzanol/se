
// seDlg.cpp: arquivo de implementação
//

#include "pch.h"
#include "framework.h"
#include "se.h"
#include "seDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Caixa de diálogo CAboutDlg usada para o Sobre o Aplicativo

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Suporte DDX/DDV

// Implementação
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// caixa de diálogo CseDlg



CseDlg::CseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Manipuladores de mensagens de CseDlg

BOOL CseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Adicione o item de menu "Sobre..." ao menu do sistema.

	// IDM_ABOUTBOX deve estar no intervalo de comandos do sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Defina o ícone para esta caixa de diálogo. A estrutura faz isso automaticamente
	//  quando a janela principal do aplicativo não é uma caixa de diálogo
	SetIcon(m_hIcon, TRUE);			// Definir ícone grande
	SetIcon(m_hIcon, FALSE);		// Definir ícone pequeno

	try
	{
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("localhost", "root", "junior55");

		/* Connect to the MySQL database */
		con->setSchema("pbd");
	}
	catch (sql::SQLException& e) {
		MessageBox(e.what(), "Connect MySQL failed!!", MB_OK | MB_ICONEXCLAMATION);
		ExitProcess(-1);
	}

	return TRUE;  // retorna TRUE a não ser que você ajuste o foco para um controle
}

SqlRes CseDlg::SqlQuery(const char* str, ...)
{
	char buf[1024];

	va_list arglist;
	va_start(arglist, str);
	vsprintf(buf, str, arglist);
	va_end(arglist);

	sql::Statement* stmt = nullptr;
	sql::ResultSet* res = nullptr;

	try
	{
		stmt = con->createStatement();
		res = stmt->executeQuery(buf);
	}
	catch (sql::SQLException& e) {
		MessageBox(e.what(), "Connect MySQL failed!!", MB_OK | MB_ICONEXCLAMATION);
	}

	return SqlRes(stmt, res);
}

void CseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Se você adicionar um botão para minimizar à sua caixa de diálogo, será necessário o código abaixo
//  para desenhar o ícone. Para aplicativos MFC usando o modelo de exibição/documento,
//  isso é feito automaticamente para você pela estrutura.

void CseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexto do dispositivo para pintura

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ícone central no retângulo do cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Desenhar o ícone
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// O sistema chama esta função para obter o cursor a ser exibido enquanto o usuário arrasta
//  a janela minimizada.
HCURSOR CseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

