
// CoreProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CoreProject.h"
#include "CoreProjectDlg.h"
#include "afxdialogex.h"
#include "ParamDialog.h"
#include<sstream>
#include<iomanip>

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
	, range(0)
{
	engine = newEngine;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoreProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listCtrl);
	DDX_Control(pDX, IDC_LIST3, list3Ctrl);
	DDX_Control(pDX, IDC_LIST4, list4Ctrl);
}

BEGIN_MESSAGE_MAP(CCoreProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32780, &CCoreProjectDlg::OnLoadData)
	ON_COMMAND_RANGE(7000, 8000, &CCoreProjectDlg::OnChooseRule)
	ON_BN_CLICKED(IDOK, &CCoreProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDBACK, &CCoreProjectDlg::OnBnClickedBack)
	ON_LBN_SELCHANGE(IDC_LIST2, &CCoreProjectDlg::OnLbnSelchangeList2)
	ON_LBN_SELCHANGE(IDC_LIST3, &CCoreProjectDlg::OnLbnSelchangeList3)
	ON_LBN_SELCHANGE(IDC_LIST4, &CCoreProjectDlg::OnLbnSelchangeList4)
	ON_WM_MOVE()
	ON_BN_CLICKED(17000, &CCoreProjectDlg::OnBnClickedRemove)
END_MESSAGE_MAP()


// CCoreProjectDlg message handlers

BOOL CCoreProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//int width = GetSystemMetrics(SM_CXSCREEN);
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
		this->GetMenu()->AppendMenu(MF_POPUP, (UINT_PTR)menu->m_hMenu, popupName);
		it++;
	}

	for (int i = 0; i < storage.size(); i++)
	{
		listCtrl.AddString(storage[i][0]);
		list3Ctrl.AddString(storage[i][1]);
		list4Ctrl.AddString(storage[i][2]);
	}
	if (isShort)
	{
		CWnd* temp = this->GetDlgItem(IDBACK);
		temp->EnableWindow(true);
	}

	RECT workArea, previousPosition;
	this->GetWindowRect(&previousPosition);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
	this->SetWindowPos(NULL, workArea.left, workArea.top, 1*workArea.right, 1*workArea.bottom, SWP_SHOWWINDOW |SWP_NOZORDER);
	this->GetWindowRect(&workArea);

	RECT tempWindowPos;
	CWnd* temp = this->GetDlgItem(IDOK);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL,tempWindowPos.left,
		workArea.bottom-100, tempWindowPos.right - tempWindowPos.left,
		tempWindowPos.bottom - tempWindowPos.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	
	temp = this->GetDlgItem(IDBACK);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL,tempWindowPos.left,
		workArea.bottom - 100, tempWindowPos.right - tempWindowPos.left,
		tempWindowPos.bottom - tempWindowPos.top, SWP_SHOWWINDOW | SWP_NOZORDER);

	temp = this->GetDlgItem(17000);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL, tempWindowPos.left,
		workArea.bottom - 100, tempWindowPos.right - tempWindowPos.left,
		tempWindowPos.bottom - tempWindowPos.top, SWP_SHOWWINDOW | SWP_NOZORDER);

	temp = this->GetDlgItem(IDC_LIST2);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL,tempWindowPos.left,
		tempWindowPos.top, tempWindowPos.right - tempWindowPos.left,
		workArea.bottom - 150, SWP_NOMOVE | SWP_NOZORDER);

	temp = this->GetDlgItem(IDC_LIST3);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL, tempWindowPos.left,
		tempWindowPos.top, tempWindowPos.right - tempWindowPos.left,
		workArea.bottom - 150, SWP_NOMOVE | SWP_NOZORDER);

	temp = this->GetDlgItem(IDC_LIST4);
	temp->GetWindowRect(&tempWindowPos);
	temp->SetWindowPos(NULL, tempWindowPos.left,
		tempWindowPos.top, tempWindowPos.right - tempWindowPos.left,
		workArea.bottom - 150, SWP_NOMOVE | SWP_NOZORDER);
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
	CPaintDC dc(this);
	if (!engine->is_empty())
	{
		int start = 16;
		for (int i = 0; i < itemColors.size(); i++)
		{
			CBrush brush;
			brush.CreateSolidBrush(itemColors[i]);
			dc.SelectObject(brush);
			dc.Rectangle(GRAPH_START - 50, start + i * 5, GRAPH_START - 30, start + (i + 1) * 5);
			start += 8;
		}
		CWnd * list = this->GetDlgItem(IDC_LIST2);
		RECT listBorders, windowBorders,workArea;
		list->GetWindowRect(&listBorders);
		this->GetWindowRect(&windowBorders);
		SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
		//this->MapWindowPoints(NULL, &windowBorders);

		CDC* memDC = new CDC;
		CDC* screenDC = GetDC();
		memDC->CreateCompatibleDC(screenDC);
		CBitmap *pb = new CBitmap;
		pb->CreateCompatibleBitmap(screenDC, workArea.right - 60 - GRAPH_START, listBorders.bottom - listBorders.top);
		CBitmap *pob = memDC->SelectObject(pb);

		DrawGraphs(memDC, workArea.right - 60 - GRAPH_START, listBorders.bottom - listBorders.top);

		memDC->SelectObject(pob);
		CImage final;
		final.Attach((HBITMAP)(*pb));
		final.StretchBlt((&dc)->m_hDC, GRAPH_START, listBorders.top - windowBorders.top-50, workArea.right - 60 - GRAPH_START, listBorders.bottom - listBorders.top, 0, 0, final.GetWidth(), final.GetHeight(), SRCCOPY);
		if (IsIconic())
		{
			// device context for painting

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

		range=engine->load_start_data(initialData, pathName);
		this->InvalidateRect(NULL);
		//GetSystemMenu(TRUE);
	}
	// TODO: Add your command handler code here
}


