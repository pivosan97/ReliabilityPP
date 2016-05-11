// ParamDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CoreProject.h"
#include "ParamDialog.h"
#include "afxdialogex.h"
#include<vector>

// CParamDialog dialog

IMPLEMENT_DYNAMIC(CParamDialog, CDialogEx)

CParamDialog::CParamDialog(CString category,std::vector<std::string> params, CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamDialog::IDD, pParent)
	, firstParam(0)
	, secondParam(0)
	, rulesCategory(category)
{
	for (int i = 0; i < params.size(); i++)
	{
		paramNames.push_back(params[i]);
	}
}

CParamDialog::~CParamDialog()
{
}

void CParamDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, firstParam);
	DDX_Text(pDX, IDC_EDIT2, secondParam);
}


BEGIN_MESSAGE_MAP(CParamDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CParamDialog::OnChooseColor)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CParamDialog message handlers


BOOL CParamDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (rulesCategory == "Two parametrs")
	{
		CWnd *temp = GetDlgItem(IDC_EDIT2);
		temp->ShowWindow(SW_SHOW);
		temp = GetDlgItem(6001);
		temp->ShowWindow(SW_SHOW);
	}
	for (int i = 0; i < paramNames.size(); i++)
	{
		CWnd *temp = GetDlgItem(6000+i);
		CString paramName;
		paramName.Format(_T("%S"), paramNames[i].c_str());
		temp->SetWindowTextW(paramName);
		

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CParamDialog::OnChooseColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		currentColor = dlg.GetColor();
		RECT rect;
		this->GetClientRect(&rect);
		this->InvalidateRect(&rect);

	}
	// TODO: Add your control notification handler code here
}


void CParamDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush brush;
	CBrush* oldBrush;
	brush.CreateSolidBrush(currentColor);
	//oldBrush=CBrush::FromHandle((HBRUSH));
	dc.SelectObject(brush);
	dc.Rectangle(200, 140, 225, 165);
	//dc.SelectObject(oldBrush);
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}


/*HBRUSH CParamDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_:
		pDC->SetTextColor(RGB(255, 0, 0));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}*/
