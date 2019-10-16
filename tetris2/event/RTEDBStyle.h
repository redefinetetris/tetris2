#ifndef __RTEDBSTYLE_H__
#define __RTEDBSTYLE_H__


typedef enum _RTEDBStyle
{
	RTEDBS_Unknown              = 0X00000000,

	RTEDBS_Timer                = 0X00000001,
	RTEDBS_Fire                 = 0X00000002,
	RTEDBS_Flush                = 0X00000004,
	RTEDBS_DownTTL              = 0X00000008,
	RTEDBS_WashTTL              = 0X00000010,
}RTEDBStyle_t;


#endif//__RTEDBSTYLE_H__

