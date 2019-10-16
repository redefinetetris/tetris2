#ifndef __RTECLOCKSTYLE_H__
#define __RTECLOCKSTYLE_H__


typedef enum _RTEClockStyle
{
	RTECS_Unknown               = 0X00000000,

	RTECS_Update                = 0X00000001,
	RTECS_New                   = 0X00000002,
	RTECS_Delete                = 0X00000004,
	RTECS_Query                 = 0X00000008,
	RTECS_Health                = 0X00000010,

	RTECS_NotFind               = 0X20000000,
	RTECS_OK                    = 0X40000000,
	RTECS_Bad                   = 0X80000000,
}RTEClockStyle_t;


#endif//__RTECLOCKSTYLE_H__

