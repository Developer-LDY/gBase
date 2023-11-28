
// gBaseDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "gBase.h"
#include "gBaseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgBaseDlg ��ȭ ����



CgBaseDlg::CgBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GBASE_DIALOG, pParent)
	, m_logger("main", ".\\log")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_imgDisplay);
}

BEGIN_MESSAGE_MAP(CgBaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CgBaseDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_DRAW_GRID, &CgBaseDlg::OnBnClickedBtnDrawGrid)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CgBaseDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CgBaseDlg �޽��� ó����

BOOL CgBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_logger.setConsoleLevel(G_LOGGER_LEVEL_TRACE);
	ScopeLog(&m_logger);
	//m_logger.infoA("start");
	//m_logger.set_level(spdlog::level::trace);
	//m_logger.changeLevel(spdlog::level::trace);

	m_imgDisplay.gSetUseRoi();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CgBaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CgBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgBaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgBaseDlg::OnBnClickedBtnLoad()
{
	CFileDialog fDlg(true);
	if (fDlg.DoModal() == IDOK)
		m_imgDisplay.gLoad(fDlg.GetPathName());
}

#include <experimental\/filesystem>
namespace fs = std::experimental::filesystem;

void MakeDirectory(const string &path) {
	fs::path p(path);


	if (fs::is_directory(p))
		return;

	fs::create_directories(p);
}

void CgBaseDlg::OnBnClickedBtnSave()
{
	//gTimeTracker::START("11",&m_logger);
	//int pitch = m_imgDisplay.gGetPitch();
	//unsigned char* fm = m_imgDisplay.gGetImgPtr();
	//CRect r = m_imgDisplay.gGetRoi();

	//for (int j = r.top; j < r.bottom; j++) {
	//	for (int i = r.left; i < r.right; i++) {
	//		fm[j*pitch + i] = 0xff - fm[j*pitch + i]; // �� ����
	//	}
	//}
	//gTimeTracker::END("11",&m_logger);

	//m_imgDisplay.UpdateDisplay(); //ȭ�� ����

	CDC* pDC = m_imgDisplay.GetDC();
	HDC hDC = pDC->m_hDC; 

	//picture control ũ��
	RECT rc; m_imgDisplay.GetClientRect(&rc); 

	//��Ʈ�ʻ��� 
	HDC hMemDC = CreateCompatibleDC(hDC); 
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap); 
	BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); 
	
	//��Ʈ�ʻ�缳��
	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right; bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1; bmih.biBitCount = 24; 
	bmih.biCompression = BI_RGB;

	// ��Ʈ��(DIB) ������ ���� 
	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS); 

	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS); 
	ReleaseDC(pDC); DeleteObject(hBitmap); 

	// ��Ʈ�� ���� ��� ����
	BITMAPFILEHEADER bmfh; bmfh.bfType = 'MB'; 
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage; 
	bmfh.bfReserved1 = 0; bmfh.bfReserved2 = 0; 
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// ���ϸ���
	CString Name; 
	Name.Format(_T("C:\\TestImage\\Test3.jpg"));
	_bstr_t gg(Name);
	BSTR lpszFileName = gg.copy(); 

	// ��Ʈ�� ���� ���� �� ������ ���� 
	DWORD dwWritten; 
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
	WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL); 
	WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL); 

	CloseHandle(hFile); 

	delete[] lpBits;


	m_imgDisplay.gSaveOverlay("C:\\TestImage\\Test.jpg",1,FALSE);

	CRect rectCrop = { 0,0,800,800 };
	
	string strFolderPath = "C:\\TestImage\\CropImages";
	MakeDirectory(strFolderPath);

	string strCropImageName_first = "\\sample image crop ";
	string strCropImageName_second = ".jpg";

	string strTimeTest;
	time_t timeNow;
	timeNow = time(NULL);
	strCropImageName_second = fmt::format(" {}-{}-{} {}{}{}.jpg", 
		(localtime(&timeNow)->tm_year + 1900), (localtime(&timeNow)->tm_mon + 1), (localtime(&timeNow)->tm_mday), 
		(localtime(&timeNow)->tm_hour), (localtime(&timeNow)->tm_min), (localtime(&timeNow)->tm_sec));
	
	int nGridWidth = m_imgDisplay.gGetWidth();
	int nGridHeight = m_imgDisplay.gGetHeight();
	int nGridRow = 8;

	for (int j = 1; j <= nGridRow; j++) {
		for (int i = 1; i <= nGridRow; i++) {
			rectCrop.SetRect((int)(nGridWidth * ((float)(i - 1) / 8)), (int)(nGridHeight * ((float)(j - 1) / 8)),
				(int)(nGridWidth * ((float)i / 8)), (int)(nGridHeight * ((float)j / 8)));

			//m_logger.debug(strCropImageName_first + to_string(i + (nGridRow*(j - 1))) + strCropImageName_second);
			//m_logger.debug("{}", (int)(nGridWidth * ((float)(i - 1) / 8)));

			m_imgDisplay.gSaveCropImage(rectCrop, strFolderPath + strCropImageName_first + to_string(i + (nGridRow*(j - 1))) + strCropImageName_second, FALSE);
		}
	}
	

}


