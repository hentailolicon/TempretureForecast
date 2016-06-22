
// TempretureForecastDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempretureForecast.h"
#include "TempretureForecastDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define POINT_COUNT 48
#define TIMER_DRAW 1
#define TIMER_COLLECT 2
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTempretureForecastDlg �Ի���



CTempretureForecastDlg::CTempretureForecastDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTempretureForecastDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTempretureForecastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BACKGROUND, m_bgPic);
	DDX_Text(pDX, IDC_EDIT_TIMEANDTEMP, m_dateAndCurTempreture);
	DDX_Text(pDX, IDC_EDIT_MAXTEMP, m_MaxTemp);
	DDX_Text(pDX, IDC_EDIT_MINTEMP, m_MinTemp);
}

BEGIN_MESSAGE_MAP(CTempretureForecastDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTempretureForecastDlg ��Ϣ�������

BOOL CTempretureForecastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//��ÿͻ���
	//m_bgPic.GetClientRect(&m_rect);
	m_bgPic.GetClientRect(m_rect);
	//��������DC
	m_memDC.CreateCompatibleDC(m_bgPic.GetDC());
	//��������bitmap
	m_bmp.CreateCompatibleBitmap(m_bgPic.GetDC(), m_rect.Width(), m_rect.Height());
    m_memDC.SelectObject(&m_bmp);

	// ��ʱ��Ϊ���������������������   
	srand((unsigned)time(NULL));
	// ������ʱ����IDΪ1����ʱʱ��Ϊ200ms   
	SetTimer(TIMER_DRAW, 200, NULL);
	SetTimer(TIMER_COLLECT, 3600000, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTempretureForecastDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTempretureForecastDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTempretureForecastDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTempretureForecastDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �������е�����Ԫ��ǰ��һ����λ����һ��Ԫ�ض���   
	for (int i = 0; i<POINT_COUNT - 1; i++)
	{
		m_waveDataValues[i] = m_waveDataValues[i + 1];
	}
	// Ϊ���һ��Ԫ�ظ�һ��50���ڵ������ֵ�����ͣ�   
	m_waveDataValues[POINT_COUNT - 1] = rand() % 50 + 1;

	//��������ϵ
	DrawCoordinate(&m_memDC, m_rect);
	// ���Ʋ���ͼ   
	DrawWave(&m_memDC, m_rect);

	// ��ʾ��ǰ������¶Ⱥ�����¶�
	m_numOfTemp = POINT_COUNT;
	//GetMaxAndMinTemp();

	// ��ʾ��ǰʱ���ʵʱ�¶�
	m_dateAndCurTempreture = GetCurTime() + GetCurTemp(m_waveDataValues[POINT_COUNT - 1]);
	//������DC����ʵ�ʵĴ�����
	m_bgPic.GetDC()->BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &m_memDC, 0, 0, SRCCOPY);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CTempretureForecastDlg::DrawCoordinate(CDC *pDC, CRect& rect)
{
	CPen dotPen;      // ���ڴ������߻���   
	CPen solidPen;     // ���ڴ���ʵ�Ļ���
	CPen *pOldPen;     // ���ڴ�žɻ���     
	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush *pOldBrush; // ���ڴ�žɻ�ˢ   
	CRect codrect;
	codrect.bottom = rect.bottom - 50;
	codrect.top = rect.top + 20;
	codrect.left = rect.left + 50;
	codrect.right = rect.right - 20;
	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(240, 240, 240));
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	pDC->Rectangle(rect);
	// �ָ��ɻ�ˢ   
	pDC->SelectObject(pOldBrush);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();

	// ����ʵ�Ļ��ʣ��ֶ�Ϊ2����ɫΪ��ɫ   
	solidPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	// �������߻��ʣ��ֶ�Ϊ1����ɫΪ��ɫ
	dotPen.CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&solidPen);
	//pDC->Rectangle(m_rect);
	//����Y��   
	pDC->MoveTo(codrect.left, codrect.bottom);
	pDC->LineTo(codrect.left, codrect.top);
	//���Ƽ�ͷ
	pDC->LineTo(codrect.left - 4, codrect.top + 4);
	pDC->MoveTo(codrect.left, codrect.top);
	pDC->LineTo(codrect.left + 4, codrect.top + 4);

	//����X��
	pDC->MoveTo(codrect.left, codrect.bottom);
	pDC->LineTo(codrect.right, codrect.bottom);
	//���Ƽ�ͷ
	pDC->LineTo(codrect.right - 4, codrect.bottom - 4);
	pDC->MoveTo(codrect.right, codrect.bottom);
	pDC->LineTo(codrect.right - 4, codrect.bottom + 4);


	//��������Ϳ̶�
	pOldPen = pDC->SelectObject(&dotPen);
	int xlength = codrect.right - codrect.left;
	int ylength = codrect.bottom - codrect.top;
	int xavlength = (codrect.right - codrect.left) / 2;
	int yavlength = ylength / 10;
	for (int i = 1; i <= 10; i++)
	{
		CString scale;
		scale.Format(_T("%d"), i * 5);
		if (i == 1)
			pDC->TextOutW(codrect.left - 20, codrect.bottom, _T("0"));
		pDC->TextOutW(codrect.left - 20, codrect.bottom - yavlength*i, scale);
		pDC->MoveTo(codrect.left, codrect.bottom - yavlength*i);
		pDC->LineTo(codrect.right, codrect.bottom - yavlength*i);
	}
	//��ʾ��������Сʱ���¶ȣ�ǰһ��Сʱ�ǲɼ����ģ���һ��Сʱ��Ԥ���
	for (int i = 0; i <2; i++)
	{
		CString strTime = this->GetCurTime();
		strTime = strTime.Mid(strTime.GetLength() - 3, 2);
		int intTime = _ttoi(strTime) + i;
		strTime.Format(_T("%d"), intTime);
		pDC->TextOutW(codrect.left + i*xavlength, codrect.bottom + 10, strTime);
	}

	//����X/Y���ʶ
	pDC->TextOutW(codrect.left - 40, codrect.bottom - yavlength * 5, _T("��"));
	pDC->TextOutW(codrect.left - 40, codrect.bottom - yavlength * 5 + 15, _T("��"));

	pDC->TextOutW(codrect.left + xavlength, codrect.bottom + 30, _T("ʱ��"));
	//AfxMessageBox(_T("SDS"));
	//InvalidateRect(rectPicture);
	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);
	// ɾ���»���   
	newBrush.DeleteObject();
	solidPen.DeleteObject();
	dotPen.DeleteObject();
}


