#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account {
protected:
    // Create protected variables for the account number, account holder name, and balance
    string account_number;
    string account_holder;
    double balance;

public:
    Account(string acc_num, string holder_name, double init_bal) : account_number(acc_num), account_holder(holder_name), balance(init_bal) {}

    virtual void displayDetails() const {
        /*Prints the details for the account*/
        cout << "Account Details for Account (ID: " << account_number << "):\n";
        cout << "   Holder: " << account_holder << "\n";
        cout << "   Balance: $" << fixed << setprecision(2) << balance << "\n";
    }

    virtual void deposit(double amount) {
        /*Adds an amount to the total balance*/
        balance += amount;
    }

    virtual void withdraw(double amount) {
        /*Subtracts from the balance if able (can't have a negative balance)*/
        if (balance >= amount) {
            balance -= amount;
        }
    }

    virtual void transfer(double amount) {
        /*Adds an amount to the total balance if account transfer*/
        balance += amount;
    }

    double getBalance() const {
        /*returns the balance*/
        return balance;
    }
};

class SavingsAccount : public Account {
private:
    //Define the interest rate
    double interest_rate;

public:
    SavingsAccount(string acc_num, string holder_name, double init_bal, double rate) : Account(acc_num, holder_name, init_bal), interest_rate(rate) {}

    void displayDetails() const override {
        /*Prints the account details and the interest rate */
        Account::displayDetails();
        //Recieved help from Chatgpt with setPrecision functionality
        cout << "   Interest Rate: " << fixed << setprecision(2) << interest_rate * 100 << "%\n\n";
    }
};

class CurrentAccount : public Account {
private:
    //Define the overdraft limit
    double overdraft_limit;

public:
    CurrentAccount(string number, string holder, double initial_balance, double limit) : Account(number, holder, initial_balance), overdraft_limit(limit) {}

    void displayDetails() const override {
        /*Prints the account details and the overdraft limit*/
        Account::displayDetails();
        cout << "   Overdraft Limit: $" << fixed << setprecision(2) << overdraft_limit << "\n\n";
    }
    // I kept getting errors in the main function on the current = current + savings line.
    // The following code was assisted by Chatgpt:
    CurrentAccount operator+(Account& other) {
        /*Adds the balance of the other account to this account*/
        double transferAmount = 300; // Define the transfer amount
        if (other.getBalance() >= transferAmount) {
            other.transfer(-transferAmount); // Withdraw from the other account
            this->transfer(transferAmount);  // Deposit to this account
        }
        return *this; // Return this account
    }
};

int main() {
    
    // Standard test case given in lab instructions
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);
    
    savings.displayDetails();
    current.displayDetails();

    current = current + savings;

    savings.displayDetails();
    current.displayDetails();

    return 0;
}
