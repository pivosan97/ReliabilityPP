#pragma once


// CParamDialog dialog

class CParamDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDialog)

public:
	CParamDialog(CString category,CWnd* pParent = NULL);   // standard constructor
	virtual ~CParamDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double firstParam;
	double secondParam;
private:
	CString rulesCategory;
public:
	virtual BOOL OnInitDialog();
};
