#include<iostream>
#include<string>
#include<vector>
#include "blockchain.h"
#include "route_optimization.h"
using namespace std;    

class Manufacturer {
private:
    string manufacturerID;  // fixed for the only manufacturer
    Blockchain* chain; // pointer to shared blockchain

public:
    Manufacturer(Blockchain* bc) {
        manufacturerID = "MFG001"; // hardcoded ID
        chain = bc;
    }

    void login() {
        cout << "\nManufacturer Loged in\n";
        cout << "Welcome, " << manufacturerID << "!\n";
    }

    void createBatch() {
        
        cout << "\nManufacturer ID: " << manufacturerID << endl;
        cout << "-----------------------------------------------------\n";
        cout << "Creating a new medicine batch. Enter the details\n";
        
        string batchID, productName, manufactureDate, expiryDate;
        cout << "Enter the batch ID: "; cin >> batchID;
        cout << "Enter the product name: "; cin >> productName;
        cout << "Enter the manufacture date: "; cin >> manufactureDate;
        cout << "Enter the expiry date: "; cin >> expiryDate;

        chain->createBatch(batchID, productName, manufactureDate, expiryDate, manufacturerID);
        cout << "\n Batch created successfully!\n";
    }

    void setRoute() {
        cout << "Enter batch ID to dispatch: ";
        string batchID;
        cin >> batchID;

        Block* batch = chain->findBatch(batchID);
        if (batch == nullptr) {
            cout << "Batch not found.\n";
            return;
        }

        cout << "Batch found!\n";
        cout << "\nChoose delivery type:\n";
        cout << "1. Single Truck (Prim's Algorithm)\n";
        cout << "2. Multiple Trucks (Dijkstra's Algorithm)\n";
        int choice;
        cin >> choice;

        // From manufacturer code
        vector<string> pharmacyList;
        if (choice == 1) {
            pharmacyList = runPrims();
        } else if (choice == 2) {
            pharmacyList = runDijkstra();
        }

        batch->deliveryPath = pharmacyList;
        for (const auto& pharmacy : pharmacyList)
            batch->delivered[pharmacy] = false;

        batch->status = "In Transit";
        cout << "\nDelivery route set successfully!\n";
        cout<<"Batch is in transit\n";

        cout << " Delivery Path: ";
        for (int i=0; i<pharmacyList.size(); i++) {
            cout << pharmacyList[i]<<" >>  ";
        }
        cout << endl;
}



    void logout() {
        cout<<"---------------------------------------";
        cout << "\nLogging out " << manufacturerID << ". Thank you!\n";
    }
};