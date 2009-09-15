#include "StdAfx.h"
#include "StatisticButton.h"
#include "MemDC.h"
#include "global.h"
#include <pcap.h>

//class CLinker;
//CLinker *h_linker;
extern UINT Connect(LPVOID pvParam);
extern UINT DisConnect(LPVOID pvParam);


CString AllTraffic;
CString Total;

int *threshold;
UINT cur=0,hhg=0;
UINT total;
BOOL *autoCutOff;
BOOL *largethan;
bool isOnline=false;

float* TrafficStats=NULL;
DWORD	TrafficEntries;

void dispatcher_handler(u_char *state, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    struct timeval *old_ts = (struct timeval *)state;
    u_int delay;
//    time_t local_tv_sec;

    /* Calculate the delay in microseconds from the last sample. */
    /* This value is obtained from the timestamp that the associated with the sample. */
    delay=(header->ts.tv_sec - old_ts->tv_sec) * 1000000 + header->ts.tv_usec - old_ts->tv_usec;
    /* Get the number of Bytes per second */
    cur=(((*(UINT*)(pkt_data + 8)) * 1000000) / (delay));
    /*                                                 ^
                                                       |
                  delay is expressed in microseconds --
    */
	for(DWORD x=0; x<TrafficEntries; x++)
		TrafficStats[x]	= TrafficStats[x+1];
	TrafficStats[TrafficEntries]=cur/1024.0;
	//TRACE("TrafficStats[%d]: %f\n", TrafficEntries,TrafficStats[TrafficEntries]);
	
	if(cur>hhg) hhg=cur;

	AllTraffic.Format(_T("CUR: %.1f KB/SEC  HHG: %.1f KB/SEC"),cur/1024.0, hhg/1024.0);
		
	total+=(*(UINT*)(pkt_data + 8))/1024;
	//自动断网
	TRACE("*****autoCutOff=%d  %I64d  %d\n", *autoCutOff,*threshold*1024,total);
	
	if(isOnline && *largethan && total>=*threshold*1024)
	{
		//linker->OnBnClickedButton2();
		*largethan=false;
		if(*autoCutOff)
		{
			AfxBeginThread(DisConnect,NULL);
			AfxMessageBox(L"流量超标，并已自动断网");
		}
		else
			AfxMessageBox(L"流量超标");

		
		//h_linker->OnBnClickedButton2();
	}

/////////////////////////////////////////
	//待加判断
	Total.Format(_T("TOTAL: %.1f MB"),total/1024.0);

    /* Print the samples */
//  TRACE("BPS=%I64u ", cur);//调试用
//	UINT Pps;
//	Pps=(((*(UINT*)(pkt_data)) * 1000000) / (delay));
//  TRACE("PPS=%I64u\n", Pps);

    //store current timestamp
    old_ts->tv_sec=header->ts.tv_sec;
    old_ts->tv_usec=header->ts.tv_usec;
}



CStatisticButton::CStatisticButton(void)
: isdu(false)
{
	brushInitalized = FALSE;

	gridxstartpos = 0;
	gridystartpos = 0;

	gridxresolution		=	GRIDXRESOLUTION;
	gridyresolution		=	GRIDYRESOLUTION;
	gridscrollxspeed	=	GRIDSCROLLXSPEED;
	gridscrollyspeed	=	GRIDSCROLLYSPEED; 
	plotgranularity		=	PLOTGRANULATRITY;
	netupdatespeed		=	NETUPDATESPEED;
	gridupdatespeed		=	GRIDUPDATESPEED;
}
CStatisticButton::CStatisticButton(bool du)
: isdu(du)
{
	brushInitalized = FALSE;

	gridxstartpos = 0;
	gridystartpos = 0;

	gridxresolution		=	GRIDXRESOLUTION;
	gridyresolution		=	GRIDYRESOLUTION;
	gridscrollxspeed	=	GRIDSCROLLXSPEED;
	gridscrollyspeed	=	GRIDSCROLLYSPEED; 
	plotgranularity		=	PLOTGRANULATRITY;
	netupdatespeed		=	NETUPDATESPEED;
	gridupdatespeed		=	GRIDUPDATESPEED;
}


CStatisticButton::~CStatisticButton(void)
{
	delete TrafficStats;
}
BEGIN_MESSAGE_MAP(CStatisticButton, CButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CStatisticButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);
	CButton::OnTimer(nIDEvent);
}

void CStatisticButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	ASSERT( lpDrawItemStruct != NULL );

	CDC * pDC   = CDC::FromHandle( lpDrawItemStruct -> hDC );
	int erg = pDC->SelectClipRgn(&ShapeDCRegion);

	CRect rect = lpDrawItemStruct -> rcItem;
	UINT state = lpDrawItemStruct -> itemState;
	UINT nStyle = GetStyle( );

	int nSavedDC = pDC -> SaveDC( );

	// Create the brush for the color bar
	if(brushInitalized == FALSE)
	{
		CBitmap bmp;
		CMyDC *memDC = new CMyDC(pDC);
		
		RECT clipRect;
		memDC->GetClipBox(&clipRect);

		if(clipRect.right - clipRect.left > 1)
		{
			if(!isdu)
			{
				bmp.CreateCompatibleBitmap(memDC,plotgranularity, TGSize.cy);
				CBitmap *pOld = memDC->SelectObject(&bmp);
				
				CSize bmps = bmp.GetBitmapDimension();		
				
				// Need for scaling the color to the size of button
				double factor = 255.0 / (float)TGSize.cy;
				BYTE r,g,b;
				for(int x = 0; x<TGSize.cy; x++)
				{
					g = (BYTE)(255-factor*x);
					r = (BYTE)(factor*x);
					b = (BYTE)64;
					memDC->SetPixelV(0,x,RGB(r,g,b));
					memDC->SetPixelV(1,x,RGB(r,g,b));
				}
				memDC->SelectObject(pOld);

				colorbrush.CreatePatternBrush(&bmp);	
				brushInitalized = TRUE;
			}
			else
			{
				bmp.CreateCompatibleBitmap(memDC,TGSize.cx, TGSize.cy);
				CBitmap *pOld = memDC->SelectObject(&bmp);
				
				CSize bmps = bmp.GetBitmapDimension();		
				
				// Need for scaling the color to the size of button
				double factor = 255.0 / (float)TGSize.cx;
				BYTE r,g,b;
				for(int x = 0; x<TGSize.cx; x++)
				{
					g = (BYTE)(255-factor*x);
					r = (BYTE)(factor*x);
					b = (BYTE)70;
					for(int y = 0; y<TGSize.cy; y++)
						memDC->SetPixelV(x,y,RGB(r,g,b));
				}
				memDC->SelectObject(pOld);

				colorbrush.CreatePatternBrush(&bmp);	
///////////////////////////////////////////////////////
				CBitmap backbmp;
				backbmp.CreateCompatibleBitmap(memDC,TGSize.cx, TGSize.cy);
				pOld = memDC->SelectObject(&backbmp);
				
				bmps = backbmp.GetBitmapDimension();		
				
				// Need for scaling the color to the size of button
				factor = 160.0 / (float)TGSize.cy;
				int c=0;
				bool jian=false;
				for(int y = 0; y<TGSize.cy; y++)
				{
					if(!jian)
					{
						c=(175+factor*y);
						if(c>=255)jian=true;
					}
					else
						c=c-factor*(y-TGSize.cy/2+1)/4;
					
					for(int x = 0; x<TGSize.cx; x++)
						memDC->SetPixelV(x,y,RGB(c,c,c));
				}
				memDC->SelectObject(pOld);

				backbrush.CreatePatternBrush(&backbmp);
///////////////////////////////////////////////////
				brushInitalized = TRUE;
			}
		}

		delete memDC;
	}
	if(initalized == TRUE)
	{
		if(!isdu)
		{
			COLORREF backcolor = GetSysColor(COLOR_BTNFACE);
			
			CBrush brush;
			CMyDC *memDC = new CMyDC(pDC);
			
			RECT clipRect;
			memDC->GetClipBox(&clipRect);
			memDC->FillSolidRect(&clipRect,backcolor);
			
			CFont *oldFont;
			int xp, yp, xx, yy;
			orgBrushOrigin = memDC->GetBrushOrg();
			
			oldFont = memDC->SelectObject(&smallFont);
			
			double scale = TGSize.cy / (hhg/1024.0);
			
			yp = TrafficDrawRectangle.bottom;
			xp = TrafficDrawRectangle.left;
			
			RECT fillrect;
			
			// Fill the background
			back = memDC->GetBkColor();
			brush.CreateSolidBrush(darkblue);//back);
			memDC->FillRect(&TrafficDrawRectangle, &brush);

			
			//画网格
			int xgridlines, ygridlines;
			
			xgridlines = TGSize.cx / gridxresolution;
			ygridlines = TGSize.cy / gridyresolution;
			CPen* oldPen = memDC->SelectObject(&GridPen);

			// Create the vertical lines
			for (int x=0; x<= xgridlines; x++)
			{
				memDC->MoveTo(x*gridxresolution + gridxstartpos, 0			);
				memDC->LineTo(x*gridxresolution + gridxstartpos, TGSize.cy	);
			}
			// And the horizontal lines
			for (int y=0; y<= ygridlines; y++)
			{
				memDC->MoveTo(0			, gridystartpos + TGSize.cy - y*gridyresolution - 2);
				memDC->LineTo(TGSize.cx	, gridystartpos + TGSize.cy - y*gridyresolution - 2);
			}

			gridxstartpos += gridscrollxspeed;
			gridystartpos += gridscrollyspeed;
			if(gridxstartpos < 0				) gridxstartpos += gridxresolution;
			if(gridxstartpos > gridxresolution	) gridxstartpos -= gridxresolution;
			if(gridystartpos < 0				) gridystartpos += gridyresolution;
			if(gridystartpos > gridyresolution	) gridystartpos -= gridyresolution;


			memDC->SelectObject(oldPen );

			for(DWORD cnt=0; cnt<TrafficEntries; cnt++)
			{
				xx = xp + cnt*plotgranularity;
				yy = yp - (int)(TrafficStats[cnt] * scale);
				
				// Just paint if we are connected...
				fillrect.bottom = yp;
				fillrect.top	= yy;
				fillrect.left	= xx;
				fillrect.right	= xx+plotgranularity;
				memDC->SetBrushOrg(xx,yp);
				//TRACE("TrafficStats[%d]: %f\n", cnt,TrafficStats[cnt]);
				if(TrafficStats[cnt] > 0.0) 
				{
					//画柱状图
					memDC->FillRect(&fillrect, &colorbrush);
					memDC->SetPixelV(xx, yy, cyan);
				}
			}

			COLORREF textcolor = memDC->GetTextColor();
			int bkmode = memDC->GetBkMode();
			memDC->SetBkMode(TRANSPARENT);

			//输出统计信息
			memDC->SetTextColor(cyan);
			memDC->TextOut(5,5,AllTraffic); 
			memDC->TextOut(5,18,Total);

			memDC->SetTextColor(textcolor);
			memDC->SetBkMode(bkmode);
			memDC->SelectObject(oldFont);
			memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);
		
			delete memDC;
		}	
		else
		{
			COLORREF backcolor = GetSysColor(COLOR_BTNFACE);
			
			CBrush brush;
			CMyDC *memDC = new CMyDC(pDC);
			
			RECT clipRect;
			memDC->GetClipBox(&clipRect);
			memDC->FillSolidRect(&clipRect,backcolor);
			memDC->FillRect(&TrafficDrawRectangle, &backbrush);
			orgBrushOrigin = memDC->GetBrushOrg();
		
			double temp=total/1024.0;
			RECT fillrect;
			int width=TrafficDrawRectangle.right-TrafficDrawRectangle.left;
			fillrect.bottom = TrafficDrawRectangle.bottom;
			fillrect.top	= TrafficDrawRectangle.top;
			fillrect.left	= TrafficDrawRectangle.left;
			fillrect.right	= TrafficDrawRectangle.left+width*(temp/(*threshold));

			memDC->SetBrushOrg(TrafficDrawRectangle.left,TrafficDrawRectangle.bottom);
			memDC->FillRect(&fillrect, &colorbrush);

			COLORREF textcolor = memDC->GetTextColor();
			int bkmode = memDC->GetBkMode();
			memDC->SetBkMode(TRANSPARENT);

			//输出统计信息
			CFont *oldFont;
			oldFont = memDC->SelectObject(&bigFont);

			memDC->SetTextColor(darkgreen);
			CString ratio;
			
			ratio.Format(_T("%.1f/%d (%.1f%%)"),temp,*threshold,temp/(*threshold)*100);//threshold);
			//ratio.Format(_T("2000.0/2000 (100%%)"));
			int xxx=ratio.GetLength();
			memDC->TextOut(width/2-xxx*3,4,ratio);

			memDC->SetTextColor(textcolor);
			memDC->SetBkMode(bkmode);
			memDC->SelectObject(oldFont);
			memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);
		
			delete memDC;
		}
	}
	pDC -> RestoreDC( nSavedDC );
}

void CStatisticButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	ModifyStyle( 0 , BS_OWNERDRAW );

	initalized = FALSE;
////////////////////////////////////////////////
	smallFont.CreateFont(-11,0,0,0,FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, _T("Arial"));
	bigFont.CreateFont(-15,0,0,0,FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, _T("Arial"));

	red		= RGB(255,125,125);
	green	= RGB(125,255,125);
	cyan	= RGB(0,255,255);
	darkblue= RGB(0,0,75);
	darkgreen	= RGB(40,75,40);

	greenbrush.CreateSolidBrush(green);
	redbrush.CreateSolidBrush(red);

	GridPen.CreatePen(PS_SOLID ,1 , darkgreen);

	GetWindowRect(&TrafficDrawRectangle);
	ScreenToClient(&TrafficDrawRectangle);
	TGSize.cx = TrafficDrawRectangle.right - TrafficDrawRectangle.left;
	TGSize.cy = TrafficDrawRectangle.bottom - TrafficDrawRectangle.top;

	///////////////////////////////////////////////
	if(!isdu)
	{
		TrafficEntries = TGSize.cx / plotgranularity;
		TrafficStats = new float[TrafficEntries+1];
		for(DWORD x=0; x<TrafficEntries; x++)
			TrafficStats[x]	= 0.0;
	}

	CRgn rectRgn, ellRgn, finalRgn;
	rectRgn.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);
	ShapeWNDRegion.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);
	ShapeDCRegion.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);

	int x1,x2,y1,y2,xe,ye,xs,ys;
	int xof, yof;
	int r;
	xs = TGSize.cx;
	ys = TGSize.cy;
	x1 = 0;
	y1 = 0;
	x2 = xs;
	y2 = ys;
	xe = 5;//Radius of edge
	ye = 5;//Radius of edge
	if(isdu)xe=ye=xe*3;
	xof = (int)( (float)xs*0.0);
	yof = (int)( (float)ys*0.0);
	r = ellRgn.CreateRoundRectRgn(x1,y1,x2,y2,xe,ye);
	r = ellRgn.OffsetRgn(-xof, -yof);
	r = ShapeWNDRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );
	r = ShapeDCRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );

	this->SetWindowRgn((HRGN)ShapeWNDRegion, TRUE);
	initalized = TRUE;

	//if(!isdu)
		SetTimer(GRIDTIMER,	gridupdatespeed, 0);

	CButton::PreSubclassWindow();
}

