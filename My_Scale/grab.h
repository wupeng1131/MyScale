#include "measure.h"

//int s_begin=180,s_end=200;//ѡȡ20������
extern float scale;

int w_begin=134,w_end=215;//����λ�ã�������ѡȡ��Ȥ����Ϊ134--215������λ��
double xx[40]={0},yy[40]={0};
float offset_x=0,offset_y=0;
//double cur_data[80]={0};//��ŵ�������ֵ80��
int cur_x=0,cur_y=0;
double P[6];
int my_head=0;//��ʼ��ͷ��������λ��
int my_height=0;//GROUND -my_head;
int s_begin=0;//(int)(GROUND -my_height*0.83),s_end=s_begin+40;//ѡȡ20������40
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
/*��飺
Ϊ�˱��ڱ�д����Ҫʹ��ͳһ�����꣬�����������ҡ�
������ͳһ�涨�����½�Ϊԭ�㣬����Ϊx������������Ϊy��������
*/
void CMy_ScaleDlg ::glGrab ()
{
	int xy_flag=0;
    glGetIntegerv(GL_VIEWPORT, viewPort);  
	if(colorArr != NULL) { delete [] colorArr; colorArr = NULL; }
	if(judgeArr1 != NULL) { delete [] judgeArr1; judgeArr1 = NULL; }
	
	winWidth = viewPort[2];  
	winHeight = viewPort[3];    
	colorArr = new GLbyte[ winWidth * winHeight * 4 ]; // MFC�����ظ�ʽֻ֧��RGBA  
	judgeArr1 = new GLbyte[cut1];  
	
	glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGBA, GL_UNSIGNED_BYTE, colorArr); // RGBA  
	
	GLbyte test[ 670] ={0};
	for(int i=670 ;i>0;i--)
	{            
				  int j = 300;
					  test[i]=colorArr[(j*WINWIDTH +i)*4+1];
					 					 				
				  
	}


	/*����Ҫ����������*/
	for(int i=669;i>GROUND;i--)
	{//ѡ��center ��һ�е����ص���Ϊ�жϱ�׼��Ҳ�����ҳ���һ��������ɫ�����ص������
	 if(colorArr[(i*winWidth+center)*4+1]<60)//����������ı���ֵ
	 {my_head =i;my_height =my_head-GROUND;break;}
	}
     s_begin=(int)(GROUND +my_height*0.84),s_end=s_begin-40;//ѡȡ20������40
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
	for(int j=s_begin ;j>s_end;j--)//���϶���ɨ��40������
	{   int k1=0;
        for (int i=0;i<30;i++) location [i]=0;   //30���������λ�õ��������� 
		for(int i=0;i<cut1 ;i++)
		  {
				//������������ɫ�����ģ����ڸ�Ϊ��ɫ//if(colorArr[(j*winWidth +i)*4]<10&&colorArr[(j *winWidth +i)*4+1]<10&&colorArr[(j *winWidth +i)*4+2]<10)
			  if(colorArr[(j*winWidth +i)*4]<30&&colorArr[(j *winWidth +i)*4+1]>10&&colorArr[(j *winWidth +i)*4+2]<30)
				{judgeArr1[i]=0;}//rgb��Ϊ��Ķ���Ϊ1������һ�����ط���������
				 else judgeArr1 [i]=1;
		  }							 
		for(int i=1;i<cut1-1 ;i++)
		  {//��¼�߶ε����˵�λ��
			if(judgeArr1[i]>judgeArr1[i-1]||judgeArr1[i]>judgeArr1[i+1])
			{location[k1]=i;k1++;}//�ѱ�Ե���ش洢��location������
		  }			
		xx[xy_flag]=location[my_max(location)];//��ʼ��ϵ�ĺ����꣨ѡȡ���ı�Ե��һ����40����
		yy[xy_flag]=j;//��ʼ��ϵ��������
		xy_flag++;																											
	}
		offset_x=xx[my_min(xx)];offset_y=yy[my_min(yy)];//����ƫ��ֵ	
		for(int i=0;i<40;i++) {xx[i]-=offset_x;yy[i]-=offset_y;}//����ע�⣬��Сֵ�ǹ̶��ģ���������С���麯��
	    //������ϵ�ѡȡ���   
		/*for(int i=cut1;i<cut2 ;i++)		
		{if(colorArr[(chest_Y *winWidth +i)*4]<10&&colorArr[(chest_Y *winWidth +i)*4+1]<10&&colorArr[(chest_Y *winWidth +i)*4+2]<10)
		  {judgeArr2[i]=0;}//rgb��Ϊ��Ķ���Ϊ1������һ�����ط���������
		 else judgeArr2 [i]=1;			
		}

		for(int i=cut1+1;i<cut2-1 ;i++)
		 {//��¼�߶ε����˵�λ��
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])
		  {location2[k2]=i;k2++;}
		  }  

		int sizenum;
		int dimension=4;
		sizenum=sizeof(xx)/sizeof(xx[0]);
		polyfit (sizenum,xx,yy,dimension,P);
       //PolyFit(xx,yy,sizenum,P,dimension+1,my_error);
		for(int i=0;i<80;i++) cur_data[i]=0;//���洢���ʵ��������㡣������������ѡȡ�˶�һ��������
		///�����������ˣ�xxΪʲô�Ǹ�ֵ��i<my_max_a��ʲô��˼������û�ɹ�										
		for (int i=0;i<xx[my_max_a(xx,40)];i++)
		{cur_data[2*i]=curvature (i,P);cur_data[2*i+1]=curvature (i+0.5,P);}//ȡһ�����㣬����������
   
        for(int i=0;i<6;i++)  cur_data[i]=0;
                                                
		cur_x=(int)(my_max1 (cur_data)/2.0+0.5)>my_max1 (cur_data)/2?my_max1 (cur_data)/2+1:my_max1 (cur_data)/2;
		//���������ĵ㣬����������//cur_y=offset_y+int(P[0]+P[1]*cur_x+P[2]*pow(cur_x,2)+P[3]*pow(cur_x,3)+P[4]*pow(cur_x,4));
		cur_y=offset_y+19-my_max1(cur_data)/2;
		cur_x=xx[19-cur_x]+offset_x;//x����ƫ�Ƶ���Ӧ����������
////////������Ǹ������ص�������
		if(judgeArr1 != NULL) { delete [] judgeArr1; judgeArr1 = NULL; }
		judgeArr1 = new GLbyte[cut1]; 
		for(int i=0;i<cut1 ;i++)
		{
			//������ɫ������Ϊ��ɫ//if(colorArr[(cur_y *winWidth +i)*4]<10&&colorArr[(cur_y *winWidth +i)*4+1]<10&&colorArr[(cur_y *winWidth +i)*4+2]<10)
			if(colorArr[(cur_y *winWidth +i)*4]<30&&colorArr[(cur_y *winWidth +i)*4+1]>10&&colorArr[(cur_y *winWidth +i)*4+2]<30)
			{judgeArr1[i]=0;}//rgb��Ϊ��Ķ���Ϊ1������һ�����ط���������
			else judgeArr1 [i]=1;			
		}

		for (int i=0;i<30;i++) location [i]=0;
			  
        int k_2=0;						
        for(int i=1;i<cut1-1 ;i++)
				{//��¼�߶ε����˵�λ��
				if(judgeArr1[i]>judgeArr1[i-1]||judgeArr1[i]>judgeArr1[i+1])
				{location[k_2]=i;k_2++;}
				}							 
//////////
		//��������Χ�ĳߴ磬���4����Ҫ����������
		if(judgeArr2 != NULL) { delete [] judgeArr2; judgeArr2 = NULL; }
		judgeArr2 = new GLbyte[cut2];
		/*int k2=0;
		int Waist_Y=int(167+152.6*scale );
		    Waist_Y =670-Waist_Y ;
		for (int i=0;i<cut2;i++)//���������ؼ�
		{if(colorArr[(Waist_Y *winWidth +i)*4]<10&&colorArr[(Waist_Y *winWidth +i)*4+1]<10&&colorArr[(Waist_Y *winWidth +i)*4+2]<10)
		     {judgeArr2[i]=0;}//rgb��Ϊ��Ķ���Ϊ1������һ�����ط���������
		      else judgeArr2 [i]=1;	
		}
		for (int i=167;i>0;i--)
		{
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//��һ�����ص�
		  {Waist_X[k2]=i;k2++;break;}		  
		}
		for (int i=168;i<cut1;i++)
		{
		   if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//�ڶ������ص�
            {Waist_X[k2]=i;k2++;break;}
		}
		for (int i=cut1+1;i<cut2-1;i++)
		{
		    if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])//�ڶ������ص�
            {Waist_X[k2]=i;k2++;}
			
		}*/
		/*for(int i=cut1;i<cut2 ;i++)		
		{if(colorArr[(chest_Y *winWidth +i)*4]<10&&colorArr[(chest_Y *winWidth +i)*4+1]<10&&colorArr[(chest_Y *winWidth +i)*4+2]<10)
		  {judgeArr2[i]=0;}//rgb��Ϊ��Ķ���Ϊ1������һ�����ط���������
		 else judgeArr2 [i]=1;			
		}

		for(int i=cut1+1;i<cut2-1 ;i++)
		 {//��¼�߶ε����˵�λ��
		  if(judgeArr2[i]>judgeArr2[i-1]||judgeArr2[i]>judgeArr2[i+1])
		  {location2[k2]=i;k2++;}
		  }  */
}