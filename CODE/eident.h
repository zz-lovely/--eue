/*------------------------------------------------------*/ 
/* 					   ͷ�ļ����� 						*/
/*======================================================*/
#ifndef _EIDENT_H
#define _EIDENT_H
//	����ͷ�ļ�
#include "data.h"
/*------------------------------------------------------*/ 
/* 						 �궨�� 						*/
/*======================================================*/
#define SAMPFRE 10
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void eident_init(void);
void adc_jug(void);
void cross_road(void);
void single_ch_filter(struct adcpara *para);
void adc_extreme(struct adcpara *para);
void adc_suminus(void);
#endif
