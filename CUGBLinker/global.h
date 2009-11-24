#pragma once

#define WM_UPDATEINFO WM_USER+200
#define WM_UPDATENOTIFY WM_USER+201

#define BALLOON_ERROR NIIF_ERROR
#define BALLOON_INFO NIIF_INFO
#define BALLOON_WARNING NIIF_WARNING

#define PLOTGRANULATRITY 2		// Defines the width of the rectangle representing a bar in the diagram

#define NETUPDATESPEED	1000	// Value for the statistics timer
#define GRIDUPDATESPEED 50		// Value vor the grid timer
#define GRIDTIMER		1		// ID for the grid timer
#define NETTIMER		2		// ID for the statistics timer

#define GRIDXRESOLUTION	10		// Distance for grid in x direction
#define GRIDYRESOLUTION	10		// Distance for grid in y direction
#define GRIDSCROLLXSPEED -1		// How fast grid scrolls in x direction
#define GRIDSCROLLYSPEED 0		// How fast grid scrolls in y direction

#define FILTER "net 192.168"

extern double curSpeed;
extern double maxSpeed;
extern float* TrafficStats;
extern DWORD TrafficEntries;

UINT Connect(LPVOID pvParam);
UINT DisConnect(LPVOID pvParam);
void Change(CString *str);

pcap_if_t* finddevs();
char* iptos(u_long in);
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);
void dispatcher_handler(u_char *state, const struct pcap_pkthdr *header, const u_char *pkt_data);
UINT statistic_traffic(LPVOID pvParam);