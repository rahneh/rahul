#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#include<iostream>

struct pro
{
	char name;
	int pri;
	int b_time;
	int pid;
	int w_time;
	int t_time;
	int r_time;
	int a_time;
	int completed;
}p[10];


int n;
int q[10];
int fr=-1,re=-1;

void enque(int i)
{
  if(re==10)
  printf("overflow");
  re++;
  q[re]=i;
  if(fr==-1)
  fr=0;
}

int deque()
{
  if(fr==-1)
  printf("underflow");
  int temp=q[fr];
  if(fr==re)
  fr=re=-1;
  else
  fr++;
  return temp;
}

void sortByArr()
{
  struct pro temp;
  int i,j;
  for(i=0;j<n-1 ; i++)
  for(j = i+1;j<n;j++)
   {
     if(p[i].a_time>p[j].a_time)
       {
          temp=p[i];
          p[i]=p[j];
          p[j]=temp;
       }
    }
}


void getIn();
void calcWaTime(struct pro *q,int);
void calcTurnArTime(struct pro *q,int);
void pQueue(struct pro *q,int si);
void RR();
void PS();
void FCFSe();
void pQueueI(struct pro);
void pQueue(struct pro *,int);



int qu1_n=0,qu2_n=0,qu3_n=0; 
struct pro *qu1,*qu2,*qu3;
int tq=10,count=0;


void getIn()
{
	int i;
	printf("\n Enter total number of process:\t");
	scanf("%d",&n);
	qu1=((struct pro*)malloc(n*sizeof(struct pro)));
	qu2=((struct pro*)malloc(n*sizeof(struct pro)));
	qu3=((struct pro*)malloc(n*sizeof(struct pro)));
	for(i=0;i<n;i++)
	{
		struct pro p;
		printf("\n\t\tProcess %d\n=============================================\n\n",i+1);			
		printf("PId:\t");
		scanf("%d",&p.pid);
		printf("Priority (1-9):\t");
		scanf("%d",&p.pri);
		printf("Arrival Time: \t");
		scanf("%d",&p.a_time);	
		printf("Burst Time: \t");
		scanf("%d",&p.b_time);
		p.r_time = p.b_time;
		if(p.pri>0 && p.pri<=3)
		{
			qu1[qu1_n++]  = p;
		}
		else if(p.pri>3 && p.pri<=6)
		{
			qu2[qu2_n++] = p;
		}
		else
		{
			qu3[qu3_n++] = p;
			count++;
		}		
	}
}


void pQueue(struct pro *q,int si)
{	
	calcWaTime(q,si);
	calcTurnArTime(q,si);
	printf("\nPId \t\tPriority \t\tBurst \t\tWaiting \t\tTurnAround \t\tArrival");
	printf("\n================================================================================\n");
	for(int i=0;i<si;i++)
	{
		pQueueI(q[i]);
	}
	printf("\n\n");
}

void pQueueI(struct pro p)
{
	printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",p.pid,p.pri,p.b_time,p.w_time,p.t_time,p.a_time);
}

void calcWaTime(struct pro *q,int si)
{
	int i;
	q[0].w_time = 0;
	for(i=1;i<si;i++)
	{
		q[i].w_time = q[i-1].w_time + q[i-1].b_time;
	}
}


void calcTurnArTime(struct pro *q,int si)
{
	q[0].w_time = 0;
	for(int i=0;i<si;i++)
	{
		q[i].t_time = q[i].w_time + q[i].b_time;
	}
}

void RRAlgo(struct pro *q,int si)
{
  int i,j,tqa;
  char c;
  float avgwt=0,avgtt=0;
  struct pro p = q[i];  
  printf("\nEnter TIME QUANTUM:");
  scanf("%d",&tqa);
  sortByArr();
  enque(0);      
  printf("\n\nPROCESS\t    ARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
  for(i=0;i<count;i++)
   {
     avgwt+=q[i].w_time;
     avgtt+=q[i].t_time;
     printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d",q[i].name,q[i].a_time,q[i].b_time,q[i].w_time,q[i].t_time);
   }
   getch();
   system("COLOR 30");
   system("CLS");
   printf("\nAverage waiting time:%f",avgwt/n);
   printf("\nAverage Turnaround time:%f",avgtt/n);
   exit(0);
}

void RR()
{
	printf("\n\n===========================================================================");
	printf("\n\t\tRound Robin\t");
	printf("\n===========================================================================\n\n");
	calcWaTime(qu3,qu3_n);
	calcTurnArTime(qu3,qu3_n);
	RRAlgo(qu3,qu3_n);
}


void PSAlgorithm(struct pro *q,int si)
{
	for(int i=0;i<si;i++)
	{
		for(int j=0;j<si;j++)
		{
			if(q[j].pri>q[i].pri)
			{
				struct pro t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}


void PS()
{
	printf("\n\n===========================================================================");
	printf("\n\t\tPriority Sorting\t");
	printf("\n===========================================================================\n\n");
	PSAlgorithm(qu2,qu2_n);
	pQueue(qu2,qu2_n);
}


void FCFSeAlgorithm(struct pro *q,int si)
{
	for(int i=0;i<si;i++)
	{
		for(int j=0;j<si;j++)
		{
			if(q[j].a_time>q[i].a_time)
			{
				struct pro t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}


void FCFSe()
{
	printf("\n\n===========================================================================");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n===========================================================================\n\n");
	FCFSeAlgorithm(qu1,qu1_n);
	pQueue(qu1,qu1_n);
}


int main()
{
	system("COLOR FC");
	getIn();
	system("CLS");
    system("COLOR 24");
	int i=1;
	while(n>0)
	{
		switch(i)
		{
			case 1:
				FCFSe();
				break;
			case 2:
				PS();
				break;
			case 3:
				RR();
				break;
            default:
            	continue;

		}
		i++;
		sleep(5);
	}
	printf("\n\n");
	return 0;
}