bool CStatisticButton::Startup(char * dev)
{
	//rpcap://\Device\NPF_{1912EFCF-0397-4FE8-947D-301A7AFC1F30}
	if(isdu)
		return false;
	if(!dev)
	{
		AfxMessageBox(L"没有找到可用硬件！");
		return false;
	}

	//引用WinPcap技术文档
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct timeval st_ts;
	u_int netmask;
	struct bpf_program fcode;
	char packet_filter[] = "(not src net 202.204.96/20 and not src net 219.225.32/19 and not src net 121.194.80/20) or (not dst net 202.204.96/20 and not dst net 219.225.32/19 and not dst net 121.194.80/20)";

	/* Open the output adapter */
	if ( (fp= pcap_open(dev, 100, PCAP_OPENFLAG_NOCAPTURE_LOCAL, 1000, NULL, errbuf) ) == NULL)
    {
        AfxMessageBox(_T("打开设备出错！"));
        return false;
    }
	/* Don't care about netmask, it won't be used for this filter */
    netmask=0xffffff; 

    //compile the filter
    if (pcap_compile(fp, &fcode, packet_filter, 1, netmask) <0 )
    {
        AfxMessageBox(_T("无法编译过滤器！"));
		pcap_close(fp);       
		/* Free the device list */
        return false;
    }
    
    //set the filter
    if (pcap_setfilter(fp, &fcode)<0)
    {
        AfxMessageBox(_T("设置过滤器失败！"));
        pcap_close(fp);
        /* Free the device list */
        return false;
    }

	/* Put the interface in statstics mode */
    if (pcap_setmode(fp, MODE_STAT)<0)
    {
        AfxMessageBox(_T("设置统计模式失败！"));
        pcap_close(fp);
        /* Free the device list */
        return false;
    }

	pcap_loop(fp, 0, dispatcher_handler, (PUCHAR)&st_ts);

    pcap_close(fp);

	return true;
}

char * CStatisticButton::FindDevs(void)
{
	if(isdu)
		return NULL;
	pcap_if_t *alldevs;
    pcap_if_t *d;
	pcap_addr_t *a;

    char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL , &alldevs, errbuf) == -1)
    {
        AfxMessageBox(_T("查找硬件设备失败！"));
        return NULL;
    }
	for(d=alldevs;d;d=d->next)
	{
		for(a=d->addresses;a;a=a->next)
			if(a->addr->sa_family==AF_INET)
				if(((struct sockaddr_in *)a->addr)->sin_addr.S_un.S_addr)
					return d->name;
	}
	return NULL;
}

void CStatisticButton::isDu(void)
{
	isdu=true;
}
