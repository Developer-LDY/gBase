
// gBaseDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gBase.h"
#include "gBaseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CgBaseDlg 대화 상자



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


// CgBaseDlg 메시지 처리기

BOOL CgBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_logger.setConsoleLevel(G_LOGGER_LEVEL_TRACE);
	ScopeLog(&m_logger);
	//m_logger.infoA("start");
	//m_logger.set_level(spdlog::level::trace);
	//m_logger.changeLevel(spdlog::level::trace);

	m_imgDisplay.gSetUseRoi();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	//		fm[j*pitch + i] = 0xff - fm[j*pitch + i]; // 색 반전
	//	}
	//}
	//gTimeTracker::END("11",&m_logger);

	//m_imgDisplay.UpdateDisplay(); //화면 갱신

	CDC* pDC = m_imgDisplay.GetDC();
	HDC hDC = pDC->m_hDC; 

	//picture control 크기
	RECT rc; m_imgDisplay.GetClientRect(&rc); 

	//비트맵생성 
	HDC hMemDC = CreateCompatibleDC(hDC); 
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap); 
	BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); 
	
	//비트맵사양설정
	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right; bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1; bmih.biBitCount = 24; 
	bmih.biCompression = BI_RGB;

	// 비트맵(DIB) 데이터 추출 
	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS); 

	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS); 
	ReleaseDC(pDC); DeleteObject(hBitmap); 

	// 비트맵 파일 헤더 설정
	BITMAPFILEHEADER bmfh; bmfh.bfType = 'MB'; 
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage; 
	bmfh.bfReserved1 = 0; bmfh.bfReserved2 = 0; 
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 파일명설정
	CString Name; 
	Name.Format(_T("C:\\TestImage\\Test3.jpg"));
	_bstr_t gg(Name);
	BSTR lpszFileName = gg.copy(); 

	// 비트맵 파일 생성 및 데이터 저장 
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
	/* 다이얼로그 내에 static image 박스의 크기를 받아왔음
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
	
	/* CDC로 그리기
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

