#ifndef __RTESTYLE_H__
#define __RTESTYLE_H__


typedef enum _RTEStyle
{
	RTES_Unknown                = 0X00000000,

	RTES_Game                   = 0X00000001,
	RTES_Session                = 0X00000002,
	RTES_Root                   = 0X00000004,
	RTES_Trail                  = 0X00000008,
	RTES_DB                     = 0X00000010,
	RTES_Clock                  = 0X00000020,
	RTES_Event                  = 0X00000040,
	RTES_Hub                    = 0X00000080,
	RTES_User                   = 0X00000100,
	RTES_Replay                 = 0X00000200,

	RTES_ReplayMode             = 0X80000000,
}RTEStyle_t;


#endif//__RTESTYLE_H__

