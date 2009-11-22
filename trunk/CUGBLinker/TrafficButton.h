#pragma once

#include "afxwin.h"
#include "global.h"

class CTrafficButton :
	public CButton
{
public:
	CTrafficButton(void);

public:
	virtual ~CTrafficButton(void);

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
};
