
/*************************************************************************************
 *   FILENAME    :   func.c
 *
 *   DESCRIPTION :   This file uses as functions file which contains all the functions
 *                   definitions and performs all designated tasks.
 *
 *   REVISION HISTORY
 *
 *   DATE            NAME             REASON
 *
 *  -------------------------------------------
 *   
 *   25/05/2022    Username           Perform Operations
 *
 * ***********************************************************************************/
#include <stdio.h> //Include required header files
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<time.h>

#include "Header2.h"

int Create_Account() //This functions create an account

{
	char name[30];
	char aadhar_no[10];
	char customer_id[20];
	int len=0;
	char password[10];;
	char account_type[10];
	double amount;
	new2 = (cust *) malloc(sizeof(cust)); //Dynamic memory allocation for customer structure
	printf("\n\n Create Your Account\n");
	while(1)
	{
		//Taking input of customer name
		printf("\nEnter Your Name:\n");
		fflush(stdin);
		scanf("%s",name);
		int len;
		int flag=0;
		for(int i=0;name[i];i++)
		{
			if(!isalpha(name[i])) //isalpha() function is used to check if user gives numbers in name section then it will not accept the name 
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("Invalid name.Name should contain only alphabets\n"); 
			continue;
		}
		len=strlen(name);
		if(len<5||len>15) //Checking that length of the name should be less than 5 and greater than 15
		{
			printf("Invalid Length.Length should not exceed 15 charecters\n");
			continue;
		}
		else
		{
			break;
		}
	}
		int an,flag=0;
		while(1)
		{
		
			//Taking input of addhar no
			printf("\nEnter aadhar no:\n");
			scanf("%d",&an);
			for(ptr=start;(ptr);ptr=ptr->next)
			{
				if(ptr->aadhar_no==an)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("already exist");
				return 0;
			}
			if(an<100000|| an>999999) //Checking if the length of the aadhar no should be 6 digits only else it will print invalid message
			{
				printf("\nInvalid Length.Length should only of 6 digits.\n"); 
				continue;
			}

			
			else{
				break;
			}
		}
			sprintf(aadhar_no,"%d",an); //stores integer in string

//	printf("\nEnter your password: \n");
//	scanf("%s",password);
        char *pr=getpassword(); //storing password in pointer

	while(1)
	{
		//Taking input of account type
		printf("\nEnter your account type:\n");
	        scanf("%s",account_type);
		if((strcmp(account_type,"SA")==0) ||(strcmp(account_type,"CA")==0)) //To check account type. It should be SA or CA.
		{
	
			break;
		}
		else{
			printf("\nInvalid account type\n");
		     continue;
		}
	}

	while(1)
	{
		//Taking the input of amount
        	printf("\nEnter your amount:\n");
	        scanf("%lf",&amount);	
			if((strcmp(account_type,"SA")==0 && amount <5000) || (strcmp(account_type,"CA")==0 && amount < 10000)) //Checking if Account type is SA and then amount should be greater than 5000 and if account type is CA then amount should be greater than 10000
			{
				printf("\nMinimum amount should be less than 5000 SA and less than 10000 for CA\n");
				continue;
			}
			else
			{
				break;
			}
	}

       	strcpy(customer_id,account_type); //Copying account type in customer id
        strcat(customer_id,aadhar_no); //Concatinate customer id and addhar no

	strcpy(new2->name,name); // Storing local variable of name in pointer of customer structure
	strcpy(new2->customer_id,customer_id); //Storing  local customer_id in pointer of customer structure
	new2->aadhar_no=atoi(aadhar_no); //Typecasting and storing it in pointer
	strcpy(new2->password,password); //storing password in pointer of customer structure
	strcpy(new2->account_type,account_type); //Storing accont type in pointer of customer structure
	new2->balance=amount; //storing amount in pointer

	printf("\nYour account is created successfully!!!!\n");
	
        printf("\nThis is your customer id: %s\n",customer_id); 
	if(!start) 
	{
		start=new2;
		new2->next=NULL;
	}
	else if(strcmp(new2->customer_id, start->customer_id)<0)
	{
		new2->next=start;
		start=new2;
	}
	else
	{
		for(ptr=start;(ptr) &&(strcmp( ptr->customer_id, new2->customer_id)<0);prev= ptr ,ptr=ptr->next);
		prev->next=new2;
		new2->next=ptr;
	}
	printf("\n");
}


