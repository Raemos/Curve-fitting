#include<iostream>
#include<SFML/Graphics.hpp>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;

struct node{
	float value;
	node *next;
};

class linkedlist
{
 private:
 
 node *head;
 
 public:
 linkedlist()
 {
  head=NULL;	
 }
 void isheadnull()
 {
  if(head==NULL)
     cout<<"\n Head NULL";	
 }
 void insertfront(float num)
 {
  node *temp;
  temp = (node *) malloc(sizeof(node));
  if(temp==NULL)
  	{
	 cout<<"/n Memory allocation error! ;";
	 exit(0);
  	}
  temp->value=num;	
  temp->next=NULL;
  if(head==NULL)
    {
     head=temp; 
    }
  else
  	{
  	 temp->next=head;
  	 head=temp;	
  	}  	
 }

 float deleterear()
 {
  float num=0.0;
  node *temp,*prev;
  if(head==NULL)
    {
     cout<<"\n Underflow Error!";
     exit(0);	
    }
  else if(head->next==NULL)
  	{
  	 temp=head;
  	 head=NULL;
  	 num=temp->value;
  	 free(temp);	
  	}    	
  else
  	{
  	 temp=head;
  	 while(temp->next!=NULL)
  	 	{
  	 	 prev=temp;
  	 	 temp=temp->next;
  	 	}
  	 num=temp->value;
  	 prev->next=NULL;
  	 free(temp);	
  	}
  return num;	
 }

 float getele(int pos)
 {
  int len=0,i;
  float num=0;	
  node *temp;
  temp=head;
  while(temp!=NULL)
  	{
  	 temp=temp->next;
  	 len++;
  	}
  pos=len-pos;
  i=1;
  temp=head;
  while(temp!=NULL)
  {
   if(i==pos)
   	  break;
   i++;
   temp=temp->next;	
  }	
  num=temp->value;
  return num;
 }

 float getmax()
 {
  float num;
  if(head==NULL)
    {
     cout<<"\n Error no elements in list";
     exit(0);	
    }	
  num=head->value;
  node *temp;
  temp=head;
  while(temp!=NULL)
  	{
  	 if(temp->value>num)
  	    num=temp->value;
  	 temp=temp->next;   	
  	}  
  return num;	
 }

 float getmin()
 {
  float num;
  if(head==NULL)
    {
     cout<<"\n Error no elements in linkedlist";
     exit(0);	
    }	
  num=head->value;
  node *temp;
  temp=head;
  while(temp!=NULL)
  	{
  	 if(temp->value<num)
  	    num=temp->value;
  	 temp=temp->next;   	
  	}  
  return num;	
 }

 void clearlist()
 {
  float temp;	
  while(head!=NULL)
  	{
  	 temp=deleterear();
  	}	
 }
};

