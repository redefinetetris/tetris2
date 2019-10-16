#ifndef __RTDBOBJECTSTYLE_H__
#define __RTDBOBJECTSTYLE_H__


typedef enum _RTDBObjectStyle
{
	RTDBOS_Unknown              = 0X00000000,

	RTDBOS_Post                 = 0X00000001,
	RTDBOS_Put                  = 0X00000002,
	RTDBOS_Delete               = 0X00000004,
	RTDBOS_Get                  = 0X00000008,
}RTDBObjectStyle_t;


#define MAX_LENGTH_PER_LINE (2048)


#endif//__RTDBOBJECTSTYLE_H__

