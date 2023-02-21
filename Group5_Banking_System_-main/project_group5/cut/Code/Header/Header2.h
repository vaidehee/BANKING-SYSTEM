#ifndef HEADER2_H          
#define HEADER2_H           
typedef struct Customer     //Customer Structure
{
	char customer_id[15];
	int aadhar_no;
	char name[30];
	char password[10];
	char account_type[10];
	double balance;
	struct Customer *next;
}cust;

typedef struct Transaction  //Transaction structure
{
	char saccount[15];
	char daccount[15];
	double amt;
	struct Transaction *next;
}tr;

tr *start1,*last1,*new1,*ptr1,*prev1;  //Declaring pointers for transaction structure

//Function Declaration of menus and submenus
int Create_Account();
int Do_Transaction();
int View_Balance();
int Edit_Customer();
int Delete_Customer();
int Do_Transfer();
int Get_Transaction_Report();
int Get_Customer_Report();
int customer_file_to_list(); 
int customer_list_to_file();
int banker_file_to_list();
int banker_list_to_file();
cust *start,*last,*new2,*ptr,*prev;           //Declaring pointers for customer structure

ssize_t password(char **pw,size_t sz,int mask,FILE *fp); 
//Function Declaration of password
int checkpassword(); 
char *getpassword();
char *pt;
#endif
