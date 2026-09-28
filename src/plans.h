#ifndef PLANS_H
#define PLANS_H

#include <stdbool.h>

typedef enum { PROVIDER_EE, PROVIDER_DU, PROVIDER_T_MOBILE, PROVIDER_COUNT } Provider;

typedef enum { PAY_CONTRACT, PAY_AS_YOU_GO } PaymentType;

typedef struct {
    Provider provider;
    char code; /* 'A' or 'B' */
    const char *allowance;
    int contract_monthly_cents;
    int contract_deposit_cents;
    int payg_monthly_cents;
} Plan;

typedef struct {
    const char *name;
    int dialling_code;
} Country;

const char *provider_name(Provider provider);
/* Case-insensitive; accepts "T-Mobile" or "TMobile". Returns false if unknown. */
bool provider_parse(const char *text, Provider *out);

/* Returns NULL if the provider has no plan with that code. */
const Plan *plan_find(Provider provider, char code);
const Plan *plans_for(Provider provider, int *count);

/* Money is integer cents throughout: floats drifted (a $45.00 plan was billed $45.50). */
int first_bill_cents(const Plan *plan, PaymentType payment);
int monthly_bill_cents(const Plan *plan, PaymentType payment);

/* Case-insensitive country code such as "UK"; returns NULL if unknown. */
const Country *country_find(const char *code);
const Country *countries(int *count);

#endif /* PLANS_H */
