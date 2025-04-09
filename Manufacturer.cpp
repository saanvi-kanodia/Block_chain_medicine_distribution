#include<iostream>
#include<string>
#include<vector>
#include "blockchain.cpp"
#include "route_optimization.cpp"

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

        cout << "\nChoose delivery type:\n";
        cout << "1. Single Truck (Prim's Algorithm)\n";
        cout << "2. Multiple Trucks (Dijkstra's Algorithm)\n";
        int choice;
        cin >> choice;

        // From manufacturer code
        if (choice == 1) {
            runPrims(); // +1 to include Mumbai
        } else if (choice == 2) {
            runDijkstra();
        }


        //batch->deliveryPath = pharmacyList;
        //for (const auto& pharmacy : pharmacyList)
         //   batch->delivered[pharmacy] = false;

        batch->status = "In Transit";
        cout << "\nDelivery route set successfully!\n";
        cout<<"Batch is in transit";
}

};