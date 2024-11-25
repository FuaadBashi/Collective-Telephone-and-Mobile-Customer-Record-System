#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "customer.h"

typedef struct customer customer;
typedef struct company company;
typedef enum companyNames companyNames;



// char* toLower(char* s) {
//   for(char *p=s; *p; p++) *p=tolower(*p);
//   return s;
// }


char *contractPlanOptions[3][3] = { "DU",       "PLAN A::  Data: 20GB,  Miniutes(WITHOUT international): 100,  Texts: 100 ($10/month(12 months WITH $5 deposist) OR $20 Pay-as-you-go)", 
                                                "PLAN B:;  Data: 60GB,  Miniutes(WITH international): 100,  Texts: 100 ($30/month(12 months WITH $5 deposist) OR $45 Pay-as-you-go)",
                                    "EE",       "PLAN A::  Data: 1GB,  Miniutes(WITH international): 200,  Texts: 100 ($15/month(12 months WITHOUT $5 deposist)) OR $20 Pay-as-you-go)", 
                                                "PLAN B:;  Data: 15GB,  Miniutes(WITH international): 300,  Texts: 300 ($20/month(12 months WITHOUT $5 deposist)) OR $45 Pay-as-you-go)",
                                    "TMOBILE",  "PLAN A::  Data: 10GB,  Miniutes(WITHOUT international): 400,  Texts: 500 ($10/month(12 months WITH $5 deposist)) OR $20 Pay-as-you-go)", 
                                                "PLAN B:;  Data: 30GB,  Miniutes(WITH international): 600,  Texts: 500 ($20/month(12 months WITH $5 deposist) OR $45 Pay-as-you-go)"};


/*prints out the all the plans available for each provider contract*/
void printOutCompanyPlans(){


    printf("%s prodives these options:\t\t%s,\t%s \n", contractPlanOptions[0][0], contractPlanOptions[0][1], contractPlanOptions[0][2]);
    printf("%s prodives these options:\t\t%s,\t%s \n", contractPlanOptions[1][0], contractPlanOptions[1][1], contractPlanOptions[1][2]);
    printf("%s prodives these options:\t%s,\t%s \n",   contractPlanOptions[2][0], contractPlanOptions[2][1], contractPlanOptions[2][2]);
}

/* Picks out the all the plans available for each provider contract*/
static char* pickCompany(){

    printOutCompanyPlans();

    char *pick = (char *)malloc( sizeof(char));
    enum companyNames names;

    
    printf("Pick a provider (EE, DU, T-Mobile):\n ");
    scanf("%s", pick);

    // for ( ; pick; ++pick) pick = tolower(&pick);

    for(int i = 0; pick[i]; i++){
        pick[i] = tolower(pick[i]);
    }

    if (strstr(pick, "ee")!= NULL){
        names = EE;
    }
    if (strstr(pick, "du")!= NULL){
        names = DU;
    }
    if (strstr(pick, "t-mobile")!= NULL || strstr(pick, "tmobile")!= NULL){
        names = TMOBILE;
    }
 
    switch (names) 
   {
      case EE: return "EE";
      case DU: return "DU";
      case TMOBILE: return "T-MOBILE";
      default: return "NULL";
   }

}


static char pickPlan(char *company){

    char pick[10];
    char picked;
    printf("Available plans: \n");

    if (strcmp(company , "EE") == 0 ){
    printf("%s prodives these options:\n%s,\n%s \n\n", contractPlanOptions[1][0], contractPlanOptions[1][1], contractPlanOptions[1][2]);
         scanf("%s", pick);
    }

    if (strcmp(company , "DU") == 0 ){
       printf("%s prodives these options:\n%s,\n%s \n\n", contractPlanOptions[0][0], contractPlanOptions[0][1], contractPlanOptions[0][2]);
        scanf("%s", pick);
    }
    
    if (strcmp(company , "T-MOBILE") == 0){
        printf("%s prodives these options:\n%s,\n%s \n\n",   contractPlanOptions[2][0], contractPlanOptions[2][1], contractPlanOptions[2][2]);
        scanf("%s", pick);
    }
    
    for(int i = 0; pick[i]; i++){
        pick[i] = toupper(pick[i]);
    }

    return pick[0];
}


static bool pickPaymentPlan(){
    int picked;
    printf("Available PAYMENT plans: \n");
    printf("(CONTRACTS NEED A ONE TIME DEPOSIT PAYMENT OF $5)");
    printf("1: 12 month contract, \t 2: Pay-As-You-Go: \n");
    scanf("%i", &picked);
    if (picked == 1) {
        return false;
    }
    return true; // True = paygo, False = contract
}

static float calcBill( char pickedPlan, bool pickedPayment ){

    if (pickedPlan == 'A' && pickedPayment){
        printf("%f\n",20.00);
        return 20.00;
    };
    if (pickedPlan == 'A' && !pickedPayment){
        printf("%f\n",15.00);
        return 15.00;
    };
    if (pickedPlan == 'B' && pickedPayment){
        printf("%f\n",45.00);
        return 45.50;
    };
    if (pickedPlan == 'B' && !pickedPayment){
        printf("%f\n",30.00);
        return 30.00;
    };
    printf("%f\n",0.00);
    return 0.00;
}

char* getCompanyName(enum companyNames names) 
{
   switch (names) 
   {
      case EE: return "EE";
      case DU: return "DU";
      case TMOBILE: return "T-Mobile";
      default: return "NULL";
   }
}

struct company
{
    char *name;
    char contractPlan;
    bool paymentType;
    float totalBill;
};


void initCompany(company *this) {

    this -> name = pickCompany();
    this -> contractPlan = pickPlan(this -> name);
    this -> paymentType = pickPaymentPlan();
    this -> totalBill = calcBill(this -> contractPlan, this -> paymentType);

}

void freeCompany(company *this){
    free(this);
}