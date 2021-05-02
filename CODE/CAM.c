/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "CAM.h"
#include "pid.h"
#include "data.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"

uint16 imageLeft[MT9V03X_H]={0};//��ÿ����������� ��ʼ��Ϊ0
uint16 imageRight[MT9V03X_H]={0};//��ÿ���һ������� ��ֵ��0-ͼ����MT9V03X_W
bool leftLose,rightLose,leftTurn,rightTurn;

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		  ��׼��Ѱ��ģ��		*/
/*==============================*/
static unsigned char found_point(char num){
//	��������
	register unsigned char j;
	unsigned char row = MT9V03X_H-1;
//	����Ѱ��
	switch(num){
		case 1://�����Ѱ��
			for(j = 0; j < 159; j++){
				if( 0 == gray_img[row][j] && 255 == gray_img[row][j+1])
                
                    break;
                
			}
			break;
		case 2://�һ���Ѱ��
            for(j = 159; j >=0 ; j--){
				if( 255 == gray_img[row][j-1] && 0 == gray_img[row][j])
                    break;
			}
			break;
	}
}

void findLeftPoint(void){
    uint8 mid=(uint16)((0 + MT9V03X_W)/2);//ÿ���м�ֵ
    bool b1=false,b2=true;
    uint16 j, i;
    uint16 leftStart1_W = 0,leftStart2_W = 0, leftStart1_H = 0,leftStart2_H = 0,leftStart = 0;
   //�һ���
    uint16 row = MT9V03X_H - 1;
    
    leftLose=false;
    rightLose = false;
    //����ͷ���м��
    for (i=row; i>0;i--){
        for( j= 1; j<mid + 20 && j< MT9V03X_W-1; j++){
            if( 0 == gray_img[i][j] && 255 == gray_img[i][j+1]){    
                leftStart1_W =j+1;
                leftStart1_H=i;
                b1=true;
                break ;
            }
        }
        
        //�ҵ����� ����ѭ��
        if(b1) break;
        
       
    }
    //����
    if(!b1){
        leftLose=true;
        
        
    }    
    //���м�����ͷ��
    for(i=row; i>0; i--){
    
        for(j= mid; j>1; j--){
            if( 255 == gray_img[i][j] && 0 == gray_img[i][j-1]){       
                leftStart2_W = j;
                leftStart2_H = i;
                b2=true;
                break ;
            }
        }
        //�ҵ����� ����ѭ��
        if(b2) break;
       // if(1 == i) leftLose=true;
    }
    
    if(leftStart1_W == leftStart2_W){
        leftStart = leftStart1_W;
        imageLeft[MT9V03X_H-1]=leftStart;
    }
    else{
        leftStart  =404;
    }
    
    //��ʾ����
    if( csimenu_flag[1] ){
    
        ips200_displayimage032(gray_img[0], MT9V03X_W, MT9V03X_H);
        
        for( i = 0; i<8;i++){
            ips200_drawpoint(leftStart1_W + i, leftStart1_H, RED);
            ips200_drawpoint(leftStart2_W + i, leftStart2_H, BLUE);
        }
        
        ips200_showuint16(0,5,leftStart);
       ips200_showuint16(0,6,leftStart1_W);
       ips200_showuint16(0,7,leftStart2_W);
       

       
        //����
        for( i = MT9V03X_H-2; i > 0; i--){
            for(j = 0; j < MT9V03X_W-2; j++){
                if( 0 == gray_img[i][j] && 255 == gray_img[i][j+1]){ 
                    imageLeft[i] = j+1;
                    ips200_drawpoint( j+1 , i, RED);
                    ips200_drawpoint( j+2 , i, RED);
                    break;
                }
            }            
        }
        
        
    }
    findRightPoint();
    drawMidLine();
}

void findRightPoint(void){
    uint8 mid=(uint8)((0 + MT9V03X_W)/2);//ÿ���м�ֵ
    uint8 j, i;
    bool b1=false,b2=false;
    uint16 rightStart1_W = 0,rightStart2_W = 0,rightStart1_H = 0,rightStart2_H = 0, rightStart = 0;

    uint8 row = MT9V03X_H - 1;
       //���һ���
    //����ͷ���м��
    for(i=row; i>0; i--){
        for( j= MT9V03X_W-2; j>mid-20 && j>0; j--){
            if( 0 == gray_img[row][j] && 255 == gray_img[row][j-1]){    
                rightStart1_W=j-1;
                rightStart1_H=i;
                b1=true;
                break;
            }
        }
        if(b1) break;

    }
     //����
    if(!b1) rightLose=true;
    //���м�����ͷ��
    for(i=row; i>0; i--){
        for(j= mid; j < MT9V03X_W-2; j++ ){
            if( 255 == gray_img[row][j] && 0 == gray_img[row][j+1]){       
                rightStart2_W=j;
                rightStart2_H=i;
                b2=true;
                break;
            }
            
        }
        if(b2) break;
       // if(1 == i) leftLose=true;
    }
    
    
    if(rightStart1_W == rightStart2_W){
        rightStart=rightStart1_W;
        imageRight[MT9V03X_H-1]=rightStart;
    }
    else{
        rightStart = 404;
    }
    
    //��ʾ����
    if( csimenu_flag[1]  ){

        for( i = 0; i<8;i++){
           ips200_drawpoint(rightStart1_W-i, rightStart1_H, GREEN);
            ips200_drawpoint(rightStart2_W-i, rightStart2_H, PURPLE);
        }
        
        ips200_showuint16(8,5, rightStart);
        
        ips200_showuint16(50,6, rightStart1_W);
       ips200_showuint16(50,7, rightStart2_W);
        //����
        for( i = MT9V03X_H-2; i > 0; i--){
            for(j = MT9V03X_W-1; j > mid-20; j--){
                if( 0 == gray_img[i][j] && 255 == gray_img[i][j-1]){ 
                    imageRight[i] = j-1;
                    ips200_drawpoint(j-1, i, RED);
                    ips200_drawpoint(j-2, i, RED);
                    break;
                }
            }
        }
    }
}




