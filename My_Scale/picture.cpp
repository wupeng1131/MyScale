#include "stdafx.h"
#include "picture.h"

void Background()  
{  
  
    glBindTexture(GL_TEXTURE_2D, texture);    
    glBegin(GL_QUADS);  
     glTexCoord2d(-1.0, 1.0); glVertex2d(-WIDTH*SCALE*ADJUST, - HEIGHT*SCALE*ADJUST);
    glTexCoord2d(0.0, 1.0); glVertex2d(+WIDTH*SCALE*ADJUST, - HEIGHT*SCALE*ADJUST);  
    glTexCoord2d( 0.0, 0.0 ); glVertex2d(+WIDTH*SCALE*ADJUST, + HEIGHT*SCALE*ADJUST);  
    glTexCoord2d(-1.0, 0.0); glVertex2d(-WIDTH*SCALE*ADJUST, + HEIGHT*SCALE*ADJUST);  
    glEnd();   
        return ;  
} 
void Background1()  
{  
 
	 glBindTexture(GL_TEXTURE_2D, texture1);
	  glBegin(GL_QUADS);  
     glTexCoord2d(1.0, 1.0); glVertex2d(-WIDTH*SCALE, - HEIGHT*SCALE);
    glTexCoord2d(0.0, 1.0); glVertex2d(+WIDTH*SCALE, - HEIGHT*SCALE);  
    glTexCoord2d( 0.0, 0.0 ); glVertex2d(+WIDTH*SCALE, + HEIGHT*SCALE);  
    glTexCoord2d(1.0, 0.0); glVertex2d(-WIDTH*SCALE, + HEIGHT*SCALE);  
    glEnd();  
        return ;  
}  
void makeTextureImg(IplImage  * image)
	{
	  int width=image->width ;
	  int height=image->height;
	  CvScalar s;
	  textureImage =new unsigned char[width*height*3];
	  for (int i=0;i<height;i++)
		  for(int j=0;j<width;j++)
		  {
		   // s=cvGet2D (image,i,j);
			//textureImage [i*3*width+3*j]=s.val[0];
			//textureImage [i*3*width+3*j+1]=s.val[1];
			//textureImage [i*3*width+3*j+2]=s.val[2];
			//if(textureImage [i*3*width+3*j]!=0&&textureImage [i*3*width+3*j+1]!=0&&textureImage [i*3*width+3*j+2]!=0) 
			textureImage [i*3*width+3*j]=textureImage [i*3*width+3*j+1]=textureImage [i*3*width+3*j+2]=255;
		   }
	}
int LoadTexture(IplImage *image,GLuint *text)
{
  if(image==NULL ) return -1;
  glGenTextures (1,text);
  glBindTexture (GL_TEXTURE_2D ,*text);
  glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MAG_FILTER ,GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MIN_FILTER ,GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
  0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image->imageData);
	 return 0;
}

void line(float a[2],float b[2])
{ 
  glBegin (GL_LINE_STRIP );
  glVertex2d (a[0]/90.0,a[1]/90.0);
  glVertex2d (b[0]/90.0,b[1]/90.0);
  glEnd ();
}
void circle(float a[])
{
  GLfloat  cos_num,sin_num;
  glBegin (GL_POINTS);
  for (int i=0;i<100;i++)
  {
     cos_num =cos(i*2*pi/100.0);
	 sin_num =sin(i*2*pi/100.0);
	 glVertex2f (a[0]/90.0+(cos_num/180.0*a[2]),a[1]/90.0+(sin_num/180.0*a[2]/2));
  }
  glEnd();
}

void drawArc(float a[])
{
	  for(float i=a[2]*pi/180.0;i<=a[3]*pi/180.0;i+=2*a[4] )
	  { glBegin(GL_LINE_STRIP);
	    float vx1=a[0]+a[5] *cos(i);
		float vy1=a[1]+a[5] *sin(i);
		float vx2=a[0]+a[5]*cos(i+a[4]);
		float vy2=a[1]+a[5]*sin(i+a[4]);
		glVertex2d (vx1/90.0,vy1/90.0);
		glVertex2d(vx2/90.0,vy2/90.0);
		 glEnd();
	  }
	 
}
void drawArc1(float a[])
{
	  for(float i=a[2]*pi/180.0;i<=a[3]*pi/180.0;i+=2*a[4] )
	  { glBegin(GL_POINTS );
	    float vx1=a[0]+a[5] *cos(i);
		float vy1=a[1]+a[5] *sin(i);		
		glVertex2d (vx1/90.0,vy1/90.0);		
		glEnd();
	  }
	 
}