int View_Balance() //View balance of customer by accepting customer id
{
	if(!start) //checking if list is empty
	{
		printf("\nThere are no records in system\n");
		return(1);
	}
	char m_customer_id[20];
	printf("\nEnter Customer id:\n");
	scanf("%s",m_customer_id);
	for(ptr=start;(ptr)&& (strcmp(ptr->customer_id,m_customer_id)!=0);ptr=ptr->next);

	if(!ptr) //if pointer id NULL then customer is not found
	{
		printf("\n %s Customer id not found\n",m_customer_id);
		return(1);
	}
	printf("\nBalance is %7.2lf\n",ptr->balance);
	
}

 int customer_file_to_list() //Inserting recrods from file to list
{
//	cust *last;
	FILE *fp;                                    //File  Pointer
	if((fp=fopen("Customer_File","rb")) == NULL) //Opening a binary file for reading
	{
		return (1);
	}
	new2 = (cust *)calloc(1,sizeof(cust));        //Allocating Dynamic memory 
	fread(new2,sizeof(cust),1,fp);                //reading file
	while(!feof(fp))
	{
		//after reading data from file , inserting into the linked list
		if(!start) 
		{
			start=last=new2;
			new2->next=NULL;
		}
		else
		{
			last->next=new2;
			last=new2;
			new2->next=NULL;
		}
		new2=(cust *) calloc(1,sizeof(cust)); //Dynamically allocating memory
		fread(new2,sizeof(cust),1,fp);         //reading file
	}
}



int customer_list_to_file() //For inserting records in customer file from list
{
	FILE *fp;                                    //File pointer
	fp=fopen("Customer_File","wb");              //opening the binary file in write mode
	for(ptr=start; (ptr);ptr=ptr->next)          
	{
		fwrite(ptr,sizeof(cust),1,fp);       //Writing in file 
	}
	fclose(fp);                                 //closing the file
}


int Get_Customer_Report() //View customer report 
{
	//after reading data from file ,inserting into the linked list
	if(!start)
	{
		printf("\nEmpty File...No records in file\n");
		return(1);
	}
	printf("\n--Customer Report--\n");
	printf("\n CUSTOMER_ID    AADHAR_NO      NAME    PASSWORD    ACCOUNT_TYPE     BALANCE\n\n");  
	for(ptr=start;(ptr);ptr=ptr->next)
	{
		printf("\n %s        %d        %s         %s        %s         %8.21f \n",ptr->customer_id,ptr->aadhar_no,ptr->name,ptr->password,ptr->account_type,ptr->balance);
	}
	
  
}


