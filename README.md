# Smart Money Tracker

A command-line C++ application for personal finance management. Users can register, log in, record income, expenses, and custom savings, and generate monthly or yearly financial reports. All data is stored locally in CSV format for portability and use in spreadsheet software such as Microsoft Excel.

![Language](https://img.shields.io/badge/language-C%2B%2B17-00599C?logo=c%2B%2B)
![Platform](https://img.shields.io/badge/platform-CLI-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Object-Oriented Design](#object-oriented-design)
- [System Design](#system-design)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Data Storage](#data-storage)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Author](#author)
- [License](#license)

## Overview

Managing personal finances manually, or through scattered notes, often results in an inaccurate picture of income, expenses, and savings over time. Smart Money Tracker addresses this by providing a lightweight, fully offline console application that allows a single user to record and review their financial activity in a structured and private manner, without dependency on an internet connection or third-party servers.

This project was developed as coursework for Object-Oriented Programming (OOP) and is intended to demonstrate the four core OOP principles in a small, functioning application.

## Features

- Secure user registration and login
- Recording of income and expense entries with an associated date
- Custom saving entries, allowing the user to define their own saving method (for example, "Fixed Deposit" or "Emergency Fund")
- On-demand generation of monthly and yearly financial reports
- Automatic, persistent storage of all login credentials and transactions in CSV format
- A clean, modular, object-oriented codebase

## Object-Oriented Design

| Principle | Implementation |
|---|---|
| Abstraction | `Transaction` is declared as an abstract class with pure virtual `display()` and `getType()` methods, defining a contract that every transaction type must implement. |
| Inheritance | `Income`, `Expense`, and `Saving` inherit the shared `date` and `amount` fields and behavior from the `Transaction` base class. |
| Polymorphism | `display()` and `getType()` resolve to the correct derived-class implementation at runtime, when called through a `Transaction*` pointer. |
| Encapsulation | Sensitive fields such as `User::password` and `Transaction::date` / `Transaction::amount` are declared private or protected and accessed only through defined public methods. |

## System Design

**Class Diagram (simplified)**

```
                        MoneyTracker
                              |
                ┌─────────────┴─────────────┐
      «abstract» Transaction               User
                #date, #amount        -username, -password
                              |
                ┌─────────────┼─────────────┐
             Income         Expense        Saving
                                            -method
```

- `Transaction` (abstract) — `date`, `amount`, `display()`, `getType()`, `getDate()`, `getAmount()`
- `Income`, `Expense` — override `display()` and `getType()`
- `Saving` — extends `Transaction` with a custom `method` field
- `User` — stores `username` and `password`, exposed through `setCredentials()` and `getUsername()`
- `MoneyTracker` — owns a `User` and a list of `Transaction*`; exposes `registerUser()`, `login()`, `addTransaction()`, `saveToFile()`, `showAll()`, `monthlyReport()`, and `yearlyReport()`

Full Class, Use Case, and Sequence diagrams are included in the accompanying project proposal document.

## Project Structure

```
smart-money-tracker/
├── SmartMoneyTracker.cpp   Source code
├── users.csv               Generated at runtime — stores registered credentials
├── report.csv              Generated at runtime — stores transaction records
└── README.md
```

## Getting Started

### Prerequisites

A C++ compiler supporting C++17 (for example, `g++`).

### Build

```bash
g++ -std=c++17 -o tracker SmartMoneyTracker.cpp
```

### Run

```bash
./tracker
```

On Windows:

```bash
g++ -std=c++17 -o tracker.exe SmartMoneyTracker.cpp
tracker.exe
```

## Usage

```
=== SMART MONEY TRACKER ===

1. Register   2. Login
Choice: 1
Choose a username: saksham
Choose a password: ********
Registration successful!

1. Register   2. Login
Choice: 2
Username: saksham
Password: ********
Login successful. Welcome, saksham!

----- MENU -----
1. Add Transaction
2. Show All Transactions
3. Monthly Report
4. Yearly Report
5. Exit
Choice: 1

1. Income   2. Expense   3. Saving
Choose type: 1
Enter date (DD-MM-YYYY): 01-08-2026
Enter amount: 50000
Transaction added successfully!
```

Reports can be generated at any point during the session:

```
Choice: 3
Enter month (MM): 08

---- Report for Month 08 ----
Total Income:  Rs. 50000
Total Expense: Rs. 2000
Total Saving:  Rs. 5000
```

## Data Storage

| File | Contents |
|---|---|
| `users.csv` | `username,password` — one row per registered user |
| `report.csv` | `username,date,type,amount` — one row per transaction |

Both files are plain CSV and can be opened directly in Microsoft Excel or Google Sheets.

**Note:** Passwords are currently stored as plain text for simplicity. This is acceptable for a coursework demonstration but should not be used in a production context without proper hashing (for example, bcrypt).

## Limitations

- Supports a single active user session at a time
- Console-based interface only; no graphical user interface
- Reports display totals only; no charts or graphs are generated
- Dates must be entered in `DD-MM-YYYY` format

## Future Improvements

- Password hashing for secure credential storage
- Spending categories and configurable budget limits
- Direct export of reports to formatted `.xlsx` files
- Multi-currency support
- A graphical or web-based front end

## Author

**Saksham Smith Sunar**
Bachelor of Science in Computer Science, King's College Nepal
Course Project: Object-Oriented Programming (OOP)

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
