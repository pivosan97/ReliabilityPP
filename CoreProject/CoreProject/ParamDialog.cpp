// ParamDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CoreProject.h"
#include "ParamDialog.h"
#include "afxdialogex.h"
#include<vector>

// CParamDialog dialog

IMPLEMENT_DYNAMIC(CParamDialog, CDialogEx)

CParamDialog::CParamDialog(std::vector<std::string> params, CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamDialog::IDD, pParent)
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
}


BEGIN_MESSAGE_MAP(CParamDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CParamDialog::OnChooseColor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CParamDialog::OnBnClickedOk)
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
	CColorDialog dlg(currentColor);
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
	RECT rect;
	GetClientRect(&rect);
	dc.Rectangle(210,348,230,368);
	

}


void CParamDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	resultParams.clear();
	for (int i = 0; i < paramNames.size(); i++)
	{
		CString temp;
		this->GetDlgItemText(8000 + i, temp);
		resultParams.push_back(_tstof(temp));
	}
	CDialogEx::OnOK();
}
