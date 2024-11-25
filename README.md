# Collective-Telephone-and-Mobile-Customer-Record-System

# Collective Telephone and Mobile Customer Record System

## Overview
The **Collective Telephone and Mobile Customer Record System** is a console-based application for managing customer data, including personal details, mobile plans, and associated bills. The program enables users to add, view, modify, and delete customer records interactively. It's designed to simulate operations of a telecommunications provider's customer management system.

---

## Features
- **Add Customer**: Create a new customer profile with attributes like name, phone number, area code, and selected mobile plan.
- **View Customers**: Search for a customer by name or phone number and display their details.
- **Modify Customer**: Update customer details, including their associated mobile plan.
- **Delete Customer**: Remove a customer record by name or phone number.
- **List All Customers**: Retrieve and display all stored customer records.
- **Mobile Plans**: 
  - Support for multiple telecom providers (DU, EE, T-Mobile).
  - Detailed mobile plans with payment options (contract or pay-as-you-go).
  - Automatic bill calculations based on the chosen plan.

---

## How It Works

### Menu Options
1. **Add New Customer**  
   Prompts for customer details (name, phone number, area code) and allows the selection of a mobile plan.
2. **View Customers**  
   Search by name or phone number to display customer information.
3. **Modify Customer**  
   Search for a customer, delete their existing record, and replace it with updated details.
4. **Delete Customer**  
   Search and remove a customer record.
5. **List All Customers**  
   Display all customer records in the system.
6. **Exit**  
   Exit the application.

### Mobile Plan Details
- Plans vary by provider (DU, EE, T-Mobile) and offer multiple contract or pay-as-you-go options.
- Each plan includes specific data, minutes, and text allowances, with associated costs.

---

## Code Structure
### Files
- **`main.c`**: Contains the main loop to initialize the menu and process user input.
- **`customer.c`**: Handles customer operations (add, view, modify, delete).
- **`company.c`**: Manages company-specific operations, including plan selection and billing.
- **`record.c`**: Handles menu logic and system-wide operations.
- **`customer.h`**: Header file for defining the `customer` structure and associated functions.

---

## Compilation and Execution

### Prerequisites
- **C Compiler** (e.g., GCC)
- Compatible operating system (Linux, macOS, Windows with a C compiler installed)

### Steps to Compile and Run
1. Clone the repository:
   ```bash
   git clone https://github.com/<username>/customer-record-system.git
   cd customer-record-system
   ```
2. Compile the program:
   ```bash
   gcc main.c -o customer_record -std=c99
   ```
3. Run the program:
   ```bash
   ./customer_record
   ```

---

## Sample Execution

### Adding a Customer
```text
WELCOME TO THE COLLECTIVE TELEPHONE AND MOBILE CUSTOMER RECORD
----------------------------------------------------------------
(1): Add new customer
(2): View customers
(3): Modify customer
(4): Delete customer
(5): Get all customers
(0): EXIT
----------------------------------------------------------------
TYPE YOUR OPTION BY NUMBER(format = 3);
1

Type your FIRST NAME:
John
NUMBER(without area-code): 523456789
WHICH COUNTRY DO LIVE IN?:(AU, UK, USA, UAE, DE, SO, IR)
USA
Pick a provider (EE, DU, T-Mobile):
T-Mobile
Available plans:
PLAN A:: Data: 10GB, Minutes(WITHOUT international): 400, Texts: 500 ($10/month(12 months WITH $5 deposit)) OR $20 Pay-as-you-go
PLAN B:: Data: 30GB, Minutes(WITH international): 600, Texts: 500 ($20/month(12 months WITH $5 deposit)) OR $45 Pay-as-you-go
A or B?
A
Available PAYMENT plans:
(CONTRACTS NEED A ONE-TIME DEPOSIT PAYMENT OF $5)
1: 12 month contract
2: Pay-As-You-Go
1
```

---

## Key Considerations

### Memory Management
- Dynamic memory is used for storing customer names and plans.
- Ensure proper memory deallocation using the `free()` function to avoid memory leaks.

### Edge Cases
- Validation for invalid menu inputs or empty fields.
- Handle cases where no customers exist in the system.
- Ensure all allocated memory is freed before exiting the program.

---

## Future Enhancements
- Implement persistent storage for customer records (e.g., file or database).
- Add payment history tracking for each customer.
- Enhance input validation and user-friendly error messages.
- Add support for international customers with country-specific formats.

---

## License
This project is licensed under the MIT License. See `LICENSE` for details.

---

## Acknowledgments
This project is developed as a learning tool for customer data management in telecommunications systems. Feedback and contributions are welcome!
