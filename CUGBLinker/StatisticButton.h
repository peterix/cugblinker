#pragma once

/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/
//����Ϊ�����������Լ��Դ��������޸�
#include "afxwin.h"
#include "global.h"

class CStatisticButton :
	public CButton
{
public:
	CStatisticButton(void);
	CStatisticButton(bool du);

public:
	virtual ~CStatisticButton(void);

public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	virtual void PreSubclassWindow();


public:
	enum traffictype
	{
		Traffic_Total		= 0,
		Traffic_Incoming	= 1,
		Traffic_Outgoing	= 2
	};

	CFont	smallFont,bigFont;
	CBrush	colorbrush,backbrush;

	COLORREF red, green, back, cyan, darkblue, darkgreen;
	CPen	GridPen;
	CSize	TGSize;

	CBrush	greenbrush;
	CBrush	redbrush;
	CPoint	orgBrushOrigin; 

	RECT	TrafficDrawRectangle;

	BOOL	initalized;
	BOOL	brushInitalized;

	CRgn	ShapeWNDRegion;
	CRgn	ShapeDCRegion;

	int gridxstartpos;		
	int gridystartpos;
	int plotgranularity;

public:
	int gridxresolution;		// The size of grid raster
	int gridyresolution;
	int gridscrollxspeed;		// Scroll speed of the grid
	int gridscrollyspeed; 
	int netupdatespeed;			// Should be set via SetUpdateSpeet method
	int gridupdatespeed;

public:
	bool Startup(char * dev);
public:
	char * FindDevs(void);
public:
	void isDu(void);
public:
	bool isdu;
};
