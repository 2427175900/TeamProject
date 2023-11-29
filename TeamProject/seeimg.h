#pragma once
#include "afxdialogex.h"
#include"opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

// seeimg 对话框

class seeimg : public CDialogEx
{
	DECLARE_DYNAMIC(seeimg)

public:
	seeimg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~seeimg();
	Mat recive_input;
	Mat recive_output;
	std::string mes;
	void DisplayinImage(const cv::Mat& image); // 图像输出到 pic控件函数 传参Mat

	void DisplayoutImage(const cv::Mat& image); // 图像输出到 pic控件函数 传参Mat

	void SetinImage(Mat img);

	void SetoutImage(Mat img);

	void SetFilterString(String str);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTIMG_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic zongjietext;
	afx_msg void OnBnClickedOutbut();
	afx_msg void OnBnClickedButton2();
};
