💰 Smart Money Tracker

A simple, command-line based C++ personal finance manager. Register, log in, track your income, expenses, and custom savings, and generate monthly/yearly reports — all stored locally in Excel-friendly CSV files.

Show Image Show Image Show Image

📖 Overview

Managing personal finances manually or through scattered notes often leads to confusion and a loss of track of income, expenses, and savings. Smart Money Tracker is a lightweight console application that lets a single user record and review their financial activity in an organized, private, and fully offline manner — no internet connection, no third-party servers.

This project was built as a proposal/coursework project for Object-Oriented Programming (OOP), and is designed to demonstrate all four OOP pillars in a small, real, working application.

✨ Features
🔐 Simple, secure username/password registration and login
💵 Add Income and Expense entries with a date
🏦 Add custom Saving entries — name your own saving method (e.g. "Fixed Deposit", "Emergency Fund")
📊 Generate monthly and yearly financial reports (totals for income, expense, saving)
📁 All login credentials and transactions are saved automatically to CSV files, viewable directly in Excel
🧱 Clean, object-oriented codebase — easy to read and extend
🧠 Object-Oriented Concepts Used
Concept	Where it's applied
Abstraction	Transaction is an abstract class with pure virtual display() and getType() methods, defining a contract every transaction type must follow.
Inheritance	Income, Expense, and Saving all inherit the shared date and amount fields from Transaction.
Polymorphism	display() and getType() behave differently for each transaction type, called through a single Transaction* pointer.
Encapsulation	User's username/password and Transaction's date/amount are kept private/protected, accessible only through controlled methods.
🗂️ Project Structure
smart-money-tracker/
├── SmartMoneyTracker.cpp   # Full source code
├── users.csv               # Auto-generated: stores registered login credentials
├── report.csv               # Auto-generated: stores all transaction records
└── README.md                # This file
🏗️ System Design

Class Diagram

                     MoneyTracker
                          |
            ┌─────────────┴─────────────┐
      «abstract» Transaction           User
            |
   ┌────────┼────────┐
 Income   Expense   Saving
Transaction (abstract) → # date, # amount → display(), getType(), getDate(), getAmount()
Income, Expense → override display() / getType()
Saving → adds - method (custom saving name)
User → - username, - password → setCredentials(), getUsername()
MoneyTracker → owns User + vector<Transaction*> → registerUser(), login(), addTransaction(), saveToFile(), showAll(), monthlyReport(), yearlyReport()

(Full Class, Use Case, and Sequence diagrams are included in the project proposal document.)

⚙️ Getting Started
Prerequisites
A C++ compiler that supports C++17 (e.g. g++)
Build
bash
g++ -std=c++17 -o tracker SmartMoneyTracker.cpp
Run
bash
./tracker

On Windows:

bash
g++ -std=c++17 -o tracker.exe SmartMoneyTracker.cpp
tracker.exe
▶️ Usage
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

Reports can be generated at any time:

Choice: 3
Enter month (MM): 08

---- Report for Month 08 ----
Total Income:  Rs. 50000
Total Expense: Rs. 2000
Total Saving:  Rs. 5000
💾 Data Storage
File	Contents
users.csv	username,password — one row per registered user
report.csv	username,date,type,amount — one row per transaction

Both files are plain CSV and open directly in Microsoft Excel or Google Sheets.

⚠️ Note: Passwords are currently stored in plain text for simplicity. This is fine for a class demo, but should not be used in production without hashing (e.g. bcrypt) — a natural next step for future work.

🚧 Limitations
Supports only one active user session at a time
Console (CMD) based — no graphical interface
Reports show totals only; no charts or graphs
Assumes dates are entered in DD-MM-YYYY format
🔮 Future Improvements
 Password hashing for secure credential storage
 Spending categories and budget limits
 Export reports directly to formatted .xlsx
 Multi-currency support
 Simple GUI (Qt or a web front-end)
👤 Author

Saksham Smith Sunar Bachelor of Science in Computer Science — King's College Nepal Course Project: Object-Oriented Programming (OOP)

📄 License

This project is licensed under the MIT License — free to use, modify, and distribute.
