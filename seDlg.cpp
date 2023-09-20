
// seDlg.cpp: arquivo de implementação
//

#include "pch.h"
#include "framework.h"
#include "se.h"
#include "seDlg.h"
#include "afxdialogex.h"
#include "seListDlg.h"

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
	DDX_Control(pDX, IDC_CPFEDIT, m_CpfTxt);
	DDX_Control(pDX, IDC_PWDEDIT, m_PwdTxt);
	DDX_Control(pDX, IDC_LISTMOTORISTA, m_Motoristas);
	DDX_Control(pDX, IDC_LISTDESTINO, m_Destinos);
	DDX_Control(pDX, IDC_LISTOBJETOS, m_Objetos);
	DDX_Control(pDX, IDC_CODIGOEDIT, m_CodigoTxt);
	DDX_Control(pDX, IDC_DESTEDIT, m_DestinoTxt);
	DDX_Control(pDX, IDC_BUTTONALL, m_AllButton);
	DDX_Control(pDX, IDC_LOGINBUTTON, m_LoginButton);
	DDX_Control(pDX, IDC_LISTOBJETOS2, m_ObjectSend);
	DDX_Control(pDX, IDC_SENDBUTTON, m_SendButton);
	DDX_Control(pDX, IDC_REMSELBUTTON, m_RemoveSelButton);
	DDX_Control(pDX, IDC_REMALLBUTTON, m_RemoveAllButton);
	DDX_Control(pDX, IDC_TRANSOUTBUTTON, m_TransOutButton);
	DDX_Control(pDX, IDC_TRANSINBUTTON, m_TransInButton);
}

BEGIN_MESSAGE_MAP(CseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGINBUTTON, &CseDlg::OnBnClickedLoginbutton)
	ON_EN_CHANGE(IDC_CODIGOEDIT, &CseDlg::OnEnChangeCodigoedit)
	ON_EN_CHANGE(IDC_DESTEDIT, &CseDlg::OnEnChangeDestedit)
	ON_BN_CLICKED(IDC_BUTTONALL, &CseDlg::OnBnClickedButtonall)
	ON_LBN_SELCHANGE(IDC_LISTOBJETOS, &CseDlg::OnLbnSelchangeListobjetos)
	ON_BN_CLICKED(IDC_SENDBUTTON, &CseDlg::OnBnClickedSendbutton)
	ON_BN_CLICKED(IDC_REMSELBUTTON, &CseDlg::OnBnClickedRemselbutton)
	ON_BN_CLICKED(IDC_REMALLBUTTON, &CseDlg::OnBnClickedRemallbutton)
	ON_LBN_SELCHANGE(IDC_LISTDESTINO, &CseDlg::OnLbnSelchangeListdestino)
	ON_BN_CLICKED(IDC_TRANSOUTBUTTON, &CseDlg::OnBnClickedTransoutbutton)
	ON_BN_CLICKED(IDC_TRANSINBUTTON, &CseDlg::OnBnClickedTransinbutton)
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
	catch (sql::SQLException& e)
	{
		MessageBox(e.what(), "Connect MySQL failed!!", MB_OK | MB_ICONEXCLAMATION);
		ExitProcess(-1);
	}

#ifdef _DEBUG
	m_CpfTxt.SetWindowTextA("000-111-222-01");
	m_PwdTxt.SetWindowTextA("admin");
#endif

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
		if (e.getErrorCode() != 0)
		{
			char errorStr[1024];
			sprintf(errorStr, "Error Code: %d\nError: %s\nSql: %s", e.getErrorCode(), e.what(), buf);

			MessageBox(errorStr, "Connect MySQL failed!!", MB_OK | MB_ICONEXCLAMATION);
		}
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

