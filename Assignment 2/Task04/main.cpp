#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    long long accountNumber;
    double balance;
    string transactions[10];
    int count;
    int nextIndex;
public:
    SavingsAccount(long long number, double opening)
        : accountNumber(number), balance(opening), count(0), nextIndex(0) {}
    void addTransaction(const string& description) {
        transactions[nextIndex] = description;
        nextIndex = (nextIndex + 1) % 10;
        if (count < 10) ++count;
    }
    void deposit(double amount);
    void withdraw(double amount);
    void miniStatement() const;
    double getBalance() const { return balance; }
};
void SavingsAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        addTransaction("Deposit +" + to_string(amount));
    }
}
void SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        addTransaction("Withdraw -" + to_string(amount));
    }
}
void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nBalance: " << balance << '\n';
    cout << "Last " << count << " transactions (oldest to newest):\n";
    int start = (count == 10) ? nextIndex : 0;
    for (int i = 0; i < count; ++i)
        cout << transactions[(start + i) % 10] << '\n';
}
int main() {
    SavingsAccount account(123456, 1000);
    for (int i = 1; i <= 11; ++i) account.deposit(i * 10);
    account.withdraw(25);
    account.miniStatement();
}
