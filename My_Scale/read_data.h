#include <stdio.h>
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
extern double O_jian[4];
extern double O_kua[4];
extern double O_xiong[2];
extern double O_zhou[4];
extern double O_wan[4];
extern double O_xi[4];
extern double O_foot[4];
int read_mydata()
{
	char ch;
	char a0=0,a1=0,a2=0;
	int i=0;
	char c1,c2,c3,c4;
	double n1,n_2,n_3,n4;
	ifstream infile("d://p//aaa.txt",ios::in|ios::_Nocreate );
	if(!infile)
	{
	  cerr<<"open data error!"<<endl;
	  exit(1);
	}
	while(infile.get(ch))
	{   a0=a1;
		a1=a2;
		a2=ch;
       if(a2==58)
	   {
		   int flag=(a0-48)*10+a1-48;
	     switch(flag)
		 {
		 case 2://×ó¼ç
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;//(1,(0.56,0.19),0.74),Ë³Ðòcnccncn
			 O_jian[0]=n_2;
			 O_jian[1]=n_3;
			 break;
		 case 5://ÓÒ¼ç
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;//(1,(0.56,0.19),0.74),Ë³Ðòcnccncn
			 O_jian[2]=n_2;
			 O_jian[3]=n_3;
			 break;
		 case 8:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_kua[0]=n_2;
			 O_kua[1]=n_3;
			 break;
		 case 11:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_kua[2]=n_2;
			 O_kua[3]=n_3;
			 break;
		 case 3:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_zhou[0]=n_2;
			 O_zhou[1]=n_3;
			 break;
		 case 6:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_zhou[2]=n_2;
			 O_zhou[3]=n_3;
			 break;
         case 4:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_wan[0]=n_2;
			 O_wan[1]=n_3;
			 break;
		 case 7:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_wan[2]=n_2;
			 O_wan[3]=n_3;
			 break;
		 case 9:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_xi[0]=n_2;
			 O_xi[1]=n_3;
			 break;
		 case 12:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_xi[2]=n_2;
			 O_xi[3]=n_3;
			 break;
		 case 10:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_foot[0]=n_2;
			 O_foot[1]=n_3;
			 break;
		 case 13:
			 infile >>c1>>n1>>c2>>c3>>n_2>>c4>>n_3;
			 O_foot[2]=n_2;
			 O_foot[3]=n_3;
			 break;
		 }
	   }
	  
	}
  return 0;


}