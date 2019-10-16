#ifndef __RTETRAILSTYLE_H__
#define __RTETRAILSTYLE_H__


typedef enum _RTETrailStyle
{
	RTETS_Unknown               = 0X00000000,

	RTETS_NewRoot               = 0X00000001,
	RTETS_DeleteRoot            = 0X00000002,
	RTETS_Query                 = 0X00000004,

	RTETS_OutMemory             = 0X80000000,
}RTETrailStyle_t;


#endif//__RTETRAILSTYLE_H__