void CseDlg::RefreshLists()
{
	m_Motoristas.ResetContent();
	m_Destinos.ResetContent();

	SqlRes mot = SqlQuery(
		"SELECT U.CPF, U.Nome FROM Usuario U\n"
		"WHERE U.codigoCentro='%s' AND U.TipoUsuario=1",
		m_CenterCode);

	if (mot.CheckResult())
	{
		int index = 0;

		do
		{
			char item[256];
			sprintf(item, "%s %s", mot.Res->getString("CPF").c_str(), mot.Res->getString("Nome").c_str());

			m_Motoristas.InsertString(index++, item);
		} while (mot.Res->next());

		if (m_Motoristas.GetCount() > 0)
			m_Motoristas.SetCurSel(0);
	}

	SqlRes dest = SqlQuery(
		"SELECT C.Codigo, C.Cidade, C.Estado\n"
		"FROM Distancia_Centro DC\n"
		"JOIN Centro C ON ((codigoCentro1!='%s' AND C.Codigo=codigoCentro1) OR (codigoCentro2!='%s' AND C.Codigo=codigoCentro2))\n"
		"WHERE codigoCentro1='%s' OR codigoCentro2='%s'\n"
		"ORDER BY Distancia ASC",
		m_CenterCode, m_CenterCode, m_CenterCode, m_CenterCode);

	if (dest.CheckResult())
	{
		int index = 0;

		do
		{
			char item[256];
			sprintf(item, "%s %s,%s", dest.Res->getString("Codigo").c_str(), dest.Res->getString("Cidade").c_str(), dest.Res->getString("Estado").c_str());

			m_Destinos.InsertString(index++, item);
		} while (dest.Res->next());

		if (m_Destinos.GetCount() > 0)
			m_Destinos.SetCurSel(0);
	}

	RefreshObjects();
}

void CseDlg::RefreshObjects()
{
	SqlRes objs = SqlQuery("SELECT Codigo, CidadeDestino, EstadoDestino FROM Objetos WHERE codigoCentro='%s' ORDER BY EstadoDestino='%s' DESC", m_CenterCode, m_SelectedEstDest);

	m_Objetos.ResetContent();

	if (objs.CheckResult())
	{
		int index = 0;

		char cod[32];
		char des[32];

		m_CodigoTxt.GetWindowTextA(cod, sizeof(cod));
		m_DestinoTxt.GetWindowTextA(des, sizeof(des));

		do
		{
			char codigoStr[32];
			char cidadeStr[32];
			char estadoStr[32];

			strcpy(codigoStr, objs.Res->getString("Codigo").c_str());
			strcpy(cidadeStr, objs.Res->getString("CidadeDestino").c_str());
			strcpy(estadoStr, objs.Res->getString("EstadoDestino").c_str());

			bool isEmpty = (cod[0] == 0 && des[0] == 0);
			bool codStr = (StrStrI(codigoStr, cod));
			bool destStr = (StrStrI(cidadeStr, des) || StrStrI(estadoStr, des));

			if (isEmpty || codStr || destStr)
			{
				char item[256];
				sprintf(item, "%s %s,%s", codigoStr, cidadeStr, estadoStr);

				m_Objetos.InsertString(index, item);
				m_Objetos.SetSel(index, CheckObjectInTransport(item));

				index++;
			}
		} while (objs.Res->next());
	}
}

void CseDlg::OnBnClickedLoginbutton()
{
	char pwd[32];

	m_CpfTxt.GetWindowTextA(m_CPF, sizeof(m_CPF));
	m_PwdTxt.GetWindowTextA(pwd, sizeof(pwd));

	SqlRes res = SqlQuery("SELECT * FROM Usuario WHERE CPF='%s' AND Senha='%s'", m_CPF, pwd);

	if (res.CheckResult())
	{
		strcpy(m_CenterCode, res.Res->getString("codigoCentro").c_str());

		m_CpfTxt.EnableWindow(0);
		m_PwdTxt.EnableWindow(0);
		m_LoginButton.EnableWindow(0);

		m_CodigoTxt.EnableWindow();
		m_DestinoTxt.EnableWindow();
		m_AllButton.EnableWindow();

		m_Motoristas.EnableWindow();
		m_Destinos.EnableWindow();
		m_Objetos.EnableWindow();

		m_ObjectSend.EnableWindow();
		m_SendButton.EnableWindow();
		m_RemoveSelButton.EnableWindow();
		m_RemoveAllButton.EnableWindow();

		m_CodigoTxt.Clear();
		m_DestinoTxt.Clear();

		m_TransInButton.EnableWindow();
		m_TransOutButton.EnableWindow();

		RefreshLists();
	}
	else
		MessageBox("CPF ou Senha incorretas!", "Falha ao Logar", MB_OK | MB_ICONERROR);
}