linkedlist x,y;
int n;

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
void drawexponential(double a, double b)
{
int i,len;
 float xpos,ypos;
 float xhigh,yhigh,xlow,ylow;
 float xscale[9],yscale[9];
 float xunit,yunit;
 float currentx,currenty,pixelx,pixely;
 char xscales[9][10],yscales[9][10];
 xhigh=x.getmax();
 yhigh=y.getmax();
 xlow=x.getmin();
 ylow=y.getmin();
 xunit=(xhigh-xlow)/8.0;
 yunit=(yhigh-ylow)/8.0;
 for(i=0;i<9;i++)
  {
   xscale[i]=xlow +i*xunit;
   sprintf(xscales[i],"%f",xscale[i]);
   setprecision(xscales[i]);
   yscale[i]=ylow +i*yunit;
   sprintf(yscales[i],"%f",yscale[i]);
   setprecision(yscales[i]);
  }
 sf::RenderWindow window(sf::VideoMode(930,900),"Exponential",sf::Style::Close);
 window.clear(sf::Color::White); 
 sf::Texture texture,pointtexture,gridtexture;
 sf::Sprite axes;
 sf::Sprite point;
 sf::Sprite grid;
 sf::RectangleShape pixel(sf::Vector2f(3,3));
 pixel.setFillColor(sf::Color(255,0,0));
 gridtexture.loadFromFile("grids.png");
 texture.loadFromFile("blankgraph.png");
 pointtexture.loadFromFile("point.png"); 
 axes.setTexture(texture);
 point.setTexture(pointtexture);
 grid.setTexture(gridtexture);;
 sf::Text xtext[9],ytext[9];
 sf::Font courierfont;
 courierfont.loadFromFile("cour.ttf");
 for(i=0;i<9;i++)
  {
   if(i%2==0)
    {
     xtext[i].setFillColor(sf::Color(0,85,255));   
     ytext[i].setFillColor(sf::Color(0,85,255));
    }
   else
    {
     xtext[i].setFillColor(sf::Color(255,0,128));   
     ytext[i].setFillColor(sf::Color(255,0,128)); 
    }       
   xtext[i].setFont(courierfont);
   ytext[i].setFont(courierfont);
   xtext[i].setString(xscales[i]);
   ytext[i].setString(yscales[i]);
   len=strlen(xscales[i])-1;
   xtext[i].setCharacterSize(84/len);
   len=strlen(yscales[i])-1;   
   ytext[i].setCharacterSize(84/len);
   xtext[i].setPosition(sf::Vector2f(130 +90*i,852));
   ytext[i].setPosition(sf::Vector2f(15,750 -90*i));
   xtext[i].setStyle(sf::Text::Bold);
   ytext[i].setStyle(sf::Text::Bold);
  }   
 window.draw(grid);
 for(currentx=xlow-xunit;currentx<=xhigh+xunit;currentx+=(xunit/90.0))
   {
    currenty= a*pow(currentx,b);
    pixelx=((currentx)-(xlow-xunit))/(xunit/90.0);
    pixely=((currenty)-(ylow-yunit))/(yunit/90.0);
    pixelx+=91;
    pixely=837-pixely;
    pixel.setPosition(sf::Vector2f(pixelx,pixely));
    window.draw(pixel);
   }
 window.draw(axes);    
 for(i=0;i<n;i++)
  {
   xpos=181-8+ (x.getele(i)-xlow)/(xunit/90.0);
   ypos=747-8- (y.getele(i)-ylow)/(yunit/90.0);
   point.setPosition(sf::Vector2f(xpos,ypos));  //181, 747
   window.draw(point);
  } 
 for(i=0;i<9;i++)
  {
   window.draw(xtext[i]);
   window.draw(ytext[i]);
  }     
 window.display();  
 while (window.isOpen())
  {
   sf::Event event;
   while (window.pollEvent(event))
    {
     if (event.type == sf::Event::Closed)
      window.close();
    }
  }
}

