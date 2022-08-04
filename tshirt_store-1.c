#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
Author:Geonhee Choi project8-> This program's read_line function read 
 the student organization,size->and then, add node as inventory parameter->  search tshirt by name of organization,size 
and then print the organization's name,size,t-shirt price, quantity-> clear inventory (list)



*/


//////////////////////
// data definitions //
//////////////////////

#define ORG_NAME_LEN 50
#define SIZE_LEN 3

struct tshirt {
	char org_name[ORG_NAME_LEN+1];
	char size[SIZE_LEN+1];
	double price;
	int quantity;
	struct tshirt *next;
};

/////////////////////////
// function prototypes //
/////////////////////////

struct tshirt *add_to_inventory(struct tshirt *inventory);
void search_by_organization(struct tshirt *inventory);
void search_by_size(struct tshirt *inventory);
void print_inventory(struct tshirt *inventory);
void clear_inventory(struct tshirt *inventory);
int read_line(char str[], int n);
void help();

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main() {
	char code;

	struct tshirt *inventory = NULL;

	help();
	printf("\n");

	for (;;) {
		// read operation code
		printf("Enter operation code: ");
		scanf(" %c", &code);
		printf("%c",code);
		while(getchar() != '\n') /* skips to end of line */
			;

		// run operation
		switch (code) {
			case 'a':
				inventory = add_to_inventory(inventory);
				break;
			case 'h':
				help();
				break;
			case 'o':
				search_by_organization(inventory);
				break;
			case 's':
				search_by_size(inventory);
				break;
			case 'p':
				print_inventory(inventory);
				break;
			case 'q':
				clear_inventory(inventory);
				return 0;
			default:
				printf("Illegal operation code!\n");
		}
		printf("\n");
	}
}


  
//////////////////////////
// function definitions //
//////////////////////////

void help() {
	printf("List of operation codes:\n");
	printf("\t'a' for adding a t-shirt to the inventory;\n");
	printf("\t'h' for help;\n");
	printf("\t'o' for searching t-shirts by organization;\n");
	printf("\t's' for searching t-shirts by size;\n");
	printf("\t'p' for printing the inventory;\n");
	printf("\t'q' for quit.\n");
}

struct tshirt *add_to_inventory(struct tshirt *inventory) {

  struct tshirt *new_t; //used to keep track of new t-shirt  added
  struct tshirt *cur_t;
  new_t = malloc(sizeof(struct tshirt)); //allocates enough memory for new tshirt information entered

  if (new_t == NULL) //if the new tshirt inventory is empty, no memory is allocated
  {
    printf("malloc failed in add_to_list\n");
    return inventory; //inventory is returned in response
  }

  //Ask the user to enter a student organization, size
  printf("Enter student organization name:\n");
  read_line(new_t->org_name,ORG_NAME_LEN);
  printf("%s\n",new_t->org_name);

  printf("Enter t-shirt size:\n");
  read_line(new_t->size, SIZE_LEN );
  printf("%s\n",new_t->size);
  //Checks whether the tshirt exited, check organization's name,size
  //If the inventory has same student organization,size as an existing tshirt in the inventory,
  //the function prints a message about the tshirt  existing already, and it exits the function.

 for (cur_t = inventory; cur_t != NULL; cur_t = cur_t->next)
  {
    if (strcmp(cur_t->org_name, new_t->org_name) == 0&& strcmp(cur_t->size, new_t->size) == 0)
    {
      printf("this t-shirt already exits\n");
      return inventory;
    }
  }

  //after tshirt is not duplicated , ask for the price and quantity
  printf("Enter price:\n");
  scanf("%lf", &new_t->price);
  printf("%g\n",new_t->price);
  printf("Enter quantity\n");
  scanf("%d", &new_t->quantity);
  printf("%d\n",new_t->quantity);


  new_t->next = NULL;

  //if the inventory is empty, it adds information from new_tshirt to inventory
  if (inventory == NULL)
  {
    inventory= new_t;
  }
  else
  {

    struct tshirt*last_t= inventory; //purpose is to add to the end of inventory

    while (last_t->next != NULL)
    {
      last_t = last_t->next;
    }

    last_t->next = new_t; //updates inventory  with the last tshirt
  }

  return inventory; //returns new inventory

	


}


void search_by_organization(struct tshirt *inventory) {

   struct tshirt *temp; //make pointer
    char search_a[ORG_NAME_LEN];//search t shirt array

  printf("Enter Student Organization: 1\n ");
  read_line(search_a, ORG_NAME_LEN + 1); //read orgnation name
  printf("%s\n",search_a);
  int flag = 0; //flag=0

  for (temp = inventory; temp != NULL; temp = temp->next)//iterate
  {
    if (strcmp(temp->org_name, search_a) == 0)//find if org_name alredy exits
    {
      flag = 1;


        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| Student organization                               | Sz. | Price | Qty. |\n");
        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| %-50s | %-3s | %5.2f | %4d |\n", temp->org_name, temp->size,temp->price,temp->quantity);
        printf("|----------------------------------------------------|-----|-------|------|\n");



        
    }
  }

  if (flag  == 0)  //if flag is 0 print no tshirt
  {
    printf(" No t-shirt found!\n");
  }


  }
 
  

void search_by_size(struct tshirt *inventory) {
 
  char search_t[SIZE_LEN];
  
  struct tshirt *tem;//make pointer to find tshirt
 

  printf("Enter size\n");  //ask size
  read_line(search_t, SIZE_LEN);//read size
  printf("%s\n",search_t);  //print tshirt


  int exists = 0;//flag as exits

  for (tem = inventory; tem != NULL; tem = tem->next)
  {
    if (strcmp( search_t,tem->size) == 0)  //find if size is same
    {
      exists = 1;
        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| Student organization                               | Sz. | Price | Qty. |\n");
        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| %-50s | %-3s | %5.2f | %4d |\n", tem->org_name, tem->size,tem->price,tem->quantity);
        printf("|----------------------------------------------------|-----|-------|------|\n");


   

    }
  }

  if (exists == 0) //if fail
  {
    printf("No t-shirt found!\n");
  } //no tshirt find




}
//print all student organization,size, price,quantity
void print_inventory(struct tshirt *inventory) {

   struct tshirt *p;
  for (p = inventory; p != NULL; p = p->next)
  {






	printf("|----------------------------------------------------|-----|-------|------|\n");
	printf("| Student organization                               | Sz. | Price | Qty. |\n");
	printf("|----------------------------------------------------|-----|-------|------|\n");
	printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size,p->price,p->quantity);
	printf("|----------------------------------------------------|-----|-------|------|\n");
}
}


void clear_inventory(struct tshirt *inventory) {
//clear the inventory list
	
  struct tshirt *p;
  while(inventory!= NULL)
  {
	    p = inventory;
      inventory = inventory->next;
      if( p!= NULL)
           free(p);
  }



}
//read all
int read_line(char str[], int n) {
	int ch, i=0;

	while (isspace(ch = getchar()))
		;
	str[i++] = ch;
	while ((ch = getchar()) != '\n') {
		if (i < n)
			str[i++] = ch;    
	}
	str[i] = '\0';
	return i;
}