void drawMidLine(void){
    uint8 i,j, road_W_L,road_W_R;
    uint8 mid = MT9V03X_W/2;
    
    //�����ж���
    uint8 cntBL=0,cntBR=0;//ĳ�кڵ����
    uint8 noBlackPoints=32;
    for(i=0;i<MT9V03X_H; i++){
        if(gray_img[i][1] == 0){
            cntBL++;
        }
        if(gray_img[i][MT9V03X_W-2] == 0){
            cntBR++;
        }
    }
    if(cntBL>noBlackPoints){
        leftLose=false;
    }
    if(cntBR>noBlackPoints){
        rightLose=false;
    }
   
            
            
//����������ߴ���
    //������
    if(!leftLose && !rightLose){
        ips200_showstr(0, 9,"No Lose!   ");
//        road_W_L=judgeTurn(imageLeft) ;
//        road_W_R=judgeTurn(imageRight);
        
        for(i=0;i<MT9V03X_H; i++){
            ips200_drawpoint((imageLeft[i]+imageRight[i])/2, i, RED);
//            ips200_drawpoint((imageLeft[i]+imageRight[i])/2+1, i, RED);
        }
            
//            ������Ⱥ���ûʲô����
//        if(road_W_L == 256 && road_W_R == 256){            
//             for(i=0;i<MT9V03X_H; i++){
//                ips200_drawpoint((imageLeft[i]+imageRight[i])/2, i, RED);
//                ips200_drawpoint((imageLeft[i]+imageRight[i])/2+1, i, RED);
//            }
//        }
//        if( road_W_L !=256 ){
//            for(i=0;i<MT9V03X_H; i++){
//                
//                ips200_drawpoint((imageLeft[i]+imageRight[i])/2, i, RED);
//                ips200_drawpoint((imageLeft[i]+imageRight[i])/2+1, i, RED);
//            }
//        }

    }
    
    //�����
    else if (leftLose&&!rightLose){
        ips200_showstr(0, 9,"leftLose  ");
        for(i=0;i<MT9V03X_H; i++){
                
                ips200_drawpoint(imageRight[i]-mid, i, RED);
  //              ips200_drawpoint(imageRight[i]-mid+1, i, RED);
        }
    }
    
    //���ұ�
    else if(rightLose && !leftLose){
        ips200_showstr(0, 9,"rightLose");
         for(i=0;i<MT9V03X_H; i++){
                ips200_drawpoint(imageLeft[i]+mid, i, RED);
  //              ips200_drawpoint(imageLeft[i]+mid+1, i, RED);
        }
    }
    else{
         ips200_showstr(0, 9,"what Happen?");
    }
}

//�ж��Ƿ�������ҹ� ������ģ���������
uint16 judgeTurn(uint16 *arr){
    //��������
    uint16 max=0,min=MT9V03X_W,i,j;
    uint16 countLeft=0,countRight=0;
    
    //�ж��Ƿ񼴽��� ��δ����   
    for(i=20;i<MT9V03X_H; i++){
        if(arr[i]>max){
            max=arr[i];
            countLeft = 0;//��ת����
        }
        else if(arr[i]<min){
            min=arr[i];
            countRight=0;
        }
        else if(arr[i]<max){
            countLeft++;
        }
        else if(arr[i]>min){
            countRight++;
        }
        
        if(countLeft > 5){
            leftTurn = true;
            ips200_showstr(0, 10,"leftTurn  ");
            break;
        }
        else if(countRight > 5){
            rightTurn = true;
            ips200_showstr(0, 10,"rightTurn  ");
            break;
        }
        else{
            ips200_showstr(0, 10,"No Turn  ");
        }
       
    }
    if(leftTurn)return imageRight[i-5] - 1 - max;
    else if(rightTurn) return min - imageLeft[i];
    else return 256;
}




/*------------------------------*/
/*		 ��򷨶�ֵ��ģ��		*/
/*==============================*/
void otsu(void){
//	��������
	float var = 0, vartmp = 0;
	float imgsize = MT9V03X_H*MT9V03X_W, sumPK = 0, sumMK = 0;
	register short i, j;
	unsigned short hist[grayscale] = {0};	
//	��ȡֱ��ͼ
	for(i = 0; i < MT9V03X_H; i++){
		for(j = 0; j < MT9V03X_W; j++)
			hist[mt9v03x_image[i][j]]++;
	}
//	����䷽��
	for(i = 0; i < grayscale; i++){
		P[i] = (float)hist[i]/imgsize;//����ÿ���Ҷȼ����ֵĸ���
		PK[i] = sumPK+P[i];//�����ۼƺ�
		sumPK = PK[i];
		MK[i] = sumMK+i*P[i];//�Ҷ�ֵ�ۼӾ�ֵ          
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
    img_thrsod =(int)((max+max2)/2);//�����ֵ
    
    
    //	�����ֵ������
	for(i = 0; i < MT9V03X_H; i++)
		for(j = 0; j < MT9V03X_W; j++){
			if(mt9v03x_image[i][j]>img_thrsod) gray_img[i][j] = 255;
			else gray_img[i][j] = 0; 
		}
	if(csimenu_flag[0]) ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
}