void CTempretureForecastDlg::DrawWave(CDC *pDC, CRect &rect)
{
	float fDeltaX;     // x������������ͼ����������   
	float fDeltaY;     // y��ÿ���߼���λ��Ӧ������ֵ   
	int nX;      // ������ʱ���ڴ洢��ͼ��ĺ�����   
	int nY;      // ������ʱ���ڴ洢��ͼ���������   
	CPen newPen;       // ���ڴ����»���   
	CPen *pOldPen;     // ���ڴ�žɻ���   

	CRect codrect;    //����ϵ��������
	codrect.bottom = rect.bottom - 50;
	codrect.top = rect.top + 20;
	codrect.left = rect.left + 50;
	codrect.right = rect.right - 20;

	// ����fDeltaX��fDeltaY   
	fDeltaX = (float)codrect.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)codrect.Height() / 50;



	// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// ����ǰ���ƶ�����ͼ�ؼ����ڵ����½ǣ��Դ�Ϊ���ε���ʼ��   
	pDC->MoveTo(codrect.left, codrect.bottom);
	// ����m_nzValues������ÿ�����Ӧ������λ�ã����������ӣ������γ�����   
	for (int i = 0; i<POINT_COUNT; i++)
	{
		nX = codrect.left + (int)(i * fDeltaX);
		nY = codrect.bottom - (int)(m_waveDataValues[i] * fDeltaY);
		if (m_waveDataValues[i] == 0)
			pDC->MoveTo(nX, nY);
		else
			pDC->LineTo(nX, nY);
	}
	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);
	// ɾ���»���   
	newPen.DeleteObject();
}


// ��õ�ǰʱ��ε�����¶Ⱥ�����¶�
void CTempretureForecastDlg::GetMaxAndMinTemp()
{
	//CAlgorithm alg;
	//m_MaxTemp = alg.GetMax(m_numOfTemp, m_waveDataValues);
	//m_MinTemp = alg.GetMin(m_numOfTemp, m_waveDataValues);
}


void CTempretureForecastDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_memDC.DeleteDC();        //ɾ��DC
	m_bmp.DeleteObject();      //ɾ��λͼ
	KillTimer(TIMER_DRAW);
	KillTimer(TIMER_COLLECT);
	CDialogEx::OnClose();
}


CString CTempretureForecastDlg::GetCurTime()
{
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	CString str;
	str.Format(_T("%02d��%02d�� %02dʱ"), curTime.wMonth, curTime.wDay,
		curTime.wHour);
	return str;
}


CString CTempretureForecastDlg::GetCurTemp(int currTemp)
{
	CString str;
	str.Format(_T("%d"), currTemp);
	str = _T("ʵʱ�¶ȣ�") + str + _T("��");
	return str;
}
