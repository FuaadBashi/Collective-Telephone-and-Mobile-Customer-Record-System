#include "../src/customers.h"
#include "../src/plans.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures = 0;

#define CHECK(condition)                                                                           \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #condition);          \
            failures++;                                                                            \
        }                                                                                          \
    } while (0)

static void each_provider_bills_its_own_prices(void) {
    CHECK(monthly_bill_cents(plan_find(PROVIDER_DU, 'A'), PAY_CONTRACT) == 1000);
    CHECK(monthly_bill_cents(plan_find(PROVIDER_EE, 'A'), PAY_CONTRACT) == 1500);
    CHECK(monthly_bill_cents(plan_find(PROVIDER_T_MOBILE, 'B'), PAY_CONTRACT) == 2000);
    CHECK(monthly_bill_cents(plan_find(PROVIDER_EE, 'B'), PAY_AS_YOU_GO) == 4500);
}

static void a_contract_first_bill_includes_the_deposit_where_one_applies(void) {
    CHECK(first_bill_cents(plan_find(PROVIDER_DU, 'B'), PAY_CONTRACT) == 3500);
    CHECK(first_bill_cents(plan_find(PROVIDER_EE, 'B'), PAY_CONTRACT) == 2000);
    CHECK(first_bill_cents(plan_find(PROVIDER_DU, 'B'), PAY_AS_YOU_GO) == 4500);
}

static void plan_codes_are_case_insensitive_and_unknown_ones_are_rejected(void) {
    CHECK(plan_find(PROVIDER_EE, 'a') == plan_find(PROVIDER_EE, 'A'));
    CHECK(plan_find(PROVIDER_EE, 'C') == NULL);
}

static void providers_parse_regardless_of_case_or_hyphen(void) {
    Provider p;
    CHECK(provider_parse("t-mobile", &p) && p == PROVIDER_T_MOBILE);
    CHECK(provider_parse("TMobile", &p) && p == PROVIDER_T_MOBILE);
    CHECK(provider_parse("ee", &p) && p == PROVIDER_EE);
    CHECK(!provider_parse("Vodafone", &p));
}

static void countries_use_their_real_dialling_codes(void) {
    CHECK(country_find("uk")->dialling_code == 44);
    CHECK(country_find("USA")->dialling_code == 1);
    CHECK(country_find("DE")->dialling_code == 49);
    CHECK(country_find("SO")->dialling_code == 252);
    CHECK(country_find("XX") == NULL);
}

static void customers_can_be_found_by_name_or_number(void) {
    static CustomerBook book;
    book_init(&book, 42);
    const Customer *added = book_add(&book, "Amina Yusuf", country_find("UK"),
                                     plan_find(PROVIDER_EE, 'A'), PAY_CONTRACT);

    CHECK(book_find_by_name(&book, "Amina Yusuf") == added);
    CHECK(book_find_by_number(&book, added->phone_number) == added);
    CHECK(added->phone_number >= 100000000L && added->phone_number <= 999999999L);
    CHECK(book_find_by_name(&book, "Nobody") == NULL);
}

static void every_customer_gets_a_different_number(void) {
    static CustomerBook book;
    book_init(&book, 7);
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        char name[32];
        snprintf(name, sizeof name, "customer-%d", i);
        CHECK(book_add(&book, name, country_find("AU"), plan_find(PROVIDER_DU, 'A'),
                       PAY_AS_YOU_GO) != NULL);
    }
    for (size_t i = 0; i < book.count; ++i) {
        for (size_t j = i + 1; j < book.count; ++j) {
            CHECK(book.entries[i].phone_number != book.entries[j].phone_number);
        }
    }
}

static void a_full_book_refuses_more_customers(void) {
    static CustomerBook book;
    book_init(&book, 1);
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        book_add(&book, "x", country_find("AU"), plan_find(PROVIDER_DU, 'A'), PAY_CONTRACT);
    }
    CHECK(book_add(&book, "one too many", country_find("AU"), plan_find(PROVIDER_DU, 'A'),
                   PAY_CONTRACT) == NULL);
}

static void deleting_keeps_the_other_customers_searchable(void) {
    static CustomerBook book;
    book_init(&book, 3);
    const Plan *plan = plan_find(PROVIDER_DU, 'A');
    book_add(&book, "Ali", country_find("SO"), plan, PAY_CONTRACT);
    book_add(&book, "Bea", country_find("SO"), plan, PAY_CONTRACT);
    book_add(&book, "Cai", country_find("SO"), plan, PAY_CONTRACT);

    CHECK(book_remove(&book, book_find_by_name(&book, "Bea")));

    CHECK(book.count == 2);
    CHECK(book_find_by_name(&book, "Bea") == NULL);
    CHECK(book_find_by_name(&book, "Ali") != NULL);
    CHECK(book_find_by_name(&book, "Cai") != NULL);
    CHECK(!book_remove(&book, NULL));
}

int main(void) {
    each_provider_bills_its_own_prices();
    a_contract_first_bill_includes_the_deposit_where_one_applies();
    plan_codes_are_case_insensitive_and_unknown_ones_are_rejected();
    providers_parse_regardless_of_case_or_hyphen();
    countries_use_their_real_dialling_codes();
    customers_can_be_found_by_name_or_number();
    every_customer_gets_a_different_number();
    a_full_book_refuses_more_customers();
    deleting_keeps_the_other_customers_searchable();

    if (failures > 0) {
        fprintf(stderr, "%d check(s) failed\n", failures);
        return EXIT_FAILURE;
    }
    printf("All tests passed\n");
    return EXIT_SUCCESS;
}