void CCoreProjectDlg::OnChooseRule(UINT nID)
{
	if (engine->is_empty()){

		MessageBox(_T("Please, load data in order to proceed"), _T("Error"),
			MB_ICONERROR | MB_OK);
	}
	else
	{
		CString menuItem;

		this->GetMenu()->GetMenuString(nID, menuItem, MF_BYCOMMAND);
		CT2CA pszConvertedAnsiString(menuItem);
		std::string  ruleName(pszConvertedAnsiString);

		std::vector<std::string> paramNames;
		engine->get_rule_param(paramNames, ruleName);
		CParamDialog dial(paramNames);
		if (dial.DoModal() == IDOK)
		{
			std::vector<double> parameters;
			for (int i = 0; i < paramNames.size(); i++)
			{
				parameters.push_back(dial.resultParams[i]);
			}
			diagramData tempData;
			double squareDev=0, relativeSquareDev=0, weightedSquareDev=0;
			rulesId.push_back(engine->create_new_rule(tempData, squareDev
				,relativeSquareDev,weightedSquareDev, ruleName, parameters));
			usedRules.push_back(tempData);
			CString result;
			std::ostringstream temp3;
			temp3.setf(std::ios::fixed);
			temp3.precision(3);
			for (int i = 0; i < parameters.size(); i++)
			{
				CString temp1, temp2;
				temp3.str("");
				temp3<< parameters[i];
				temp1.Format(_T("%S"), temp3.str().c_str());
				temp2.Format(_T("%S"), paramNames[i].c_str());
				result += temp2 + "=" + temp1 + _T(" ");
			}
			temp3.str("");
			temp3 << squareDev << "; " << relativeSquareDev << "; " << weightedSquareDev;
			CString deviationString;

			deviationString.Format(_T("%S"), temp3.str().c_str());
			listCtrl.AddString(menuItem);
			list3Ctrl.AddString(result);
			list4Ctrl.AddString(deviationString);

			itemColors.push_back(dial.currentColor);
			RECT rect;
			this->GetClientRect(&rect);
			this->InvalidateRect(&rect);
		}
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
		engine->set_result_rule(rulesId[listCtrl.GetCurSel()]);
		storage.clear();
		for (int i = 0; i < listCtrl.GetCount(); i++)
		{
			CString temp1,temp2,temp3;
			listCtrl.GetText(i, temp1);
			list3Ctrl.GetText(i, temp2);
			list4Ctrl.GetText(i, temp3);
			std::vector<CString> temp;
			temp.push_back(temp1);
			temp.push_back(temp2);
			temp.push_back(temp3);
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


void CCoreProjectDlg::OnLbnSelchangeList2()
{
	list3Ctrl.SetCurSel(listCtrl.GetCurSel());
	list4Ctrl.SetCurSel(listCtrl.GetCurSel());
	// TODO: Add your control notification handler code here
}


void CCoreProjectDlg::OnLbnSelchangeList3()
{
	listCtrl.SetCurSel(list3Ctrl.GetCurSel());
	list4Ctrl.SetCurSel(list3Ctrl.GetCurSel());
	// TODO: Add your control notification handler code here
}


void CCoreProjectDlg::OnLbnSelchangeList4()
{
	list3Ctrl.SetCurSel(list4Ctrl.GetCurSel());
	listCtrl.SetCurSel(list4Ctrl.GetCurSel());
	// TODO: Add your control notification handler code here
}


void CCoreProjectDlg::DrawGraphs(CDC* memDC,int width,int height)
{
	CBrush* oldBrush = (CBrush*)memDC->SelectStockObject(WHITE_BRUSH);
	CPen* oldPen = new CPen();
	memDC->Rectangle(0, 0,width, height);
	memDC->SelectObject(oldBrush);

	int startX = 30, startY = -30;
	double koeffX = (1.*width - 2*startX) / range, koeffY = (1.*height +2*startY) / 1.3;
	
	for (int i = 0; i < usedRules.size(); i++)
	{
		CPen* pen = new CPen();
		CBrush* brush = new CBrush();
		pen->CreatePen(PS_SOLID, 3, itemColors[i]);
		brush->CreateSolidBrush(itemColors[i]);
		oldPen= memDC->SelectObject(pen);
		oldBrush = memDC->SelectObject(brush);
		int pointR = 2;
		for (int j = 0; j < usedRules[i].size()-1; j++)
		{
			memDC->MoveTo(startX + (int)(usedRules[i][j].first*koeffX), startY+ height - (int)(usedRules[i][j].second*koeffY));
		//	memDC->Ellipse(startX + (int)(usedRules[i][j].first*koeffX - 3.0), startY + height - (int)(usedRules[i][j].second*koeffY) - 3, startX + (int)(usedRules[i][j].first*koeffX) + 3, startY + height - (int)(usedRules[i][j].second*koeffY) + 3);
			memDC->LineTo(startX + (int)(usedRules[i][j + 1].first*koeffX), startY + height - (int)(usedRules[i][j + 1].second*koeffY));
		}

		memDC->SelectObject(oldPen);
		memDC->SelectObject(oldBrush);
	}

	CPen* pen = new CPen();
	pen->CreatePen(PS_SOLID, 3, RGB(0,0,0));
	oldPen = memDC->SelectObject(pen);

	for (int i = 0; i < initialData.size()-1; i++)
	{
		memDC->MoveTo(startX + (int)(initialData[i].first*koeffX), startY + height - (int)(initialData[i].second*koeffY));
		memDC->LineTo(startX + (int)(initialData[i+1].first*koeffX), startY + height - (int)(initialData[i+1].second*koeffY));
	}

	memDC->SelectObject(oldPen);

	CPen* redPen = new CPen();
	redPen->CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	oldPen = memDC->SelectObject(redPen);

	CFont* font = new CFont();
	font->CreateFont(
		12,                       
		0,                         
		0,                        
		0,                         
		FW_NORMAL,                 
		FALSE,                     
		FALSE,                     
		0,                         
		ANSI_CHARSET,              
		OUT_DEFAULT_PRECIS,        
		CLIP_DEFAULT_PRECIS,      
		DEFAULT_QUALITY,           
		DEFAULT_PITCH | FF_SWISS,  
		_T("Arial"));  
	CFont* oldFont = memDC->SelectObject(font);

	std::ostringstream trunc;
	trunc.setf(std::ios::fixed);
	trunc.precision(3);

	memDC->MoveTo(startX, startY + height);
	memDC->LineTo(startX, -startY);
	memDC->MoveTo(startX, startY + height);
	memDC->LineTo(width - startX, startY + height);

	for (int i = startX + (width - 2 * startX) / 15,j=1; i < width - startX; i += (width - 2 * startX) / 15,j++)
	{
		memDC->MoveTo(i, startY + height - 5);
		memDC->LineTo(i, startY + height + 5);
		CString str;
		trunc.str("");
		trunc << ((1.*j) / 15)*range*1.3;
		str.Format(_T("%S"),trunc.str().c_str() );
		memDC->TextOutW(i -14, startY + height + 10,str);
	}

	for (int i = startY + height - (height + 2 * startY) / 8,j = 1; i >-startY; i -= (height + 2 * startY) / 8,j++)
	{
		memDC->MoveTo(startX-5, i);
		memDC->LineTo(startX+5, i);
		CString str;
		trunc.str("");
		trunc << ((1.*j) / 8)*1.3;
		str.Format(_T("%S"), trunc.str().c_str());
		memDC->TextOutW(startX-25, i+5, str);
	}
}


void CCoreProjectDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	this->InvalidateRect(NULL);
	// TODO: Add your message handler code here
}


void CCoreProjectDlg::OnBnClickedRemove()
{
	int currentRule = list3Ctrl.GetCurSel();
	if (currentRule < 0)
	{
		MessageBox(_T("Please, select rule in the list in order to proceed"), _T("Error"),
			MB_ICONERROR | MB_OK);
	}
	else
	{
		listCtrl.DeleteString(currentRule);
		list3Ctrl.DeleteString(currentRule);
		list4Ctrl.DeleteString(currentRule);

		usedRules.erase(usedRules.begin()+currentRule);
		engine->remove_rule(rulesId[currentRule]);
		rulesId.erase(rulesId.begin() + currentRule);
		itemColors.erase(itemColors.begin() + currentRule);
		this->InvalidateRect(NULL);
	}
	// TODO: Add your control notification handler code here
}
