#ifndef __RTEGAMESTYLE_H__
#define __RTEGAMESTYLE_H__


typedef enum _RTEGameStyle
{
	RTEGS_EnableAll             = 0XFFFFFFFF,
	RTEGS_DisableAll            = 0X00000000,

	RTEGS_New                   = 0X00000001,
	RTEGS_Delete                = 0X00000002,
	RTEGS_Doctor                = 0X00000004,
	RTEGS_Move                  = 0X00000008,
	RTEGS_Transfer              = 0X00000010,
	RTEGS_Hit                   = 0X00000020,
	RTEGS_Freeze                = 0X00000040,
	RTEGS_Target                = 0X00000080,
	RTEGS_Coin                  = 0X00000100,
	RTEGS_Remove                = 0X00000200,
	RTEGS_Watch                 = 0X00000400,
	RTEGS_Over                  = 0X00000800,
	RTEGS_Timer                 = 0X00001000,
	RTEGS_Health                = 0X00002000,
	RTEGS_Hole                  = 0X00004000,

	RTEGS_Unknown               = 0X08000000,
	RTEGS_OK                    = 0X10000000,
	RTEGS_Bad                   = 0X20000000,
	RTEGS_OutMemory             = 0X40000000,

	RTEGS_ReplayMode            = 0X80000000,

	RTEGS_4_Area                = RTEGS_Over | RTEGS_Watch | RTEGS_Coin | RTEGS_Doctor,
	RTEGS_4_Target              = RTEGS_Over | RTEGS_Watch | RTEGS_Coin | RTEGS_Doctor | RTEGS_Remove,
	RTEGS_4_Doctor              = RTEGS_Over | RTEGS_Watch | RTEGS_Coin | RTEGS_Move | RTEGS_Transfer | RTEGS_Hit | RTEGS_Freeze | RTEGS_Target | RTEGS_Remove,
}RTEGameStyle_t;


#endif//__RTEGAMESTYLE_H__