void drawparabola(double a, double b, double c)
{
 int i,len;
 float xpos,ypos;
 float xhigh,yhigh,xlow,ylow;
 float xscale[9],yscale[9];
 float xunit,yunit;
 float currentx,currenty,pixelx,pixely;
 char xscales[9][10],yscales[9][10];
 xhigh=x.getmax();
 yhigh=y.getmax();
 xlow=x.getmin();
 ylow=y.getmin();
 xunit=(xhigh-xlow)/8.0;
 yunit=(yhigh-ylow)/8.0;
 for(i=0;i<9;i++)
  {
   xscale[i]=xlow +i*xunit;
   sprintf(xscales[i],"%f",xscale[i]);
   setprecision(xscales[i]);
   yscale[i]=ylow +i*yunit;
   sprintf(yscales[i],"%f",yscale[i]);
   setprecision(yscales[i]);
  }
 sf::RenderWindow window(sf::VideoMode(930,900),"Parabola",sf::Style::Close);
 window.clear(sf::Color::White); 
 sf::Texture texture,pointtexture,gridtexture;
 sf::Sprite axes;
 sf::Sprite point;
 sf::Sprite grid;
 sf::RectangleShape pixel(sf::Vector2f(3,3));
 pixel.setFillColor(sf::Color(255,0,0));
 gridtexture.loadFromFile("grids.png");
 texture.loadFromFile("blankgraph.png");
 pointtexture.loadFromFile("point.png"); 
 axes.setTexture(texture);
 point.setTexture(pointtexture);
 grid.setTexture(gridtexture);;
 sf::Text xtext[9],ytext[9];
 sf::Font courierfont;
 courierfont.loadFromFile("cour.ttf");
 for(i=0;i<9;i++)
  {
   if(i%2==0)
    {
     xtext[i].setFillColor(sf::Color(0,85,255));   
     ytext[i].setFillColor(sf::Color(0,85,255));
    }
   else
    {
     xtext[i].setFillColor(sf::Color(255,0,128));   
     ytext[i].setFillColor(sf::Color(255,0,128)); 
    }       
   xtext[i].setFont(courierfont);
   ytext[i].setFont(courierfont);
   xtext[i].setString(xscales[i]);
   ytext[i].setString(yscales[i]);
   len=strlen(xscales[i])-1;
   xtext[i].setCharacterSize(84/len);
   len=strlen(yscales[i])-1;   
   ytext[i].setCharacterSize(84/len);
   xtext[i].setPosition(sf::Vector2f(130 +90*i,852));
   ytext[i].setPosition(sf::Vector2f(15,750 -90*i));
   xtext[i].setStyle(sf::Text::Bold);
   ytext[i].setStyle(sf::Text::Bold);
  }   
 window.draw(grid);
 for(currentx=xlow-xunit;currentx<=xhigh+xunit;currentx+=(xunit/90.0))
   {
    currenty= a*currentx*currentx + b*currentx + c;
    pixelx=((currentx)-(xlow-xunit))/(xunit/90.0);
    pixely=((currenty)-(ylow-yunit))/(yunit/90.0);
    pixelx+=91;
    pixely=837-pixely;
    pixel.setPosition(sf::Vector2f(pixelx,pixely));
    window.draw(pixel);
   }
 window.draw(axes);    
 for(i=0;i<n;i++)
  {
   xpos=181-8+ (x.getele(i)-xlow)/(xunit/90.0);
   ypos=747-8- (y.getele(i)-ylow)/(yunit/90.0);
   point.setPosition(sf::Vector2f(xpos,ypos));  //181, 747
   window.draw(point);
  } 
 for(i=0;i<9;i++)
  {
   window.draw(xtext[i]);
   window.draw(ytext[i]);
  }     
 window.display();  
 while (window.isOpen())
  {
   sf::Event event;
   while (window.pollEvent(event))
    {
     if (event.type == sf::Event::Closed)
      window.close();
    }
  }
}

