#define WM_UPDATEINFO WM_USER+200

#define PLOTGRANULATRITY 2		// Defines the width of the rectangle representing a bar in the diagram

#define NETUPDATESPEED	1000	// Value for the statistics timer
#define GRIDUPDATESPEED 50		// Value vor the grid timer
#define GRIDTIMER		1		// ID for the grid timer
#define NETTIMER		2		// ID for the statistics timer

#define GRIDXRESOLUTION	10		// Distance for grid in x direction
#define GRIDYRESOLUTION	10		// Distance for grid in y direction
#define GRIDSCROLLXSPEED -1		// How fast grid scrolls in x direction
#define GRIDSCROLLYSPEED 0		// How fast grid scrolls in y direction

UINT Connect(LPVOID pvParam);
UINT DisConnect(LPVOID pvParam);
void Change(CString *str);