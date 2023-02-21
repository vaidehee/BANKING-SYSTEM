/************************************************************************************
 *   FILENAME    :   submenu.c
 *
 *   DESCRIPTION :   This file is used as submenu which includes customer corner and
 *                   banker corner options that  perform various task. 
 *
 *   REVISION HISTORY
 *
 *   DATE            NAME             REASON
 *
 *  -------------------------------------------
 *   
 *   25/05/2022    Username           submenu
 * 
 * *********************************************************************************/
#include<stdio.h> // Include required header files
#include<ctype.h>
#include<stdlib.h>
#include<pthread.h>
#include"Header2.h"
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER; //Initialize mutex
pthread_t thread_id; //Initialize thread id
int Customer_Corner()
{
	int choice=0;
	while(choice!=4)
	{

//		system("clear");
		printf("\n___________________\n\n");
		printf("\n   Customer Corner \n ");
		printf("\n1. Create Account\n");
		printf("\n2. Do Transaction\n");
		printf("\n3. View Balance\n");
		printf("\n4. Back to Menu\n");
		printf("\n___________________\n\n");
		printf("\n   Enter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1 : Create_Account(); // calls Create_Account from Function.c
				 break;
			case 2 : pthread_create(&thread_id,NULL,Do_Transaction,NULL); // starting a new thread in function calling process
				 pthread_join(thread_id,NULL); // this provides a mechanism allowing an application to wait for thread to terminate
				 break;
			case 3 : View_Balance();    // calls View_Balance from Function.c
				 break;
			case 4 : break;            //returns to main menu in The Banking System 
			default : printf("\nInvalid Choice\n");
		}
	}
}

int Banker_Corner()
{
	int choice=0;
	while(choice!=6)
	{
	//	system("clear");
		printf("\n_______________________\n\n");
		printf("\n Banker's Corner\n");
		printf("1. Edit Customer Details\n");
		printf("2. Delete Customer Details\n");
		printf("3. Do Transfer\n");
		printf("4. Get Transaction Report\n");
		printf("5. Get Customer Report\n");
		printf("6. Back to Menu\n");
		printf("\n_________________________\n\n");
		printf("\nEnter your Choice:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1 : Edit_Customer();   // calls Edit_Customer from Function.c
				 break;
			case 2 : Delete_Customer();  // calls Delete_Customer from Function.c
				 break;
			case 3 :pthread_create(&thread_id,NULL, Do_Transfer,NULL);// calls Do_Transfer from Function.c
			        pthread_join(thread_id,NULL);
				 break;
			case 4 : Get_Transaction_Report();  // calls from Get_Transaction_Report from Function.c
				 break;
			case 5 : Get_Customer_Report(); // calls Get_Customer_Report from Function.c
				 break;
			case 6 : break;
			default : printf("\n Invalid Choice\n");
		}
	}
}
int Do_Transaction()//allows user to withdraw and deposit amount
{
	int token,auto_token;
	time_t t1;
	int choice=0;
	double amount=0;
	char m_customer_id[20];
	double b_amount=0;
	printf("\nEnter\n1: Withdraw\n2. Deposit\n3. Back to menu\n");
	scanf("%d",&choice);
	if(choice==3)
		return 0;
	printf("\nEnter your Customer id\n");
	scanf("%s",m_customer_id); 
	for(ptr=start;(ptr);ptr=ptr->next)
	{
		if(strcmp(ptr->customer_id,m_customer_id)!=0)
		{

			printf("\n Customer ID  not found!!!\n");
			return 0;
		}
	}
	srand((unsigned) time(&t1));//generates a random unique number for token
	auto_token=rand() % 50;
        pthread_mutex_lock(&lock); //release mutex object
	printf("\n Your token for current transaction is %d\n",auto_token);
	pthread_mutex_unlock(&lock); //lock a mutex object which identifies a mutex
	printf("\n PLEASE CONFIRM YOUR TOKEN\n");
	scanf("%d",&token);
	if(token==auto_token)//checks the token 
	{

		if(choice==1)//withdraw option
		{
			for(ptr=start;(ptr)&&(strcmp(ptr->customer_id,m_customer_id)!=0);ptr=ptr->next);
			if(ptr==NULL)//checks if pointer is null then it will print id is not found else it will do transaction 
			{
				printf("\n%s Customer id is not Found\n",m_customer_id);

				return 0;
			}
			else
			{
				printf("\nAvailable balance is: %7.2lf\n",ptr->balance);
				while(1)
				{
					printf("\nEnter Amount to withdraw:\n ");
					scanf("%lf",&amount);
					b_amount=ptr->balance-amount;


					if((strcmp(ptr->account_type,"SA")==0 && b_amount <5000) || (strcmp(ptr->account_type,"CA")==0 && b_amount < 10000)) //checks if account typr is SA then amount should be greater than 5000 and if account type is CA then amount should be greater than 10000.
					{
						printf("\nCannot Withdraw amount....Low Balance\n");
						break;
					}
					else if((strcmp(ptr->account_type,"SA")==0 && amount >50000) || ((strcmp(ptr->account_type,"CA")==0) && amount > 100000)) //check if account type is SA then amount should be less than 50000 and if account type is CA then amount should be less than 100000.
					{
						printf("\nAmount cannot be greater than 50000 for Savings Account and 100000 for Current Account\n");
						continue;
					}
					else
					{
						ptr->balance = ptr->balance-amount; //Storing transaction in pointer
						printf("\nCurrent Balance: %7.2lf\n",ptr->balance);
						printf("\nRs. %lf Withdrawn\n",amount);
						break;
					}
				}

			}
		}
		if(choice==2)//Deposit Option
		{
			for(ptr=start;(ptr)&&(strcmp(ptr->customer_id,m_customer_id)!=0);ptr=ptr->next);

				if(ptr==NULL) //checks if customer id is valid if not then it will print customer id not found
				{
					printf("\n%s Customer id not found\n",m_customer_id);

					return 0;
				}
				else
				{
					while(1)

					{
						printf("\nEnter Amount to deposit:\n ");
						scanf("%lf",&amount);
						if((strcmp(ptr->account_type,"SA")==0 && amount >50000) || ((strcmp(ptr->account_type,"CA")==0) && amount > 100000))//checks the condition if account type is SA then amount should be less than 50000 and if account type is CA then amount should be less than 100000
						{
							printf("\nAmount cannot be greater than 50000 for Savings Account and 100000 for Current Account\n");
							continue;
						}
						else
						{
							ptr->balance = ptr->balance+amount;//storing transaction in pointer
							printf("\nCurrent Balance: %7.2lf\n",ptr->balance);
							printf("\nRs. %lf Deposited\n",amount);
							break;
						}


					}
				}
			}

	}
	else
	{
		return 0;
	}
}

