#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
#include "SEEKFREE_MT9V03X.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
//	������־λ
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
//	һ���˵�
#define ROWS 4
#define menu_limit0 0
#define menu_limit1 2
#define menu_limit2 0
#define menu_limit3 1
//	����ͷ
#define EFF_ROW 54
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	����ͷģ��		*/
/*======================*/
extern unsigned char cjug_sta;
//	ͼ��ver2
extern unsigned char lefbor[EFF_ROW+1], rigbor[EFF_ROW+1], mid_point[EFF_ROW+1];
extern unsigned char lefp, rigp, midp;
extern unsigned short imgthrsod;
extern float lefslope, rigslope, midslope;
//	ver3
extern float P[256], PK[256], MK[256];
extern unsigned char gray_img[MT9V03X_H][MT9V03X_W];
extern unsigned char img_thrsod;
/*----------------------*/
/*	 	 ���ģ��		*/
/*======================*/
//	�ṹ������
typedef struct adcpara{//��Ż�������
	unsigned short value;
	unsigned short max;
	unsigned short min;
	unsigned short pin;
}adcpara;
typedef struct adcerrpa{//��ȺͲ����
	float alpha, beta, omega;
	float P;
	short rs;
}adcerrpa;
//	ȫ�ֽṹ������
extern struct adcpara adc0;
extern struct adcpara adc1;
extern struct adcpara adc2;
extern struct adcpara adc3;
extern struct adcpara adc4;
extern struct adcerrpa adc_err;
//	״̬��־λ
extern unsigned char ajug_sta;
//	ָ�뺯��
extern void(*adc_pfc[])(void);
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	���
extern unsigned short Kp_act;
extern unsigned char act_sta;
extern short spd, spd_bias;
extern short spd_adcset;
extern short rad;
extern char rad_bias;
/*----------------------*/
/*	 	  PIDģ��		*/
/*======================*/
//	�ṹ������
typedef struct pidpara{
	float alpha;
	float Kp;
	float Ki;
	float Kd;
	float I;
	int e1;
	int e2;
	int e3;
	short rs;
}pidpara;
extern struct pidpara adc_steering;
extern struct pidpara adc_straight;
extern struct pidpara cam_steering;
/*----------------------*/
/*	 	 ������ȥ		*/
/*======================*/
extern unsigned char subuff_num;
extern unsigned char subuff_arr[3];
extern unsigned short subuff_ranging;
/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	һ���˵�
extern unsigned char menu_index;
extern unsigned char menu[ROWS];
extern unsigned char nom[128];
//	��־λ
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];
extern unsigned char excollflag;
extern unsigned char menu_level;
//	�����˵�
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	����ָ��
extern void(*menu_pfc[])(unsigned char);
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);

#endif
