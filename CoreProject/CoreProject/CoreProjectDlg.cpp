
// CoreProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CoreProject.h"
#include "CoreProjectDlg.h"
#include "afxdialogex.h"
#include "ParamDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCoreProjectDlg dialog



CCoreProjectDlg::CCoreProjectDlg(rulesEngine* newEngine,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoreProjectDlg::IDD, pParent)
	, isShort(false)
{
	engine = newEngine;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoreProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listCtrl);
}

BEGIN_MESSAGE_MAP(CCoreProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32780, &CCoreProjectDlg::OnLoadData)
	ON_COMMAND_RANGE(7000, 8000, &CCoreProjectDlg::OnChooseRule)
	ON_BN_CLICKED(IDOK, &CCoreProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDBACK, &CCoreProjectDlg::OnBnClickedBack)
END_MESSAGE_MAP()


// CCoreProjectDlg message handlers

BOOL CCoreProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(IDR_MENU1);

	std::unordered_map<std::string, std::vector<std::string>> rulesMap = engine->get_rules_map();
	
	auto it = rulesMap.begin();
	int idInner = 7000;
	while (it != rulesMap.end())
	{
		CMenu *menu = new CMenu;
		menu->CreatePopupMenu();
		auto it2 = it->second.begin();
		while (it2 != it->second.end())
		{
			CString menuItem;
			menuItem.Format(_T("%S"), it2->c_str());
			menu->AppendMenu(MF_STRING, idInner, menuItem);
			it2++;
			idInner++;
		}
		CString popupName;
		popupName.Format(_T("%S"), it->first.c_str());
		this->GetMenu()->AppendMenu(MF_POPUP, (UINT_PTR)menu->m_hMenu,popupName);
		it++;
	}

	for (int i = 0; i < storage.size(); i++)
	{
		listCtrl.AddString(storage[i]);
	}
	if (isShort)
	{
		CWnd* temp = this->GetDlgItem(IDBACK);
		temp->EnableWindow(true);
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	if (isShort)
	{
		this->SetWindowTextW(_T("Shortened testing"));
	}
	else
	{
		this->SetWindowTextW(_T("Boosted testing"));
	}
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCoreProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCoreProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCoreProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCoreProjectDlg::OnLoadData()
{
	TCHAR szFilters[] = _T("(*.txt)|*.txt");
	CFileDialog fileDlg(TRUE, _T("txt"), _T("*.txt"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CT2CA pszConvertedAnsiString(fileDlg.GetPathName());
		std::string pathName(pszConvertedAnsiString);

		diagramData tempData;

		engine->load_start_data(tempData, pathName);
	
		//GetSystemMenu(TRUE);
	}
	// TODO: Add your command handler code here
}


void CCoreProjectDlg::OnChooseRule(UINT nID)
{
	CString menuItem,subMenu;
	std::string rulesGroup,ruleName;
	this->GetMenu()->GetMenuString(nID, menuItem, MF_BYCOMMAND);
	std::unordered_map<std::string, std::vector<std::string>> rulesMap = engine->get_rules_map();

	auto it = rulesMap.begin();
	while (it != rulesMap.end())
	{
		auto it2 = it->second.begin();
		while (it2 != it->second.end())
		{
			CString tempItem;
			tempItem.Format(_T("%S"), it2->c_str());
			if (tempItem == menuItem)
			{
				subMenu.Format(_T("%S"), it->first.c_str());
				rulesGroup = it->first;
				ruleName = *(it2);
				break;
			}
			it2++;
		}
		it++;
	}
	CParamDialog dial(subMenu);
	if (dial.DoModal() == IDOK)
	{
		std::vector<double> parameters;
		parameters.push_back(dial.firstParam);
		if (subMenu == "Two parametrs")
		{
			parameters.push_back(dial.secondParam);
		}
		diagramData tempData;
		engine->create_new_rule(tempData, rulesGroup, ruleName, parameters);
		usedRules.push_back(tempData); 
		CString result = menuItem + _T(": ");
		std::vector<std::string> paramNames;
		engine->get_rule_param(paramNames, rulesGroup, ruleName);
		for (int i = 0; i < parameters.size(); i++)
		{
			CString temp1,temp2;
			temp1.Format(_T("%f"), parameters[i]);
			temp2.Format(_T("%S"), paramNames[i].c_str());
			result += temp2+"="+temp1+_T(" ");
		}
		listCtrl.AddString(result);
		selectedRule.first = rulesGroup;
		selectedRule.second = ruleName;
	}
	
}


void CCoreProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (listCtrl.GetCurSel() < 0)
	{
		MessageBox(_T("Please, select rule in the list in order to proceed"), _T("Error"),
			MB_ICONERROR | MB_OK);
	}
	else{
		storage.clear();
		for (int i = 0; i < listCtrl.GetCount(); i++)
		{
			CString temp;
			listCtrl.GetText(i, temp);
			storage.push_back(temp);
		}
		CDialogEx::OnOK();
	}
}


void CCoreProjectDlg::OnBnClickedBack()
{
	this->EndDialog(IDBACK);
	// TODO: Add your control notification handler code here
}
