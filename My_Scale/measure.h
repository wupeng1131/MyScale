#include "My_ScaleDlg.h"
#include "fit.h"
#include "DrawFlag.h"
#include <vector>
#include "parameter.h"
#define SCAN  if(colorArr[(py*WINWIDTH +px)*4]<20&&colorArr[(py *WINWIDTH +px)*4+1]>60&&colorArr[(py *WINWIDTH +px)*4+2]<20)\
					 {}\
			         else{Arr[2*i]=px;Arr[2*i+1]=py;return 1;}
#define A   px=x-1;py=y+1;SCAN	
#define B   px=x;py=y+1;SCAN	
#define C   px=x+1;py=y+1;SCAN	
#define D   px=x+1;py=y;SCAN	
#define E   px=x+1;py=y-1;SCAN	
#define F   px=x;py=y-1;SCAN
#define G   px=x-1;py=y-1;SCAN	
#define H   px=x-1;py=y;SCAN	
extern int my_head;
extern int center;
extern int B_kua_y;
extern int B_jian_y;
extern int jian[4];
extern int kua[4];
extern int zhou[4];
extern int wan[4];
extern int xi[4];
extern int foot[4];
int kuagu_y;
int L_jian_x,L_jian_y;
int R_jian_x,R_jian_y;
int global_yao_y;
int hu_kou_x;
int hu_kou_y;
int yao_y=0;
int L_neck_x=0;
int L_neck_y=0;
int R_neck_x=0;
int R_neck_y=0;
int front_jian=0;
int xiong_kuan=0;
int tun_Y =0;
int xiong_wei_global=0;
//x0:������꣬xe:�յ����꣬x��Բ������
int measure_kua(GLbyte  colorArr[])
{   
	/*int k =1;
    int flag=0;
	int near_kua=0;
	int arr_x[670-GROUND-50]={0};//�ӵ��濪ʼ50���������ϱ���
	int arr_y[670-GROUND-50]={0};//��������ֱ���x��������y������
	for(int i=0;i<670-GROUND-50;i++)
	{
	  arr_y[i]=i+GROUND+50;//�������긳ֵ
	}
  for(int j=GROUND+50;j<670;j++)//��������y
	  for(int i=670;i>0;i--)//�������x
	  {
		  if(colorArr[(j*WINWIDTH +i)*4]<20&&colorArr[(j *WINWIDTH +i)*4+1]>60&&colorArr[(j *WINWIDTH +i)*4+2]<20)
					 {//������ɫ������ֹ
					  }						 
		  else{arr_x[k]=i;k++;break;}	  
	  } 
//�����Ǳ���ɨ��ȡ��
	  for(int i=1;i<670-GROUND-50;i++)
	  { 
		  int temp=arr_x[i]-arr_x[i-1];
	  	  if (temp>0) flag++;
		  else if(temp==0) {flag=flag+0;}
		  else {  flag--;if (flag<0) flag=0;}
		  
		  if (flag>=5)//˵�������ǵ㸽����Ȼ��ֻҪ���ص�x������С���ĵ���ǿ�ǵ㣬��ֹѭ��
		  {
		    near_kua =i;break;//��ֹѭ�����Խ�����һ��ѭ��
		  }	
	  }
	    for(int j=near_kua;j<670;j++)
			   if (arr_x[j]-arr_x[j-1]<0)
			   {
			       kua_y=j+GROUND+50;break;//��ֹѭ�����ҵ���ǵ�
			   }
	*/	  
    int head=my_head ;//����ͷ
	int foot=GROUND;//�����
	int height=head-foot;//�������
	double kua_down=foot+height*KUA_DOWN;//�����²���
	double kua_up=kua_down+NUM_K;//�����ϲ���,����80����
	double mykua_x[NUM_K+1]={0};//�����и�Сϸ�ڣ���ʵ�������õ�81 �����أ��������ҵ��쳣�������˺�һ�����
	double mykua_y[NUM_K+1]={0};
	int k=0;
	//double a=670-kua_up;//�������������������Ե�
	//double b=670-kua_down;
	
	for (int j=kua_down;j<kua_up;j++)
		for (int i=670;i>0;i--)
		{	
			 if(colorArr[(j*WINWIDTH +i)*4]<20&&colorArr[(j *WINWIDTH +i)*4+1]>60&&colorArr[(j *WINWIDTH +i)*4+2]<20)
					 {//����ɫ�������κβ���
						
					 }
					 else{mykua_x[k]=i;mykua_y[k]=j;k++;break;}//������ɫ����ֹ������������
		}
		int sizenum=NUM_K;
		int dimension=4;
		double P[5]={0};
		polyfit (sizenum,mykua_y,mykua_x,dimension,P);
		double result[NUM_K*2]={0};
		for(int i=0;i<NUM_K;i++)
		{
		  double x=mykua_y[i];double a=P[4];double b=P[3];double c=P[2];double d=P[1];double e=P[0];
		  result[2*i]=x;
		  result[2*i+1]=a*x*x*x*x+b*x*x*x+c*x*x+d*x+e;		  
		}
		double max=0;//��ͻ���Ĳ���
		double max_y=0;//Ҳ���ǿ貿��y����
		for(int i=0;i<NUM_K;i++)
		{
		   if(result[2*i+1]>max)
		   {
		     max=result[2*i+1];
			 max_y=result[2*i];
		   }
		} 
		kuagu_y =max_y;//���ֵ���ǿ�ǵ�����꣬�Ժ���õ���
	  return 0;
}
int arc_scan(int x0,int y0,int xe,int ye,int x ,int y,GLbyte  colorArr[])
{//����shun ����˳ʱ�뻹����ʱ��
  int xi=0,yi=0,Fe,i=1,shun=1,rr=NULL;//rrΪ�뾶��ƽ��
  //if((xe-x)*(xe-x)+(ye-y)*(ye-y)==(x0-x)*(x0-x)+(y0-y)*(y0-y))
			rr=(xe-x)*(xe-x)+(ye-y)*(ye-y);
		//else return 0;
	xi=x0;yi=y0;//��㸳��xiyi
	while(xi!=xe||yi!=ye)//û�е����յ�ʱ
	{
		Fe=(xi-x)*(xi-x)+(yi-y)*(yi-y)-rr;
		//cout<<"Fe:"<<Fe<<endl;//system("pause");
		if(Fe>=0)
		{
			if(shun==1){
				if(xi>=x&&yi<=y)
					xi--;
				else if(xi<=x&&yi<=y)
					yi++;
				else if(xi<=x&&yi>=y)
					xi++;
				else if(xi>=x&&yi>=y)
					yi--;
			}
			else if(shun==2){
				if(xi>=x&&yi<=y)
					yi++;//xi--;
				else if(xi<=x&&yi<=y)
					xi++;//yi++;
				else if(xi<=x&&yi>=y)
					yi--;//xi++;
				else if(xi>=x&&yi>=y)
					xi--;//yi--;
			}
		}
		else
		{
			if(shun==1){
				if(xi>=x&&yi<=y)
					yi--;//xi--;
				else if(xi<=x&&yi<=y)
					xi--;//yi++;
				else if(xi<=x&&yi>=y)
					yi++;//xi++;
				else if(xi>=x&&yi>=y)
					xi++;//yi--;
			}
			else if(shun==2){
				if(xi>=x&&yi<=y)
					xi++;//yi++;//xi--;
				else if(xi<=x&&yi<=y)
					yi--;//xi++;//yi++;
				else if(xi<=x&&yi>=y)
					xi--;//yi--;//xi++;
				else if(xi>=x&&yi>=y)
					yi++;//xi--;//yi--;
			}

		}
		i++;
		//��ʱ��xi��yi�ֱ�ΪԲ���岹�������
		//���õ��RGBֵ�Ƿ�Ϊ��ɫ��������ɫ������ֹ��ȷ�����������
		//��������ɫ�������ɨ�裬ֱ����ֹ
		if(colorArr[(yi*WINWIDTH +xi)*4]<20&&colorArr[(yi*WINWIDTH +xi)*4+1]>60&&colorArr[(yi *WINWIDTH +xi)*4+2]<20)
			  {hu_kou_x =xi;hu_kou_y =yi;return 0;}//�ж�����ɫ
		
	}
	return 0;
}
//x,y�ֱ�Ϊ�������꣬a,b�ֱ�Ϊ������Arr�������������һ�����鱣�棬colorArr�������������������,��i����������
int R_scan(int x,int y ,int a ,int b,int i,int Arr[],GLbyte colorArr[])//���������ɨ��
{   int px=0,py=0;//��ʱʹ������������
		if(a==0&&b!=0)
		{
			  if(b>0)
			  {
				H
				A
				B
				C
				D
				E
				F
			  }
			  else
			  { 
				D
				E
				F
				G
				H
				A
				B

			  }
	}
	else if(a!=0&&b==0)
	{
		  if(a>0)
		  {
	         B
			 C
			 D
			 E
			 F
			 G
			 H

		  }
		  else
		  {
	         F
			 G
			 H
			 A
			 B
			 C
			 D

		  }
	}
	else
	{
		   if(a>0&&b>0)
		   {

			 A
		     B
			 C
			 D
			 E
			 F
			 G

            
		   }
		   else if(a>0&&b<0)
		   { 
			 C
			 D
			 E
			 F
			 G
			 H
			 A
		   }
		   else if(a<0&&b<0)
		   {
		      E
			  F
			  G
			  H
			  A
			  B
			  C
		   }
		   else
		   {
		     G
			 H
			 A
			 B
			 C
			 D
			 E
		   }
	}
  return -1;
}
int L_scan(int x,int y ,int a ,int b,int i,int Arr[],GLbyte colorArr[])
{
   int px=0,py=0;//��ʱʹ������������
		if(a==0&&b!=0)
		{
			  if(b>0)//(0,1)
			  {
				D
				C
				B
				A
				H
				G
				F

			  }
			  else//(0,-1)
			  { 
				H
				G
				F
				E
				D
				C
				B

			  }
	}
	else if(a!=0&&b==0)
	{
		  if(a>0)//(1,0)
		  {
	         F
			 E
			 D
			 C
			 B
			 A
			 H

		  }
		  else//(-1,0)
		  {
	         B
			 A
			 H
			 G
			 F
			 E
			 D

		  }
	}
	else
	{
		   if(a>0&&b>0)//(1,1)
		   {

			 E
			 D
			 C
			 B
			 A
			 H
			 G

            
		   }
		   else if(a>0&&b<0)//(1,-1)
		   { 
			 G
			 F
			 E
			 D
			 C
			 B
			 A
		   }
		   else if(a<0&&b<0)//(-1,-1)
		   {
		      A
			  H
			  G
			  F
			  E
			  D
			  C
		   }
		   else//(-1,1)
		   {
		     C
			 B
			 A
			 H
			 G
			 F
			 E
		   }
	}
  return -1;
}
int R_scan_add(int x,int y ,int a ,int b,int i,vector<int> &Arr,GLbyte colorArr[])//���������ɨ��
{   int px=0,py=0;//��ʱʹ������������
		if(a==0&&b!=0)
		{
			  if(b>0)
			  {
				H
				A
				B
				C
				D
				E
				F
			  }
			  else
			  { 
				D
				E
				F
				G
				H
				A
				B

			  }
	}
	else if(a!=0&&b==0)
	{
		  if(a>0)
		  {
	         B
			 C
			 D
			 E
			 F
			 G
			 H

		  }
		  else
		  {
	         F
			 G
			 H
			 A
			 B
			 C
			 D

		  }
	}
	else
	{
		   if(a>0&&b>0)
		   {

			 A
		     B
			 C
			 D
			 E
			 F
			 G

            
		   }
		   else if(a>0&&b<0)
		   { 
			 C
			 D
			 E
			 F
			 G
			 H
			 A
		   }
		   else if(a<0&&b<0)
		   {
		      E
			  F
			  G
			  H
			  A
			  B
			  C
		   }
		   else
		   {
		     G
			 H
			 A
			 B
			 C
			 D
			 E
		   }
	}
  return -1;
}
int L_scan_add(int x,int y ,int a ,int b,int i,vector<int> &Arr,GLbyte colorArr[])
{
   int px=0,py=0;//��ʱʹ������������
		if(a==0&&b!=0)
		{
			  if(b>0)//(0,1)
			  {
				D
				C
				B
				A
				H
				G
				F

			  }
			  else//(0,-1)
			  { 
				H
				G
				F
				E
				D
				C
				B

			  }
	}
	else if(a!=0&&b==0)
	{
		  if(a>0)//(1,0)
		  {
	         F
			 E
			 D
			 C
			 B
			 A
			 H

		  }
		  else//(-1,0)
		  {
	         B
			 A
			 H
			 G
			 F
			 E
			 D

		  }
	}
	else
	{
		   if(a>0&&b>0)//(1,1)
		   {

			 E
			 D
			 C
			 B
			 A
			 H
			 G

            
		   }
		   else if(a>0&&b<0)//(1,-1)
		   { 
			 G
			 F
			 E
			 D
			 C
			 B
			 A
		   }
		   else if(a<0&&b<0)//(-1,-1)
		   {
		      A
			  H
			  G
			  F
			  E
			  D
			  C
		   }
		   else//(-1,1)
		   {
		     C
			 B
			 A
			 H
			 G
			 F
			 E
		   }
	}
  return -1;
}
/*���룺���飬�����С��������Ϣ  �������������ϵ�ֱ�ߵĽǶ�*/
double grad(vector<int>&BeginPoint,vector<int> (*pf)(vector<int>&,GLbyte *,const int ),GLbyte colorArr[],const int num)
{
  vector<int>Arr =pf(BeginPoint,colorArr,num);//���ش���ϵ�x����
  /******�ڶ����Ǹ�����40�����ص㣬���һ��ֱ��******/
	const int sizenum_jian=40;
	int dimension_jian=1;
	double coef[2]={0};
	double X_Arr[40] = {0};
	double Y_Arr[40] = {0};
	for (int i = 0; i < num; i++)
	{
	  X_Arr[i] = Arr[2*i];
	  Y_Arr[i] = Arr[2*i+1];
	}
	polyfit (num,X_Arr,Y_Arr,dimension_jian,coef);
	//delete []X_Arr;
	//delete []Y_Arr;
	/************�������Ǹ�����õ�б����Ƕ�**************/
	float angle,pi_angle;
    pi_angle=atan(coef[1]);//����
    angle=pi_angle*180/3.14159;//�Ƕȣ���ע�����������Һ������ƣ�asin,acos
	return angle;

}
vector<int> L_ScanFun(vector<int>&BeginPoint,GLbyte colorArr[],const int num)
{
	int x=BeginPoint[0],y=BeginPoint[1];//ɨ�����ʼ��
	int a=BeginPoint[2],b=BeginPoint[3];//��ɨ�����ʼ����
	vector<int> Arr(num*2);
	for(int i = 0; i < num ; i++)
	{
	   L_scan_add (x,y,a,b,i,Arr,colorArr);
		a=Arr[2*i]-x;b=Arr[2*i+1]-y;
		x=Arr[2*i];y=Arr[2*i+1];
	}
	return Arr;
}
vector<int> R_ScanFun(vector<int>&BeginPoint,GLbyte colorArr[],const int num)
{
	int x=BeginPoint[0],y=BeginPoint[1];//ɨ�����ʼ��
	int a=BeginPoint[2],b=BeginPoint[3];//��ɨ�����ʼ����
	vector<int> Arr(num*2);
	for(int i = 0; i < num ; i++)
	{
	   R_scan_add (x,y,a,b,i,Arr,colorArr);
		a=Arr[2*i]-x;b=Arr[2*i+1]-y;
		x=Arr[2*i];y=Arr[2*i+1];
	}
	return Arr;
}
vector<int> L_OnePoint(int y,GLbyte colorArr[])//��������������꣬�Լ�ͼ������ء����������㣬�ҷŵ�һ��������
{
	vector<int> begin_point(2);
	 for (int i=0;i<=center ;i++)//ȡ�������
		{
			if(colorArr[(y*WINWIDTH +i)*4]<20&&colorArr[(y *WINWIDTH +i)*4+1]>60&&colorArr[(y *WINWIDTH +i)*4+2]<20)
			{}//������ɫ������ֹ										 
			else{begin_point[0]=i;begin_point[1]=y;break;}
		}
	 return begin_point;
}
vector<int> R_OnePoint(int y,GLbyte colorArr[])//��������������꣬�Լ�ͼ������ء����������㣬�ҷŵ�һ��������
{
	vector<int> begin_point(2);
	 for (int i=cut1;i>=0 ;i--)//ȡ������
		{
			if(colorArr[(y*WINWIDTH +i)*4]<20&&colorArr[(y *WINWIDTH +i)*4+1]>60&&colorArr[(y *WINWIDTH +i)*4+2]<20)
			{}//������ɫ������ֹ										 
			else{begin_point[0]=i;begin_point[1]=y;break;}
		}
	 return begin_point;
}
int measure_jian(GLbyte  colorArr[])
{
	extern int s_begin;
    extern int s_end;
	const int len = 80;
	double x_left[len] = {0}  ; double y_left[len] = {0} ;
	double x_right[len] = {0} ; double y_right[len] = {0};//Ҫ�ǵã����Ҫɾ��
	double P_L[6]={0},P_R[6]={0};
	GLbyte* judgeArr1;
	judgeArr1 = new GLbyte[cut1];  
	int flag1=0,flag2=0;
	vector<int> left_arr(len); vector<int> right_arr(len);
	vector<int> start_point = L_OnePoint(s_begin,colorArr);
	start_point.push_back (1); start_point.push_back(0);
	left_arr = L_ScanFun(start_point,colorArr,len);
	//��������ұߵ�����
	start_point = R_OnePoint(s_begin,colorArr);
	start_point.push_back (-1); start_point.push_back(0);
	right_arr = R_ScanFun(start_point,colorArr,len);
	//���潫�������ϵ�������
	for(int i = 0; i<len; i++)
	{
	  x_left[i] = left_arr[2*i];
	  y_left[i] = left_arr[2*i+1];
	  x_right[i] = right_arr[2*i];
	  cout<<x_right[i]<<endl;
	  y_right[i] = right_arr[2*i+1];
	}
	//int f_t=0;
	//int f_tt=0;
	//for(int j=s_begin ;j>s_end;j--)
	//{            f_t++;
	//			  for (int i=0;i<=center ;i++)//ȡ�������
	//			  {
	//				 if(colorArr[(j*WINWIDTH +i)*4]<20&&colorArr[(j *WINWIDTH +i)*4+1]>60&&colorArr[(j *WINWIDTH +i)*4+2]<20)
	//				 {}//������ɫ������ֹ										 
	//				 else{x_left[flag1]=i;y_left[flag1]=j;flag1++;break;}
	//			  }

	//			  for (int i=cut1;i>center;i--)//ȡ�Ҽ���ұ�
	//			  {f_tt++;
	//			     if (colorArr[(j*WINWIDTH +i)*4]<20&&colorArr[(j *WINWIDTH +i)*4+1]>60&&colorArr[(j *WINWIDTH +i)*4+2]<20)
	//				 {}//������ɫ������ֹ					 
	//				 else{ x_right[flag2]=i;y_right[flag2]=j;flag2++;break;}
	//			  }
	//			 
	//}
	int sizenum=len;
	int dimension=4;
//	int jian_y=(jian[1]+jian[3])/2-y_offset ;
	polyfit (sizenum,x_left,y_left,dimension,P_L);
	polyfit (sizenum,x_right,y_right,dimension,P_R);
	double diff_data_L[len]={0};
	double diff_data_R[len]={0};
	for (int i=0;i<len;i++)
	{ 
	  diff_data_L[i]=diff1(x_left[i],P_L); 
	}
	for (int i=0;i<len;i++)//����ע��x��ȡֵ��Χ
	{  
		diff_data_R[i]=diff1(x_right[i],P_R);//����ע��x��y��һһ��Ӧ
	}
	int diff_x_L=0;
	int diff_x_R=0;

	for(int i=len-5;i>=0;i--)
	{
		if (diff_data_L[i]<=1){diff_x_L=x_left[i];L_jian_y =y_left[i];break;}
	}
	for(int i=len-5;i>=0;i--)
	{   
		if (fabs(diff_data_R[i])<=1){diff_x_R=x_right[i];R_jian_y=y_right[i];break;}	
	}

/**************�����ǲ��Ժ���****************/
	vector<int> L_edge = L_OnePoint(L_jian_y,colorArr);//Ϊ�˱�֤���ڱ�Ե
	vector<int> R_edge = R_OnePoint(R_jian_y,colorArr);
	vector<int> BeginPoint(4);
	BeginPoint[0]=L_edge[0];BeginPoint[1]=L_edge[1];BeginPoint[2]=1;BeginPoint[3]=0;
	double test_angle1 = grad(BeginPoint,L_ScanFun,colorArr,40);//��ʼλ�úͷ���
	double test_angle2 = grad(BeginPoint,R_ScanFun,colorArr,40);
	double average_angle_L = (test_angle1 + test_angle2)/2;
	BeginPoint[0]=R_edge[0];BeginPoint[1]=R_edge[1];BeginPoint[2]=-1;BeginPoint[3]=0;
	double test_angle3 = grad(BeginPoint,L_ScanFun,colorArr,40);//��ʼλ�úͷ���
	double test_angle4 = grad(BeginPoint,R_ScanFun,colorArr,40);
	double average_angle_R = (test_angle3 + test_angle4)/2;
	double L_grad = tan((average_angle_L+10)/180*3.14159);
	double R_grad = tan((abs(average_angle_R)+10)/180*3.14159);
	for(int i=len-5;i>=0;i--)
	{
		if (diff_data_L[i]<=L_grad){diff_x_L=x_left[i];L_jian_y =y_left[i];break;}
	}
	for(int i=len-5;i>=0;i--)
	{   
		if (fabs(diff_data_R[i])<=R_grad){diff_x_R=x_right[i];R_jian_y=y_right[i];break;}	
	}
///*******************************************/
	vector<int> L_edge_last = L_OnePoint(L_jian_y,colorArr);//Ϊ�˱�֤���ڱ�Ե
	vector<int> R_edge_last = R_OnePoint(R_jian_y,colorArr);
	int k=diff_x_R-diff_x_L;	
	L_jian_x=L_edge_last[0];
	R_jian_x=R_edge_last[0];
	L_jian_y=L_edge_last[1];
	R_jian_y=R_edge_last[1];
	/*L_jian_x = diff_x_L;
	R_jian_x = diff_x_R;
	int k=diff_x_R-diff_x_L;*/	
	int jian_y_l=670-L_jian_y;
	int jian_y_r=670-R_jian_y;
	front_jian=k;

	return k;
	/*double cur_data_L[40]={0};
	double cur_data_R[40]={0};
	for(int i=5;i<35;i++)//������������Ե��Ӱ��
	{
	  cur_data_L[i]=curvature(x_left[i],P_L);
	  cur_data_R[i]=curvature(x_right[i],P_R);
	}
	L_jian_x =x_left[my_max(cur_data_L)];
	R_jian_x=x_right[my_max(cur_data_R)];
	L_jian_y =y_left[my_max(cur_data_L)];
	R_jian_y =y_right[my_max(cur_data_R)];
	int T_L_jian_y =670-y_left[my_max(cur_data_L)];
	int T_R_jian_y =670-y_right[my_max(cur_data_R)];
	return R_jian_x-L_jian_x;*/
	/*double cur_data_L[40]={0};
	double cur_data_R[40]={0};
	for (int i=0;i<x_left[my_max(x_left)];i++)
	{  if(i>=40) break;
	  cur_data_L[i]=curvature(i,P_L); 
	}
	for (int i=x_right[my_min(x_right)];i<x_right[my_max(x_right)];i++)//����ע��x��ȡֵ��Χ
	{   if(i>=x_right[my_min(x_right)]+40) break;
		int j=i-x_right[my_min(x_right)];
		cur_data_R[j]=curvature (i,P_R);//����ע��x��y��һһ��Ӧ
	}	
	for(int i=0;i<5;i++){cur_data_L[i]=0;cur_data_R[i]=0;}
	int cur_x_L=my_max(cur_data_L);
	int cur_x_R=my_max(cur_data_R);
	return cur_x_R-cur_x_L+x_right[my_min(x_right)];//Ϊ��ʹ�����λ��һһ��Ӧ������������
	*/
/*
	int x1=0,x2=0;//�����Ŀ��
	for(int i=x_left[my_min(x_left)];i<x_left[my_max(x_left)];i++)
	{
	  if( evaluation(i,P_L)>=jian_y)
	  {
	    x1=i;break;
	  }
	}
	for(int i=x_right[my_min(x_right)];i<x_right[my_max(x_right)];i++)
	{
	  if( evaluation(i,P_R)<=jian_y)
	  {
	    x2=i;break;
	  }
	}
	L_jian_y =R_jian_y=jian_y+y_offset ;
	L_jian_x=x1+x_offset;
	R_jian_x=x2+x_offset;

	return x2-x1;*/

}//������λ��ƫ����

