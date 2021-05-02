/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "CAM.h"
#include "pid.h"
#include "data.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"

int imageLeft[MT9V03X_H]={0};//存每行左基点坐标 初始化为0
int imageRight[MT9V03X_H]={0};//存每行右基点坐标 数值：0-图像宽度MT9V03X_W
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		  基准点寻找模块		*/
/*==============================*/
static unsigned char found_point(char num){
//	变量定义
	register unsigned char j;
	unsigned char row = MT9V03X_H-1;
//	基点寻找
	switch(num){
		case 1://左基点寻找
			for(j = 0; j < 159; j++){
				if( 0 == gray_img[row][j] && 255 == gray_img[row][j+1])
                
                    break;
                
			}
			break;
		case 2://右基点寻找
            for(j = 159; j >=0 ; j--){
				if( 255 == gray_img[row][j-1] && 0 == gray_img[row][j])
                    break;
			}
			break;
	}
}

void findLeftPoint(void){
    uint8 mid=(uint16)((0 + MT9V03X_W)/2);//每行中间值
    bool b1=false,b2=true;
    uint16 j, i;
    uint16 leftStart1_W = 0,leftStart2_W = 0, leftStart1_H = 0,leftStart2_H = 0,leftStart = 0;
   //找基点
    uint16 row = MT9V03X_H - 1;
    //从两头往中间版
    for (i=row; i>0;i--){
        for( j= 1; j<mid + 20 && j< MT9V03X_W-1; j++){
            if( 0 == gray_img[i][j] && 255 == gray_img[i][j+1]){    
                leftStart1_W =j+1;
                leftStart1_H=i;
                b1=true;
                break ;
            }
        }
        
        //找到基点 跳出循环
        if(b1) break;
        //丢边
        if(1 == i);
    }
    
    //从中间往两头版
    for(i=row; i>0; i--){
    
        for(j= mid; j>1; j--){
            if( 255 == gray_img[i][j] && 0 == gray_img[i][j-1]){       
                leftStart2_W = j;
                leftStart2_H = i;
                b2=true;
                break ;
            }
        }
        //找到基点 跳出循环
        if(b2) break;
    }
    
    if(leftStart1_W == leftStart2_W){
        leftStart = leftStart1_W;
        imageLeft[MT9V03X_H-1]=leftStart;
    }
    else{
        leftStart  =404;
    }
    
    //显示数据
    if( csimenu_flag[1] ){
    
        ips200_displayimage032(gray_img[0], MT9V03X_W, MT9V03X_H);
        
        for( i = 0; i<8;i++){
            ips200_drawpoint(leftStart1_W + i, leftStart1_H, RED);
            ips200_drawpoint(leftStart2_W + i, leftStart2_H, BLUE);
        }
        
        ips200_showuint16(0,5,leftStart);
       ips200_showuint16(0,6,leftStart1_W);
       ips200_showuint16(0,7,leftStart2_W);
       
        ips200_showuint16(50,6,leftStart1_H);
       ips200_showuint16(50,7,leftStart2_H);
       
        //找线
        for( i = MT9V03X_H-2; i > 0; i--){
            for(j = 0; j < MT9V03X_W-2; j++){
                if( 0 == gray_img[i][j] && 255 == gray_img[i][j+1]){ 
                    imageLeft[i] = j+1;
                    ips200_drawpoint( j+1 , i, RED);
                    break;
                }
            }
            
        }
        
        
    }
    findRightPoint();
}

void findRightPoint(void){
    uint8 mid=(uint8)((0 + MT9V03X_W)/2);//每行中间值
    uint8 j, i;
    bool b1=false,b2=false;
    uint16 rightStart1_W = 0,rightStart2_W = 0,rightStart1_H = 0,rightStart2_H = 0, rightStart = 0;
   //找基点
    uint8 row = MT9V03X_H - 1;
    
    //从两头往中间版
    for(i=row; i>0; i--){
        for( j= MT9V03X_W-2; j>mid-20 && j>0; j--){
            if( 0 == gray_img[row][j] && 255 == gray_img[row][j-1]){    
                rightStart1_W=j;
                rightStart1_H=i;
                b1=true;
                break;
            }
        }
        if(b1) break;
    }
    
    //从中间往两头版
    for(i=row; i>0; i--){
        for(j= mid; j < MT9V03X_W; j++ ){
            if( 255 == gray_img[row][j] && 0 == gray_img[row][j-1]){       
                rightStart2_W=j;
                rightStart2_H=i;
                b2=true;
                break;
            }
            
        }
        if(b2) break;
    }

    
    if(rightStart1_W == rightStart2_W){
        rightStart=rightStart1_W;
        imageRight[MT9V03X_H-1]=rightStart;
    }
    else{
        rightStart = 404;
    }
    
    //显示数据
    if( csimenu_flag[1]  ){

        for( i = 0; i<8;i++){
           ips200_drawpoint(rightStart1_W+i, rightStart1_H, GREEN);
        ips200_drawpoint(rightStart2_W+i, rightStart2_H, PURPLE);
        }
        
        ips200_showuint16(8,5,rightStart);
       
        //找线
        for( i = MT9V03X_H-2; i > 0; i--){
            for(j = MT9V03X_W-1; j > 0; j--){
                if( 0 == gray_img[i][j] && 255 == gray_img[i][j-1]){ 
                    imageRight[i] = j-1;
                    ips200_drawpoint(j-1, i, RED);
                    break;
                }
            }
        }
    }
}


/*------------------------------*/
/*		 大津法二值化模块		*/
/*==============================*/
void otsu(void){
//	变量定义
	float var = 0, vartmp = 0;
	float imgsize = MT9V03X_H*MT9V03X_W, sumPK = 0, sumMK = 0;
	register short i, j;
	unsigned short hist[grayscale] = {0};	
//	获取直方图
	for(i = 0; i < MT9V03X_H; i++){
		for(j = 0; j < MT9V03X_W; j++)
			hist[mt9v03x_image[i][j]]++;
	}
//	求类间方差
	for(i = 0; i < grayscale; i++){
		P[i] = (float)hist[i]/imgsize;//计算每个灰度级出现的概率
		PK[i] = sumPK+P[i];//概率累计和
		sumPK = PK[i];
		MK[i] = sumMK+i*P[i];//灰度值累加均值          
		sumMK = MK[i];
	}
    int max=0,max2=0;
	for(i = 10; i < 200; i++){
		vartmp = ((MK[grayscale-1]*PK[i] - MK[i])*(MK[grayscale-1]*PK[i] - MK[i])) / (PK[i]*(1 - PK[i]));
		if(vartmp > var){
			var = vartmp;
            max2=max;
            max=i;
			
		}
	}
    img_thrsod =(int)((max+max2)/2);//输出阈值
    
    
    //	数组二值化处理
	for(i = 0; i < MT9V03X_H; i++)
		for(j = 0; j < MT9V03X_W; j++){
			if(mt9v03x_image[i][j]>img_thrsod) gray_img[i][j] = 255;
			else gray_img[i][j] = 0; 
		}
	if(csimenu_flag[0]) ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
}
