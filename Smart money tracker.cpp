/*
    Smart Money Tracker : A CMD-Based Personal Finance Manager
    -----------------------------------------------------------
    A simple console C++ application that demonstrates:
        - Encapsulation
        - Inheritance
        - Polymorphism
        - Abstraction

    Features:
        - Register / Login
        - Add Income, Expense, or Saving (with date)
        - View all transactions
        - Monthly report
        - Yearly report
        - Data saved to CSV files (users.csv, report.csv)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ======================================================
//  ABSTRACTION
//  Transaction is an abstract class. It cannot be
//  created directly; every transaction type MUST
//  implement display() and getType().
// ======================================================
class Transaction {
protected:
    string date;
    double amount;

public:
    Transaction(string d, double a) : date(d), amount(a) {}

    virtual void display() const = 0;      // pure virtual function
    virtual string getType() const = 0;    // pure virtual function

    string getDate() const   { return date; }
    double getAmount() const { return amount; }

    virtual ~Transaction() {}
};

// ======================================================
//  INHERITANCE
//  Income, Expense, and Saving all inherit the common
//  date and amount fields from Transaction.
// ======================================================
class Income : public Transaction {
public:
    Income(string d, double a) : Transaction(d, a) {}

    void display() const override {
        cout << date << " | Income  | Rs. " << amount << endl;
    }
    string getType() const override { return "Income"; }
};

class Expense : public Transaction {
public:
    Expense(string d, double a) : Transaction(d, a) {}

    void display() const override {
        cout << date << " | Expense | Rs. " << amount << endl;
    }
    string getType() const override { return "Expense"; }
};

class Saving : public Transaction {
private:
    string method;   // custom saving method, e.g. "Fixed Deposit"

public:
    Saving(string d, double a, string m) : Transaction(d, a), method(m) {}

    void display() const override {
        cout << date << " | Saving (" << method << ") | Rs. " << amount << endl;
    }
    string getType() const override { return "Saving"; }
};

// ======================================================
//  ENCAPSULATION
//  username and password are private; they can only be
//  accessed through the public methods below.
// ======================================================
class User {
private:
    string username;
    string password;

public:
    void setCredentials(string u, string p) {
        username = u;
        password = p;
    }
    string getUsername() const { return username; }
};

// ======================================================
//  MoneyTracker - the main controller class
// ======================================================
class MoneyTracker {
private:
    User user;
    vector<Transaction*> transactions;
    string userFile   = "users.csv";
    string reportFile = "report.csv";

    // check username/password against users.csv
    bool findUser(string u, string p) {
        ifstream fin(userFile);
        string line;
        while (getline(fin, line)) {
            size_t pos = line.find(',');
            if (pos == string::npos) continue;
            if (line.substr(0, pos) == u && line.substr(pos + 1) == p)
                return true;
        }
        return false;
    }

public:
    // ---- Register a new user ----
    void registerUser() {
        string u, p;
        cout << "Choose a username: "; cin >> u;
        cout << "Choose a password: "; cin >> p;

        ofstream fout(userFile, ios::app);
        fout << u << "," << p << "\n";
        cout << "Registration successful!\n";
    }

    // ---- Log an existing user in ----
    bool login() {
        string u, p;
        cout << "Username: "; cin >> u;
        cout << "Password: "; cin >> p;

        if (findUser(u, p)) {
            user.setCredentials(u, p);
            cout << "Login successful. Welcome, " << u << "!\n";
            return true;
        }
        cout << "Invalid username or password.\n";
        return false;
    }

    // ---- Save one transaction to report.csv ----
    void saveToFile(Transaction* t) {
        ofstream fout(reportFile, ios::app);
        fout << user.getUsername() << ","
             << t->getDate() << ","
             << t->getType() << ","
             << t->getAmount() << "\n";
    }

    // ---- Ask the user for a new Income / Expense / Saving ----
    void addTransaction() {
        cout << "\n1. Income   2. Expense   3. Saving\n";
        cout << "Choose type: ";
        int choice;
        cin >> choice;

        string date;
        double amount;
        cout << "Enter date (DD-MM-YYYY): "; cin >> date;
        cout << "Enter amount: ";            cin >> amount;

        Transaction* t = nullptr;

        if (choice == 1) {
            t = new Income(date, amount);
        } else if (choice == 2) {
            t = new Expense(date, amount);
        } else if (choice == 3) {
            string method;
            cout << "Enter saving method (e.g. Fixed Deposit): ";
            cin >> method;
            t = new Saving(date, amount, method);
        } else {
            cout << "Invalid choice.\n";
            return;
        }

        transactions.push_back(t);
        saveToFile(t);
        cout << "Transaction added successfully!\n";
    }

    // ---- Show every transaction recorded this session ----
    void showAll() {
        if (transactions.empty()) {
            cout << "\nNo transactions recorded yet.\n";
            return;
        }
        cout << "\n---- All Transactions ----\n";
        for (Transaction* t : transactions) {
            t->display();   // POLYMORPHISM: correct display() runs automatically
        }
    }

    // ---- Totals for one month, given as "MM" ----
    void monthlyReport(string month) {
        double income = 0, expense = 0, saving = 0;

        for (Transaction* t : transactions) {
            if (t->getDate().substr(3, 2) == month) {
                if (t->getType() == "Income")       income  += t->getAmount();
                else if (t->getType() == "Expense") expense += t->getAmount();
                else                                 saving  += t->getAmount();
            }
        }

        cout << "\n---- Report for Month " << month << " ----\n";
        cout << "Total Income:  Rs. " << income  << endl;
        cout << "Total Expense: Rs. " << expense << endl;
        cout << "Total Saving:  Rs. " << saving  << endl;
    }

    // ---- Totals for one year, given as "YYYY" ----
    void yearlyReport(string year) {
        double income = 0, expense = 0, saving = 0;

        for (Transaction* t : transactions) {
            if (t->getDate().substr(6, 4) == year) {
                if (t->getType() == "Income")       income  += t->getAmount();
                else if (t->getType() == "Expense") expense += t->getAmount();
                else                                 saving  += t->getAmount();
            }
        }

        cout << "\n---- Report for Year " << year << " ----\n";
        cout << "Total Income:  Rs. " << income  << endl;
        cout << "Total Expense: Rs. " << expense << endl;
        cout << "Total Saving:  Rs. " << saving  << endl;
    }

    ~MoneyTracker() {
        for (Transaction* t : transactions) delete t;
    }
};

// ======================================================
//  main()
// ======================================================
int main() {
    MoneyTracker tracker;
    int choice;
    bool loggedIn = false;

    cout << "=== SMART MONEY TRACKER ===\n";

    // ---- Login / Register loop ----
    while (!loggedIn) {
        cout << "\n1. Register   2. Login\nChoice: ";
        cin >> choice;

        if (choice == 1)      tracker.registerUser();
        else if (choice == 2) loggedIn = tracker.login();
        else                  cout << "Invalid choice.\n";
    }

    // ---- Main menu loop ----
    while (true) {
        cout << "\n----- MENU -----\n";
        cout << "1. Add Transaction\n";
        cout << "2. Show All Transactions\n";
        cout << "3. Monthly Report\n";
        cout << "4. Yearly Report\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            tracker.addTransaction();
        } else if (choice == 2) {
            tracker.showAll();
        } else if (choice == 3) {
            string month;
            cout << "Enter month (MM): "; cin >> month;
            tracker.monthlyReport(month);
        } else if (choice == 4) {
            string year;
            cout << "Enter year (YYYY): "; cin >> year;
            tracker.yearlyReport(year);
        } else if (choice == 5) {
            cout << "\nThank you for using Smart Money Tracker!\n";
            break;
        } else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}