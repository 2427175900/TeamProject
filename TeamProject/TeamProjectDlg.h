﻿
// TeamProjectDlg.h: 헤더 파일
//

#pragma once
#include"opencv2/opencv.hpp"
#include"seeimg.h"
using namespace cv;

// CTeamProjectDlg 대화 상자
class CTeamProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CTeamProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEAMPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void DisplayImage(const cv::Mat& image); // 图像输出到 pic控件函数 传参Mat

	double calculateNoiseSeverity(const cv::Mat& image);//分析噪点强度

	cv::Mat denoiseImage(const cv::Mat& image, double noiseSeverity);//去噪

	cv::Mat applyGaussianFilter(const cv::Mat& image);//高斯

	cv::Mat applyMedianFilter(const cv::Mat& image);//中值

	cv::Mat applyBilateralFilter(const cv::Mat& image);//双边

	cv::Mat applyMeanFilter(const cv::Mat& image);//均值
    Mat oriimg;
	Mat outimg;

private:
	seeimg seeimg1;
	seeimg seeimg2;
	seeimg seeimg3;
	seeimg seeimg4;
	seeimg seeimg5;
	
public:
	afx_msg void OnBnClickedButtonauto();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	
	CStatic noisetext;
};
