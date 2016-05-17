#pragma once
#include<vector>
#include "afxcmn.h"
#include "afxwin.h"
// CParamDialog dialog

class CParamDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDialog)

public:
	CParamDialog(  std::vector<std::string> params,CWnd* pParent = NULL);   // standard constructor
	virtual ~CParamDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString rulesCategory;
	std::vector<std::string> paramNames;
public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnChooseColor();
	COLORREF currentColor;
	afx_msg void OnPaint();

	std::vector<double> resultParams;
	afx_msg void OnBnClickedOk();
};
