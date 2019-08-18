#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define MAX 25//方格最大值 

int x[MAX*20],y[MAX*20];//蛇身最大值 
int ch;
int sx,sy;
void shiwu()
{
	int i;
	srand(time(0));
	sx=rand()/2%(MAX-3)+1;
	sy=rand()%(MAX*2-3)+1;
}
void chushi()
{
	int i;
	ch=3;
	for(i=0;i<ch;i++)
	{
		y[i]=MAX;
		x[i]=MAX/2-1+i;
	}
}
void xianshi()
{
	char d[MAX][2*MAX];
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<2*MAX;j++){
			if(i==0||i==MAX-1)
			d[i][j]='-';
			else if(j==0||j==2*MAX-1)
			d[i][j]='|';
			else if(i==sx&&j==sy)
			d[i][j]='#';
			else
			d[i][j]=' ';
		}
	}
	int e=0;
	for(i=0;i<MAX&&e<ch;i++)
	for(j=0;j<2*MAX&&e<ch;j++){
	if(i==x[e]&&y[e]==j)
	{
		d[i][j]='*';
		if(e==0)
		d[i][j]='@';
		e++;
		j=i=0;
	}
	}
	
	for(i=0;i<MAX;i++){
	for(j=0;j<2*MAX;j++)
	printf("%c",d[i][j]);
	printf("\n");
	}
}
void caozuo(int n)
{
	int i;
	i=ch-1;
	for(i;i>0;i--)
	{
		x[i]=x[i-1];
		y[i]=y[i-1];
	}
	if(n==1)
	x[0]++;
	if(n==3)
	x[0]--;
	if(n==2)
	y[0]++;
	if(n==4)
	y[0]--;
}
int jiancha()
{
	int i;
	for(i=1;i<ch;i++)
	{
		if(x[0]==x[i]&&y[0]==y[i])
		return 1;
	}
	return 0;
}
int main()
{
	system("color f0");
	system("mode con cols=100 lines=50");
	int t;
	int s=0;
	chushi();
	shiwu();
	int n=3;
	char ru;
	while(1)
	{
	t=n;
	system("cls");
	printf("当前吃了%d个食物\n",s);
	xianshi();
	Sleep(150);
	if(kbhit()){
	ru=getch();
	if(ru=='w')
	n=3;
	if(ru=='s')
	n=1;
	if(ru=='a')
	n=4;
	if(ru=='d')
	n=2;
	if(n-t==2||n-t==-2)
	n=t;
	
	}
	caozuo(n);
	if(x[0]==sx&&y[0]==sy)
	{
		ch++;
		shiwu();
		s++;
	}
	if(jiancha())
	break;
	if(x[0]==MAX-1||x[0]==0||y[0]==MAX*2-1||y[0]==0)
	break;
	}
	system("color 0f");
	Sleep(500);
	system("color f0");
	Sleep(1000);
	system("cls");
	printf("\n\n\n\n\n\t\t\t游戏结束！\n\n\t\t本次共吃了%d个食物",s);
}