int Do_Transfer()// Transfer money from one account to another account
{
	char saccount[15];
	char daccount[15];
	double amt;
	int token,auto_token;
	time_t t1;
	tr *new1=(tr *)malloc(sizeof(tr));//Dynamic memory allocation for transaction
	double amount=0,after_balance=0;
	int Banker_Pass=0;
	Banker_Pass=checkpassword(); //storing the password
	if(Banker_Pass==1)//checking the password and if its wroong it wiil print invalid password
	{
		printf("\nINVALID PASSWORD!!!\n");
		return 0;
	}
	else
	{

		printf("\n-------Transfor Money-------\n");


		printf("\nSource Account Customer ID-\n");
		scanf("%s",saccount);
		for(ptr=start;(ptr);ptr=ptr->next)
		{
			if(strcmp(ptr->customer_id,saccount)!=0)
			{

				printf("\n Source account not found!!!\n");
				return 0;
			}
		}
		printf("\nDestination Account Number/Id\n");
		scanf("%s",daccount);
		for(ptr=start;(ptr);ptr=ptr->next)
		{
			if(strcmp(ptr->customer_id,daccount)!=0)
			{

				printf("\n Destination  account not found!!!\n");
				return 0;
			}
		}
		printf("\nEnter Amount To Transfer\n");
		scanf("%lf",&amt);
		srand((unsigned) time(&t1)); //generates random unique token no
		auto_token=rand() % 50;
                pthread_mutex_lock(&lock); //lock mutex object
	
		printf("\n YOUR TOKEN FOR CURRENT TRANSACTION IS %d\n",auto_token);
                pthread_mutex_unlock(&lock); //release mutex object
		printf("\n PLEASE CONFIRM YOUR TOKEN\n");
		scanf("%d",&token);
		if(token==auto_token) //checks the token number
		{
			for(ptr=start;(ptr);ptr=ptr->next)
			{
				if((strcmp(ptr->customer_id,saccount)==0))
				{
					after_balance=ptr->balance-amt;
					while(1)
					{
						if((strcmp(ptr->account_type,"SA")==0 && after_balance<5000) || (strcmp(ptr->account_type,"CA")==0 && after_balance < 10000)) //checks if account type is SA then amount should be greater than 5000 and if account type is CA then amount should be greater than 10000
						{
							printf("Can't Transfer. You are at low balance\n");
							continue;
						}

						if((strcmp(ptr->account_type,"SA")==0 && amt >50000) || (strcmp(ptr->account_type,"CA")==0 && amt > 100000)) //checks if account type is SA then amount should be less than 50000 and if account type is CA then amount should be less than 100000
						{
							printf("Amount cannot be greater than 50000 for Savings Account and 100000 for Current Account");
							continue;
						}
						else
						{
							printf("After deduction %7.2lf\n",after_balance);
							ptr->balance = ptr->balance-amt;//storing the amount in pointer	
							printf("Rs. %lf Debited\n",amt);
							printf("Current Balance: %7.2lf\n",ptr->balance);
							break;
						}
					}

				}

				if(strcmp(ptr->customer_id,daccount)==0)
				{
					ptr->balance=ptr->balance+amt;//storing amount in pointer
					printf("Rs. %7.2lf credited to account\n",amt);
					printf("Your balance is Rs. %7.2lf\n",ptr->balance);
					return 0;

				}
			}
		}
		else
		{
			printf("\n INVALID TOKEN!!!!!\n");
			return 0;
		}
		strcpy(new1->saccount,saccount);//storing local variable of source account  in structure variable to create linked list
		strcpy(new1->daccount,daccount);//storing local variable of destination account in structure variable to create linked list
		new1->amt=amt;
		if(!start1)//empty list
		{
			start1=new1;
			last1=new1;
			new1->next=NULL;


		}
		else
		{
			last1->next=new1;
			last1=new1;
			new1->next=NULL;

		}
		printf("\n");
	}
}
