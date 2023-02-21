
/************************************************************************************
 *   FILENAME    :   menu.c
 *
 *   DESCRIPTION :   This file is used as Main menu of the banking system which calls
 *                   customer corner and bankers corner options.
 *
 *   REVISION HISTORY
 *
 *   DATE            NAME             REASON
 *
 *  -------------------------------------------
 *   
 *   25/05/2022    Username            Menu
 *
 * ***********************************************************************************/

#include <stdio.h>   //Including required Header files
#include<stdlib.h>
#include "Header2.h"
#include "Header1.h"
#include "func.c"
#include "submenu.c"
#include "Password.c"




void gotoxy(int x, int y) // Sets co-ordinates in (x,y)
{
	printf("%c[%d;%df",0x1B,y,x);
}

int main()               // This is the Main function.
{
	
	customer_file_to_list(); //Calling file to list function of customer corner
	start=ptr=last=prev=new2=NULL; //Declares all pointer of customer structure as NULL
	start1=last1=ptr1=new1=NULL; //Declares all pointer of transaction structure as NULL
	int choice=0;
	int Banker_pass=0;
	while(choice!=3)
	{
	        system("clear");
		printf("\n__________________________\n\n");
		printf("\n\n---------WELCOME----------\n");
		printf("\n-----------To-------------\n");
		printf("\n ---The Banking System--- \n\n");
		printf("\n__________________________\n\n");
		printf("\n1. Customer Corner \n2. Banker Corner \n3. Exit \n");
		printf("\nEnter Your Choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: Customer_Corner();  // Calling Customer_Corner function
				break;
			case 2: Banker_pass=checkpassword(); // Check banker's password
				if(Banker_pass==1)
				{
					printf("\nINVALID PASSWORD!!\n");
					continue;
				}
				else
				{
					Banker_Corner();  // Calling Banker_Corner function
				}
				break;
			case 3: break;
			default: printf("\nInvalid Choice\n");
		}
	}
	if(start)
		customer_list_to_file(); // Calling  the list to file function of customer corner

	if(start1)
		banker_list_to_file();  //Calling list to file  function for bankers corner

  system("read a");
}
