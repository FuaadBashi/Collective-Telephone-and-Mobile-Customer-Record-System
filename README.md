# Telephone Customer Record System

A C console project for customer records and telephone billing. It separates menu flow, customer data, and record operations across small source files.

## Run locally

Requires a C compiler such as Clang or GCC.

```bash
git clone https://github.com/FuaadBashi/Collective-Telephone-and-Mobile-Customer-Record-System.git
cd Collective-Telephone-and-Mobile-Customer-Record-System
cd TelephoneBillingSystem
cc main.c -o telephone-records
./telephone-records
```

The entry point includes `record.c` directly; do not also compile every `.c` file into the same executable. Build from source rather than using the checked-in binaries.

## Code to explore

- [main.c](TelephoneBillingSystem/main.c): menu loop.
- [record.c](TelephoneBillingSystem/record.c): record operations.
- [customer.h](TelephoneBillingSystem/customer.h) and [customer.c](TelephoneBillingSystem/customer.c): customer representation.

Use fictional records when exploring this educational application.
