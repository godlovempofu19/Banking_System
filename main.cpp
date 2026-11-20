#include <iostream>
#include <string>
using namespace std;
string names[10];
int accountNumbers[10];
int pins[10];
double balances[10];
int numUsers = 0;
int currentUser = -1;
int choice = 0;
int receiptChoice = 0;
double amount = 0;
int receiverAcc = 0;
int accNum = 0;
int pin = 0;
int i = 0;
int receiverIndex = -1;
string lastTransaction = "";
double lastAmount = 0;
string lastReceiverName = "";

void showBankName() {
    cout << "==============================" << endl;
    cout << " ^^^^^^^^^^ACETIC AXE BANK" << endl;
    cout << "==============================" << endl;
}

int displayMenu() {
    showBankName();
    cout << "====== MENU ======" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int findAccount(int accNum) {
    for (i = 0; i < numUsers; i++) {
        if (accountNumbers[i] == accNum) {
            return i;
        }
    }
    return -1;
}

void printSlip(int userIndex) {
    showBankName();
    cout << "------------------------------" << endl;
    cout << "    ACETIC AXE - RECEIPT" << endl;
    cout << "------------------------------" << endl;
    cout << "Name: " << names[userIndex] << endl;
    cout << "Account Number: " << accountNumbers[userIndex] << endl;
    if (lastTransaction != "") {
        cout << "Transaction: " << lastTransaction << endl;
        cout << "Amount: R" << lastAmount << endl;
        if (lastReceiverName != "") {
            cout << "To: " << lastReceiverName << endl;
        }
    }
    cout << "Balance: R" << balances[userIndex] << endl;
    cout << "------------------------------" << endl;
    cout << "Thank you for banking with" << endl;
    cout << "ACETIC AXE BANK" << endl;
    cout << "------------------------------" << endl;
}

void askReceipt() {
    cout << "\nDo you want a receipt?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "Enter choice: ";
    cin >> receiptChoice;
    if (receiptChoice == 1) {
        printSlip(currentUser);
    } else {
        cout << "No receipt printed." << endl;
    }
    lastTransaction = "";
    lastAmount = 0;
    lastReceiverName = "";
}


double deposit(double balance, double amount) {
    if (amount <= 0) {
        cout << "ERROR: Deposit amount must be more than 0!" << endl;
        return balance;
    }
    balance = balance + amount;
    cout << "Deposit successful! New Balance: R" << balance << endl;
    lastTransaction = "Deposit";
    lastAmount = amount;
    return balance;
}


double withdraw(double balance, double amount) {
    if (amount <= 0) {
        cout << "ERROR: Withdrawal amount must be more than 0!" << endl;
        return balance;
    }
    if (amount > balance) {
        cout << "ERROR: Cannot withdraw more than your balance! Balance is R" << balance << endl;
        return balance;
    }
    balance = balance - amount;
    cout << "Withdrawal successful! New Balance: R" << balance << endl;
    lastTransaction = "Withdraw";
    lastAmount = amount;
    return balance;
}


void sendCash(int senderIndex, double amount, int receiverAcc) {
    receiverIndex = findAccount(receiverAcc);
    if (receiverIndex == -1) {
        cout << "ERROR: Account " << receiverAcc << " does NOT exist!" << endl;
        return;
    }
    if (receiverIndex == senderIndex) {
        cout << "ERROR: Cannot send cash to yourself!" << endl;
        return;
    }
    if (amount <= 0) {
        cout << "ERROR: Amount must be more than 0!" << endl;
        return;
    }
    if (amount > balances[senderIndex]) {
        cout << "ERROR: Not enough balance! Balance is R" << balances[senderIndex] << endl;
        return;
    }
    balances[senderIndex] = balances[senderIndex] - amount;
    balances[receiverIndex] = balances[receiverIndex] + amount;
    cout << "Send Cash successful! Sent R" << amount << " to " << names[receiverIndex] << endl;
    cout << "Your new balance: R" << balances[senderIndex] << endl;
    lastTransaction = "Send Cash";
    lastAmount = amount;
    lastReceiverName = names[receiverIndex];
}


void checkBalance(int userIndex) {
    cout << "\n--- Account Details ---" << endl;
    cout << "Name: " << names[userIndex] << endl;
    cout << "Account Number: " << accountNumbers[userIndex] << endl;
    cout << "Balance: R" << balances[userIndex] << endl;
    lastTransaction = "Check Balance";
    lastAmount = balances[userIndex];
}


void registerUsers() {
    showBankName();
    cout << "====== REGISTER USERS ======" << endl;
    cout << "How many users? (Enter 3 or more, max 10): ";
    cin >> numUsers;
    while (numUsers < 3 || numUsers > 10) {
        cout << "ERROR: Must be 3 or more people and max 10!" << endl;
        cout << "How many users? (Enter 3 or more, max 10): ";
        cin >> numUsers;
    }
    for (i = 0; i < numUsers; i++) {
        cout << "\n--- Enter Details For Person " << (i + 1) << " ---" << endl;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, names[i]);
        cout << "Enter Account Number: ";
        cin >> accountNumbers[i];
        cout << "Enter PIN: ";
        cin >> pins[i];
        cout << "Enter Starting Balance: R";
        cin >> balances[i];
    }
}


int loginUser() {
    showBankName();
    cout << "====== LOGIN ======" << endl;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;
    currentUser = findAccount(accNum);
    if (currentUser == -1 || pins[currentUser] != pin) {
        cout << "ERROR: Wrong account number or PIN!" << endl;
        return 0;
    }
    cout << "\nWelcome, " << names[currentUser] << "!" << endl;
    return 1;
}


int main() {
    showBankName();
    registerUsers();
    if (loginUser() == 0) {
        return 0;
    }
    do {
        choice = displayMenu();
        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: R";
                cin >> amount;
                balances[currentUser] = deposit(balances[currentUser], amount);
                if (lastTransaction != "") {
                    askReceipt();
                }
                break;
            case 2:
                cout << "Enter amount to withdraw: R";
                cin >> amount;
                balances[currentUser] = withdraw(balances[currentUser], amount);
                if (lastTransaction != "") {
                    askReceipt();
                }
                break;
            case 3:
                cout << "Enter receiver account number: ";
                cin >> receiverAcc;
                cout << "Enter amount to send: R";
                cin >> amount;
                sendCash(currentUser, amount, receiverAcc);
                if (lastTransaction != "") {
                    askReceipt();
                }
                break;
            case 4:
                checkBalance(currentUser);
                askReceipt();
                break;
            case 5:
                lastTransaction = "Balance Slip";
                lastAmount = balances[currentUser];
                printSlip(currentUser);
                lastTransaction = "";
                lastAmount = 0;
                break;
            case 6:
                showBankName();
                cout << "Thank you for banking with ACETIC AXE BANK. Goodbye!" << endl;
                break;
            default:
                cout << "ERROR: Invalid choice! Please enter 1 - 5." << endl;
                break;
        }
    } while (choice != 6);
    return 0;
}
