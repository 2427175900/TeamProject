// seeimg.cpp: 实现文件
//

#include "pch.h"
#include "TeamProject.h"
#include "afxdialogex.h"
#include "seeimg.h"


// seeimg 对话框

IMPLEMENT_DYNAMIC(seeimg, CDialogEx)

seeimg::seeimg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OUTIMG_DLG, pParent)
{

}

seeimg::~seeimg()
{
}

void seeimg::DisplayinImage(const cv::Mat& image)
{
	if (image.empty()) {
		AfxMessageBox(_T("图像为空，无法显示"));
		return;
	}

	CStatic* pPicControl = (CStatic*)GetDlgItem(IDC_STATICin);
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
void seeimg::SetinImage(Mat img) {
	recive_input = img;
}
void seeimg::SetoutImage(Mat img) {
	recive_output = img;
}void seeimg::SetFilterString (std::string str) {
	mes = str;
}

void seeimg::DisplayoutImage(const cv::Mat& image)
{
	if (image.empty()) {
		AfxMessageBox(_T("图像为空，无法显示"));
		return;
	}

	CStatic* pPicControl = (CStatic*)GetDlgItem(IDC_STATICout);
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

void seeimg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, zongjie, zongjietext);
}


BEGIN_MESSAGE_MAP(seeimg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &seeimg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OUTBUT, &seeimg::OnBnClickedOutbut)
END_MESSAGE_MAP()


// seeimg 消息处理程序


void seeimg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DisplayinImage(recive_input);
	DisplayoutImage(recive_output);
	std::wstring wmes(mes.begin(), mes.end());
	SetDlgItemText(zongjie,wmes.c_str());
}


void seeimg::OnBnClickedOutbut()
{
	cv::imwrite("outputimg.jpg",recive_output);
	// TODO: 在此添加控件通知处理程序代码
}
