#include<stdio.h>
#include<math.h>
#include<malloc.h>
#define LEN sizeof(struct management)
struct management
{	
	int num;
	char name[10];
	char gender;
	int age;
	long int entry_date;
	char address[50];
	long int contact;
	struct management *next;
};
int n;
struct management *creat()
{
        struct management *head,*p1,*p2;
	p1=p2=(struct management *)malloc(LEN);
	printf("please in put the staffs'information:\nnum   name  gender  nage   entry_date    add   contact\n");
	scanf("%d %s %c %d %ld %s %ld",&p1->num,p1->name,&p1->gender,&p1->age,&p1->entry_date,p1->address,&p1->contact);
	head=NULL;
	while(p1->num!=0)
	{
		n=n+1;
		if(n==1) head=p1;
		else p2->next=p1;
		p2=p1;
		p1=(struct management*)malloc(LEN);
		scanf("%d %s %c %d %ld %s %ld",&p1->num,p1->name,&p1->gender,&p1->age,&p1->entry_date,p1->address,&p1->contact);
	}
	p2->next=NULL;
	return(head);
}
struct management *del(struct management *head,int num)
{
	struct management *p1,*p2;
	if(head==NULL) {
		printf("null!\n");
	}
	p1=head;
	while(num!=p1->num && p1->next != NULL)
	{
		p2=p1;
		p1=p1->next;
	}
	if(num==p1->num)
	{
		if(p1==head)
			head=p1->next;
		else p2->next=p1->next;
			printf("delete%d\n",num);
		n=n-1;
	}
	else printf("%d not been found!\n",num);
	return(head);
}
struct management *insert(struct management *head,struct management *stu)
{	
	struct management *p0,*p1,*p2;
	p1=head;
	p0=stu;
	if(head==NULL)
	{
		head=p0;
		p0->next=NULL;
	}
	else{   
		while((p0->num>p1->num)&&(p1->next=NULL))
		{
			p2=p1;
			p1=p1->next;
		}
		if(p0->num <= p1->num)
		{
			if(head==p1) head=p0;
			else
				p2->next=p0;
				p0->next=p1;
		}
		else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	n=n+1;
	return(head);
}
struct management *print(struct management *head)
{	
	struct management *p;
	p=head;
	if(head!=NULL)
		do{
			printf("%d %s %c %d %ld %s %ld\n",p->num,p->name,p->gender,p->age,p->entry_date,p->address,p->contact);       
			p=p->next;
		}while(p!=NULL);
}
int main()
{	
	int num1;
	char choose,Y,y,N,n;
	struct management *head,*stu;
	int del_num;
	printf("\ncreat  records:");
	head=creat();
	print(head);
	printf("\ninput the deleted number:");
	scanf("%d",&del_num);
	while(del_num!=0)
	{
		head=del(head,del_num);
		print(head);
		printf("\ninput the delect num:\n");
		scanf("%d",&del_num);
	}
	printf("\ninput the insert record:");
	stu=(struct management *)malloc(LEN);
        scanf("%d %s %c %d %ld %s %ld",&stu->num,stu->name,&stu->gender,&stu->age,&stu->entry_date,stu->address,&stu->contact);
	while(stu->num!=0)
	{
		head=insert(head,stu);
		print(head);
		printf("\ninput the inserted record:");
		stu=(struct management*)malloc(LEN);
		scanf("%d %s %c %d %ld %s %ld",&stu->num,stu->name,&stu->gender,&stu->age,&stu->entry_date,stu->address,&stu->contact);
	}
	char a;
	printf("If you want search the record:choose Y or N\n");
	scanf("%c%c",&a,&choose);
	printf("%c\n",choose);
	switch(choose)
	{	
		case'y':
		case'Y':
			print(head);break;
		case 'n':
		case 'N':
			printf("exit now\n");break;
		default:
			printf("error entry!\n");	
	}	
}
