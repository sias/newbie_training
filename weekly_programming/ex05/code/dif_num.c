/*
file name:dif_num.c
purporse:copy the random numbers into a file
creator:Bruse li
create time:2012-08-25
modify history:
Bruse li,2012-08-27
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 10000000
#define M 5000000
int main()
{
	int i;
	int m=M;
	FILE *fp;
	if((fp=fopen("file.txt","at+"))==NULL)
	{
		printf("errno on open!\n");
		exit(1);
	}
	for(i=0;i<N;i++)
	{	
		if((rand()%(N-i))<m)
		{
			fprintf(fp,"%5d",i);
			m--;	
		}
	}
	fclose(fp);
}
