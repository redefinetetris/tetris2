#ifndef __RTVALUESTYLE_H__
#define __RTVALUESTYLE_H__


//���������ʱ��Ҫ�޸�CRTValue�ࡢRTNSKeep�����ռ�
typedef enum _RTValueStyle
{
	RTVS_unknown = 0,

	RTVS_int,
	RTVS_unsigned_int,
	RTVS_double,
	RTVS_string,
	RTVS_dict,
	RTVS_vector_int,
	RTVS_vector_unsigned_int,
	RTVS_vector_double,
	RTVS_vector_string,
	RTVS_vector_dict,
}RTValueStyle_t;


#endif

