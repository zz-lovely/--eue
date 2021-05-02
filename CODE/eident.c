/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "Init.h"
#include "math.h"
#include "stdlib.h"
#include "menu_2.h"
#include "eident.h"
#include "zf_adc.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	   ���ʶ��ģ��		*/
/*======================*/
void adc_jug(void){
//	��������
	short mid_sq;
	short mid_dif, out_dif;
	short oai_dif, oali_dif, oari_dif, lr_dif;
	static unsigned char ajug_sta_temp, count_sta, hold_jug, hold_jug_temp;
	static unsigned short jug_count;
//	��ֵ����
	mid_sq = adc0.value*adc0.value+adc4.value*adc4.value;
	mid_dif = adc1.value*adc1.value - adc3.value*adc3.value;
	out_dif = adc0.value*adc0.value - adc4.value*adc4.value;
	oai_dif = mid_sq - adc1.value*adc1.value - adc3.value*adc3.value;
	oali_dif = mid_sq - adc1.value*adc1.value;
	oari_dif = mid_sq - adc3.value*adc3.value;
	lr_dif = oali_dif - oari_dif;
//	Ԫ��ʶ��
	ajug_sta_temp = ajug_sta;
	ajug_sta = 0;
//	���뻷
	if(abs(lr_dif) > 4500)
		if(oari_dif > 13000)
			ajug_sta = 1;
//	״̬��
	if(ajug_sta != ajug_sta_temp){//������
		if(ajug_sta == 1) count_sta = 2, jug_count = 0;//Բ��
		else count_sta = 1, jug_count = 0;//�������
	}
	if(count_sta){
		switch(count_sta){
			case 1://�������
				if(ajug_sta == 0) jug_count++;
				else count_sta = 0;
				if(jug_count>1000) hold_jug_temp = hold_jug, hold_jug = 0, count_sta = 0;
				break;
			case 2:
				if(act_sta == 0){//��Բ��
					if(ajug_sta == 1) jug_count++;
					else count_sta = 0;
					if(jug_count>20) hold_jug_temp = hold_jug, hold_jug = 1, count_sta = 0;
				}
				else{//��Բ��
					if(ajug_sta == 1) jug_count++;
					else count_sta = 0;
					if(jug_count>30) hold_jug_temp = hold_jug, hold_jug = 2, count_sta = 0;
				}
				break;
		}
	}
//	״̬����
	if(hold_jug != hold_jug_temp){
		if(hold_jug_temp==0)
			if(hold_jug==1)//��Բ��
				act_sta = 1;
		if(hold_jug_temp==0)//��Բ��
			if(hold_jug==2)
				act_sta = 2;
		if(hold_jug_temp==2)
			if(hold_jug==0)
				act_sta = 0;
	}
//	adc_pfc[1]();
}
/*----------------------*/
/*	   	 ʮ��ֱ��		*/
/*======================*/
void cross_road(void){
	uart_putchar(UART_7, 0);
	spd_bias = 5;
}
/*----------------------*/
/*	   ��ȺͲ��㷨		*/
/*======================*/
void adc_suminus(void){
//	��������
	float divd, divs;
	short mid_val;
//	��ȺͲ��㷨
	mid_val = adc1.value - adc3.value;
	divd = adc_err.alpha*(float)(adc0.value - adc4.value) + adc_err.beta*(float)mid_val;
	divs = adc_err.alpha*(float)(adc0.value+adc4.value) + adc_err.omega*abs((float)mid_val);
	adc_err.rs = adc_err.P*divd/divs;
	switch(act_sta){
		case 0:
			rad_bias = 0;
			break;
		case 1:
			rad_bias = 15;
			break;
		case 2:
			rad_bias = -7;
			break;
	}
//	if(adc_err.rs < 0) adc_err.rs = adc_err.rs*1.14;//���Ҽ�Ȩ
//	PID���㡢���ݷ���
//	adc_steering.Kp = 1.36+(adc_err.rs*adc_err.rs)/(float)Kp_act;//��̬P
	pos_pid(&adc_steering, 0, -adc_err.rs, 100, -100);
//	spd_bias = -abs(adc_steering.rs)>>3;//�������
//	���ݼ���
//	if(csimenu_flag[1]){
//		ips200_showint16(0, 0, adc0.value);
//		ips200_showint16(0, 1, adc1.value);
//		ips200_showint16(0, 2, adc2.value);
//		ips200_showint16(0, 3, adc3.value);
//		ips200_showint16(0, 4, adc4.value);
//		ips200_showint16(0, 5, adc_convert(ADC_MOD1, ADC_PIN0));
//		ips200_showint16(0, 6, adc_convert(ADC_MOD1, ADC_PIN1));
//		ips200_showint16(0, 7, adc_convert(ADC_MOD1, ADC_PIN2));
//		ips200_showint16(0, 8, adc_convert(ADC_MOD1, ADC_PIN3));
//		ips200_showint16(0, 9, adc_convert(ADC_MOD1, ADC_PIN4));
//		ips200_showstr(100, 0, "divd");
//		ips200_showfloat(160, 0, divd, 4, 4);
//		ips200_showstr(100, 1, "divs");
//		ips200_showfloat(160, 1, divs, 4, 4);
//		ips200_showstr(100, 2, "rs");
//		ips200_showfloat(160, 2, adc_err.rs, 4, 3);
//		ips200_showstr(100, 3, "pid");
//		ips200_showfloat(160, 3, adc_steering.rs, 4, 3);
//		ips200_showstr(100, 4, "a1");
//		ips200_showfloat(160, 4, adc_err.alpha*(float)(adc0.value-adc4.value), 4, 4);
//		ips200_showstr(100, 5, "b");
//		ips200_showfloat(160, 5, adc_err.beta*(float)mid_val, 4, 4);
//		ips200_showstr(100, 6, "a2");
//		ips200_showfloat(160, 6, adc_err.alpha*(float)(adc0.value+adc4.value), 4, 4);
//		ips200_showstr(100, 7, "c");
//		ips200_showfloat(160, 7, adc_err.omega*abs((float)mid_val), 4, 4);
//	}
}
/*----------------------*/
/*	    ��ͨ���˲�		*/
/*======================*/
void single_ch_filter(struct adcpara *para){
//	��������
	unsigned char i;
	register unsigned char j;
	unsigned short value[3];
	unsigned int sum_val = 0;
	unsigned char max_val, min_val;
//	��ֵ��ֵ�˲�
	for(i = 0; i < SAMPFRE; i++){
		//	����
			max_val = 0, min_val = 0;
		//	�ɼ���������
			for(j = 0; j < 3; j++)
				value[j] = adc_convert(ADC_MOD1, para->pin);
		//	�ж�����ֵ�Ƿ����
			if(value[0] == value[1])
				if(value[1] == value[2]){sum_val+= value[0];continue;}
		//	����ֵ
			for(j = 1; j < 3; j++){
				if(value[max_val] < value[j]) max_val = j;
				if(value[min_val] > value[j]) min_val = j;
			}
			sum_val += value[3-max_val-min_val];
		}
		para->value = (sum_val / SAMPFRE);
	//	�޷�
		if(para->value > para->max) para->value = para->max;
		if(para->value < para->min) para->value = para->min;
	//	��һ��
		para->value = 100*(para->value-para->min)/(para->max-para->min);
}
/*----------------------*/
/*	     �����ֵ		*/
/*======================*/
void adc_extreme(struct adcpara *para){
//	��������
	unsigned short adc_colltemp;
//	ADC�ɼ�����ֵ�Ƚ�
	adc_colltemp = adc_convert(ADC_MOD1, para->pin);
	if(para->max < adc_colltemp) para->max = adc_colltemp;
	if(para->min > adc_colltemp) para->min = adc_colltemp;
//	ˢ�¸�����ֵ
	ips200_pencolor = 0xFFFF;
	ips200_bgcolor = 0xB6DB;
	menu2value_hl();
	ips200_pencolor = 0xB6DB;
	ips200_bgcolor = 0xFFFF;
}
