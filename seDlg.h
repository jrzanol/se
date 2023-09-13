
// seDlg.h: arquivo de cabeçalho
//

#pragma once

class SqlRes
{
public:
	SqlRes(sql::Statement* s, sql::ResultSet* r)
	{
		Sta = s;
		Res = r;
	}
	~SqlRes()
	{
		if (Sta)
			delete Sta;
		if (Res)
			delete Res;
	}
	bool CheckResult()
	{
		return Sta != nullptr && Res != nullptr && Res->next();
	}

	sql::Statement* Sta;
	sql::ResultSet* Res;

private:
	SqlRes() { }
};

// caixa de diálogo CseDlg
class CseDlg : public CDialogEx
{
// Construção
public:
	CseDlg(CWnd* pParent = nullptr);	// construtor padrão

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Suporte DDX/DDV

private:
	sql::Driver* driver;
	sql::Connection* con;

	SqlRes SqlQuery(const char*, ...);

	char m_CPF[32];
	char m_CenterCode[16];
	char m_SelectedCidDest[32];
	char m_SelectedEstDest[32];

	void RefreshLists();
	void RefreshObjects();

	void DeselectObjectList(const char*);
	bool CheckObjectInTransport(const char*);

// Implementação
protected:
	HICON m_hIcon;

	// Funções geradas de mapa de mensagens
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CpfTxt;
	CEdit m_PwdTxt;
	afx_msg void OnBnClickedLoginbutton();
	CListBox m_Motoristas;
	CListBox m_Destinos;
	CListBox m_Objetos;
	CEdit m_CodigoTxt;
	CEdit m_DestinoTxt;
	CButton m_AllButton;
	CButton m_LoginButton;
	afx_msg void OnEnChangeCodigoedit();
	afx_msg void OnEnChangeDestedit();
	afx_msg void OnBnClickedButtonall();
	afx_msg void OnLbnSelchangeListobjetos();
	afx_msg void OnBnClickedSendbutton();
	afx_msg void OnBnClickedRemselbutton();
	afx_msg void OnBnClickedRemallbutton();
	CListBox m_ObjectSend;
	CButton m_SendButton;
	CButton m_RemoveSelButton;
	CButton m_RemoveAllButton;
	afx_msg void OnLbnSelchangeListdestino();
	CButton m_TransOutButton;
	CButton m_TransInButton;
	afx_msg void OnBnClickedTransoutbutton();
	afx_msg void OnBnClickedTransinbutton();
};
