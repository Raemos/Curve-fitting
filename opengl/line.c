#include <GL/glut.h>  
#include <stdio.h>
#include <string.h>

int npoints;
int xpoints[100];
int ypoints[100];
int xmax=0,ymax=0,xmin=99999,ymin=99999;
float xunit,yunit;
float xscales[8],yscales[8];
double a,b;

void setprecision(char *str)
{
 int i,count=-1,flag=0;
 for(i=0;str[i]!='\0';i++)
	{
	 if(str[i]=='.') 
		flag=1;
	 if(flag==1)
		count++;
	 if(count==2)
		str[i+1]='\0';        
	}   
}

void displaylabels()
{
    char msgx[100];
    char msgy[100];
    int w,len,c,i;
    for(i=0;i<8;i++)
    {
        if(i%2==0)
            glColor3f(0,0,1);
        else
            glColor3f(1.0,0,0.5);
        sprintf(msgx,"%f",xscales[i]);
        sprintf(msgy,"%f",yscales[i]);
        setprecision(msgx);
        setprecision(msgy);
        
        glRasterPos2f(i*100 + 170, 60);
        len = strlen(msgx);
        for (c = 0; c < len; c++) {
             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msgx[c]);
        }

        glRasterPos2f(10, i*100 + 200);
        len = strlen(msgy);
        for (c = 0; c < len; c++) {
             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msgy[c]);
        }
        
    }

}


void putpoint(int x, int y)
{
    int psize=7;
    glLineWidth(4);
    glColor3f(0,0.5,0.2);
    glBegin(GL_LINES);
    glVertex2f(x-psize,y-psize);
    glVertex2f(x,y);
    glVertex2f(x+psize,y-psize);
    glVertex2f(x,y);
    glVertex2f(x-psize,y+psize);
    glVertex2f(x,y);
    glVertex2f(x+psize,y+psize);
    glVertex2f(x,y);
    glEnd();
}


void display() {
   int i;
   glClear(GL_COLOR_BUFFER_BIT);    

   //x and y axis
   glColor3f(0,0,0);
   glLineWidth(2);
   glBegin(GL_LINES);              
      glVertex2f(0,100);
      glVertex2f(1000,100);
      glVertex2f(100,0);
      glVertex2f(100,1000);
   glEnd();

   //x and y axis scale
   glColor3f(0,0,0);
   glLineWidth(3);
   glBegin(GL_LINES);
   for(i=200;i<1000;i+=100)
        {
         glVertex2f(90,i);
         glVertex2f(110,i);
         glVertex2f(i,110);
         glVertex2f(i,90);
        }
   glEnd();

   //x axis and y axis arrow head
   glBegin(GL_LINES);
   glVertex2f(90,990);
   glVertex2f(100,1000);
   glVertex2f(110,990);
   glVertex2f(100,1000);
   glVertex2f(990,90);
   glVertex2f(1000,100);
   glVertex2f(990,110);
   glVertex2f(1000,100);
   glEnd();

   //x and y grids
   glLineWidth(1);
   glLineStipple(1, 0xAAAA);  
   glEnable(GL_LINE_STIPPLE);
   glColor3f(0.6,0.6,0.6);
   glBegin(GL_LINES);
   for(i=200;i<1000;i+=100)
    {
     glVertex2f(i,100);
     glVertex2f(i,1000);
     glVertex2f(100,i);
     glVertex2f(1000,i);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    //line
    float xvalue;
    float yvalue;
    float ydisp;
    glColor3f(1,0,0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for(i=100;i<=1000;i++)
        {
            xvalue = xmin-xunit + (i-100.0)/(900.0)*xmax;
            yvalue = a*xvalue + b;
            ydisp = (yvalue-ymin)/(yunit/100)+200;
            glVertex2f(i,ydisp);
        }
    glEnd();


    //scale labels
    displaylabels();

    //points
    for(i=0;i<npoints;i++)
       {
        int x,y;
        x = (xpoints[i]-xmin)/(xunit/100)+200;
        y = (ypoints[i]-ymin)/(yunit/100)+200;

        putpoint(x,y);
         
       }
   glFlush();
}

void getdata(int argc, char **argv)
{
    int i,count;
    
    a = atof(argv[1]);
    b = atof(argv[2]);
    npoints = atoi(argv[3]);
    count=4;
    for(i=0;i<npoints;i++)
        {
            xpoints[i] = atoi(argv[count++]);
            ypoints[i] = atoi(argv[count++]);
            //printf("\n%d: %d,%d",i,xpoints[i],ypoints[i]);
        }
    for(i=0;i<npoints;i++)
        if(xmax < xpoints[i])
            xmax=xpoints[i];
    for(i=0;i<npoints;i++)
        if(ymax < ypoints[i])
            ymax=ypoints[i];
    for(i=0;i<npoints;i++)
        if(xmin > xpoints[i])
            xmin =xpoints[i];
    for(i=0;i<npoints;i++)
        if(ymin > ypoints[i])
            ymin=ypoints[i];
    xunit = (xmax-xmin)/7.0;
    yunit = (ymax-ymin)/7.0;
    
    for(i=0;i<8;i++)
        {
            xscales[i] = xmin + i*xunit;
            yscales[i] = ymin + i*yunit;
        }
    
    /*
    printf("\na: %f, b: %f",a,b);
    printf("\nnpoints: %d",npoints);
    printf("\nx:%d %d",xmin,xmax);
    printf("\ny:%d %d",ymin,ymax);
    printf("\nxunit:%f, yunix:%f",xunit,yunit);
    printf("\nThe scales are: \nx axis:");
    for(i=0;i<8;i++)
        printf(" %f",xscales[i]);
    printf("\ny axis:");
    for(i=0;i<8;i++)
        printf(" %f",yscales[i]);
    */

    
    
            
}

void minit()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,1000,0,1000);
    //glLoadIdentity();
} 

int main(int argc, char** argv) {
  
   getdata(argc, argv);

   glutInit(&argc, argv);    
   glutInitWindowPosition(400, 400);
   glutInitWindowSize(800, 800);
   glutCreateWindow("Line"); 
   minit();
   glutDisplayFunc(display); 
   glutMainLoop();           

   return 0;
}