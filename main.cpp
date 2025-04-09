#include<iostream>
#include<string>
#include<random>
#include<vector>
using namespace std;

// Include all class files
#include "Blockchain.cpp"
#include "Manufacturer.cpp"
#include "Pharmacist.cpp"
#include "Customer.cpp"

// Menu system
void showMenu() {
    cout << "\n\nWelcome to the Blockchain Medicine Distribution System\n";
    cout << "Please select your role:\n";
    cout << "1. Manufacturer\n";
    cout << "2. Pharmacist\n";
    cout << "3. Customer\n";
    cout << "4. Exit\n";
}

int getRole() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    Blockchain blockchain;
    Manufacturer manufacturer(&blockchain);
    Customer customer;

    int choice;

    do {
        showMenu();
        choice = getRole();

        switch (choice) {
            case 1:
                //manufacturer.login();
                manufacturer.createBatch();
                manufacturer.setRoute();
                //manufacturer.logout();
                break;

            case 2: {
                Pharmacist pharmacist;
                //pharmacist.login();
                pharmacist.incomingBatch(blockchain);
                //pharmacist.logout();
                break;
            }

            case 3:
                //customer.login();
                customer.verifyAuthenticity(blockchain);
                //customer.logout();
                break;

            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
