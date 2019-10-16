#ifndef __RTESESSIONSTYLE_H__
#define __RTESESSIONSTYLE_H__


typedef enum _RTESessionStyle
{
	RTESS_Unknown               = 0X00000000,

	RTESS_NewGame               = 0X00000001,
	RTESS_DeleteGame            = 0X00000002,
	RTESS_Timer                 = 0X00000004,
	RTESS_Jump                  = 0X00000008,
	RTESS_Move                  = 0X00000010,
	RTESS_Race                  = 0X00000020,
	RTESS_Fire                  = 0X00000040,
	RTESS_Win                   = 0X00000080,
	RTESS_Over                  = 0X00000100,
	RTESS_Health                = 0X00000200,
	RTESS_Toll                  = 0X00000400,

	RTESS_NotFind               = 0X04000000,
	RTESS_BadToken              = 0X08000000,
	RTESS_OK                    = 0X10000000,
	RTESS_Bad                   = 0X20000000,
	RTESS_OutMemory             = 0X40000000,

	RTESS_ReplayMode            = 0X80000000,
}RTESessionStyle_t;


#endif//__RTESESSIONSTYLE_H__

