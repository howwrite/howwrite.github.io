#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#define ting printf("\n\n�س������ز˵�");getchar()
struct good{
	int txm;/*����txmΪ�����롣���*/ 
	char name[20];/*����nameΪ��Ʒ����*/ 
	float money;/*����moneyΪ����*/ 
	int many;/*����manyΪ����*/ 
	struct good *next;
};


void look(struct good *p1,struct good *p2)
{
	printf("**********************************************************\n");
	if(p1==NULL||strcmp(p1->name,"��û��")==0){
	printf("û����Ʒ");
	return;
	}
	printf("���  ����      ����   ���");
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
		printf("\n������ %d����Ʒ������:",p->txm);
		scanf("%s",&a);
		getchar();
		while((p2=chaxun(head,a,-1))!=NULL)
		{
			printf("���������Ʒ���Ѿ�������ϵͳ��\n");
			look(p2,p2->next);
			do{
				printf("[1]����������Ʒ��\t[2]���ز˵�ȥ�޸���Ʒ\n������1-2"); 
			scanf("%d",&n);
			getchar();
			}while(n<1||n>2);
			if(n==1)
			{
		printf("\n���������� %d����Ʒ������:",p->txm);
		scanf("%s",&a);
			}
			if(n==2)
			{
				strcpy(p->name,"������1");
				return p;
			} 
			
		}
		strcpy(p->name,a);
		printf("������ %d����Ʒ�ļ۸�:",p->txm);
		scanf("%f",&p->money);
		getchar();
		printf("������ %d����Ʒ������:",p->txm);
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
	printf("������¼����Ʒ�ĸ���:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		p=(struct good*)malloc(size);
		printf("\n\n��%d������Ʒ�����%d\n\n",i+1,++txm);
		p->txm=txm;
		p=shuru(head,p);
		if(strcmp(p->name,"������1")==0)
		{
			free(p);
			save(head);
		}
		p->next=NULL;
		if(strcmp(head->name,"��û��")==0)
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
	printf("[1]���ձ���޸�               [2]���������޸�\n\t����ɾ���뽫��������Ϊ-1");
	int n;
	do{
		printf("\n\n������1-2\n");
	scanf("%d",&n);
	getchar();
	}while(n<1||n>2);
	if(n==2){
	n=-1;
	printf("��������Ҫ�޸ĵ���Ʒ����:");
	scanf("%s",a);
	getchar();
	}
	else
	{
		do{
		printf("������Ҫ�޸ĵ���Ʒ���:");
		scanf("%d",&n);
		}while(n<0);
		getchar();
	}
	if((p=chaxun(head,a,n))==NULL)
	{
	printf("\n\nû���ҵ�����Ʒ����˶Ժ���������\n\n");
	ting;
	}
	else
	{
	look(p,p->next);
	cop(p3,p);
	p=shuru(head,p);
	if(strcmp(p->name,"������1")==0)
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
		strcpy(head->name,"��û��");
	}
	while(1){
	system("cls");
	printf("\n\n\n                       ����VAE����\n\n");
	printf("*****************************************************************\n\n");
	printf("         [1]���Ǽ�                     [2]���������Ʒ��Ϣ\n\n         [3]�˿ͽ���                     [4]��ѯ��Ʒ��Ϣ\n\n         [5]�޸���Ʒ��Ϣ                 [6]�˳�ϵͳ\n");
	printf("\n*****************************************************************\n");
	do
	{
		printf("������1-6\n");
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
	case 4:printf("[1]��Ų�ѯ           [2]��Ʒ����ѯ\n\n");
	do{
		printf("������1-2\n"); 
	scanf("%d",&n);
	getchar();
	}while(n<1||n>2);
	if(n==2){
		n=-1;
	printf("��������Ҫ��ѯ����Ʒ����:");
	scanf("%s",a);
	getchar();
	}
	else
	{
	printf("��������Ҫ��ѯ����Ʒ���:");
	scanf("%d",&n);
	getchar();
	}
	p=chaxun(head,a,n);
	if(p==NULL)
	printf("û���ҵ�����Ʒ����˶Ժ�����\n");
	else
	look(p,p->next);ting;break;
	case 5:xiugai(head);break;
	case 3:printf("\n�ù���̫�鷳�ˡ����������ˡ�������ɡ����������������\n\n");ting;break;
	}
	}
	}
}