#define COLOR_RED	RGB(0xff,0x00,0x00)
void CgBaseDlg::OnBnClickedBtnDrawGrid()
{
	/* ���̾�α� ���� static image �ڽ��� ũ�⸦ �޾ƿ���
	CWnd *wndStaticDisplay;
	wndStaticDisplay = GetDlgItem(IDC_STATIC_DISPLAY);
	
	CRect rectStaticDisplay;
	(*wndStaticDisplay).GetClientRect(rectStaticDisplay);

	int nGridWidth = rectStaticDisplay.Width();
	int nGridHeight = rectStaticDisplay.Height();
	*/

	int nGridWidth = m_imgDisplay.gGetWidth();
	int nGridHeight = m_imgDisplay.gGetHeight();

	int nGridRow = 8;
	for (int i = 0; i <= nGridRow; i++) {

		if (i == 0) {
			m_imgDisplay.gDrawLine({ 0, 0 }, { nGridWidth,0 }, COLOR_RED, 5);
			m_imgDisplay.gDrawLine({ 0, 0 }, { 0,nGridHeight }, COLOR_RED, 5);
		}
		else {
			m_imgDisplay.gDrawLine({ 0, (int)(nGridHeight * ((float)i / 8)) }, { nGridWidth, (int)(nGridHeight * ((float)i / 8)) }, COLOR_RED, 5);
			m_imgDisplay.gDrawLine({ (int)(nGridWidth * ((float)i / 8)), 0 }, { (int)(nGridWidth * ((float)i / 8)), nGridHeight }, COLOR_RED, 5);
		}
	}
	
	m_imgDisplay.UpdateDisplay();
	
	/* CDC�� �׸���
	CWnd *wndStaticDisplay;
	wndStaticDisplay = GetDlgItem(IDC_STATIC_DISPLAY);

	CDC* dc = m_imgDisplay.GetDC();

	CClientDC pdc(this);

	CRect rectStaticDisplay; 
	wndStaticDisplay->GetClientRect(rectStaticDisplay);


	CPen penRed;
	penRed.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen = dc->SelectObject(&penRed);

	for (int i = 0; i <= 8; i++) {
		if (i == 0) {
			dc->MoveTo(rectStaticDisplay.left, rectStaticDisplay.top);
			dc->LineTo(rectStaticDisplay.right, rectStaticDisplay.top);
		}
		else {
			dc->MoveTo(rectStaticDisplay.left, rectStaticDisplay.bottom * i / 8);
			dc->LineTo(rectStaticDisplay.right, rectStaticDisplay.bottom * i / 8);
		}
	}

	for (int i = 0; i <= 8; i++) {
		if (i == 0) {
			dc->MoveTo(rectStaticDisplay.left, rectStaticDisplay.top);
			dc->LineTo(rectStaticDisplay.left, rectStaticDisplay.bottom);
		}
		else {
			dc->MoveTo(rectStaticDisplay.right  * i / 8, rectStaticDisplay.top);
			dc->LineTo(rectStaticDisplay.right  * i / 8, rectStaticDisplay.bottom);
		}
	}
	dc->SelectObject(oldPen);
	*/
}

