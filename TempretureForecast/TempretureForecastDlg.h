
// TempretureForecastDlg.h : 头文件
//

#pragma once
#define POINT_COUNT 48


// CTempretureForecastDlg 对话框
class CTempretureForecastDlg : public CDialogEx
{
// 构造
public:
	CTempretureForecastDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEMPRETUREFORECAST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	//int m_waveDataValues[POINT_COUNT];
public:
	CString m_dateAndCurTempreture;         //当前时间和当前温度
	CStatic m_bgPic;      //背景
	CDC m_memDC;          //内存DC
	CBitmap m_bmp;        //缓存位图
	CRect m_rect;         //矩形客户区
	//CDataSave m_optData;  //数据操作对象
	int m_MaxTemp;        //最高温度
	int m_MinTemp;        //最低温度
	int m_numOfTemp;      //温度数据数量
	int m_waveDataValues[POINT_COUNT];
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	void DrawCoordinate(CDC *pDC, CRect& rect);
	void DrawWave(CDC *pDC, CRect& rect);
	// 获得当前时间段的最高温度和最低温度
	void GetMaxAndMinTemp();
public:
	afx_msg void OnClose();
	//获得当前时间
	CString GetCurTime();
	CString GetCurTemp(int currTemp);
};
