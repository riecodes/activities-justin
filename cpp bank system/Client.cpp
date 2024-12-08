#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Client {
    int pin;
    string name;
    double balance;
    Client* next;
};

// Global linked list to store clients
Client* head = nullptr;

// Function to create a new client record
Client* createClient(int pin, string name, double balance) {
    Client* newClient = new Client;
    newClient->pin = pin;
    newClient->name = name;
    newClient->balance = balance;
    newClient->next = nullptr;
    return newClient;
}

// Function to check if PIN already exists in the linked list
bool isPINExists(int pin) {
    Client* temp = head;
    while (temp != nullptr) {
        if (temp->pin == pin) return true;
        temp = temp->next;
    }
    return false;
}

// Registration function
void registerClient() {
    int pin;
    string name;
    double balance = 0.0;
    
    cout << "Enter a unique PIN: ";
    cin >> pin;
    
    if (isPINExists(pin)) {
        cout << "PIN already exists! Please choose another PIN." << endl;
        return;
    }
    
    cout << "Enter your name: ";
    cin.ignore(); // To clear the newline character from input buffer
    getline(cin, name);
    
    Client* newClient = createClient(pin, name, balance);
    newClient->next = head;
    head = newClient;
    
    cout << "Registration successful!" << endl;
}

// Login function
Client* loginClient() {
    int pin;
    cout << "Enter your PIN: ";
    cin >> pin;

    Client* temp = head;
    while (temp != nullptr) {
        if (temp->pin == pin) {
            cout << "Login successful! Welcome " << temp->name << "!" << endl;
            return temp; // Return client record upon successful login
        }
        temp = temp->next;
    }

    cout << "Invalid PIN!" << endl;
    return nullptr;
}

// Banking operations
void deposit(Client* client) {
    double amount;
    cout << "Enter deposit amount: ";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "Invalid amount!" << endl;
        return;
    }
    
    client->balance += amount;
    cout << "Deposit successful! New balance: " << client->balance << endl;
}

void withdraw(Client* client) {
    double amount;
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "Invalid amount!" << endl;
        return;
    }
    
    if (amount > client->balance) {
        cout << "Insufficient funds!" << endl;
        return;
    }
    
    client->balance -= amount;
    cout << "Withdrawal successful! New balance: " << client->balance << endl;
}

void balanceInquiry(Client* client) {
    cout << "Your current balance is: " << client->balance << endl;
}

void changePIN(Client* client) {
    int newPin;
    cout << "Enter your new PIN: ";
    cin >> newPin;

    if (isPINExists(newPin)) {
        cout << "PIN already exists! Choose another PIN." << endl;
        return;
    }

    client->pin = newPin;
    cout << "PIN changed successfully!" << endl;
}

// Admin console operations
void viewClients() {
    if (head == nullptr) {
        cout << "No clients registered." << endl;
        return;
    }
    
    Client* temp = head;
    while (temp != nullptr) {
        cout << "PIN: " << temp->pin << ", Name: " << temp->name << ", Balance: " << temp->balance << endl;
        temp = temp->next;
    }
}

void deleteClient() {
    int pin;
    cout << "Enter PIN to delete account: ";
    cin >> pin;
    
    Client* temp = head;
    Client* prev = nullptr;
    
    if (temp != nullptr && temp->pin == pin) {
        head = temp->next;
        delete temp;
        cout << "Account deleted successfully!" << endl;
        return;
    }
    
    while (temp != nullptr && temp->pin != pin) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Account not found!" << endl;
        return;
    }
    
    prev->next = temp->next;
    delete temp;
    cout << "Account deleted successfully!" << endl;
}

void searchClient() {
    int choice;
    cout << "Search by:\n1. PIN\n2. Name" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    
    if (choice == 1) {
        int pin;
        cout << "Enter PIN: ";
        cin >> pin;
        
        Client* temp = head;
        while (temp != nullptr) {
            if (temp->pin == pin) {
                cout << "Client found! Name: " << temp->name << ", Balance: " << temp->balance << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Client not found!" << endl;
    } else if (choice == 2) {
        string name;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        
        Client* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Client found! PIN: " << temp->pin << ", Balance: " << temp->balance << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Client not found!" << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

// Displaying main and client menu
void displayMainMenu() {
    cout << "Welcome to CPP Bank System!" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Admin Console" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayClientMenu() {
    cout << "\nClient Menu:" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Balance Inquiry" << endl;
    cout << "4. Change PIN" << endl;
    cout << "5. Logout" << endl;
    cout << "Enter your choice: ";
}

void displayAdminMenu() {
    cout << "\nAdmin Console:" << endl;
    cout << "1. View Clients" << endl;
    cout << "2. Delete Client Account" << endl;
    cout << "3. Search Client" << endl;
    cout << "4. Logout" << endl;
    cout << "Enter your choice: ";
}

// Main function
int main() {
    int choice;
    Client* loggedInClient = nullptr;
    
    while (true) {
        displayMainMenu();
        cin >> choice;
        
        if (choice == 1) {
            registerClient();
        } else if (choice == 2) {
            loggedInClient = loginClient();
            
            if (loggedInClient != nullptr) {
                while (true) {
                    displayClientMenu();
                    cin >> choice;
                    
                    if (choice == 1) {
                        deposit(loggedInClient);
                    } else if (choice == 2) {
                        withdraw(loggedInClient);
                    } else if (choice == 3) {
                        balanceInquiry(loggedInClient);
                    } else if (choice == 4) {
                        changePIN(loggedInClient);
                    } else if (choice == 5) {
                        break; // Logout
                    } else {
                        cout << "Invalid choice!" << endl;
                    }
                }
            }
        } else if (choice == 3) {
            int adminPin;
            cout << "Enter Admin PIN: ";
            cin >> adminPin;
            
            if (adminPin == 1234) { // Example Admin PIN
                while (true) {
                    displayAdminMenu();
                    cin >> choice;
                    
                    if (choice == 1) {
                        viewClients();
                    } else if (choice == 2) {
                        deleteClient();
                    } else if (choice == 3) {
                        searchClient();
                    } else if (choice == 4) {
                        break; // Admin logout
                    } else {
                        cout << "Invalid choice!" << endl;
                    }
                }
            } else {
                cout << "Invalid Admin PIN!" << endl;
            }
        } else if (choice == 4) {
            break; // Exit program
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
