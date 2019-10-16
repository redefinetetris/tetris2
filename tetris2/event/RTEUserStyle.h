#ifndef __RTEUSERSTYLE_H__
#define __RTEUSERSTYLE_H__


typedef enum _RTEUserStyle
{
	RTEUS_Unknown               = 0X00000000,

	RTEUS_Login                 = 0X00000001,
	RTEUS_Logout                = 0X00000002,
	RTEUS_Regin                 = 0X00000004,
	RTEUS_Regout                = 0X00000008,

	RTEUS_Logined               = 0X04000000,
	RTEUS_Regined               = 0X08000000,
	RTEUS_OutMemory             = 0X10000000,
	RTEUS_NotFind               = 0X20000000,
	RTEUS_OK                    = 0X40000000,
	RTEUS_Bad                   = 0X80000000,
}RTEUserStyle_t;


#endif//__RTEUSERSTYLE_H__

