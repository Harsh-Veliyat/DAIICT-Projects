#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "202012050_project_header.h"
#include<signal.h>

void main()
{
	signal(SIGINT, handler);
	int ch;
	while(ch!=7)
	{
		system("clear");
		printf("===========================================================\n");
		printf("======================School Records=======================\n");
		printf("===========================================================\n");
		printf(" Choose from the menu\n");
		printf(" 1. Insert Student Record\n");
		printf(" 2. Display Student Record\n");
		printf(" 3. Search Student Record\n");
		printf(" 4. Delete Student Record\n");
		printf(" 5. Update Any Student's Record\n");
		printf(" 6. View Records in Sorted Manner\n");
		printf(" 7. Exit\n");
		printf(" Enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				system("clear");
				insert_rec();
				break;
			case 2:
				system("clear");
				display_rec();
				break;
			case 3:
				system("clear");
				search_rec();
				break;
			case 4:
				system("clear");
				del_rec();
				break;
			case 5:
				system("clear");
				update_rec();
				break;
			case 6:
				system("clear");
				sort_rec();
				break;
			case 7:
				exit(0);
			default:
				printf(" No such option available!");
		}
		printf("\nEnter any character to continue!\n");
		getchlin();
	}
}
