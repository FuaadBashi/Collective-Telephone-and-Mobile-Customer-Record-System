#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "customer.c"



static int Menu(){
    int option;

    printf("\n WELCOME TO THE COLLECTIVE TELEPHONE AND MOBILE CUSTOMER RECORD\n");
    printf("----------------------------------------------------------------\n");

    printf("(1): \t Add new customer\n");
    printf("(2): \t View customers\n");
    printf("(3): \t Modify customer\n");
    printf("(4): \t Delete customer\n");
    printf("(5): \t Get all customers \n");
    // printf("(6): \t Payment History \n");
    printf("(0): \t EXIT \n");
    printf("----------------------------------------------------------------\n");

    printf("TYPE YOUR OPTION BY NUMBER(format = 3); \n");


    scanf("%d", &option);

    // return atoi(op);
    return option;
}


customer addCustomer(){
    customer customer;
    newCustomer(&customer);
    for (int i = 0; i < _SIZE; i++) {
        if (customers[i].name == NULL){
            customers[i] = customer;
            break;
        }
    }
    return customer;
}

void printCustomer( customer *c ){
    printf("\n®Customer name: %s\n ®PhoneNumber: +0%d %ld\n ®Balance: %f\n",c -> name,  c -> areaCode, c -> phoneNumber, c -> balance);
}

bool viewCustomer(){
    int choice1;
    char choice2[_SIZE];
    long choice3;

    printf("(1):\t NAME OF CUSTOMER YOU WANT TO VIEW \n");
    printf("(2):\t NUMBER OF CUSTOMER YOU WANT TO VIEW \n");
    printf("format(1 or 2)\n");
    scanf("%d", &choice1);

    switch (choice1)
    {
        case 1:
        printf("TYPE (NAME) OF CUSTOMER YOU WANT TO VIEW: \n");
        scanf("%s", choice2);
        printf("test 1");
        break;

        case 2:
        printf("TYPE (NUMBER) OF CUSTOMER YOU WANT TO VIEW: \n");
        scanf("%ld", &choice3);
        break;

        default:
        return false;
        break;

    }
    printf("\n%s\n", choice2);

    int size = sizeof(customers);
    
    for (int i = 0; i < size; i++) {


        if (customers[i].name != NULL){

            if (strcmp(customers[i].name , choice2) == 0 || customers[i].phoneNumber == choice3){
            
            printCustomer(&customers[i]);
            return true;
            }
        }
    }
    return false;
}

void getAllCustomers(){
    for (int i = 0; i < _SIZE; i++) {
        if (customers[i].name != NULL){
            printCustomer(&customers[i]);
        }
    }
}

bool deleteCustomer(){
    int choice1;
    char choice2[_SIZE];
    long choice3;

    printf("(1):\t NAME OF CUSTOMER YOU WANT TO DELETE \n");
    printf("(2):\t NUMBER OF CUSTOMER YOU WANT TO DELETE \n");
    scanf("%d", &choice1);

    switch (choice1)
    {
        case 1:
        printf("TYPE (NAME) OF CUSTOMER YOU WANT TO DELETE: \n");
        scanf("%s", choice2);
        break;

        case 2:
        printf("TYPE (NUMBER) OF CUSTOMER YOU WANT TO DELETE \n");
        scanf("%ld", &choice3);
        break;

        default:
        return false;
        break;

    }

    for (int i = 0; i < _SIZE; i++) {
        if (strcmp(customers[i].name , choice2) == 0  || customers[i].phoneNumber == choice3){
            customer c = {  .name = NULL,
                            .phoneNumber = 0,
                            .areaCode = 0,
                            .balance = 0,
                    
            };
            customers[i] = c;
            return true;
        }
    }
    return false;
}

bool ModifyCustomer(){
    int choice1;
    char *choice2 = (char *)malloc(_SIZE * sizeof(char));
    long choice3;
    
    printf("(1):\t NAME OF CUSTOMER YOU WANT TO MODIFY \n");
    printf("(2):\t NUMBER OF CUSTOMER YOU WANT TO MODIFY \n");
    scanf("%d", &choice1);


   switch (choice1)
   {
        case 1:
        printf("TYPE (NAME) OF CUSTOMER YOU WANT TO MODIFY: \n");
        scanf("%s", choice2);
        break;

        case 2:
        printf("TYPE (NUMBER) OF CUSTOMER YOU WANT TO MODIFY \n");
        scanf("%ld", &choice3);
        break;

        default:
        return false;
        break;
    }
    printf("test");
    int size = sizeof(customers);

    for (int i = 0; i < size; i++) {
        printf("%d", i);
        if (strcmp(customers[i].name , choice2) == 0 || customers[i].phoneNumber == choice3){
            customer c = {  .name = NULL,
                            .phoneNumber = 0,
                            .areaCode = 0,
                            .balance = 0,
                    
            };
            customers[i] = c;
            customers[i] = addCustomer();
            free(choice2);
            return true;
        }
    }

    return false;
}

bool initOptions(int option){
    bool worked;
    switch (option)
    {
    case 1:
        addCustomer();
        return false;
        break;
    
    case 2:
        worked = viewCustomer();
        if (worked == false) {
            printf("\nA MISTAKE WHILST TYPING WAS MADE\n");
            return false;
        }
        return false;
        break;
    
    case 3:
        worked = ModifyCustomer();
        if (worked == false) {
            printf("\nA MISTAKE WHILST TYPING WAS MADE\n");
        }
        return false;
        break;
    
    case 4:
        worked = deleteCustomer();
        if (worked == false) {
            printf("\nA MISTAKE WHILST TYPING WAS MADE\n");
        }
        return false;
        break;
    
    case 5:
        getAllCustomers();
        return false;
        break;

    // case 6:
    //     paymentHistory();
    //     break;

    case 0:
        for (int i = 0; i < _SIZE; i++) {
            printCustomer(&customers[i]);
        }
        return true;
        break;
    
    default:
        printf("The option you picked has not worked, try again.\n");
        printf("%d\n", option);
     
        break;
    }
    return false;
}
