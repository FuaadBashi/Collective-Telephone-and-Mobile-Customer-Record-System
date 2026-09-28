#include "customers.h"

#include <stdio.h>
#include <string.h>

#define PHONE_MIN 100000000L
#define PHONE_MAX 999999999L

void book_init(CustomerBook *book, unsigned int seed) {
    book->count = 0;
    book->rng_state = seed == 0 ? 1u : seed;
}

/* xorshift32: small, portable, and seeded once. Reseeding from time(0) on every call handed out
 * the same number to customers added within the same second. */
static unsigned int next_random(CustomerBook *book) {
    unsigned int x = book->rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    book->rng_state = x;
    return x;
}

static long fresh_phone_number(CustomerBook *book) {
    for (;;) {
        long candidate = PHONE_MIN + (long)(next_random(book) % (PHONE_MAX - PHONE_MIN + 1));
        if (book_find_by_number(book, candidate) == NULL) {
            return candidate;
        }
    }
}

const Customer *book_add(CustomerBook *book, const char *name, const Country *country,
                         const Plan *plan, PaymentType payment) {
    if (book->count == MAX_CUSTOMERS) {
        return NULL;
    }
    Customer *c = &book->entries[book->count];
    snprintf(c->name, sizeof c->name, "%s", name);
    c->country = country;
    c->plan = plan;
    c->payment = payment;
    c->phone_number = fresh_phone_number(book);
    book->count++;
    return c;
}

Customer *book_find_by_name(CustomerBook *book, const char *name) {
    for (size_t i = 0; i < book->count; ++i) {
        if (strcmp(book->entries[i].name, name) == 0) {
            return &book->entries[i];
        }
    }
    return NULL;
}

Customer *book_find_by_number(CustomerBook *book, long phone_number) {
    for (size_t i = 0; i < book->count; ++i) {
        if (book->entries[i].phone_number == phone_number) {
            return &book->entries[i];
        }
    }
    return NULL;
}

bool book_remove(CustomerBook *book, const Customer *customer) {
    if (customer < book->entries || customer >= book->entries + book->count) {
        return false;
    }
    size_t index = (size_t)(customer - book->entries);
    /* Keep entries contiguous so every search stays within count. */
    memmove(&book->entries[index], &book->entries[index + 1],
            (book->count - index - 1) * sizeof book->entries[0]);
    book->count--;
    return true;
}
