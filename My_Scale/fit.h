#include <math.h>
#include <stdio.h>
void polyfit(int n, double *x, double *y, int poly_n, double p[]);  
void gauss_solve(int n,double A[],double x[],double b[]);  
double curvature(double x,double p[]);     //////////////拟合函数，这三个函数不需要，只需要上面两个即可
double evaluation(double x,double p[]);    //////////////
double diff1(double x ,double p[]);        //////////////

/*==================polyfit(n,x,y,poly_n,a)===================*/  
/*=======拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n========*/  
/*=====n是数据个数 xy是数据值 poly_n是多项式的项数======*/  
/*===返回a0,a1,a2,……a[poly_n]，系数比项数多一（常数项）=====*/  
void polyfit(int n,double x[],double y[],int poly_n,double p[])  
{  
    int i,j;  
    double *tempx,*tempy,*sumxx,*sumxy,*ata;  
      
    tempx = (double *)calloc(n , sizeof(double));  
    sumxx = (double *)calloc((poly_n*2+1) , sizeof(double));  
    tempy = (double *)calloc(n , sizeof(double));  
    sumxy = (double *)calloc((poly_n+1) , sizeof(double));  
    ata = (double *)calloc( (poly_n+1)*(poly_n+1) , sizeof(double) );  
    for (i=0;i<n;i++)  
    {  
        tempx[i]=1;  
        tempy[i]=y[i];  
    }  
    for (i=0;i<2*poly_n+1;i++)  
    {  
        for (sumxx[i]=0,j=0;j<n;j++)  
        {  
            sumxx[i]+=tempx[j];  
            tempx[j]*=x[j];  
        }  
    }  
  
    for (i=0;i<poly_n+1;i++)  
    {  
        for (sumxy[i]=0,j=0;j<n;j++)  
        {  
            sumxy[i]+=tempy[j];  
            tempy[j]*=x[j];  
        }  
    }  
  
    for (i=0;i<poly_n+1;i++)  
    {  
        for (j=0;j<poly_n+1;j++)  
        {  
            ata[i*(poly_n+1)+j]=sumxx[i+j];  
        }  
    }  
    gauss_solve(poly_n+1,ata,p,sumxy);  
      
    free(tempx);  
    free(sumxx);  
    free(tempy);  
    free(sumxy);  
    free(ata);  
}  
  
/*============================================================*/  
////    高斯消元法计算得到   n 次多项式的系数  
////    n: 系数的个数  
////    ata: 线性矩阵  
////    sumxy: 线性方程组的Y值  
////    p: 返回拟合的结果  
/*============================================================*/  
void gauss_solve(int n,double A[],double x[],double b[])  
{  
    int i,j,k,r;  
    double max;  
    for (k=0;k<n-1;k++)  
    {  
        max=fabs(A[k*n+k]);                 // find maxmum   
        r=k;  
        for (i=k+1;i<n-1;i++)  
        {  
            if (max<fabs(A[i*n+i]))  
            {  
                max=fabs(A[i*n+i]);  
                r=i;  
            }  
        }  
        if (r!=k)  
        {  
            for (i=0;i<n;i++)        //change array:A[k]&A[r]  
            {  
                max=A[k*n+i];  
                A[k*n+i]=A[r*n+i];  
                A[r*n+i]=max;  
            }  
  
            max=b[k];                    //change array:b[k]&b[r]  
            b[k]=b[r];  
            b[r]=max;  
        }  
          
        for (i=k+1;i<n;i++)  
        {  
            for (j=k+1;j<n;j++)  
                A[i*n+j]-=A[i*n+k]*A[k*n+j]/A[k*n+k];  
            b[i]-=A[i*n+k]*b[k]/A[k*n+k];  
        }  
    }   
      
    for (i=n-1;i>=0;x[i]/=A[i*n+i],i--)  
    {  
        for (j=i+1,x[i]=b[i];j<n;j++)  
            x[i]-=A[i*n+j]*x[j];  
    }  
  
}  
double curvature(double x,double p[])
{
  double k1,k2;
  k1=fabs(2*p[2]+6*p[3]*x+12*p[4]*pow(x,2));
  k2=pow(1+pow(p[1]+2*p[2]*x+3*p[3]*pow(x,2)+4*p[4]*pow(x,3),2),1.5);
  return k1/k2;
  
}
double diff1(double x ,double p[])
{
   double k1;
   k1=p[1]+2*p[2]*x+3*p[3]*pow(x,2)+4*p[4]*pow(x,3);
   return k1;
}

