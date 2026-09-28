#include "plans.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>

static const Plan PLANS[] = {
    {PROVIDER_DU, 'A', "20GB data, 100 minutes (no international), 100 texts", 1000, 500, 2000},
    {PROVIDER_DU, 'B', "60GB data, 100 minutes (with international), 100 texts", 3000, 500, 4500},
    {PROVIDER_EE, 'A', "1GB data, 200 minutes (with international), 100 texts", 1500, 0, 2000},
    {PROVIDER_EE, 'B', "15GB data, 300 minutes (with international), 300 texts", 2000, 0, 4500},
    {PROVIDER_T_MOBILE, 'A', "10GB data, 400 minutes (no international), 500 texts", 1000, 500,
     2000},
    {PROVIDER_T_MOBILE, 'B', "30GB data, 600 minutes (with international), 500 texts", 2000, 500,
     4500},
};

/* International dialling codes. The originals were wrong (UK was 79, USA 27) and DE was missing. */
static const Country COUNTRIES[] = {
    {"AU", 61}, {"UK", 44}, {"USA", 1}, {"UAE", 971}, {"DE", 49}, {"SO", 252}, {"IR", 98},
};

const char *provider_name(Provider provider) {
    switch (provider) {
    case PROVIDER_EE:
        return "EE";
    case PROVIDER_DU:
        return "du";
    case PROVIDER_T_MOBILE:
        return "T-Mobile";
    default:
        return "unknown";
    }
}

bool provider_parse(const char *text, Provider *out) {
    if (strcasecmp(text, "EE") == 0) {
        *out = PROVIDER_EE;
    } else if (strcasecmp(text, "DU") == 0) {
        *out = PROVIDER_DU;
    } else if (strcasecmp(text, "T-MOBILE") == 0 || strcasecmp(text, "TMOBILE") == 0) {
        *out = PROVIDER_T_MOBILE;
    } else {
        return false;
    }
    return true;
}

const Plan *plan_find(Provider provider, char code) {
    code = (char)toupper((unsigned char)code);
    for (size_t i = 0; i < sizeof PLANS / sizeof PLANS[0]; ++i) {
        if (PLANS[i].provider == provider && PLANS[i].code == code) {
            return &PLANS[i];
        }
    }
    return NULL;
}

const Plan *plans_for(Provider provider, int *count) {
    const Plan *first = NULL;
    *count = 0;
    for (size_t i = 0; i < sizeof PLANS / sizeof PLANS[0]; ++i) {
        if (PLANS[i].provider == provider) {
            if (first == NULL) {
                first = &PLANS[i];
            }
            ++*count;
        }
    }
    return first;
}

int monthly_bill_cents(const Plan *plan, PaymentType payment) {
    return payment == PAY_CONTRACT ? plan->contract_monthly_cents : plan->payg_monthly_cents;
}

int first_bill_cents(const Plan *plan, PaymentType payment) {
    int deposit = payment == PAY_CONTRACT ? plan->contract_deposit_cents : 0;
    return monthly_bill_cents(plan, payment) + deposit;
}

const Country *country_find(const char *code) {
    for (size_t i = 0; i < sizeof COUNTRIES / sizeof COUNTRIES[0]; ++i) {
        if (strcasecmp(COUNTRIES[i].name, code) == 0) {
            return &COUNTRIES[i];
        }
    }
    return NULL;
}

const Country *countries(int *count) {
    *count = (int)(sizeof COUNTRIES / sizeof COUNTRIES[0]);
    return COUNTRIES;
}
