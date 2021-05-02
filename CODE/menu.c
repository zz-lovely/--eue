/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "menu.h"
#include "Init.h"
#include "eident.h"
#include "menu_2.h"
#include "string.h"
#include "zf_gpio.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

//----------------------------�ָ���----------------------------//
/*--------------------------------------------------------------*/
/* 							 һ���˵� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 �˵���Ϣ�洢ģ��		*/
/*==============================*/
static char info(char index, char num){
//	��������
	register unsigned char i;
//	��ģ
	unsigned char cai0[] = {0x00,0x00,0x00,0x20,0x08,0x20,0x7F,0xFE,0x00,0x20,0x00,0x78,0x3F,0x88,0x11,0x08,0x08,0x90,0x09,0x20,0x7F,0xFE,0x01,0x80,0x03,0x40,0x0D,0x30,0x31,0x0C,0x40,0x02};/*"��"*/
	unsigned char dan0[] = {0x00,0x00,0x00,0x10,0x08,0x10,0x04,0x20,0x3F,0xF8,0x21,0x04,0x21,0x04,0x3F,0xFC,0x21,0x04,0x21,0x04,0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x01,0x00,0x01,0x00,0x01,0x00};/*"��"*/
	unsigned char zhuan0[] = {0x00,0x00,0x00,0x20,0x10,0x20,0x7E,0x20,0x21,0xFE,0x20,0x40,0x40,0x40,0x51,0xFE,0x50,0x40,0x7C,0x40,0x10,0x7E,0x10,0x04,0x3C,0x04,0x10,0x08,0x10,0x70,0x00,0x0E};/*"ת"*/
	unsigned char xiang0[] = {0x00,0x00,0x01,0x00,0x01,0x00,0x1F,0xF8,0x20,0x06,0x20,0x02,0x27,0xE2,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x27,0xE2,0x20,0x02,0x20,0x1C};/*"��"*/
	unsigned char dian0[] = {0x00,0x00,0x01,0x00,0x01,0x00,0x1F,0xF0,0x61,0x0C,0x41,0x04,0x41,0x04,0x7F,0xFC,0x41,0x04,0x41,0x04,0x41,0x04,0x7F,0xFC,0x01,0x00,0x01,0x02,0x01,0x02,0x01,0xFC};/*"��"*/
	unsigned char ci0[] = {0x00,0x00,0x00,0x00,0x00,0x88,0x7F,0xFE,0x20,0x88,0x20,0x88,0x21,0x28,0x39,0x4A,0x69,0x52,0xAA,0x54,0x2B,0x8C,0x28,0x8C,0x29,0x4A,0x29,0x4A,0x2A,0xD6,0x13,0x5A};/*"��"*/
	unsigned char she0[] = {0x00,0x00,0x00,0x00,0x20,0xF8,0x30,0x88,0x10,0x88,0x01,0x08,0x71,0x0A,0x10,0x04,0x11,0xFC,0x10,0x84,0x10,0x88,0x10,0x48,0x10,0x50,0x14,0x30,0x18,0xC8,0x03,0x06};/*"��"*/
	unsigned char zhi0[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x44,0x44,0x44,0x44,0x3B,0xB8,0x7F,0xFE,0x01,0x00,0x1F,0xF8,0x10,0x08,0x1F,0xF8,0x10,0x08,0x1F,0xF8,0x1F,0xF8,0x10,0x08,0xFF,0xFF};/*"��"*/	
	unsigned char jian0[] = {0x00,0x00,0x00,0x00,0x04,0x80,0x24,0xFE,0x24,0x80,0x25,0x00,0x25,0x20,0x26,0x10,0x04,0x08,0x00,0x00,0x3F,0xFC,0x24,0x44,0x24,0x44,0x24,0x44,0x24,0x44,0x7F,0xFE};/*"��"*/
	unsigned char shi0[] = {0x00,0x00,0x00,0x00,0x11,0xFC,0x11,0x04,0x79,0x24,0x09,0x24,0x09,0x24,0x11,0x24,0x19,0x24,0x35,0x34,0x51,0x30,0x10,0x50,0x10,0x50,0x10,0x92,0x11,0x12,0x16,0x1E};/*"��"*/
	unsigned char qi0[] = {0x00,0x00,0x00,0x00,0x3E,0x7C,0x22,0x84,0x22,0x84,0x3E,0x7C,0x01,0x10,0x7F,0xFE,0x04,0x40,0x08,0x30,0x70,0x0E,0x3E,0x7C,0x22,0x84,0x22,0x84,0x22,0x84,0x3E,0x7C};/*"��"*/
	unsigned char zi0[] = {0x00,0x00,0x00,0x00,0x62,0x00,0x13,0xFC,0x04,0x84,0x08,0xC8,0x0D,0x20,0x33,0x10,0x4D,0x0E,0x01,0x00,0x7F,0xFE,0x04,0x20,0x08,0x20,0x07,0x40,0x01,0xF0,0x7E,0x0E};/*"��"*/
	unsigned char tai0[] = {0x00,0x00,0x00,0x00,0x01,0x00,0x7F,0xFE,0x01,0x80,0x02,0x40,0x05,0x20,0x19,0x18,0xE0,0x86,0x00,0x00,0x24,0x88,0x24,0x84,0x24,0x54,0x24,0x52,0x44,0x12,0x47,0xF0};/*"̬"*/
	unsigned char tu0[] = {0x00,0x00,0x00,0x00,0x3F,0xFE,0x44,0x02,0x47,0xF2,0x4C,0x22,0x53,0x62,0x40,0x82,0x43,0x62,0x5E,0x1A,0x41,0x82,0x40,0x62,0x43,0x02,0x40,0xC2,0x40,0x22,0x3F,0xFC};/*"ͼ"*/
	unsigned char xiang1[] = {0x00,0x00,0x10,0x80,0x11,0xF0,0x1E,0x10,0x23,0xF8,0x2C,0x46,0x28,0x42,0x67,0xFA,0x60,0x84,0x23,0x46,0x2C,0xB8,0x23,0x20,0x2C,0xF0,0x23,0x28,0x2C,0x26,0x23,0x40};/*"��"*/
	unsigned char xian0[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x20,0x04,0x20,0x04,0x3F,0xFC,0x20,0x04,0x20,0x04,0x1F,0xF8,0x24,0x44,0x14,0x48,0x14,0x48,0x14,0x48,0x0C,0x50,0x04,0x40,0x7F,0xFE};/*"��"*/
	unsigned char shi1[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x00,0x80,0x08,0x90,0x08,0x88,0x10,0x88,0x10,0x84,0x20,0x84,0x20,0x82,0x40,0x82,0x07,0x80};/*"ʾ"*/
	unsigned char wu0[] = {0x00,0x00,0x00,0x00,0x63,0xFC,0x12,0x04,0x02,0x04,0x02,0x04,0xE3,0xFC,0x20,0x00,0x23,0xFE,0x20,0x40,0x20,0x40,0x27,0xFE,0x20,0x60,0x28,0x90,0x31,0x0C,0x06,0x02};/*"��"*/
	unsigned char cha0[] = {0x00,0x00,0x08,0x10,0x04,0x10,0x04,0x20,0x7F,0xFE,0x01,0x00,0x3F,0xFC,0x02,0x00,0x02,0x00,0x7F,0xFE,0x04,0x00,0x07,0xFC,0x18,0x40,0x60,0x40,0x00,0x40,0x1F,0xFE};/*"��"*/
	unsigned char bi0[] = {0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x80,0x20,0x84,0x20,0x88,0x3E,0x90,0x20,0x60,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x81,0x20,0x81,0x20,0x82,0x26,0x82,0x18,0x7E};/*"��"*/
	unsigned char he0[] = {0x00,0x00,0x00,0x00,0x3E,0x00,0x08,0x7E,0x08,0x82,0x08,0x82,0x7F,0x82,0x08,0x82,0x1C,0x82,0x2A,0x82,0x29,0x82,0x48,0x82,0x08,0x82,0x08,0x82,0x08,0x7E,0x08,0x00};/*"��"*/
//	������
	switch(index){
		case 0:
		//	������
			switch(num){
			//	�����߼�
				case 0://ͼ����ʾ
					for(i = 0; i < 32; i++) nom[i] = tu0[i];
					for(i = 0; i < 32; i++) nom[32+i] = xiang1[i];
					for(i = 0; i < 32; i++) nom[64+i] = xian0[i];
					for(i = 0; i < 32; i++) nom[96+i] = shi1[i];
					return 4;
			}
			break;
		case 1:
			switch(num){
			//	�����޸��߼�
				case 0://�������
					for(i = 0; i < 32; i++) nom[i] = dian0[i];
					for(i = 0; i < 32; i++) nom[32+i] = ci0[i];
					for(i = 0; i < 32; i++) nom[64+i] = she0[i];
					for(i = 0; i < 32; i++) nom[96+i] = zhi0[i];
					return 4;
				case 1://ת��
					for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
					return 2;
				case 2://��ȺͲ�
					for(i = 0; i < 32; i++) nom[i] = cha0[i];
					for(i = 0; i < 32; i++) nom[32+i] = bi0[i];
					for(i = 0; i < 32; i++) nom[64+i] = he0[i];
					for(i = 0; i < 32; i++) nom[96+i] = cha0[i];
					return 4;
			}
			break;
		case 2:
			switch(num){
			//	��̬�޸��߼�
				case 0:
					for(i = 0; i < 32; i++) nom[i] = zi0[i];
					for(i = 0; i < 32; i++) nom[32+i] = tai0[i];
					return 2;
			}
			break;
		case 3:
			switch(num){
			//	�������߼�
				case 0://������
					for(i = 0; i < 32; i++) nom[i] = wu0[i];
					for(i = 0; i < 32; i++) nom[32+i] = cha0[i];
					for(i = 0; i < 32; i++) nom[64+i] = jian0[i];
					for(i = 0; i < 32; i++) nom[96+i] = shi0[i];
					return 4;
				case 1://��ż���
					for(i = 0; i < 32; i++) nom[i] = dian0[i];
					for(i = 0; i < 32; i++) nom[32+i] = ci0[i];
					for(i = 0; i < 32; i++) nom[64+i] = jian0[i];
					for(i = 0; i < 32; i++) nom[96+i] = shi0[i];
					return 4;
			}
			break; 
		case 100://�˵�
			for(i = 0; i < 32; i++) nom[i] = cai0[i];
			for(i = 0; i < 32; i++) nom[32+i] = dan0[i];
			return 2;
	}
	return 0;
}
/*------------------------------*/
/*		   �˵���ʾģ��			*/
/*==============================*/
void menu_display(void){
//	��������
	char show_index[ROWS];
//	����
	ips200_clear(WHITE);
//	������ʾ����
	if(menu_index-1<0) show_index[0] = ROWS-1;
	else show_index[0] = menu_index - 1;

	show_index[1] = menu_index;

	if(menu_index+1>ROWS-1) show_index[2] = 0,show_index[3] = 1;
	else if(menu_index+2>ROWS-1) show_index[2] = menu_index+1,show_index[3] = 0;
	else show_index[2] = menu_index+1,show_index[3] = menu_index+2;
//	�˵���ʾ
	ips200_display_chinese(0, 208, 16, nom, info(100, menu[show_index[0]]), 0XFDF8);
	ips200_display_chinese(14, 224, 16, nom, info(show_index[0], menu[show_index[0]]), 0xB6DB);
	
	ips200_display_chinese(20, 256, 16, nom, info(show_index[1], menu[show_index[1]]), 0xB6DB);
	
	ips200_display_chinese(10, 288, 16, nom, info(show_index[2], menu[show_index[2]]), 0xB6DB);
	ips200_display_chinese(0, 304, 16, nom, info(show_index[3], menu[show_index[3]]), 0xB6DB);
}
/*------------------------------*/
/*		 �˵���ֵ����ģ��		*/
/*==============================*/
static char menu_limit(char index, char num){
//	����������ֵ
	switch(index){
		case 0:if(num<menu_limit0) return 1;break;
		case 1:if(num<menu_limit1) return 1;break;
		case 2:if(num<menu_limit2) return 1;break;
		case 3:if(num<menu_limit3) return 1;break;
	}
	return 0;
}
/*------------------------------*/
/*		 һ���˵��¼�ģ��		*/
/*==============================*/
void menu_select(unsigned char event){
//	һ���˵�
	if(!menu_level){
	//	�˵��¼���֧
		switch(event){
			case 6://�Ұ���
				if(menu_limit(menu_index, menu[menu_index])) menu[menu_index]++;
				else return;
				break;
			
			case 4://�󰴼�
				if(menu[menu_index] > 0) menu[menu_index]--;
				else return;
				break;
			
			case 2://�ϰ���
				if(menu_index>0) menu_index--;
				else menu_index = ROWS-1;
				break;
			
			case 5://�°���
				if(menu_index<ROWS-1) menu_index++;
				else menu_index = 0;
				break;
			
			case 1://ȷ����
			//	��ʼ�������˵�
				menu2_init();
				menu2_display();
				menu_level = 1;
				return;
			case 3:break;
		}
		menu_display();
	}
}