int measure_xiong(GLbyte colorArr[])
{
	int L_ye_x=0,L_ye_y=0;
	int R_ye_x=0,R_ye_y=0;
	for(int k=L_jian_y-15;k>0;k--)//������  ���
    {
	  for(int i=L_jian_x+5;i<L_jian_x+25;i++)	//�������ɨ������         
		{//�ж�Ϊ��ɫ
		    if(colorArr[(k*WINWIDTH +i)*4]<10&&colorArr[(k*WINWIDTH +i)*4+1]>30&&colorArr[(k *WINWIDTH +i)*4+2]<10)
			{
			  L_ye_x=i;L_ye_y=k;k=-1;break ;//����get��һ��С���ɣ������������˫��ѭ���ķ���
			}
		}
	 } 

	for(int k=R_jian_y-5;k>0;k--)//������   �Ҽ�
    {
	  for(int i=R_jian_x-5;i>R_jian_x-25;i--)	//�������ɨ������         
		{
		    if(colorArr[(k*WINWIDTH +i)*4]<10&&colorArr[(k*WINWIDTH +i)*4+1]>30&&colorArr[(k *WINWIDTH +i)*4+2]<10)
			{
			  R_ye_x=i;R_ye_y=k;k=-1;break;
			}
		}
	 } 
	double P1[2]={0};
	double P2[2]={0};//����ֱ�ߵ�ϵ��������������������
	int a,b,c,d;
	a=L_jian_x ;b=L_jian_y ;c=L_ye_x ;d=L_ye_y ;
	P1[0]=(double)(a-c)/(b-d);
	P1[1]=(double)(b*c-a*d)/(b-d);
	a=R_jian_x ;b=R_jian_y ;c=R_ye_x ;d=R_ye_y ;
	P2[0]=(double)(a-c)/(b-d);
	P2[1]=(double)(b*c-a*d)/(b-d);
	int xiong_y=kuagu_y+(B_jian_y-kuagu_y)*38/52.5;//������ռ����ı���Ϊ38/52.5������ص�y����
	int L_xiong_x=P1[0]*xiong_y+P1[1];//��������ֱ�߷���
	int R_xiong_x=P2[0]*xiong_y+P2[1];
	//int front_xiong=R_xiong_x-L_xiong_x;//�����Ѿ���������صĿ�ȣ�����������صĿ��
	int front_xiong=R_ye_x-L_ye_x;//ע�⣬�������Χ���������޸ģ���Ҹ�µ�Ϊ׼��������������룬�ݲ��޸�
	int ce_xiong_begin=0,ce_xiong_end=0;

	for(int i=cut1;i<cut2;i++)
	{//����ע�⣬�жϲ�����ɫ��Ҫ
	    if (colorArr[(xiong_y*WINWIDTH +i)*4]<20&&colorArr[(xiong_y *WINWIDTH +i)*4+1]>60&&colorArr[(xiong_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_xiong_begin=i;break;}
	}
	for(int i=cut2;i>cut1;i--)
	{
	  if (colorArr[(xiong_y*WINWIDTH +i)*4]<20&&colorArr[(xiong_y *WINWIDTH +i)*4+1]>60&&colorArr[(xiong_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_xiong_end=i;break;}
	}
	int ce_xiong=ce_xiong_end-ce_xiong_begin;
	
	int xiong_1= front_jian*35/46;
	int xiong_2=front_jian*29/46;
	xiong_kuan=xiong_1;
	//return (int)(front_xiong*2.0/3.0+ce_xiong)*2;
	xiong_wei_global = int(xiong_1*2.0/3.0+xiong_2)*2;
	double xiong_wei_global_1=int(front_xiong*2.0/3.0+ce_xiong)*2;//���ֵ�Ǹ���ͼ����ȷ����
	double xiong_wei_global_2=xiong_wei_global;
	return (xiong_wei_global_1+xiong_wei_global_2)*0.5;
}

double measure_xiongkuan()
{
	return xiong_kuan*1.4;
}

int measure_arm(GLbyte  colorArr[])
{
   // int a=L_jian_x,b=L_jian_y,c=zhou[0],d=zhou[1],e=wan[0],f=wan[1];
   //return sqrt((a -c)*(a -c)+(b -d)*(b -d) )+sqrt((c -e)*(c -e)+(d -f)*(d -f) );
	/*for(int i=R_jian_y-20 ;i>0;i--)
	{
	  
	}
	arc_scan(294,419,279,404,278,425,colorArr);*/
	int B_x=0,B_y=0;
	int Arr[500];
	int x,y;
	int a=0,b=-1;
	int arm_start = R_jian_y - 90;//Ϊ�˷�ֹ���ӵ�Ӱ�죬������һ��
	for(int i=cut1;i>0;i--)
	{
	   if(colorArr[(arm_start*WINWIDTH +i)*4]<20&&colorArr[(arm_start*WINWIDTH +i)*4+1]>60&&colorArr[(arm_start *WINWIDTH +i)*4+2]<20){}	   
	   else{B_x=i;B_y=arm_start;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
	}
	x=B_x;y=B_y;
	for(int i=0;i<250;i++)
	{
	    R_scan (x,y,a,b,i,Arr,colorArr);
		a=Arr[2*i]-x;b=Arr[2*i+1]-y;
		x=Arr[2*i];y=Arr[2*i+1];
	}
	int ana[250];
	for(int i=0;i<250;i++)   {ana[i]=Arr[2*i];}
	int flag=0;
	int near_f=0;
	for(int i=1;i<250;i++)
	{
		if (ana[i]-ana[i-1]<0){flag++; }//���x�����С��˵���Ѿ���ʼ���˻���λ������				   
		else
		{
			if(flag==0){flag=0;}//��֤����С����
			else{flag--;}
		}
		if (flag>=4) {near_f=i;break;}//����ʱ�򣬾Ϳ���ȷ���ǳ��ڻ�������λ�ø�����
					
	}
	int f=0;
	do{near_f++;}
	while((ana[near_f]-ana[near_f+4])>=2);
	/*while((ana[near_f+4]<=ana[near_f]))
	{
		//if(ana[near_f+1]=ana[near_f]){f++;}
		//else{f=0;}
		near_f++;
	    
	}*/
	int hu_x=Arr[2*near_f];
	int hu_y=Arr[2*near_f+1];
	int a1=R_jian_x ,b1=R_jian_y ,c1=hu_x,d1=hu_y;
	int test_y =670-hu_y;
	  return sqrt((a1 -c1)*(a1 -c1)+(b1 -d1)*(b1-d1) );
}

int measure_zhong_yao(GLbyte colorArr[])
{
	double P_L[3]={0},P_R[3]={0};
	double left_x[10]={0},right_x[10]={0},left_y[10]={0},right_y[10]={0};
	int f1=0,f2=0;
  int zhong_yao_y=kuagu_y+(B_jian_y-kuagu_y)*23/52.5;//��������ռ����ı���Ϊ23/52.5�����������y����
	for(int i=zhong_yao_y+5;i>zhong_yao_y-5;i--)
	{
			for(int j=kua[0];j>0;j--)
			{
			  if(colorArr[(i*WINWIDTH +j)*4]<20&&colorArr[(i*WINWIDTH +j)*4+1]>60&&colorArr[(i *WINWIDTH +j)*4+2]<20)
			  {left_x[f1]=j;left_y[f1]=i;f1++;break;}//�ж�����ɫ
			}
		  

		  for(int k=kua[2];k<cut1;k++)
		  {
		    if(colorArr[(i*WINWIDTH +k)*4]<20&&colorArr[(k*WINWIDTH +i)*4+1]>60&&colorArr[(k *WINWIDTH +i)*4+2]<20)
			{right_x[f2]=k;right_y[f2]=i;f2++;break;}
		  }
	 }

	int sizenum=10;
	int dimension=2;
	
	polyfit (sizenum,left_y,left_x,dimension,P_L);
	polyfit (sizenum,right_y,right_x,dimension,P_R);
	//polyfit (sizenum,left_x,left_y,dimension,P_L);
	//polyfit (sizenum,right_x,right_y,dimension,P_R);
	double y1=zhong_yao_y ,a1=P_L[0],b1=P_L[1],c1=P_L[2];
	double y2=zhong_yao_y ,a2=P_R[0],b2=P_R[1],c2=P_R[2];
	double x1=a1+b1*y1+c1*y1*y1;
	double x2=a2+b2*y2+c2*y2*y2;
	int ce_zhong_yao_begin=0,ce_zhong_yao_end=0;
	for(int i=cut1;i<cut2;i++)
	{
	   if(colorArr[(zhong_yao_y*WINWIDTH +i)*4]<20&&colorArr[(zhong_yao_y*WINWIDTH +i)*4+1]>60&&colorArr[(zhong_yao_y *WINWIDTH +i)*4+2]<20){}
	   
	   else{ce_zhong_yao_begin=i;break;}//�жϲ�����ɫ
	}
	for(int i=cut2;i>cut1;i--)
	{
		if(colorArr[(zhong_yao_y*WINWIDTH +i)*4]<20&&colorArr[(zhong_yao_y*WINWIDTH +i)*4+1]>60&&colorArr[(zhong_yao_y *WINWIDTH +i)*4+2]<20) {}
		else {ce_zhong_yao_end=i;break;}//������ɫ������ֹ
	}
	int ce_zhong_yao=ce_zhong_yao_end -ce_zhong_yao_begin ;
	int zhong_yao_1=front_jian *30/46;
	int zhong_yao_2=front_jian *22/46;
	int a =  zhong_yao_1;
	int b = zhong_yao_2;
	double result = 2*b+a*1.5;//2*3.14*b +4*(a-b);
	//return int((x2-x1)*2.0/3.0+ce_zhong_yao )*2;
	//return int(zhong_yao_1*2.0/3.0+zhong_yao_2 )*2;
	return int(result);
}

int measure_yao(GLbyte colorArr[])
{
    double P_L[3]={0},P_R[3]={0};
	double left_x[10]={0},right_x[10]={0},left_y[10]={0},right_y[10]={0};
	int f1=0,f2=0;
	yao_y=kuagu_y+(B_jian_y-kuagu_y)*14/52.5;//������ռ����ı���Ϊ14/52.5���������y����
	global_yao_y=yao_y;
	for(int i=yao_y+5;i>yao_y-5;i--)//ȡ��������10�����أ��������
	{
			for(int j=center ;j>0;j--)
			{
			  if(colorArr[(i*WINWIDTH +j)*4]<20&&colorArr[(i*WINWIDTH +j)*4+1]>60&&colorArr[(i *WINWIDTH +j)*4+2]<20)
			  {left_x[f1]=j;left_y[f1]=i;f1++;break;}
			}
		  

		  for(int k=center;k<cut1;k++)
		  {
		    if(colorArr[(i*WINWIDTH +k)*4]<20&&colorArr[(k*WINWIDTH +i)*4+1]>60&&colorArr[(k *WINWIDTH +i)*4+2]<20)
			{right_x[f2]=k;right_y[f2]=i;f2++;break;}
		  }
		  
	 }

    int sizenum=10;
	int dimension=2;
	
	polyfit (sizenum,left_y,left_x,dimension,P_L);
	polyfit (sizenum,right_y,right_x,dimension,P_R);
	double y1=yao_y ,a1=P_L[0],b1=P_L[1],c1=P_L[2];
	double y2=yao_y ,a2=P_R[0],b2=P_R[1],c2=P_R[2];
	double x1=a1+b1*y1+c1*y1*y1;
	double x2=a2+b2*y2+c2*y2*y2;
	int ce_yao_begin=0,ce_yao_end=0;
	for(int i=cut1;i<cut2;i++)
	{	   
	    if (colorArr[(yao_y*WINWIDTH +i)*4]<20&&colorArr[(yao_y *WINWIDTH +i)*4+1]>60&&colorArr[(yao_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_yao_begin=i;break;}
	}
	for(int i=cut2;i>cut1;i--)
	{
	    if (colorArr[(yao_y*WINWIDTH +i)*4]<20&&colorArr[(yao_y *WINWIDTH +i)*4+1]>60&&colorArr[(yao_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_yao_end=i;break;}
	}
	int ce_yao=ce_yao_end -ce_yao_begin ;
	int yao_1=front_jian*33/46;
	int yao_2=front_jian*24/46;
	//return int((x2-x1)*2.0/3.0+ce_yao )*2;
	return int(yao_1*2.0/3.0+yao_2 )*2;
   
}

int measure_leg()
{
	return yao_y -GROUND;
}

int measure_tun(GLbyte colorArr[])
{
	
	    double P_L[3]={0},P_R[3]={0};
	double left_x[10]={0},right_x[10]={0},left_y[10]={0},right_y[10]={0};
	int f1=0,f2=0;
	int tun_y=0;//���������Χ�Ĵ�С
	//���ȣ�Ҫȷ���β���y���꣬��������y��������ɨ�裬����ͻ���ĵط��������ҵ��β���y���꣬����Ϊ�˷��㣬��yao_y����tun_y
	for(int j=WINWIDTH-10;j>0;j--)//�Ӻ�����ǰ����,������
	{
	  for(int i=global_yao_y-80;i<global_yao_y;i++ )//��������������������
	  {
	     if (colorArr[(i*WINWIDTH +j)*4]<20&&colorArr[(i *WINWIDTH +j)*4+1]>60&&colorArr[(i *WINWIDTH +j)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{tun_y=i;j=0;;break;}
	  }
	}

	
	for(int i=tun_y+5;i>tun_y-5;i--)//ȡ�����
	{
			for(int j=center;j>0;j--)
			{
			  if(colorArr[(i*WINWIDTH +j)*4]<10&&colorArr[(i*WINWIDTH +j)*4+1]>30&&colorArr[(i *WINWIDTH +j)*4+2]<10)
			  {left_x[f1]=j;left_y[f1]=i;f1++;break;}
			}
		  

		  for(int k=center;k<cut1;k++)
		  {
		    if(colorArr[(i*WINWIDTH +k)*4]<10&&colorArr[(i*WINWIDTH +k)*4+1]>30&&colorArr[(i *WINWIDTH +k)*4+2]<10)
			{right_x[f2]=k;right_y[f2]=i;f2++;break;}
		  }
		  
	 }

    int sizenum=10;
	int dimension=2;
	
	polyfit (sizenum,left_y,left_x,dimension,P_L);
	polyfit (sizenum,right_y,right_x,dimension,P_R);
	double y1=tun_y ,a1=P_L[0],b1=P_L[1],c1=P_L[2];
	double y2=tun_y ,a2=P_R[0],b2=P_R[1],c2=P_R[2];
	tun_Y = tun_y;
	double x1=a1+b1*y1+c1*y1*y1;
	double x2=a2+b2*y2+c2*y2*y2;
	int ce_yao_begin=0,ce_yao_end=0;
	for(int i=cut1;i<cut2;i++)
	{
	  
	   if (colorArr[(tun_y*WINWIDTH +i)*4]<20&&colorArr[(tun_y *WINWIDTH +i)*4+1]>60&&colorArr[(tun_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_yao_begin=i;break;}
	}
	for(int i=cut2;i>cut1;i--)
	{
	  if (colorArr[(tun_y*WINWIDTH +i)*4]<20&&colorArr[(tun_y *WINWIDTH +i)*4+1]>60&&colorArr[(tun_y *WINWIDTH +i)*4+2]<20)
					 { }	//������ɫ������ֹ			
					 else{ce_yao_end=i;break;}
	}
	int ce_yao=ce_yao_end -ce_yao_begin ;
	double a = (x2-x1);//��
	double b = (ce_yao);//��
	double result = 3.349+2.465*a-0.025*a*a+0.043*a*b;
	//double b1= a*0.343;
	//double b2 = b-b1;
	double A_1 = a/2.0;

	//return int(result);
	//return int((x2-x1)*2.0/3.0+ce_yao )*2;
	//return 2*(a+b);
	//return int(1.14*b+4*A_1);
	return xiong_wei_global + 18;
}

int measure_linwei(GLbyte colorArr[])
{
	//���ȸ��ݼ�����꣬������5�����أ�Ȼ����б�Եɨ��
	int start=L_jian_y+5;//��Լ�����￪ʼ,������ʼ�㣬Ԥɨ��
	int start_R=R_jian_y +5;//�Ҽ����ʼ�㣬Ԥɨ��
	int B_x=0,B_y=0;//ȷ�����ɨ����ʼ��
	int B_x_R=0,B_y_R=0;//ȷ���Ҽ�ɨ����ʼ��
	int x,y;//�ݴ滷ɨ��ĵ�
	int x_R,y_R;//
	int a=1,b=0;//��ɨ�����ʼ����
	int a_R =-1,b_R =0;//
	int Arr[200];//����ȫ���Ļ�ɨ��ĵ�
	int Arr_R[200];//
	for(int i=0;i<cut1;i++)
	{
	   if(colorArr[(start*WINWIDTH +i)*4]<20&&colorArr[(start*WINWIDTH +i)*4+1]>60&&colorArr[(start *WINWIDTH +i)*4+2]<20){}	   
	   else{B_x=i;B_y=start;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
	}
	for(int i=cut1;i>0;i--)//Ѱ���ұߵ����
	{
	   if(colorArr[(start_R*WINWIDTH +i)*4]<20&&colorArr[(start_R*WINWIDTH +i)*4+1]>60&&colorArr[(start_R *WINWIDTH +i)*4+2]<20){}	   
	   else{B_x_R=i;B_y_R=start_R;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
	}
	x=B_x;y=B_y;
	for(int i=0;i<100;i++)//�һ�ɨ��ĺ��Ĳ���
	{
	    R_scan (x,y,a,b,i,Arr,colorArr);
		a=Arr[2*i]-x;b=Arr[2*i+1]-y;
		x=Arr[2*i];y=Arr[2*i+1];
	}
	x_R=B_x_R;y_R=B_y_R;
	for(int i=0;i<100;i++)//�һ�ɨ��ĺ��Ĳ���
	{
	    L_scan (x_R,y_R,a_R,b_R,i,Arr_R,colorArr);
		a_R=Arr_R[2*i]-x_R;b_R=Arr_R[2*i+1]-y_R;
		x_R=Arr_R[2*i];y_R=Arr_R[2*i+1];
	}


	int arry_x[100]={0};//ȡ100��x����ĵ�
	for(int i=0; i<100;i++)
	{
	  arry_x[i]=Arr[2*i];
	}
	int arry_x_R[100]={0};
	for(int i=0; i<100;i++)
	{
	  arry_x_R[i]=Arr_R[2*i];
	}

	int near_f=0;
	do{near_f++;}
	while((arry_x[near_f+7]-arry_x[near_f])>4);
	 L_neck_x=Arr[2*(near_f+5)];
	 L_neck_y=Arr[2*(near_f+5)+1];
	 

	int near_f_R=0;
	do{near_f_R++;}
	while((arry_x_R[near_f_R]-arry_x_R[near_f_R+7])>4);
	 R_neck_x=Arr_R[2*(near_f_R+5)];
	 R_neck_y=Arr_R[2*(near_f_R+5)+1];

	
	int test_x=L_neck_x;
	int test_y=670-L_neck_y;
	int test_x1=R_neck_x ;
	int test_y1=670-R_neck_y ;
	int r = R_neck_x  - L_neck_x ;
	return 3.14*r ;
}

double measure_qian_shen(GLbyte colorArr[])
{
	int begin=L_neck_y;
	int end=tun_Y;
	int step = (begin-end)/19;//����һ��Ҫע���ˣ���ȡ20���㣬��19�ξ��룡
	int position[40] ={0};
	int position_test[40]={0};
	int k = 0;
	int test = 0;
	for(int i=begin;i>=end;i-=step)
	{test ++;
		  for(int j=cut1;j<cut2;j++)
		{
		   if(colorArr[(i*WINWIDTH +j)*4]<20&&colorArr[(i*WINWIDTH +j)*4+1]>60&&colorArr[(i *WINWIDTH +j)*4+2]<20){}	   
		   else{position[2*k]=j;position[2*k+1]=i;position_test[2*k]=j;position_test[2*k+1]=670-i;k++;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
			
		  }
	}
	double distance[19]={0};
	for (int i=0;i<19;i++)
	{
		double x_1=position[2*i];
		double y_1=position[2*i+1];
		double x_2=position[2*i+2];
		double y_2=position[2*i+3];
		distance[i]=sqrt((x_2-x_1)*(x_2-x_1)+(y_2-y_1)*(y_2-y_1));
	}
	double sum = 0;
	for (int i = 0;i<19;i++)
	{
		sum = sum+distance[i];
	}
	//���棬�ٲ���һ�ξ���
	int a=0;
	int b=0;
	for (int i=cut1;i<670;i++)
	{
	   if(colorArr[(begin*WINWIDTH +i)*4]<20&&colorArr[(begin*WINWIDTH +i)*4+1]>60&&colorArr[(begin *WINWIDTH +i)*4+2]<20){}	   
		   else{a=i;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
	}
		for (int i=670;i>cut1;i--)
	{
	   if(colorArr[(begin*WINWIDTH +i)*4]<20&&colorArr[(begin*WINWIDTH +i)*4+1]>60&&colorArr[(begin *WINWIDTH +i)*4+2]<20){}	   
		   else{b=i;break;}//�жϲ�����ɫ,�ҵ�ɨ�����ʼ��
	}
  return sum+(b-a)/2;
}

int measure_lidang()
{
  return front_jian*20/43;
}

double measure_jin_jian()
{
  int ax=L_jian_x;
  int ay=L_jian_y;
  int bx=L_neck_x;
  int by=L_neck_y;
  int cx=R_neck_x;
  int cy=R_neck_y;
  int dx=R_jian_x;
  int dy=R_jian_y;
  Line line1;
  Line line2;

    //line1
    line1.point1.x = ax;
    line1.point1.y = ay;
    line1.point2.x = bx;
    line1.point2.y = by;

    //line2
    line2.point1.x = cx;
    line2.point1.y = cy;
    line2.point2.x = dx;
    line2.point2.y = dy;
	double average_y = (by+cy)/2;//ȡy�������ֵ
    point CointP = getCross(line1, line2);
	double c_a = (cx - bx)/2;//��Բ������
	double c_b = (CointP.y - average_y)/2;
	double circ = 3.14*c_b+2*(c_a-c_b);

  
	//return sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay))+sqrt((bx-cx)*(bx-cx)+(by-cy)*(by-cy))+sqrt((cx-dx)*(cx-dx)+(cy-dy)*(cy-dy));
  //return dx-ax;
	return circ+sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay))+sqrt((cx-dx)*(cx-dx)+(cy-dy)*(cy-dy));
}

