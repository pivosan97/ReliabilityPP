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
	, fourthParameter(0)
	, fifthParameter(0)
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
	DDX_Text(pDX, 8000, firstParam);
	DDX_Text(pDX, 8001, secondParam);
	DDX_Text(pDX, 8002, thirdParameter);
	DDX_Text(pDX, 8003, fourthParameter);
	DDX_Text(pDX, 8004, fifthParameter);
}


BEGIN_MESSAGE_MAP(CParamDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CParamDialog::OnChooseColor)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CParamDialog message handlers


BOOL CParamDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	for (int i = 0; i < paramNames.size(); i++)
	{
		CWnd *temp = GetDlgItem(6000+i);
		CString paramName;
		paramName.Format(_T("%S"), paramNames[i].c_str());
		temp->SetWindowTextW(paramName);
		temp->ShowWindow(SW_SHOW);

		temp = GetDlgItem(8000 + i);
		temp->ShowWindow(SW_SHOW);

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
