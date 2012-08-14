/*
file name:staff.c
purpose:manage staffs
creator:Bruse li
create time:2012-08-10
modify history:
Bruse li 2012-08-14
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
#define LEN sizeof(struct management)
struct management
{	
	char num[6];
	char name[10];
	char sex;
	int age;
	long int entry_date;
	char address[50];
	long int contact;
	struct management *next;
};
int n;
struct management *creat()
{
        struct management *head,*node1,*node2;
	if((node1=node2=(struct management *)malloc(LEN))==NULL)
	{
		printf("creat malloc error\n");
		exit(1);
	}
	printf("please in put the staffs'information:\nnum  name sex  age  entry_date  add  contact\n");
	scanf("%s %s %c %d %ld %s %ld",node1->num,node1->name,&node1->sex,&node1->age,&node1->entry_date,node1->address,&node1->contact);
	head=NULL;
	while((strcmp(node1->num,"0")!=0) && (sizeof(node1->num)==6) && (node1->sex=='m'||node1->sex=='w') && (node1->age<130))
	{	
		n=n+1;
		if(n==1) 
		{
			head=node1;
		}
		else 
		{	
			node2->next=node1;
		}
		node2=node1;
		node1=(struct management*)malloc(LEN);
		scanf("%s %s %c %d %ld %s %ld",node1->num,node1->name,&node1->sex,&node1->age,&node1->entry_date,node1->address,&node1->contact);
	}
	node2->next=NULL;
	return(head);
}
struct management *del(struct management *head,char num[10])
{
	struct management *node1,*node2;
	if(head==NULL) {
		printf("null!\n");
	}
		node1=head;
	while((strcmp(num,node1->num)>0) && node1->next != NULL)
	{
		node2=node1;
		node1=node1->next;
	}
	if(strcmp(num,node1->num)==0)
	{
		if(node1==head)
		{
			head=node1->next;
		}
		else
		{
			node2->next=node1->next;
		}
			printf("delete%s\n",num);
	}
	else 
	{	
		printf("%s not been found!\n",num);
	}
		return(head);
}
struct management *insert(struct management *head,struct management *staff)
{	
	struct management *p0,*node1,*node2;
	node1=head;
	p0=staff;
	if(head==NULL)
	{
		head=p0;
		p0->next=NULL;
	}
	else{   
		while((strcmp(p0->num,node1->num)>0)&&(node1->next!=NULL))
		{
			node2=node1;
			node1=node1->next;
		}
		if(strcmp(p0->num,node1->num)<=0)
		{
			if(head==node1)
			{
				head=p0;
				p0->next=node1;
			}
			else
			{	
				node2->next=p0;
				p0->next=node1;
			}
		}
		else{
			node1->next=p0;
			p0->next=NULL;
		}
	}
	return(head);
}
struct management *print(struct management *head)
{	
	struct management *pri;
	pri=head;
	if(head!=NULL)
		do{
			printf("%s %s %c %d %ld %s %ld\n",pri->num,pri->name,pri->sex,pri->age,pri->entry_date,pri->address,pri->contact);       
			pri=pri->next;
		}while(pri!=NULL);
}
int main()
{	
	char choose;
	struct management *head,*staf;
	char del_num[6];
	/*创建链表*/
	printf("\ncreat  records:");
	head=creat();
	print(head);
	/*删除结点*/
	printf("\ninput the deleted number:");
	scanf("%s",del_num);
	while(strcmp(del_num,"0")!=0)
	{
		head=del(head,del_num);
		print(head);
		printf("\ninput the delect num:\n");
		scanf("%s",del_num);
	}
	/*插入节点*/
	printf("\ninput the insert record:");
	if((staf=(struct management *)malloc(LEN))==NULL)
	{
		printf("insert malloc error \n");
		exit(1);
	}
        scanf("%s %s %c %d %ld %s %ld",staf->num,staf->name,&staf->sex,&staf->age,&staf->entry_date,staf->address,&staf->contact);
	while(strcmp(staf->num,"0")!=0)
	{
		head=insert(head,staf);
		print(head);
		printf("\ninput the inserted record:");
		staf=(struct management*)malloc(LEN);
		scanf("%s %s %c %d %ld %s %ld",staf->num,staf->name,&staf->sex,&staf->age,&staf->entry_date,staf->address,&staf->contact);
	}
	
	printf("\nIf you want search the record:choose Y or N:");
	scanf("%*c%c",&choose);
	switch(choose)
	{	
		case 'y':
		case 'Y':
			print(head);
			break;
		case 'n':
		case 'N':
			printf("exit now\n");
			break;
		default:
			printf("error entry!\n");	
	}
	free(staf);
}	
