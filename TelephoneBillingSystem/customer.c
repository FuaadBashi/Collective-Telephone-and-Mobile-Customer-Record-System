#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "company.c"
#include "customer.h"

#define MAX 100000000
// ddddddddddd 5416968064
#define MIN 10000000


typedef struct customer customer;
typedef struct company company;
typedef enum companyNames companyNames;

#define NULL  __DARWIN_NULL



char* setName(){
    // char name[100];
    char* name = (char *) malloc( sizeof(char));
    printf("Type your FIRST NAME: \n");
    scanf("%s", name);
    return name;
}

long setPhonenNumber(){
    unsigned int val1seed = time(0);
    long rd_num = rand_r(&val1seed) % (MAX - MIN + 1) + MIN;
    printf("NUMBER(without area-code): %ld\n", rd_num);
    return rd_num;
}

int setAreaCode(){
    char pick[10];
    printf("\n WHICH COUNTRY DO LIVE IN?:(AU, UK, USA, UAE, DE, SO, IR) \n");
    scanf("%s", pick);

    for(int i = 0; i < 10; i++){
        pick[i] = toupper(pick[i]);
    }
    
    if (strcmp(pick ,"AU") == 0) {
        return 23;
    }
    if (strcmp(pick ,"UK") == 0) {
        return 79;
    }
    if (strcmp(pick ,"USA") == 0) {
        return 27;
    }
    if (strcmp(pick ,"UAE") == 0) {
        return 971;
    }
    if (strcmp(pick ,"UAE") == 0) {
        return 10;
    }
    if (strcmp(pick ,"SO") == 0) {
        return 20;
    }
    if (strcmp(pick ,"IR") == 0) {
        return 66;
    }
    return 0;
}

float setBalance(company *c){
    if (c != NULL){
         printf("\n %f",c -> totalBill);
        return c -> totalBill;
    }
    printf("zero balance");
    return 0.00;
}


struct customer
{
    char *name;
    long phoneNumber;
    int areaCode;
    struct company company;
    float balance;
};


customer customers[_SIZE];

 
void newCustomer( customer *this ){
    this -> name = setName();
    this -> phoneNumber = setPhonenNumber();
    // this -> phoneNumber = 100000000001;
    this -> areaCode = setAreaCode();
    company c;
    initCompany(&c);
    this -> company = c;
    this -> balance = setBalance(&c);
}
