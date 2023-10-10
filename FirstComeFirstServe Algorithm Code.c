#include<stdio.h>
#include<conio.h>
#include<string.h>
int n,Bu[20],Twt,Ttt,A[10],Wt[10],w;
float Awt,Att;
char pname[20][20],c[20][20];
void Getdata();
void Gantt_chart();
void Calculate();
void fcfs();
void Getdata()
{
int i;
printf("\n Enter the number of processes: ");
scanf("%d",&n);
for(i=1;i<=n;i++)
{
fflush(stdin);
printf(" Enter the process name: ");
scanf("%s",&pname[i]);
printf(" Enter the Arrival Time for Process %s = ",pname[i]);
scanf("%d",&A[i]);
printf(" Enter The BurstTime for Process %s = ",pname[i]);
scanf("%d",&Bu[i]);
}
}
void Gantt_chart()
{
int i;
printf("\n\n\t\tFIRST COME FIRST SERVED ALGORITHM");
printf("\n\t\t\t GANTT CHART\n");
printf("\n\
t|--------------------------------------------|\n");
printf("\t|");
for(i=1;i<=n;i++)
printf(" %s |",pname[i]);
printf("\n\
t|--------------------------------------------|\n");
printf(" ");
for(i=1;i<=n;i++)
printf("%d ",Wt[i]);
printf("%d",Wt[n]+Bu[n]);
}
void Calculate()
{
int i;
Wt[1]=0;
for(i=2;i<=n;i++)
{
Wt[i]=Bu[i-1]+Wt[i-1];
}
for(i=1;i<=n;i++)
{
Twt=Twt+(Wt[i]-A[i]);
Ttt=Ttt+((Wt[i]+Bu[i])-A[i]);
}
Att=(float)Ttt/n;
Awt=(float)Twt/n;
printf("\n Average Turn around time = %3.2f ms \
n",Att);
printf(" Average Waiting Time = %3.2f ms",Awt);
}
void fcfs()
{
int i,j,temp, temp1;
Twt=0;
Ttt=0;
for(i=1;i<=n;i++)
{
for(j=i+1;j<=n;j++)
{
if(A[i]>A[j])
{
temp=Bu[i];
temp1=A[i];
Bu[i]=Bu[j];
A[i]=A[j];
Bu[j]=temp;
A[j]=temp1;
strcpy(c[i],pname[i]);
strcpy(pname[i],pname[j]);
strcpy(pname[j],c[i]);
}
}
}
Calculate();
Gantt_chart();
}
void main()
{

Getdata();
fcfs();
getch();
}