double evaluation(double x,double p[])
{
	return p[0]+x*p[1]+pow(x,2)*p[2]+pow(x,3)*p[3]+pow(x,4)*p[4];
}
int my_min(double a[])
{
  int min_flag=0;
   //for(int i=1;i<40;i++)
	   
	for(int i=1;i<40;i++)
  {
    if(a[i]<a[min_flag])
	{
	 min_flag=i;
	}
  }
   return min_flag;
}
int my_max(double a[])
{ int max_flag=0;
  for(int i=1;i<40;i++)
  {
    if(a[i]>a[max_flag])
	{
	 max_flag=i;
	}
  }
  return max_flag ;
}
 int my_max1(double a[])
{ int max_flag=0;
  for(int i=1;i<80;i++)
  {
    if(a[i]>a[max_flag])
	{
	 max_flag=i;//找到最大值得元素坐标
	}
  }
  return max_flag;
 }
  int my_max_a(double a[],int n)
{ int max_flag=0;
  for(int i=1;i<n;i++)
  {
    if(a[i]>a[max_flag])//找到最大值的元素坐标，可调节
	{
	 max_flag=i;
	}
  }
  return max_flag;
 }
 void PolyFit(double *x, double *y, int n, double *a, int m, double *dt)
{
	int i, j, k;
	double z, p, c, g, q, d1, d2, s[20], t[20], b[20];
	for (i = 0; i <= m-1; i++)
	{
		a[i] = 0.0;
	}
	if (m > n)
	{
		m = n;
	}
	if (m > 20)
	{
		m = 20;
	}
	z = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		z = z+x[i]/(1.0 *n);
	}
	b[0] = 1.0;
	d1 = 1.0 * n;
	p = 0.0;
	c = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		p = p+(x[i]-z);
		c = c+y[i];
	}
	c = c/d1;
	p = p/d1;
	a[0] = c * b[0];
	if (m > 1)
	{
		t[1] = 1.0;
		t[0] = -p;
		d2 = 0.0;
		c = 0.0;
		g = 0.0;
		for (i = 0; i <= n-1; i++)
		{
			q = x[i]-z-p;
			d2 = d2+q * q;
			c = c+y[i] *q;
			g = g+(x[i]-z) *q * q;
		}
		c = c/d2;
		p = g/d2;
		q = d2/d1;
		d1 = d2;
		a[1] = c * t[1];
		a[0] = c * t[0]+a[0];
	}
	for (j = 2; j <= m-1; j++)
	{
		s[j] = t[j-1];
		s[j-1] = -p * t[j-1]+t[j-2];
		if (j >= 3)
			for (k = j-2; k >= 1; k--)
		    {
				s[k] = -p * t[k]+t[k-1]-q * b[k];
		    }
		s[0] = -p * t[0]-q * b[0];
		d2 = 0.0;
		c = 0.0;
		g = 0.0;
		for (i = 0; i <= n-1; i++)
		{
			q = s[j];
			for (k = j-1; k >= 0; k--)
			{
				q = q *(x[i]-z)+s[k];
			}
			d2 = d2+q * q;
			c = c+y[i] *q;
			g = g+(x[i]-z) *q * q;
		}
		c = c/d2;
		p = g/d2;
		q = d2/d1;
		d1 = d2;
		a[j] = c * s[j];
		t[j] = s[j];
		for (k = j-1; k >= 0; k--)
		{
			a[k] = c * s[k]+a[k];
			b[k] = t[k];
			t[k] = s[k];
		}
	}
	dt[0] = 0.0;
	dt[1] = 0.0;
	dt[2] = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		q = a[m-1];
		for (k = m-2; k >= 0; k--)
		{
			q = a[k]+q *(x[i]-z);
		}
		p = q-y[i];
		if (fabs(p) > dt[2])
		{
			dt[2] = fabs(p);
		}
		dt[0] = dt[0]+p * p;
		dt[1] = dt[1]+fabs(p);
	}
	return ;
}

struct point{
    double x;
    double y;
};

typedef struct line{
    point point1;
    point point2;
}Line;

//计算两条直线的交点
point getCross(Line line1, Line line2)
{
    point CrossP;
    //y = a * x + b;
    double a1 = (line1.point1.y - line1.point2.y) / (line1.point1.x - line1.point2.x);
    double b1 = line1.point1.y - a1 * (line1.point1.x);

    double a2 = (line2.point1.y - line2.point2.y) / (line2.point1.x - line2.point2.x);
    double b2 = line2.point1.y - a2 * (line2.point1.x);

    CrossP.x = (b1 - b2) / (a2 - a1);
    CrossP.y = a1 * CrossP.x + b1;
    return CrossP;
}
