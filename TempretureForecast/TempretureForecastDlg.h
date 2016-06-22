
// TempretureForecastDlg.h : ͷ�ļ�
//

#pragma once
#define POINT_COUNT 48


// CTempretureForecastDlg �Ի���
class CTempretureForecastDlg : public CDialogEx
{
// ����
public:
	CTempretureForecastDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEMPRETUREFORECAST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	//int m_waveDataValues[POINT_COUNT];
public:
	CString m_dateAndCurTempreture;         //��ǰʱ��͵�ǰ�¶�
	CStatic m_bgPic;      //����
	CDC m_memDC;          //�ڴ�DC
	CBitmap m_bmp;        //����λͼ
	CRect m_rect;         //���οͻ���
	//CDataSave m_optData;  //���ݲ�������
	int m_MaxTemp;        //����¶�
	int m_MinTemp;        //����¶�
	int m_numOfTemp;      //�¶���������
	int m_waveDataValues[POINT_COUNT];
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ��õ�ǰʱ��ε�����¶Ⱥ�����¶�
	void GetMaxAndMinTemp();
public:
	afx_msg void OnClose();
	//��õ�ǰʱ��
	CString GetCurTime();
	CString GetCurTemp(int currTemp);
};
