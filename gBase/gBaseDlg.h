
// gBaseDlg.h : ��� ����
//

#pragma once
#define __G_DEBUG__
#include "afxwin.h"

#include "gLogger.h"
#include "gImage.h"



// CgBaseDlg ��ȭ ����
class CgBaseDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CgBaseDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GBASE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	gImage m_imgDisplay;
	gLogger m_logger;
	
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnDrawGrid();
	afx_msg void OnBnClickedBtnSave();
};