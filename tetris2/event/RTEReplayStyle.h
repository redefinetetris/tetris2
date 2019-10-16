#ifndef __RTEREPLAYSTYLE_H__
#define __RTEREPLAYSTYLE_H__


typedef enum _RTEReplayStyle
{
	RTERS_Unknown               = 0X00000000,

	RTERS_Init                  = 0X00000001,
	RTERS_Query                 = 0X00000002,
	RTERS_Backward              = 0X00000004,
	RTERS_Forward               = 0X00000008,

	RTERS_Error                 = 0X20000000,
	RTERS_NotFind               = 0X40000000,
	RTERS_OutMemory             = 0X80000000,
}RTEReplayStyle_t;


#endif//__RTEREPLAYSTYLE_H__

