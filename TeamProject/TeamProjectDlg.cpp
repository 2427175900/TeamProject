
// TeamProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TeamProject.h"
#include "TeamProjectDlg.h"
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


// CTeamProjectDlg 대화 상자



CTeamProjectDlg::CTeamProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEAMPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTeamProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTeamProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTeamProjectDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTeamProjectDlg 메시지 처리기

BOOL CTeamProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTeamProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTeamProjectDlg::OnPaint()
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
HCURSOR CTeamProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTeamProjectDlg::DisplayImage(const cv::Mat& image)
{
	if (image.empty()) {
		AfxMessageBox(_T("图像为空，无法显示"));
		return;
	}

	CStatic* pPicControl = (CStatic*)GetDlgItem(IDC_STATIC);
	CDC* pDC = pPicControl->GetDC();
	CRect rect;
	pPicControl->GetClientRect(&rect);

	// 清空控件内容
	pDC->FillSolidRect(&rect, RGB(255, 255, 255));

	// 计算最佳的缩放比例
	double scale = min((double)rect.Width() / image.cols, (double)rect.Height() / image.rows);
	cv::Size size((int)(image.cols * scale), (int)(image.rows * scale)); // 缩放后的尺寸

	// 根据缩放后的大小调整原图
	cv::Mat resizedImg;
	cv::resize(image, resizedImg, size);

	// 创建一个临时CImage
	CImage tempImage;
	tempImage.Create(size.width, size.height, image.channels() * 8);

	// 复制数据到CImage
	if (resizedImg.step == static_cast<size_t>(tempImage.GetPitch()))
	{
		memcpy(tempImage.GetBits(), resizedImg.data, resizedImg.step * resizedImg.rows);
	}
	else
	{
		for (int y = 0; y < resizedImg.rows; ++y) {
			uchar* src = resizedImg.ptr<uchar>(y); // 指向 Mat 的当前行
			uchar* dst = reinterpret_cast<uchar*>(tempImage.GetBits()) + y * tempImage.GetPitch(); // 指向 CImage 的当前行
			memcpy(dst, src, resizedImg.step); // 复制行
		}
	}

	// 将临时CImage的内容绘制到控件上，居中显示
	int x = (rect.Width() - size.width) / 2;
	int y = (rect.Height() - size.height) / 2;
	tempImage.Draw(pDC->m_hDC, x, y);

	// 释放DC
	pPicControl->ReleaseDC(pDC);

	// 清空之前的图像资源
	HBITMAP hBitmap = tempImage.Detach();
	if (hBitmap != NULL) {
		DeleteObject(hBitmap);
	}
}


void CTeamProjectDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString filter;
	filter = _T("Image Files (*.bmp;*.jpg;*.jpeg;*.gif;*.png)|*.bmp;*.jpg;*.jpeg;*.gif;*.png|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, this);

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName(); // 获取选定文件的全路径
		oriimg = cv::imread(cv::String(CT2A(filePath.GetString())));
		DisplayImage(oriimg); // 使用封装后的函数来显示图像
	}
}
