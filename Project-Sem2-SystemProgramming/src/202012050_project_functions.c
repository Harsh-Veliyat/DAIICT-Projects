#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

struct student
{
	int id, marks;
	char name[20], sec[10];
	float grade;
};
struct student s;

void display_rec()
{
	FILE *fp;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","r+");
	
	if(fp==NULL)
	{
		printf(" Error: Cannot Open the file!\n");
		return;
	}
	
	printf("=====================Student Record========================\n");
	printf("ID \t Name \t Section \t Total MArks \t Grade\n");
	
	while(fread(&s,sizeof(s),1,fp)==1)
	{
		printf("%d\t%s\t%s\t%d\t%f\n",s.id,s.name,s.sec,s.marks,s.grade);
	}
	fclose(fp);
}

void sort_rec()
{
	struct student temp;
	struct student arr[50];
	
	int i,j,k=0;
	FILE *fp, *ft;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","rb");
	ft=fopen("/home/harshveliyat/project/src/stu1.txt","ab+");
	
	i=0;
	while(fread(&arr[i],sizeof(arr[i]),1,fp)==1)
	{
		i++;k++;
	}
	
	for(i=0;i<k;i++)
	{
		for(j=0;j<k-i-1;j++)
		{
			if(arr[j].id>arr[j+1].id)
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		fwrite(&arr[i],sizeof(arr[i]),1,ft);
	}
	fclose(fp);
	fclose(ft);
	remove("/home/harshveliyat/project/src/stu.txt");
	rename("/home/harshveliyat/project/src/stu1.txt","/home/harshveliyat/project/src/stu.txt");
}

void insert_rec()
{
	FILE *fp;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","a+");
	
	if(fp==NULL)
	{
		printf(" Error: Cannot Open the file!\n");
		return;
	}
	
	display_rec();
	
	printf("=================Enter New Student Record==================\n");
	printf("1. Enter Student ID:");
	scanf("%d",&s.id);
	fflush(stdin);
	printf(" 2.Enter Student Name:");
	scanf("%s",s.name);
	printf(" 3.Enter Student Section:");
	scanf("%s",s.sec);
	printf(" 4. Enter Student Total Marks:");
	scanf("%d",&s.marks);
	printf(" 5. Enter Student Grade:");
	scanf("%f",&s.grade);
	fwrite(&s,sizeof(s),1,fp);
	
	{
		printf("!!!Record Inserted Sucessfully!!!\n");
	}
	fclose(fp);
	printf("!!! Updated Record List!!!\n");
	sort_rec();
	
}
void search_rec()
{
	int ids, check=0;
	FILE *fp;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","rb");
	
	if(fp==NULL)
	{
		printf(" Error: Cannot Open the file!\n");
		return;
	}
	display_rec();
	printf("Enter the Student ID which you want to search: ");
	scanf("%d",&ids);
	while(fread(&s,sizeof(s),1,fp)>0 && check == 0)
	{
		if(s.id == ids)
		{
			check =1 ;
			printf("One Match Found!\n");
			printf("ID \t Name \t Section \t Total MArks \t Grade\n");
			printf("%d\t%s\t%s\t%d\t%f\n",s.id,s.name,s.sec,s.marks,s.grade);
		}
	}
	if(check == 0)
	{
		printf("No Match Found!\n");
	}
	fclose(fp);
}
void del_rec()
{
	char name[20];
	unsigned flag = 0;
	FILE *fp, *ft;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","rb");
	if(fp==NULL)
	{
		printf(" Error: Cannot Open the file!\n");
		return;
	}
	display_rec();
	
	printf("Enter Student name which you want to Delete:");
	scanf("%s",name);
	ft=fopen("/home/harshveliyat/project/src/stu1.txt","ab+");
	while(fread(&s,sizeof(s),1,fp)==1)
	{
		if(strcmp(name,s.name) != 0)
		{
			fwrite(&s,sizeof(s),1,ft);
		}
		else
			flag=1;
	}
	if(flag == 0)
		printf("No Such Record Found!\n");
	fclose(fp);
	fclose(ft);
	remove("/home/harshveliyat/project/src/stu.txt");
	rename("/home/harshveliyat/project/src/stu1.txt","/home/harshveliyat/project/src/stu.txt");
	printf("!!!Records Updated!!!\n");
	display_rec();
}

void update_rec()
{
	int ids, flag=0;
	FILE *fp;
	fp=fopen("/home/harshveliyat/project/src/stu.txt","rb+");
	if(fp==NULL)
	{
		printf(" Error: Cannot Open the file!\n");
		return;
	}
	display_rec();
	printf("\nEnter the ID of STudent whose record you want to update:");
	scanf("%d",&ids);
	while(fread(&s,sizeof(s),1,fp)>0 && flag == 0)
	{
		if(s.id == ids)
		{
			flag = 1;
			printf("ID \t Name \t Section \t Total MArks \t Grade\n");
			printf("%d\t%s\t%s\t%d\t%f\n",s.id,s.name,s.sec,s.marks,s.grade);
			printf("Now Enter the New Record");
			printf("===============Now Enter New Student Record================\n");
			printf("Updated Student ID:");
			scanf("%d",&s.id);
			fflush(stdin);
			printf("Updated Student Name:");
			scanf("%s",s.name);
			printf("Updated Student Section:");
			scanf("%s",s.sec);
			printf("Updated Student Marks:");
			scanf("%d",&s.marks);
			printf("Updated Student Grade:");
			scanf("%f",&s.grade);
			fseek(fp,-(long)sizeof(s),1);
			fwrite(&s,sizeof(s),1,fp);
			printf("Record Updated Sucessfully!!!\n");
		}
		if(flag==0)
		{
			printf("Error: Something went wrong!!\n");
		}
		fclose(fp);
	}
}

char getchlin()
{
	char c,test;
	scanf("%c",&c);
	scanf("%c",&test);
	return c;
}
void handler(int num)
{
	write(STDOUT_FILENO, "\nYou should keep a practise of working without error.\nDont worry your data is safe.\n",84);
	kill(getpid(),SIGKILL);
	getchlin();
}
