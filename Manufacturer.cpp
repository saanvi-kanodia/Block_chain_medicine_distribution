#include<iostream>
#include<string>
#include<vector>
#include "blockchain.cpp"

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

    void createBatch() {
        
        cout << "\nManufacturer ID: " << manufacturerID << endl;
        cout << "-----------------------------------------------------\n";
        cout << "Enter the details of the batch\n";
        
        string batchID, productName, manufactureDate, expiryDate;
        cout << "Enter the batch ID: "; cin >> batchID;
        cout << "Enter the product name: "; cin >> productName;
        cout << "Enter the manufacture date: "; cin >> manufactureDate;
        cout << "Enter the expiry date: "; cin >> expiryDate;

        chain->createBatch(batchID, productName, manufactureDate, expiryDate, manufacturerID);
        cout << "\n✅ Batch created successfully!\n";
    }

    void setRoute() {
        cout << "Enter batch ID to dispatch: ";
        string batchID;
        cin >> batchID;

        Block* batch = chain->findBatch(batchID);
        if (batch == nullptr) {
            cout << "❌ Batch not found.\n";
            return;
        }

        int numPharmacies;
        cout << "\nEnter number of pharmacies to deliver to: ";
        cin >> numPharmacies;

        vector<string> pharmacyList(numPharmacies);
        cout << "Enter names of the pharmacies:\n";
        for (int i = 0; i < numPharmacies; ++i) {
            cout << "Pharmacy " << i + 1 << ": ";
            cin >> pharmacyList[i];
        }

        cout << "\nChoose delivery type:\n";
        cout << "1. Single Truck (Prim's Algorithm)\n";
        cout << "2. Multiple Trucks (Dijkstra's Algorithm)\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
           // deliveryGraph.runPrims();
        } else if (choice == 2) {
           // deliveryGraph.runDijkstra();
        } else {
            cout << "Invalid choice.\n";
            return;
        }

        batch->deliveryPath = pharmacyList;
        for (const auto& pharmacy : pharmacyList)
            batch->delivered[pharmacy] = false;

        batch->status = "In Transit";
        cout << "\nDelivery route set successfully!\n";
        cout<<"Batch is in transit";
}

};