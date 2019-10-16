#ifndef __RTHEALTHSTYLE_H__
#define __RTHEALTHSTYLE_H__


typedef enum _RTHealthStyle
{
	RTHS_Death                  = 0X00000000,
	RTHS_Zombie                 = 0X00000001,
	RTHS_Debug                  = 0X00000002,
	RTHS_Run                    = 0X00000004,
	RTHS_Replay                 = 0X00000008,
	RTHS_HungUp                 = 0X00000010,

	RTHS_DoMail					= RTHS_Debug | RTHS_Run | RTHS_Replay,
	
	RTHS_EnableAll              = 0XFFFFFFFF,
}RTHealthStyle_t;


#endif

