#ifndef CUSTOMER
#define CUSTOMER


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define _SIZE 30

typedef uint32_t u32;
typedef struct customer customer;
typedef struct company company;
typedef enum companyNames companyNames;


enum companyNames {EE, DU, TMOBILE};

struct company;

void initCompany(company *c);

void freeCompany(company *c);

struct customer;

void newCustomer(customer *c);

void freeCustomer(customer *c);

customer addCustomer();

void printCustomer( customer *c );

bool viewCustomer();

void getAllCustomers();

bool deleteCustomer();

bool ModifyCustomer();

bool initOptions(int option);


















#endif