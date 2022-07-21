#include<stdio.h>
#include<math.h>
#include<stdlib.h>
struct Node{
 float value;
 struct Node *next;
};
void enqueue(int queueno,float data);
void input();
float dequeue(int queueno);
int n;
struct Node *tempq=NULL,*x=NULL, *y=NULL;

void displayexponential(float a, float b, char *pointslist)
{
    char command[500] ="./exponential";
    sprintf(command,"%s %f %f %s",command,a,b,pointslist);
    system(command);
}
void Exponential()
{
 input();
 int i;
 float valuex,valuey,valueX,valueY;
 float sumX=0,sumY=0,sumX2=0,sumXY=0;
 float A,a,b;
 char temp[100];
 sprintf(temp,"%d",n); 
 for(i=0;i<n;i++)
    {
     valuex=dequeue(1);
     valuey=dequeue(2);
     sprintf(temp,"%s %d %d",temp,(int)valuex,(int)valuey);
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
 printf(" y = %fx^%f",a,b);
 printf("\n\n Press ENTER to continue");
 displayexponential(a,b,temp);
 getchar();
 getchar();
}
void displayparabola(float a, float b, float c, char *pointslist)
{
    char command[500] ="./parabola";
    char temp[50];
    sprintf(command,"%s %f %f %f %s",command,a,b,c,pointslist);
    system(command);
}
void parabola()
{
 input();
 int i;
 float valuex,valuey;
 float sumx=0,sumy=0,sumx2=0,sumx3=0,sumx4=0,sumxy=0,sumx2y=0;
 float a,b,c;
 float dn,da,db,dc;
 char temp[100];
 sprintf(temp,"%d",n);
 for(i=0;i<n;i++)
    {
     valuex=dequeue(1);
     valuey=dequeue(2);
     sprintf(temp,"%s %d %d",temp,(int)valuex,(int)valuey);
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
 printf("\n\n The required equation of Parabola is: \n");
 printf(" y = %fx^2 + %fx + %f",a,b,c);
 printf("\n\n Press ENTER to continue");
 displayparabola(a,b,c,temp);
 getchar();
 getchar();
}

void displayline(float a, float b, char *pointslist)
{
    char command[500] ="./line";
    char temp[50];
    sprintf(command,"%s %f %f %s",command,a,b,pointslist);
    system(command);
}


void straightline()
{
 input();
 int i;
 float valuex,valuey;
 float sumx=0,sumy=0,sumx2=0,sumxy=0;
 float a,b;
 char temp[100];
 sprintf(temp,"%d",n);
 for(i=0;i<n;i++)
    {
     valuex=dequeue(1);
     valuey=dequeue(2);
     sprintf(temp,"%s %d %d",temp,(int)valuex,(int)valuey);
     sumx+=valuex;
     sumy+=valuey;
     sumx2+=valuex*valuex;
     sumxy+=valuex*valuey; 
    }
 a = (sumy*sumx - n*sumxy)/(sumx*sumx - n*sumx2);
 b = (sumx*sumxy - sumy*sumx2)/(sumx*sumx - n*sumx2);
 printf("\n\n The required equation of Straight line is: \n");
 printf(" y = %fx + %f",a,b);
 printf("\n\n Press ENTER to continue");
 displayline(a,b,temp);
 getchar();
 getchar();
}

void input()
{
 int i;
 float ivalue;
 printf("\n Input the Bi-Variate Data");
 printf("\n Enter the total no of elements: ");
 scanf("%d",&n);
 for(i=0;i<n;i++)
    {
     printf(" Enter x%d: ",i+1);
     scanf("%f",&ivalue);
     enqueue(1,ivalue);
     printf(" Enter y%d: ",i+1);
     scanf("%f",&ivalue);
     enqueue(2,ivalue);
    }
 printf("\n The input value is: \n");
 for(i=0;i<n;i++)
    {
     printf("\n x%d: ",i+1);
     ivalue = dequeue(1);
     printf("%f , ",ivalue);
     enqueue(0,ivalue);
     printf("y%d: ",i+1);
     ivalue = dequeue(2);
     printf("%f",ivalue); 
     enqueue(0,ivalue);
    }
 for(i=0;i<n;i++)
    {
     ivalue=dequeue(0);
     enqueue(1,ivalue);
     ivalue=dequeue(0);
     enqueue(2,ivalue);
    }   
}

float dequeue(int queueno)
{
 struct Node *head;
 switch(queueno)
 {
  case 0: head=tempq;
          break;
  case 1: head=x;
          break;
  case 2: head=y;
          break;      
 }
 struct Node *temp,*prev;
 float rvalue=0.0;
 if(head==NULL)
   {
    printf("\n UNDERFLOW ERROR \n");
    exit(0);
   }
 else if(head->next==NULL)
   {
    temp=head;;
    head=NULL;
    rvalue=temp->value;
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
    rvalue=temp->value;
    prev->next=NULL;
    free(temp);   
   }
 switch(queueno)
 {
  case 0: tempq=head;
          break;
  case 1: x=head;
          break;
  case 2: y=head;
          break;     
 }
 return rvalue;
}

void enqueue(int queueno,float data)
{
 struct Node *head;
 switch(queueno)
 {
  case 0: head=tempq;
          break;
  case 1: head=x;
          break;
  case 2: head=y;
          break;      
 }
 struct Node *temp;
 temp = (struct Node*)malloc(sizeof(struct Node)); 
 if(temp==NULL)
   {
    printf("\n Memory Allocation Error");
    exit(0);
   }
 temp->next=NULL;
 temp->value=data;
 if(head == NULL)
   {
    head=temp;  
   }
 else
   {
    temp->next=head;
    head=temp; 
   }
 switch(queueno)
 {
  case 0: tempq=head;
          break;
  case 1: x=head;
          break;
  case 2: y=head;
          break;       
 }
}

void main()
{
 int opt;
 do{
    printf("\n -----------------------------------------------");
    printf("\n Welcome! ");
    printf("\n 1) Fit a Straight line of the form y = ax + b");
    printf("\n 2) Fit a Parabola of the form y = ax^2 + bx + c");
    printf("\n 3) Fit a Exponential curve of the form y = ax^b");
    printf("\n 4) Exit");
    printf("\n Choose your option: ");
    scanf("%d",&opt);
    printf(" ------------------------------------------------\n");
    switch(opt)
    {
     case 1: straightline();
             break;
     case 2: parabola();
             break;
     case 3: Exponential();
             break;        
     case 4: exit(0);
    }
 }while(opt!=4);   
}       




