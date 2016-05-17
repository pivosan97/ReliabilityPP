
// CoreProjectDlg.h : header file
//

#pragma once

#include<fstream>
#include <vector>
#include <string>
#include "RulesEngine.h"
#include "abstractRule.h"
#include "lineRule.h"
#include "hyperbolaRule.h"
#include "afxwin.h"
// CCoreProjectDlg dialog
class CCoreProjectDlg : public CDialogEx
{
// Construction
public:
	CCoreProjectDlg(rulesEngine* engine,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COREPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLoadData();
	void SetEngine(rulesEngine* newEngine)
	{
		engine = newEngine;
	}
private:
	rulesEngine* engine;
public:
	std::vector<diagramData> usedRules;
private:
	void OnChooseRule(UINT nID);
    int GRAPH_START = 480;
public:
	CListBox listCtrl;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBack();
	std::vector<std::vector<CString>> storage;
	bool isShort;
	CListBox list3Ctrl;
	CListBox list4Ctrl;
	std::vector<COLORREF> itemColors;
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnLbnSelchangeList4();
	std::vector<int> rulesId;
	void DrawGraphs(CDC* memDC, int width, int height);
	int range;
};
