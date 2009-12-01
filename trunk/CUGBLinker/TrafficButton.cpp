#include "StdAfx.h"
#include "TrafficButton.h"
#include "MyDC.h"
#include "global.h"
#include <pcap.h>


CTrafficButton::CTrafficButton(void)
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

CTrafficButton::~CTrafficButton(void)
{
}
BEGIN_MESSAGE_MAP(CTrafficButton, CButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CTrafficButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);
	CButton::OnTimer(nIDEvent);
}

void CTrafficButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
		delete memDC;
	}
	if(initalized == TRUE)
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

		double scale = TGSize.cy / (maxSpeed/1024.0);

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
		CString traffic;
		traffic.Format(L"CUR: %.2f  HHG: %.2f",curSpeed/1024.0,maxSpeed/1024.0);
		memDC->TextOut(5,5,traffic); 

		memDC->SetTextColor(textcolor);
		memDC->SetBkMode(bkmode);
		memDC->SelectObject(oldFont);
		memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);

		delete memDC;

	}
	pDC -> RestoreDC( nSavedDC );
}

void CTrafficButton::PreSubclassWindow()
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

	TrafficEntries = TGSize.cx / plotgranularity;
	TrafficStats = new float[TrafficEntries+1];
	for(DWORD x=0; x<=TrafficEntries; x++)
		TrafficStats[x]	= 0.0;

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

	xof = (int)( (float)xs*0.0);
	yof = (int)( (float)ys*0.0);
	r = ellRgn.CreateRoundRectRgn(x1,y1,x2,y2,xe,ye);
	r = ellRgn.OffsetRgn(-xof, -yof);
	r = ShapeWNDRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );
	r = ShapeDCRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );

	this->SetWindowRgn((HRGN)ShapeWNDRegion, TRUE);
	initalized = TRUE;

	SetTimer(GRIDTIMER,	gridupdatespeed, 0);

	CButton::PreSubclassWindow();
}