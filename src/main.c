#include "customers.h"
#include "plans.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_MAX_LEN 128

/* Reads one line without its newline; false at end of input. Replaces scanf("%s"), which
 * overflowed a one-byte malloc on any name and looped forever on non-numeric input. */
static bool read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }
    size_t len = strcspn(buffer, "\n");
    if (buffer[len] != '\n' && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    buffer[len] = '\0';
    return true;
}

static bool read_long(const char *prompt, long min, long max, long *out) {
    char line[LINE_MAX_LEN];
    for (;;) {
        if (!read_line(prompt, line, sizeof line)) {
            return false;
        }
        char *end;
        errno = 0;
        long value = strtol(line, &end, 10);
        if (end != line && *end == '\0' && errno == 0 && value >= min && value <= max) {
            *out = value;
            return true;
        }
        printf("Please enter a number from %ld to %ld.\n", min, max);
    }
}

static void print_money(int cents) {
    printf("$%d.%02d", cents / 100, cents % 100);
}

static void print_customer(const Customer *c) {
    printf("  %-20s  +%d %ld  %-8s plan %c  %-13s  ", c->name, c->country->dialling_code,
           c->phone_number, provider_name(c->plan->provider), c->plan->code,
           c->payment == PAY_CONTRACT ? "12-month" : "pay-as-you-go");
    print_money(monthly_bill_cents(c->plan, c->payment));
    printf("/month\n");
}

static void print_plans(void) {
    for (int p = 0; p < PROVIDER_COUNT; ++p) {
        int count;
        const Plan *plans = plans_for((Provider)p, &count);
        printf("%s\n", provider_name((Provider)p));
        for (int i = 0; i < count; ++i) {
            const Plan *plan = &plans[i];
            printf("  Plan %c: %s\n          contract ", plan->code, plan->allowance);
            print_money(plan->contract_monthly_cents);
            printf("/month");
            if (plan->contract_deposit_cents > 0) {
                printf(" + ");
                print_money(plan->contract_deposit_cents);
                printf(" deposit");
            }
            printf(", or pay-as-you-go ");
            print_money(plan->payg_monthly_cents);
            printf("/month\n");
        }
    }
}

/* Asks for provider, plan and payment type. Returns false at end of input. */
static bool choose_plan(const Plan **plan, PaymentType *payment) {
    char line[LINE_MAX_LEN];
    Provider provider;
    print_plans();
    for (;;) {
        if (!read_line("Provider (EE, du, T-Mobile): ", line, sizeof line)) {
            return false;
        }
        if (provider_parse(line, &provider)) {
            break;
        }
        printf("Unknown provider.\n");
    }
    for (;;) {
        if (!read_line("Plan (A or B): ", line, sizeof line)) {
            return false;
        }
        *plan = strlen(line) == 1 ? plan_find(provider, line[0]) : NULL;
        if (*plan != NULL) {
            break;
        }
        printf("Please enter A or B.\n");
    }
    long choice;
    if (!read_long("Payment: 1 = 12-month contract, 2 = pay-as-you-go: ", 1, 2, &choice)) {
        return false;
    }
    *payment = choice == 1 ? PAY_CONTRACT : PAY_AS_YOU_GO;
    return true;
}

static bool add_customer(CustomerBook *book) {
    char name[CUSTOMER_NAME_MAX];
    char line[LINE_MAX_LEN];
    const Country *country;

    if (book->count == MAX_CUSTOMERS) {
        printf("The book is full (%d customers).\n", MAX_CUSTOMERS);
        return true;
    }
    if (!read_line("Customer name: ", name, sizeof name)) {
        return false;
    }
    if (name[0] == '\0') {
        printf("A name is required.\n");
        return true;
    }
    for (;;) {
        if (!read_line("Country (AU, UK, USA, UAE, DE, SO, IR): ", line, sizeof line)) {
            return false;
        }
        if ((country = country_find(line)) != NULL) {
            break;
        }
        printf("Unknown country.\n");
    }
    const Plan *plan;
    PaymentType payment;
    if (!choose_plan(&plan, &payment)) {
        return false;
    }

    const Customer *c = book_add(book, name, country, plan, payment);
    printf("Added:\n");
    print_customer(c);
    printf("  First bill: ");
    print_money(first_bill_cents(plan, payment));
    printf("\n");
    return true;
}

/* Finds a customer by name or number. *found is NULL if there is no match. */
static bool lookup(CustomerBook *book, Customer **found) {
    long how;
    *found = NULL;
    if (!read_long("Find by 1 = name, 2 = phone number: ", 1, 2, &how)) {
        return false;
    }
    if (how == 1) {
        char name[CUSTOMER_NAME_MAX];
        if (!read_line("Name: ", name, sizeof name)) {
            return false;
        }
        *found = book_find_by_name(book, name);
    } else {
        long number;
        if (!read_long("Phone number (without country code): ", 0, 999999999L, &number)) {
            return false;
        }
        *found = book_find_by_number(book, number);
    }
    if (*found == NULL) {
        printf("No matching customer.\n");
    }
    return true;
}

int main(void) {
    static CustomerBook book;
    book_init(&book, (unsigned int)time(NULL));

    bool running = true;
    while (running) {
        printf("\n===== Telephone Customer Records =====\n"
               "1. Add customer\n"
               "2. Find customer\n"
               "3. Change a customer's plan\n"
               "4. Delete customer\n"
               "5. List all customers\n"
               "6. Show plans\n"
               "0. Exit\n");
        long option;
        if (!read_long("Select an option: ", 0, 6, &option)) {
            break;
        }

        Customer *c;
        switch (option) {
        case 1:
            running = add_customer(&book);
            break;
        case 2:
            running = lookup(&book, &c);
            if (c != NULL) {
                print_customer(c);
            }
            break;
        case 3:
            running = lookup(&book, &c);
            if (c != NULL) {
                running = choose_plan(&c->plan, &c->payment);
                if (running) {
                    printf("Updated:\n");
                    print_customer(c);
                }
            }
            break;
        case 4:
            running = lookup(&book, &c);
            if (c != NULL) {
                printf("Deleted %s.\n", c->name);
                book_remove(&book, c);
            }
            break;
        case 5:
            printf("%zu customer(s):\n", book.count);
            for (size_t i = 0; i < book.count; ++i) {
                print_customer(&book.entries[i]);
            }
            break;
        case 6:
            print_plans();
            break;
        case 0:
            running = false;
            break;
        }
    }
    return EXIT_SUCCESS;
}
