#include "measure.h"

//int s_begin=180,s_end=200;//选取20个像素
extern float scale;

int w_begin=134,w_end=215;//求胯骨位置，在这里选取兴趣区域为134--215的像素位置
double xx[40]={0},yy[40]={0};
float offset_x=0,offset_y=0;
//double cur_data[80]={0};//存放的是曲率值80个
int cur_x=0,cur_y=0;
double P[6];
int my_head=0;//初始化头顶的像素位置
int my_height=0;//GROUND -my_head;
int s_begin=0;//(int)(GROUND -my_height*0.83),s_end=s_begin+40;//选取20个像素40
int s_end=0;
int jian_kuan=0;
int xiong_wei=0;
int bi_chang=0;
int tui_chang=0;
int zhong_yao=0;
int yao=0;
int tun=0;
int linwei=0;
int xiongkuan=0;
int qianshen=0;
int lidang=0;
/*简介：
为了便于编写程序，要使用统一的坐标，否则会引起混乱。
在这里统一规定：左下角为原点，向右为x的正方向，向上为y的正方向
*/
void CMy_ScaleDlg ::glGrab ()
{
	int xy_flag=0;
    glGetIntegerv(GL_VIEWPORT, viewPort);  
	if(colorArr != NULL) { delete [] colorArr; colorArr = NULL; }
	if(judgeArr1 != NULL) { delete [] judgeArr1; judgeArr1 = NULL; }
	
	winWidth = viewPort[2];  
	winHeight = viewPort[3];    
	colorArr = new GLbyte[ winWidth * winHeight * 4 ]; // MFC的像素格式只支持RGBA  
	judgeArr1 = new GLbyte[cut1];  
	
	glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGBA, GL_UNSIGNED_BYTE, colorArr); // RGBA  
	
	GLbyte test[ 670] ={0};
	for(int i=670 ;i>0;i--)
	{            
				  int j = 300;
					  test[i]=colorArr[(j*WINWIDTH +i)*4+1];
					 					 				
				  
	}


	/*首先要把身高求出来*/
	for(int i=669;i>GROUND;i--)
	{//选择center 这一列的像素点作为判断标准，也就是找出第一个不是绿色的像素点的坐标
	 if(colorArr[(i*winWidth+center)*4+1]<60)//可以在这里改变阈值
	 {my_head =i;my_height =my_head-GROUND;break;}
	}
     s_begin=(int)(GROUND +my_height*0.84),s_end=s_begin-40;//选取20个像素40
	 measure_kua (colorArr);
	jian_kuan=measure_jian (colorArr);
	xiong_wei=measure_xiong(colorArr);
	bi_chang=measure_arm(colorArr);
	zhong_yao=measure_zhong_yao (colorArr);
	yao=measure_yao(colorArr);
	tun=measure_tun(colorArr);
	tui_chang=measure_leg();
	//measure_linwei(colorArr);
	linwei=measure_linwei (colorArr);
	jian_kuan=int(measure_jin_jian ());
	xiongkuan=measure_xiongkuan();
	qianshen=int(measure_qian_shen(colorArr));
	lidang=measure_lidang();
	//delete []colorArr;
	//delete []judgeArr1;
	//delete []judgeArr2;
	/*
	for(int j=s_begin ;j>s_end;j--)//自上而下扫描40个像素
	{   int k1=0;
        for (int i=0;i<30;i++) location [i]=0;   //30个存放像素位置的数组清零 
		for(int i=0;i<cut1 ;i++)
		  {
				//这是用来检测黑色背景的，现在改为绿色//if(colorArr[(j*winWidth +i)*4]<10&&colorArr[(j *winWidth +i)*4+1]<10&&colorArr[(j *winWidth +i)*4+2]<10)
			  if(colorArr[(j*winWidth +i)*4]<30&&colorArr[(j *winWidth +i)*4+1]>10&&colorArr[(j *winWidth +i)*4+2]<30)
				{judgeArr1[i]=0;}//rgb不为零的都化为1，代表一个像素放在数组中
				 else judgeArr1 [i]=1;
		  }							 
		for(int i=1;i<cut1-1 ;i++)
		  {//记录线段的两端的位置
			if(judgeArr1[i]>judgeArr1[i-1]||judgeArr1[i]>judgeArr1[i+1])
			{location[k1]=i;k1++;}//把边缘像素存储在location数组中
		  }			
		xx[xy_flag]=location[my_max(location)];//初始拟合点的横坐标（选取最大的边缘点一共是40个）
		yy[xy_flag]=j;//初始拟合点的纵坐标
		xy_flag++;																											
	}
		offset_x=xx[my_min(xx)];offset_y=yy[my_min(yy)];//保存偏移值	
		for(int i=0;i<40;i++) {xx[i]-=offset_x;yy[i]-=offset_y;}//这里注意，最小值是固定的，不能用最小数组函数
	    //至此拟合点选取完毕   
		/*for(int i=cut1;i<cut2 ;i++)		
		{if(colorArr[(chest_Y *winWidth +i)*4]<10&&colorArr[(chest_Y *winWidth +i)*4+1]<10&&colorArr[(chest_Y *winWidth +i)*4+2]<10)
		  {judgeArr2[i]=0;}//rgb不为零的都化为1，代表一个像素放在数组中
		 else judgeArr2 [i]=1;			
		}

		for(int i=cut1+1;i<cut2-1 ;i++)
		 {//记录线段的两端的位置
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])
		  {location2[k2]=i;k2++;}
		  }  

		int sizenum;
		int dimension=4;
		sizenum=sizeof(xx)/sizeof(xx[0]);
		polyfit (sizenum,xx,yy,dimension,P);
       //PolyFit(xx,yy,sizenum,P,dimension+1,my_error);
		for(int i=0;i<80;i++) cur_data[i]=0;//将存储曲率的数组清零。。。。。这是选取了多一倍的样本
		///纠结在这里了，xx为什么是负值，i<my_max_a是什么意思，调试没成功										
		for (int i=0;i<xx[my_max_a(xx,40)];i++)
		{cur_data[2*i]=curvature (i,P);cur_data[2*i+1]=curvature (i+0.5,P);}//取一定个点，并求其曲率
   
        for(int i=0;i<6;i++)  cur_data[i]=0;
                                                
		cur_x=(int)(my_max1 (cur_data)/2.0+0.5)>my_max1 (cur_data)/2?my_max1 (cur_data)/2+1:my_max1 (cur_data)/2;
		//求曲率最大的点，并四舍五入//cur_y=offset_y+int(P[0]+P[1]*cur_x+P[2]*pow(cur_x,2)+P[3]*pow(cur_x,3)+P[4]*pow(cur_x,4));
		cur_y=offset_y+19-my_max1(cur_data)/2;
		cur_x=xx[19-cur_x]+offset_x;//x坐标偏移到对应的像素坐标
////////下面就是根据像素点求肩宽了
		if(judgeArr1 != NULL) { delete [] judgeArr1; judgeArr1 = NULL; }
		judgeArr1 = new GLbyte[cut1]; 
		for(int i=0;i<cut1 ;i++)
		{
			//将检测黑色背景改为绿色//if(colorArr[(cur_y *winWidth +i)*4]<10&&colorArr[(cur_y *winWidth +i)*4+1]<10&&colorArr[(cur_y *winWidth +i)*4+2]<10)
			if(colorArr[(cur_y *winWidth +i)*4]<30&&colorArr[(cur_y *winWidth +i)*4+1]>10&&colorArr[(cur_y *winWidth +i)*4+2]<30)
			{judgeArr1[i]=0;}//rgb不为零的都化为1，代表一个像素放在数组中
			else judgeArr1 [i]=1;			
		}

		for (int i=0;i<30;i++) location [i]=0;
			  
        int k_2=0;						
        for(int i=1;i<cut1-1 ;i++)
				{//记录线段的两端的位置
				if(judgeArr1[i]>judgeArr1[i-1]||judgeArr1[i]>judgeArr1[i+1])
				{location[k_2]=i;k_2++;}
				}							 
//////////
		//下面求腰围的尺寸，求出4个主要的像素坐标
		if(judgeArr2 != NULL) { delete [] judgeArr2; judgeArr2 = NULL; }
		judgeArr2 = new GLbyte[cut2];
		/*int k2=0;
		int Waist_Y=int(167+152.6*scale );
		    Waist_Y =670-Waist_Y ;
		for (int i=0;i<cut2;i++)//将该行像素简化
		{if(colorArr[(Waist_Y *winWidth +i)*4]<10&&colorArr[(Waist_Y *winWidth +i)*4+1]<10&&colorArr[(Waist_Y *winWidth +i)*4+2]<10)
		     {judgeArr2[i]=0;}//rgb不为零的都化为1，代表一个像素放在数组中
		      else judgeArr2 [i]=1;	
		}
		for (int i=167;i>0;i--)
		{
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//第一个像素点
		  {Waist_X[k2]=i;k2++;break;}		  
		}
		for (int i=168;i<cut1;i++)
		{
		   if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//第二个像素点
            {Waist_X[k2]=i;k2++;break;}
		}
		for (int i=cut1+1;i<cut2-1;i++)
		{
		    if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//第二个像素点
            {Waist_X[k2]=i;k2++;}
			
		}*/
		/*for(int i=cut1;i<cut2 ;i++)		
		{if(colorArr[(chest_Y *winWidth +i)*4]<10&&colorArr[(chest_Y *winWidth +i)*4+1]<10&&colorArr[(chest_Y *winWidth +i)*4+2]<10)
		  {judgeArr2[i]=0;}//rgb不为零的都化为1，代表一个像素放在数组中
		 else judgeArr2 [i]=1;			
		}

		for(int i=cut1+1;i<cut2-1 ;i++)
		 {//记录线段的两端的位置
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])
		  {location2[k2]=i;k2++;}
		  }  */
}