void drawline(double a,double b)
{
 int i,len;
 float xpos,ypos;
 float xhigh,yhigh,xlow,ylow;
 float xscale[9],yscale[9];
 float xunit,yunit;
 float linelength=100,lineangle=80,linex1=200,liney1=200,linex2=300,liney2=300;
 char xscales[9][10],yscales[9][10];
 xhigh=x.getmax();
 yhigh=y.getmax();
 xlow=x.getmin();
 ylow=y.getmin();
 xunit=(xhigh-xlow)/8.0;
 yunit=(yhigh-ylow)/8.0;
 for(i=0;i<9;i++)
	{
	 xscale[i]=xlow +i*xunit;
	 sprintf(xscales[i],"%f",xscale[i]);
	 setprecision(xscales[i]);
	 yscale[i]=ylow +i*yunit;
	 sprintf(yscales[i],"%f",yscale[i]);
	 setprecision(yscales[i]);
	}
 if((ylow-yunit-b)/a >= (xlow-xunit) && (ylow-yunit-b)/a <= xhigh) //line intercepts x axis
 	{
 	 if((yhigh-b)/a >= (xlow-xunit) && (yhigh-b)/a <= xhigh) //line intercepts x high
 	   	{
 	  	 linex1=(((ylow-yunit-b)/a)-(xlow-xunit))/(xunit/90.0);
 	  	 liney1=((ylow-yunit)-(ylow-yunit))/(yunit/90.0);
 	  	 linex2=(((yhigh-b)/a)-(xlow-xunit))/(xunit/90.0);
 	  	 liney2=((yhigh)-(ylow-yunit))/(yunit/90.0);
 	   	}
 	 else if(a*(xlow-xunit)+b >= ylow-yunit && a*(xlow-xunit)+b <= yhigh)//line intercepts y axis
 	   	{
 	   	 linex1=(((ylow-yunit-b)/a)-(xlow-xunit))/(xunit/90.0);
 	  	 liney1=((ylow-yunit)-(ylow-yunit))/(yunit/90.0);
 	     linex2=((xlow-xunit)-(xlow-xunit))/(xunit/90.0);
 	  	 liney2=(((xlow-xunit)*a+b)-(ylow-yunit))/(yunit/90.0);
 	    }
 	 else if(a*xhigh+b >= ylow-yunit && a*xhigh+b<= yhigh)//line intercepts y high
 	    {
		   linex1=(((ylow-yunit-b)/a)-(xlow-xunit))/(xunit/90.0);
 	  	 liney1=((ylow-yunit)-(ylow-yunit))/(yunit/90.0);
 	     linex2=((xhigh)-(xlow-xunit))/(xunit/90.0);
 	  	 liney2=((xhigh*a+b)-(ylow-yunit))/(yunit/90.0);
 	    }    	
 	}
 else if(a*(xlow-xunit)+b >= ylow-yunit && a*(xlow-xunit)+b <= yhigh) //line intercepts y axis
 	{
 	 if(a*xhigh+b >= ylow-yunit && a*xhigh+b<= yhigh) //line intercepts y high
 	 	{
 	 	   linex1=((xlow-xunit)-(xlow-xunit))/(xunit/90.0);
 	  	 liney1=(((xlow-xunit)*a+b)-(ylow-yunit))/(yunit/90.0);
 	  	 linex2=((xhigh)-(xlow-xunit))/(xunit/90.0);
 	  	 liney2=((xhigh*a+b)-(ylow-yunit))/(yunit/90.0);
 	 	}
 	 else if((yhigh-b)/a >= (xlow-xunit) && (yhigh-b)/a <= xhigh) //line intercepts x high
 	 	{
 	 	 linex1=((xlow-xunit)-(xlow-xunit))/(xunit/90.0);
 	  	 liney1=(((xlow-xunit)*a+b)-(ylow-yunit))/(yunit/90.0);
 	  	 linex2=(((yhigh-b)/a)-(xlow-xunit))/(xunit/90.0);
 	  	 liney2=((yhigh)-(ylow-yunit))/(yunit/90.0);
 	 	}	
 	}
 else if(a*xhigh+b >= ylow-yunit && a*xhigh+b<= yhigh) //line intercepts y high
    {
     if((yhigh-b)/a >= (xlow-xunit) && (yhigh-b)/a <= xhigh) //line intercepts x high
        {	
         linex1=((xhigh)-(xlow-xunit))/(xunit/90.0);
 	  	   liney1=((xhigh*a+b)-(ylow-yunit))/(yunit/90.0);
 	    	 linex2=(((yhigh-b)/a)-(xlow-xunit))/(xunit/90.0);
 	    	 liney2=((yhigh)-(ylow-yunit))/(yunit/90.0);
        }
    }
 linex1+=92;
 linex2+=92;
 linex2+=90;
 liney2+=90;
 liney1=836-liney1;
 liney2=836-liney2;
 linelength=sqrt(pow(linex2-linex1,2)+pow(liney2-liney1,2));
 lineangle=atan((liney2-liney1)/(linex2-linex1));
 lineangle=lineangle*180.0/M_PI;
 sf::RenderWindow window(sf::VideoMode(930,900),"Straight Line",sf::Style::Close);
 window.clear(sf::Color::White); 
 sf::Texture texture,pointtexture,gridtexture;
 sf::Sprite axes;
 sf::Sprite point;
 sf::Sprite grid;
 gridtexture.loadFromFile("grids.png");
 texture.loadFromFile("blankgraph.png");
 pointtexture.loadFromFile("point.png"); 
 axes.setTexture(texture);
 point.setTexture(pointtexture);
 grid.setTexture(gridtexture);
 sf::RectangleShape straightline(sf::Vector2f(linelength, 4.f));
 straightline.setFillColor(sf::Color(232,146,32));
 straightline.setRotation(lineangle);
 straightline.setPosition(sf::Vector2f(linex1,liney1));
 sf::Text xtext[9],ytext[9];
 sf::Font courierfont;
 courierfont.loadFromFile("cour.ttf");
 for(i=0;i<9;i++)
	{
	 if(i%2==0)
		{
		 xtext[i].setFillColor(sf::Color(0,85,255));   
		 ytext[i].setFillColor(sf::Color(0,85,255));
		}
	 else
		{
		 xtext[i].setFillColor(sf::Color(255,0,128));   
		 ytext[i].setFillColor(sf::Color(255,0,128));	
		}       
	 xtext[i].setFont(courierfont);
	 ytext[i].setFont(courierfont);
	 xtext[i].setString(xscales[i]);
	 ytext[i].setString(yscales[i]);
	 len=strlen(xscales[i])-1;
	 xtext[i].setCharacterSize(84/len);
	 len=strlen(yscales[i])-1;   
	 ytext[i].setCharacterSize(84/len);
	 xtext[i].setPosition(sf::Vector2f(130 +90*i,852));
	 ytext[i].setPosition(sf::Vector2f(15,750 -90*i));
	 xtext[i].setStyle(sf::Text::Bold);
	 ytext[i].setStyle(sf::Text::Bold);
	} 	
 window.draw(grid);
 window.draw(straightline);
 window.draw(axes);
 for(i=0;i<n;i++)
	{
	 xpos=181-8+ (x.getele(i)-xlow)/(xunit/90.0);
	 ypos=747-8- (y.getele(i)-ylow)/(yunit/90.0);
	 point.setPosition(sf::Vector2f(xpos,ypos));	//181, 747
	 window.draw(point);
	}	
 for(i=0;i<9;i++)
	{
	 window.draw(xtext[i]);
	 window.draw(ytext[i]);
	}		 	
 window.display();	
 while (window.isOpen())
	{
	 sf::Event event;
	 while (window.pollEvent(event))
		{
		 if (event.type == sf::Event::Closed)
			window.close();
		}
	}
}