void CseDlg::OnEnChangeCodigoedit()
{
	RefreshObjects();
}

void CseDlg::OnEnChangeDestedit()
{
	RefreshObjects();
}

void CseDlg::OnBnClickedButtonall()
{
	m_ObjectSend.ResetContent();

	for (int i = 0; i < m_Objetos.GetCount(); ++i)
	{
		m_Objetos.SetSel(i);

		char item[256];
		m_Objetos.GetText(i, item);

		m_ObjectSend.AddString(item);
	}
}

void CseDlg::OnLbnSelchangeListobjetos()
{
	int selId = m_Objetos.GetCurSel();
	if (selId >= 0)
	{
		char item[256];
		m_Objetos.GetText(selId, item);

		int option = m_Objetos.GetSel(selId);
		if (option == 1)
			m_ObjectSend.AddString(item);
		else
		{
			int Id;
			for (Id = 0; Id < m_ObjectSend.GetCount(); ++Id)
			{
				char listItem[256];
				m_ObjectSend.GetText(Id, listItem);

				if (strcmp(item, listItem) == 0)
					break;
			}

			if (Id < m_ObjectSend.GetCount())
				m_ObjectSend.DeleteString(Id);
		}
	}
}

void CseDlg::OnBnClickedSendbutton()
{
	int motId = m_Motoristas.GetCurSel();
	int destId = m_Destinos.GetCurSel();

	if (motId >= 0 && destId >= 0)
	{
		char motStr[256], motCpf[32];
		m_Motoristas.GetText(motId, motStr);

		if (sscanf(motStr, "%s", motCpf) == 1)
		{
			char destStr[256], destCenter[32];
			m_Destinos.GetText(destId, destStr);

			if (sscanf(destStr, "%s", destCenter) == 1)
			{
				time_t rawnow = time(0);
				tm* now = localtime(&rawnow);

				char dateTime[64];
				sprintf(dateTime, "%d-%d-%d %d:%d:%d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

				SqlQuery("INSERT INTO Transporte VALUES (true, '%s', '%s', '%s')", dateTime, m_CenterCode, motCpf);
				SqlQuery("INSERT INTO Transporte VALUES (false, '%s', '%s', '%s')", dateTime, destCenter, motCpf);
				SqlQuery("UPDATE Usuario SET codigoCentro=NULL WHERE CPF='%s'", motCpf);

				for (int Id = 0; Id < m_ObjectSend.GetCount(); ++Id)
				{
					char objStr[256], objCod[32];
					m_ObjectSend.GetText(Id, objStr);

					if (sscanf(objStr, "%s", objCod) == 1)
					{
						SqlQuery("INSERT INTO Transporte_Objetos VALUES (1, '%s', '%s', '%s')", dateTime, objCod, m_CenterCode);
						SqlQuery("UPDATE Objetos SET codigoCentro=NULL WHERE Codigo='%s'", objCod);

						SqlQuery("INSERT INTO Despacho VALUES ('%s', '%s', '%s', true, '%s', NULL)", m_CPF, m_CenterCode, objCod, dateTime);
					}
				}

				m_ObjectSend.ResetContent();

				RefreshLists();
				RefreshObjects();
			}
		}
	}
	else
		MessageBox("Voce deve selecionar o Motorista e o Destino.");
}

void CseDlg::DeselectObjectList(const char* item)
{
	for (int Id = 0; Id < m_Objetos.GetCount(); ++Id)
	{
		if (m_Objetos.GetSel(Id) == 1)
		{
			char listItem[256];
			m_Objetos.GetText(Id, listItem);

			if (strcmp(item, listItem) == 0)
			{
				m_Objetos.SetSel(Id, 0);
				break;
			}
		}
	}
}

bool CseDlg::CheckObjectInTransport(const char* item)
{
	for (int Id = 0; Id < m_ObjectSend.GetCount(); ++Id)
	{
		char listItem[256];
		m_ObjectSend.GetText(Id, listItem);

		if (strcmp(item, listItem) == 0)
			return true;
	}

	return false;
}

void CseDlg::OnBnClickedRemselbutton()
{
	int Id = 0;

	while (Id < m_ObjectSend.GetCount())
	{
		if (m_ObjectSend.GetSel(Id) == 1)
		{
			char item[256];
			m_ObjectSend.GetText(Id, item);
			m_ObjectSend.DeleteString(Id);

			DeselectObjectList(item);

			Id = 0;
		}
		else
			Id++;
	}
}

void CseDlg::OnBnClickedRemallbutton()
{
	for (int Id = 0; Id < m_ObjectSend.GetCount(); ++Id)
		m_ObjectSend.SetSel(Id);

	OnBnClickedRemselbutton();

	// Corrige caso tenha algum problema de sincronia:
	for (int Id = 0; Id < m_Objetos.GetCount(); ++Id)
	{
		if (m_Objetos.GetSel(Id) == 1)
			m_Objetos.SetSel(Id, 0);
	}
}

void CseDlg::OnLbnSelchangeListdestino()
{
	int Id = m_Destinos.GetCurSel();
	if (Id >= 0)
	{
		char item[256];
		m_Destinos.GetText(Id, item);

		(void)sscanf(item, "%*s %[^,],%s", m_SelectedCidDest, m_SelectedEstDest);

		RefreshObjects();
	}
}

void CseDlg::OnBnClickedTransoutbutton()
{
	CseListDlg fw(this);
	fw.m_StrList.clear();

	SqlRes res = SqlQuery(
		"SELECT U.Nome, C.Cidade, C.Estado, T.DataSaida\n"
		"FROM Transporte T\n"
		"INNER JOIN Usuario U ON U.CPF = T.cpfMotorista\n"
		"INNER JOIN(SELECT DataSaida, codigoCentro FROM Transporte WHERE Saida = 0) TD ON TD.DataSaida = T.DataSaida\n"
		"INNER JOIN Centro C ON C.Codigo=TD.codigoCentro\n"
		"WHERE T.Saida = 1 AND T.codigoCentro = '%s';", m_CenterCode);

	if (res.CheckResult())
	{
		int transCounter = 1;

		do
		{
			fw.AddStrListString("Transporte %d:", transCounter);
			fw.AddStrListString("\tMotorista: %s", res.Res->getString("Nome").c_str());
			fw.AddStrListString("\tDestino: %s, %s", res.Res->getString("Cidade").c_str(), res.Res->getString("Estado").c_str());
			fw.AddStrListString("\tData da Saida: %s\n", res.Res->getString("DataSaida").c_str());

			transCounter++;
		} while (res.Res->next());
	}

	fw.DoModal();
}

void CseDlg::OnBnClickedTransinbutton()
{
	CseListDlg fw(this);
	fw.m_StrList.clear();

	SqlRes res = SqlQuery(
		"SELECT U.Nome, C.Cidade, C.Estado, T.DataSaida\n"
		"FROM Transporte T\n"
		"INNER JOIN Usuario U ON U.CPF = T.cpfMotorista\n"
		"INNER JOIN(SELECT DataSaida, codigoCentro FROM Transporte WHERE Saida = 1) TD ON TD.DataSaida = T.DataSaida\n"
		"INNER JOIN Centro C ON C.Codigo=TD.codigoCentro\n"
		"WHERE T.Saida = 0 AND T.codigoCentro = '%s';", m_CenterCode);

	if (res.CheckResult())
	{
		int transCounter = 1;

		do
		{
			fw.AddStrListString("Transporte %d:", transCounter);
			fw.AddStrListString("\tMotorista: %s", res.Res->getString("Nome").c_str());
			fw.AddStrListString("\tDestino: %s, %s", res.Res->getString("Cidade").c_str(), res.Res->getString("Estado").c_str());
			fw.AddStrListString("\tData da Saida: %s\n", res.Res->getString("DataSaida").c_str());

			transCounter++;
		} while (res.Res->next());
	}

	fw.DoModal();
}
