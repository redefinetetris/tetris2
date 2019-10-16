#ifndef __RTEROOTSTYLE_H__
#define __RTEROOTSTYLE_H__


typedef enum _RTERootStyle
{
	RTERS_Unknown               = 0X00000000,

	RTERS_NewSession            = 0X00000001,
	RTERS_DeleteSession         = 0X00000002,
	RTERS_Query                 = 0X00000004,
	RTERS_Health                = 0X00000008,

	RTERS_NotFind               = 0X04000000,
	RTERS_BadToken              = 0X08000000,
	RTERS_OK                    = 0X10000000,
	RTERS_Bad                   = 0X20000000,
	RTERS_OutMemory             = 0X40000000,

	RTERS_ReplayMode            = 0X80000000,
}RTERootStyle_t;


#endif//__RTEROOTSTYLE_H__

