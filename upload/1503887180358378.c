#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#define ting printf("\n\n回车键返回菜单");getchar()
struct good{
	int txm;/*定义txm为条形码。编号*/ 
	char name[20];/*定义name为商品名字*/ 
	float money;/*定义money为单价*/ 
	int many;/*定义many为个数*/ 
	struct good *next;
};


void look(struct good *p1,struct good *p2)
{
	printf("**********************************************************\n");
	if(p1==NULL||strcmp(p1->name,"还没有")==0){
	printf("没有商品");
	return;
	}
	printf("编号  名称      单价   库存");
	for(p1;p1!=p2;p1=p1->next)
	printf("\n%04d %-10s %-6.2f %d",p1->txm,p1->name,p1->money,p1->many);
	printf("\n\n**********************************************************\n");
}
struct good *chaxun(struct good *head,char s[],int n)
{
	struct good *p;
	if(n==-1){
	for(p=head;p!=NULL;p=p->next)
	if(strcmp(p->name,s)==0)
	return p;
	}
	if(n!=-1){
	for(p=head;p!=NULL;p=p->next)
	if(p->txm==n)
	return p;
	}
	return NULL;
}
struct good *shuru(struct good *head,struct good *p)
{
	struct good *p2;
	int n;
	char a[20];
		printf("\n请输入 %d号商品的名称:",p->txm);
		scanf("%s",&a);
		getchar();
		while((p2=chaxun(head,a,-1))!=NULL)
		{
			printf("您输入的商品名已经存在与系统中\n");
			look(p2,p2->next);
			do{
				printf("[1]重新输入商品名\t[2]返回菜单去修改商品\n请输入1-2"); 
			scanf("%d",&n);
			getchar();
			}while(n<1||n>2);
			if(n==1)
			{
		printf("\n请重新输入 %d号商品的名称:",p->txm);
		scanf("%s",&a);
			}
			if(n==2)
			{
				strcpy(p->name,"出错了1");
				return p;
			} 
			
		}
		strcpy(p->name,a);
		printf("请输入 %d号商品的价格:",p->txm);
		scanf("%f",&p->money);
		getchar();
		printf("请输入 %d号商品的数量:",p->txm);
		scanf("%d",&p->many);
		getchar();
		return p;
}
void cop(struct good *p,struct good *p1)
{
	strcpy(p->name,p1->name);
	p->many=p1->many;
	p->money=p1->money;
	p->next=p1->next;
	p->txm=p1->txm;
}
void save(struct good *head)
{
	FILE *p;
	p=fopen("data.txt","w");
	for(head;head!=NULL;head=head->next)
	fprintf(p,"%d %s %.2f %d\n",head->txm,head->name,head->money,head->many);
	fprintf(p,"-1");
	fclose(p);
}




void join(struct good *head)
{
	int size=sizeof(struct good),n,i,txm;
	struct good *tail,*p;
	tail=head;
	while(tail->next!=NULL)
	tail=tail->next;
	txm=tail->txm;
	printf("请输入录入商品的个数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		p=(struct good*)malloc(size);
		printf("\n\n第%d个的商品编号是%d\n\n",i+1,++txm);
		p->txm=txm;
		p=shuru(head,p);
		if(strcmp(p->name,"出错了1")==0)
		{
			free(p);
			save(head);
		}
		p->next=NULL;
		if(strcmp(head->name,"还没有")==0)
		{
			cop(head,p);
			free(p);
		}
		else
		tail->next=p;
		tail=p;
	}
	save(head);
	
}
struct good *du()
{
	FILE *fp;
	struct good *head,*p,*tail;
	head=tail=NULL;
	int size=sizeof(struct good);
	if((fp=fopen("data.txt","r"))==NULL){
	fclose(fp);
	return NULL;
	}
	else
	{
	fclose(fp);
	fp=fopen("data.txt","r");
	while(1)
	{
		p=(struct good*)malloc(size);
		fscanf(fp,"%d",&p->txm);
		if(p->txm==-1)
		break;
		fscanf(fp,"%s %f %d",p->name,&p->money,&p->many);
		if(head==NULL)
		head=p;
		else
		tail->next=p;
		tail=p;
		p=p->next;
	}
	fclose(fp);
	}
	return head;
}

void xiugai(struct good *head)
{
	struct good *p,*p2,*p3;
	p3=(struct good*)malloc(sizeof(struct good));
	char a[20];
	printf("[1]按照编号修改               [2]按照名称修改\n\t如需删除请将数量设置为-1");
	int n;
	do{
		printf("\n\n请输入1-2\n");
	scanf("%d",&n);
	getchar();
	}while(n<1||n>2);
	if(n==2){
	n=-1;
	printf("请输入需要修改的商品名称:");
	scanf("%s",a);
	getchar();
	}
	else
	{
		do{
		printf("请输入要修改的商品编号:");
		scanf("%d",&n);
		}while(n<0);
		getchar();
	}
	if((p=chaxun(head,a,n))==NULL)
	{
	printf("\n\n没有找到该商品，请核对后重新输入\n\n");
	ting;
	}
	else
	{
	look(p,p->next);
	cop(p3,p);
	p=shuru(head,p);
	if(strcmp(p->name,"出错了1")==0)
	cop(p,p3);
	if(p->many==-1){
		if(p->next==NULL)
		{
		for(p2=head;p2!=NULL;p2=p2->next)
		if(p2->next==p)
		p2->next=NULL;
		free(p);
		}
		else{
	p2=p->next;
	p->many=p2->many;
	p->money=p2->money;
	strcpy(p->name,p2->name);
	p->txm=p2->txm;
	p->next=p2->next;
	free(p2);
		}
	}
	}
	save(head);
	
	 
}

int main()
{
	int i,n;
	struct good *p,*head;
	char a[20];
	head=du();
	if(head==NULL)
	{
		head=(struct good*)malloc(sizeof(struct good));
		head->txm=0;
		head->next=NULL;
		strcpy(head->name,"还没有");
	}
	while(1){
	system("cls");
	printf("\n\n\n                       ☆☆☆VAE☆☆☆\n\n");
	printf("*****************************************************************\n\n");
	printf("         [1]入库登记                     [2]浏览所有商品信息\n\n         [3]顾客结账                     [4]查询商品信息\n\n         [5]修改商品信息                 [6]退出系统\n");
	printf("\n*****************************************************************\n");
	do
	{
		printf("请输入1-6\n");
		scanf("%d",&i);
		getchar();
	}while(i<1||i>6);
	if(i==6)
	break;
	else{
	system("cls");
	switch(i){
	case 1:join(head);break;
	case 2:look(head,NULL);ting;break;
	case 4:printf("[1]编号查询           [2]商品名查询\n\n");
	do{
		printf("请输入1-2\n"); 
	scanf("%d",&n);
	getchar();
	}while(n<1||n>2);
	if(n==2){
		n=-1;
	printf("请输入需要查询的商品名称:");
	scanf("%s",a);
	getchar();
	}
	else
	{
	printf("请输入需要查询的商品编号:");
	scanf("%d",&n);
	getchar();
	}
	p=chaxun(head,a,n);
	if(p==NULL)
	printf("没有找到该商品，请核对后重试\n");
	else
	look(p,p->next);ting;break;
	case 5:xiugai(head);break;
	case 3:printf("\n该功能太麻烦了。。不想做了。。就这吧。。猥琐发育。别浪\n\n");ting;break;
	}
	}
	}
}