void input()
{
 int i;
 float inputval;
 cout<<"\n Enter the bivariate data";
 cout<<"\n Enter the total number of elements: ";
 cin>>n;
 for(i=1;i<=n;i++)
 	{
 	 cout<<" Enter x"<<i<<": ";
 	 cin>>inputval;
 	 x.insertfront(inputval);
 	 cout<<" Enter y"<<i<<": ";
 	 cin>>inputval;
 	 y.insertfront(inputval);
 	}
 cout<<"\n The input value is: ";	
 for(i=1;i<=n;i++)
	{	
	 inputval=x.getele(i-1);
	 cout<<"\n x"<<i<<":"<<inputval<<", y"<<i<<":";
	 inputval=y.getele(i-1);
	 cout<<inputval;
	}
}

void Exponential()
{
 input();
 int i;
 float valuex,valuey,valueX,valueY;
 float sumX=0,sumY=0,sumX2=0,sumXY=0;
 float A,a,b;
 for(i=0;i<n;i++)
    {
     valuex=x.getele(i);
     valuey=y.getele(i);
     valueX=log(valuex);
     valueY=log(valuey);
     sumX+=valueX;
     sumY+=valueY;
     sumX2+=valueX*valueX;
     sumXY+=valueX*valueY;
    }   
 A = (sumY*sumX2-sumX*sumXY)/(n*sumX2-sumX*sumX);
 b = (n*sumXY-sumY*sumX)/(n*sumX2-sumX*sumX);
 a = exp(A);
 printf("\n\n The required equation of Exponential Curve is: \n");
 cout<<" y = "<<a<<"x^"<<b;
 cout<<"\n\n Press ENTER to continue";
 getchar();
 getchar();
 drawexponential(a,b);
 x.clearlist();
 y.clearlist();
 n=-1;
}

