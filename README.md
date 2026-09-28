# Telephone Customer Records

[![CI](https://github.com/FuaadBashi/Collective-Telephone-and-Mobile-Customer-Record-System/actions/workflows/ci.yml/badge.svg)](https://github.com/FuaadBashi/Collective-Telephone-and-Mobile-Customer-Record-System/actions/workflows/ci.yml)

A console customer-records and billing system for a mobile reseller, written in C. Sign customers
up to a provider plan, give them a unique number, look them up by name or number, change their
plan, and see what they'll be billed.

```
Added:
  Amina Yusuf           +44 574348572  EE       plan B  12-month       $20.00/month
  First bill: $20.00
```

## Highlights

- **Data-driven plans.** Providers, plans, prices, deposits and country dialling codes live in
  tables, not branching code. Adding a plan is a one-line change.
- **Exact money.** All prices are integer cents. Contract deposits are added to the first bill
  only, and only for providers that charge one.
- **Unique numbers.** Phone numbers come from a seeded xorshift generator and are checked against
  the book, so no two customers share one. The seed makes tests reproducible.
- **Safe storage.** Customers live in a contiguous array bounded by `count`, so searches never
  touch an empty slot, and deletion compacts the array.
- **Defensive input.** Every prompt reads a full line and re-asks on anything invalid.
- **Tested under sanitizers.** Unit tests run with AddressSanitizer and UBSan in CI, and the build
  treats warnings as errors.

## Getting started

Requires a C11 compiler and `make`.

```bash
git clone https://github.com/FuaadBashi/Collective-Telephone-and-Mobile-Customer-Record-System.git
cd Collective-Telephone-and-Mobile-Customer-Record-System
make
./telephone-records
```

## Plans

| Provider | Plan | Allowance | Contract | Pay-as-you-go |
| --- | --- | --- | --- | --- |
| du | A | 20GB, 100 min, 100 texts | $10/mo + $5 deposit | $20/mo |
| du | B | 60GB, 100 min intl., 100 texts | $30/mo + $5 deposit | $45/mo |
| EE | A | 1GB, 200 min intl., 100 texts | $15/mo | $20/mo |
| EE | B | 15GB, 300 min intl., 300 texts | $20/mo | $45/mo |
| T-Mobile | A | 10GB, 400 min, 500 texts | $10/mo + $5 deposit | $20/mo |
| T-Mobile | B | 30GB, 600 min intl., 500 texts | $20/mo + $5 deposit | $45/mo |

## Project structure

```
src/plans.[ch]       providers, plans, pricing, country codes
src/customers.[ch]   customer book: add, find, remove, number allocation
src/main.c           menu and input validation
tests/               unit tests
Makefile             build, test, format
```

## Tests

```bash
make test           # unit tests under ASan + UBSan
make format-check   # clang-format
```
