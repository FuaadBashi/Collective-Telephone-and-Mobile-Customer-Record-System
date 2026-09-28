#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "plans.h"

#include <stdbool.h>
#include <stddef.h>

#define CUSTOMER_NAME_MAX 64
#define MAX_CUSTOMERS 100

typedef struct {
    char name[CUSTOMER_NAME_MAX];
    const Country *country;
    long phone_number; /* 9 digits, unique within the book */
    const Plan *plan;
    PaymentType payment;
} Customer;

typedef struct {
    Customer entries[MAX_CUSTOMERS];
    size_t count;
    unsigned int rng_state;
} CustomerBook;

/* The seed makes number allocation reproducible in tests. */
void book_init(CustomerBook *book, unsigned int seed);

/* Assigns a fresh phone number and stores a copy. Returns NULL when the book is full. */
const Customer *book_add(CustomerBook *book, const char *name, const Country *country,
                         const Plan *plan, PaymentType payment);

/* Searches only the occupied entries, so an empty slot can never be dereferenced. */
Customer *book_find_by_name(CustomerBook *book, const char *name);
Customer *book_find_by_number(CustomerBook *book, long phone_number);

bool book_remove(CustomerBook *book, const Customer *customer);

#endif /* CUSTOMERS_H */
