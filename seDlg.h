
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

private:
	SqlRes() { }

	sql::Statement* Sta;
	sql::ResultSet* Res;
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

// Implementação
protected:
	HICON m_hIcon;

	// Funções geradas de mapa de mensagens
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