void parabola()
{
 input();
 int i;
 float valuex,valuey;
 float sumx=0,sumy=0,sumx2=0,sumx3=0,sumx4=0,sumxy=0,sumx2y=0;
 float a,b,c;
 float dn,da,db,dc;
 for(i=0;i<n;i++)
    {
     valuex=x.getele(i);
     valuey=y.getele(i);
     sumx+=valuex;
     sumy+=valuey;
     sumx2+=valuex*valuex;
     sumx3+=valuex*valuex*valuex;
     sumx4+=valuex*valuex*valuex*valuex;
     sumxy+=valuex*valuey;
     sumx2y+=valuex*valuex*valuey;
    }
 dn=sumx2*(sumx2*sumx2-sumx*sumx3)-sumx*(sumx3*sumx2-sumx*sumx4)+n*(sumx3*sumx3-sumx2*sumx4);
 da=sumy*(sumx2*sumx2-sumx*sumx3)-sumx*(sumxy*sumx2-sumx*sumx2y)+n*(sumxy*sumx3-sumx2*sumx2y);
 db=sumx2*(sumxy*sumx2-sumx*sumx2y)-sumy*(sumx3*sumx2-sumx*sumx4)+n*(sumx3*sumx2y-sumxy*sumx4);
 dc=sumx2*(sumx2*sumx2y-sumxy*sumx3)-sumx*(sumx3*sumx2y-sumxy*sumx4)+sumy*(sumx3*sumx3-sumx2*sumx4);
 a=da/dn;
 b=db/dn;
 c=dc/dn;
 cout<<"\n\n The required equation of Parabola is: \n";
 cout<<" y = "<<a<<"x^2 + "<<b<<"x + "<<c;
 cout<<"\n\n Press ENTER to continue";
 getchar();
 getchar();
 drawparabola(a,b,c);
 x.clearlist();
 y.clearlist();
 n=-1;
}

void straightline()
{
 input();
 int i;
 float valuex,valuey;
 float sumx=0,sumy=0,sumx2=0,sumxy=0;
 float a,b;
 for(i=0;i<n;i++)
    {
     valuex=x.getele(i);
     valuey=y.getele(i);
     sumx+=valuex;
     sumy+=valuey;
     sumx2+=valuex*valuex;
     sumxy+=valuex*valuey; 
    }
 a = (sumy*sumx - n*sumxy)/(sumx*sumx - n*sumx2);
 b = (sumx*sumxy - sumy*sumx2)/(sumx*sumx - n*sumx2);
 cout<<"\n\n The required equation of straight line is: \n ";
 cout<<"y = "<<a<<"x + "<<b;
 cout<<"\n\n Press ENTER to continue";
 getchar();
 getchar();
 drawline(a,b);
 x.clearlist();
 y.clearlist();
 n=-1;
}

int main()
{
 int opt;
 do {
 	 cout<<"\n -----------------------------------------------";
 	 cout<<"\n Welcome! ";
 	 cout<<"\n 1) Fit a Straight line of the form y = ax + b";
 	 cout<<"\n 2) Fit a Parabola of the form y = ax^2 + bx + c";
 	 cout<<"\n 3) Fit a Exponential curve of the form y = ax^b";
 	 cout<<"\n 4) Exit";
 	 cout<<"\n Choose your option: ";
 	 cin>>opt;
 	 cout<<" ------------------------------------------------\n";
 	 switch(opt)
 	 {
 	  case 1:straightline(); 
 	         break;    
 	  case 2:parabola();
 	         break;
 	  case 3:Exponential();
 	         break;        
 	  case 4:exit(0);   	
 	 }
    }while(opt!=4);	
}