
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
	DDX_Control(pDX, IDC_BUTTON1, noisetext);
	DDX_Control(pDX, IDC_BUTTON1, noisetext);
	DDX_Control(pDX, NoiseText, noisetext);
}

BEGIN_MESSAGE_MAP(CTeamProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTeamProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTONauto, &CTeamProjectDlg::OnBnClickedButtonauto)
	ON_BN_CLICKED(IDC_BUTTON3, &CTeamProjectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTeamProjectDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTeamProjectDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTeamProjectDlg::OnBnClickedButton6)
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
	seeimg1.Create(IDD_OUTIMG_DLG);
	seeimg2.Create(IDD_OUTIMG_DLG);
	seeimg3.Create(IDD_OUTIMG_DLG);
	seeimg4.Create(IDD_OUTIMG_DLG);
	seeimg5.Create(IDD_OUTIMG_DLG);
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


//---------------------------------------------------------//
//噪声检测部分//
// 检测椒盐噪声
bool detectSaltAndPepperNoise(const cv::Mat& img, double threshold = 0.05) {
	int count_sp = 0;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255 || img.at<uchar>(i, j) == 0) {
				count_sp++;
			}
		}
	}
	double sp_ratio = static_cast<double>(count_sp) / (img.rows * img.cols);
	return sp_ratio > threshold;
}

// 检测高斯噪声
bool detectGaussianNoise(const cv::Mat& img, double threshold = 1.0) {
	cv::Mat mean, stddev;
	cv::meanStdDev(img, mean, stddev);
	double std_dev = stddev.at<double>(0, 0);
	return std_dev > threshold;
}

// 检测斑点噪声
bool detectSpeckleNoise(const cv::Mat& img, double threshold = 1.0) {
	cv::Mat gray, squared, mean, stddev;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	cv::multiply(gray, gray, squared);
	cv::meanStdDev(squared, mean, stddev);
	double variance = stddev.at<double>(0, 0) * stddev.at<double>(0, 0);
	return variance > threshold;
}

// 检测泊松噪声
bool detectPoissonNoise(const cv::Mat& img) {
	// 对于泊松噪声，通常需要更复杂的分析，这里提供一个简化的检测方法
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	double minVal, maxVal;
	cv::minMaxLoc(gray, &minVal, &maxVal);
	return maxVal < 128; // 假设在低亮度下泊松噪声更明显
}

std::string detectNoiseType(const cv::Mat& img) {
	if (detectSaltAndPepperNoise(img)) {
		return "Salt-and-Pepper";
	}
	else if (detectGaussianNoise(img)) {
		return "Gaussian";
	}
	else if (detectSpeckleNoise(img)) {
		return "Speckle";
	}
	else if (detectPoissonNoise(img)) {
		return "Poisson";
	}
	else {
		return "None";
	}
}


//---------------------------------//

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

double CTeamProjectDlg::calculateNoiseSeverity(const cv::Mat& image) {
	if (image.channels() != 1 && image.channels() != 3) {
		// 只支持单通道（灰度）和三通道（彩色）图像
		std::cerr << "Unsupported image format" << std::endl;
		return -1.0;
	}

	cv::Mat grayImage;
	if (image.channels() == 3) {
		// 如果是三通道图像，转换为灰度图像
		cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
	}
	else {
		// 如果是单通道图像，直接使用
		grayImage = image.clone();
	}

	cv::Mat blurredImage;
	cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0);

	cv::Mat diff;
	cv::absdiff(grayImage, blurredImage, diff);

	cv::Scalar mean, stddev;
	cv::meanStdDev(diff, mean, stddev);

	double noiseSeverity = stddev.val[0] / 255.0; // 标准差归一化到0到1之间

	return noiseSeverity;

}
// 自动选择合适的滤波器进行去噪

//手动滤波器
cv::Mat  CTeamProjectDlg::applyGaussianFilter(const cv::Mat& image) {
	cv::Mat denoisedImage;
	cv::GaussianBlur(image, denoisedImage, cv::Size(5, 5), 0);
	return denoisedImage;
}

cv::Mat  CTeamProjectDlg::applyMedianFilter(const cv::Mat& image) {
	cv::Mat denoisedImage;
	cv::medianBlur(image, denoisedImage, 5);
	return denoisedImage;
}

cv::Mat   CTeamProjectDlg ::CTeamProjectDlg::applyBilateralFilter(const cv::Mat& image) {
	cv::Mat denoisedImage;
	cv::bilateralFilter(image, denoisedImage, 9, 75, 75);
	return denoisedImage;
}

cv::Mat  CTeamProjectDlg::applyMeanFilter(const cv::Mat& image) {
	cv::Mat denoisedImage;
	cv::blur(image, denoisedImage, cv::Size(5, 5));
	return denoisedImage;
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
	double num  = calculateNoiseSeverity(oriimg);
	if (num < 0.05) {
		SetDlgItemText(NoiseText, _T("Noise Severity: Low "));
	}
	else if (num >= 0.05 && num < 0.10) {
		SetDlgItemText(NoiseText, _T("Noise Severity: Moderate"));
	}
	else if (num >= 0.10 && num < 0.17) {
		SetDlgItemText(NoiseText, _T("Noise Severity: High"));
	}
	else {
		SetDlgItemText(NoiseText, _T("Noise Severity: Very High"));
	}
	std::string num1;
	num1 = std::to_string(num);
	std::wstring wnum(num1.begin(), num1.end());
	AfxMessageBox(wnum.c_str());

}


void CTeamProjectDlg::OnBnClickedButtonauto()
{
	// TODO: 在此添加控件通知处理程序代码
	String str;
	if (detectNoiseType(oriimg) == "Salt-and-Pepper") {
		medianBlur(oriimg, outimg, 5);
		str = "Noise type : Salt-and-Pepper \nFilter : Median ";
	}
	else if (detectNoiseType(oriimg) == "Gaussian") {
		GaussianBlur(oriimg, outimg, cv::Size(5, 5), 0);
		str = "Noise type : Gaussian \nFilter : Gaussian  ";
	}
	else if (detectNoiseType(oriimg) == "Speckle") {
		bilateralFilter(oriimg, outimg, 9, 75, 75);
		str = "Noise type : Speckle  \nFilter : Bilateral   ";
	}
	else if (detectNoiseType(oriimg) == "Poisson") {
		medianBlur(oriimg, outimg, 5);
		str = "Noise type : Poisson \nFilter : Median ";
	
	}else if (detectNoiseType(oriimg) == "None") {
	
	}



	seeimg1.SetinImage(oriimg);
	seeimg1.SetoutImage(outimg);
	seeimg1.SetFilterString(str);
	seeimg1.ShowWindow(SW_NORMAL);
}


void CTeamProjectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	outimg = applyGaussianFilter(oriimg);
	seeimg2.SetinImage(oriimg);
	seeimg2.SetoutImage(outimg);
	seeimg2.ShowWindow(SW_NORMAL);
}


void CTeamProjectDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	outimg = applyMedianFilter(oriimg);
	seeimg3.SetinImage(oriimg);
	seeimg3.SetoutImage(outimg);
	seeimg3.ShowWindow(SW_NORMAL);
}


void CTeamProjectDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	outimg = applyBilateralFilter(oriimg);
	seeimg4.SetinImage(oriimg);
	seeimg4.SetoutImage(outimg);
	seeimg4.ShowWindow(SW_NORMAL);
}


void CTeamProjectDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	outimg = applyMeanFilter(oriimg);
	seeimg5.SetinImage(oriimg);
	seeimg5.SetoutImage(outimg);
	seeimg5.ShowWindow(SW_NORMAL);
}