int Edit_Customer() //Edit the details of customer details with all validations
{
	char  m_customer_id[20];
	int flag=0;
	char name[30];
	char  m_account_type[10];
	char m_aadhar_no[10];

	printf("\nEnter the customer id\n");
	scanf("%s",m_customer_id);
	for(ptr=start; (ptr) &&(strcmp(ptr->customer_id,m_customer_id)!=0);ptr=ptr->next);


	if(!ptr)
	{
		printf("\n%d Customer id not found\n",m_customer_id);
		return(1);
	}
	printf("\nThe old customer name %s , account type %s and balance of customer id %s is %7.21f\n",ptr->name,ptr->account_type,ptr->customer_id,ptr->balance);

	while(1)
	
	{
		sprintf(m_aadhar_no,"%d",ptr->aadhar_no);
		//Taking input of customer name
		printf("\nEnter Your Name:\n");
		fflush(stdin);
		scanf("%s",name);
		int len;
		int flag=0;
		for(int i=0;name[i]!='\0';i++)
		{
			if(!isalpha(name[i])) //isalpha() function is used to check if user gives numbers in name section then it will not accept the name 
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("Invalid name.Name should contain only alphabets\n"); 
			continue;
		}
		len=strlen(name);
		if(len<5||len>15) //Checking that length of the name should be less than 5 and greater than 15
		{
			printf("Invalid Length.Length should not exceed 15 charecters\n");
			continue;
		}
		else
		{
			break;
		}
	}
	while(1) //edit account type
	{	
		printf("\nEnter the new account type\n");
		scanf("%s",&m_account_type);
		if((strcmp(m_account_type,"SA")==0) || (strcmp(m_account_type,"CA")==0))
		{

			if(strcmp(m_account_type,"CA")==0)
			{
				if(ptr->balance<10000)
				{
					printf("\nMinimum account balance of CA should be more than Rs10000\n");
					continue;
				}
				else
				{
					strcpy(ptr->account_type,m_account_type);
					strcpy(ptr->customer_id,m_account_type);
					strcat(ptr->customer_id,m_aadhar_no);
					printf("New account type : %s",ptr->customer_id);

					break;
				}
			}
			else if(strcmp(m_account_type,"SA")==0)
			{

				strcpy(ptr->account_type,m_account_type);
				strcpy(ptr->customer_id,m_account_type);
				strcat(ptr->customer_id,m_aadhar_no);
				printf("\nNew account type : %s",ptr->customer_id);
				break;
			}
		}
		else
		{
			printf("\nInvalid account type\n");
			continue;
		}
	}
	strcpy(ptr->name,name);
}

int Delete_Customer() //Delete customer details
{
	if(!start)
	{
		printf("\nEmpty Records\n");
		return(1);
	}
	char  m_customer_id[20];
	printf("\nEnter the Customer id\n");
	scanf("%s",m_customer_id);
	if(strcmp(m_customer_id,start->customer_id)==0)
	{
		ptr=start;
		start=ptr->next;
		free(ptr);
	}
	else
	{
		for(ptr=start;(ptr) &&(strcmp (ptr->customer_id,m_customer_id)!=0);prev=ptr,ptr=ptr->next);
		if(!ptr)
		{
			printf("\n%s Customer id not found\n",m_customer_id);
			return(1);
		}
		printf("\nThe record of customer id %s deleted succesfully\n\n",ptr->customer_id);
		prev->next=ptr->next;
		free(ptr);
	}
}


int banker_file_to_list() //For insering records in list from banker file
{
	tr *last;         //last pointer
	FILE *fp;
	if((fp=fopen("Transaction_File","rb"))==NULL)  //Opening the binary file in read mode
	{
		printf("\nEmpty File...No records in file\n");
		return 1;
	}
	new1=(tr *)calloc(1,sizeof(tr)); //Dynamically allocating memory for new1 for bankers
	fread(new1,sizeof(tr),1,fp);     //reading file
	while(!feof(fp))
	{
		//after reading data from file inserting into linked list
		if(!start1)
		{
			start1=last=new1;
			new1->next=NULL;
		}
		else
		{
			last->next=new1;
			last=new1;
			new1->next=NULL;
		}
		new1=(tr *)calloc(1,sizeof(tr));
		fread(new1,sizeof(tr),1,fp);
	}
}


int banker_list_to_file()
{ 
	FILE *fp;                                  //File pointer
	fp=fopen("Transaction_File","wb");         //opening the binary file in write mode
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)    //appending data at the end
	{
		fwrite(ptr1,sizeof(tr),1,fp);      //writing in file banker
	}
	fclose(fp);  //closing the file
}

int Get_Transaction_Report() //display transaction report
{

	if(!start1)
	{
		printf("Empty List\n");
		return(1);
	}
	printf("\n--Transaction Report--\n");
	printf("\n SOURCE   DESTINATION    AMOUNT\n\n");
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
 
		printf("\n %s         %s           %7.21f \n",ptr1->saccount,ptr1->daccount,ptr1->amt);
	}
	
}



