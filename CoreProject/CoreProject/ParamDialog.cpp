// ParamDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CoreProject.h"
#include "ParamDialog.h"
#include "afxdialogex.h"


// CParamDialog dialog

IMPLEMENT_DYNAMIC(CParamDialog, CDialogEx)

CParamDialog::CParamDialog(CString category,CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamDialog::IDD, pParent)
	, firstParam(0)
	, secondParam(0)
	, rulesCategory(category)
{
	
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
END_MESSAGE_MAP()


// CParamDialog message handlers


BOOL CParamDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (rulesCategory == "Two parametrs")
	{
		CWnd *temp = GetDlgItem(IDC_EDIT2);
		temp->ShowWindow(SW_SHOW);
		temp = GetDlgItem(IDC_STATIC2);
		temp->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
