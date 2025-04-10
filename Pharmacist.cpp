#include<iostream>
#include<string>
#include<vector>
#include "blockchain.h"
using namespace std;    

class Pharmacist {
private:
    string pharmacyName; 
    Blockchain* chain; // pointer to shared blockchain

public:
    bool verifyReceivedBatch(Blockchain& blockchain) {
        string batchID, productName, mDate, eDate;
        cout << "Enter batch details to verify:\n";
        cout << "Batch ID: "; cin >> batchID;
        cout << "Product Name: "; cin >> productName;
        cout << "Manufacture Date: "; cin >> mDate;
        cout << "Expiry Date: "; cin >> eDate;

        bool valid = blockchain.verifyBatch(batchID, productName, mDate, eDate);
        if (valid){
            cout << " Batch is valid.\n";
            return valid;
        }
        else
            cout << " Invalid batch! Data tampered or not found.\n";
            return valid;

    }

    void login() {
        cout << "\n Pharmacist Login\n";
        cin.ignore();
        cout << "Enter pharmacy name: ";
        getline(cin, pharmacyName);
        cout << "Welcome, " << pharmacyName << "!\n";
    }

    void incomingBatch(Blockchain& chain) {
        cout << "\nChecking for incoming batches for " << pharmacyName << "...\n";
        Block* temp = chain.getHead();
        bool found = false;
    
        while (temp != nullptr) {
            vector<string>& path = temp->deliveryPath;
            for (int i = 0; i < path.size(); i++) {
                if (path[i] == pharmacyName) {
                    found = true;
    
                    // Check if it's this pharmacist's turn
                    if ((i == 0 || temp->delivered[path[i - 1]]) && !temp->delivered[pharmacyName]) {
                        cout << " Batch " << temp->batchID << " is now ready for confirmation at your pharmacy.\n";
                        bool valid = verifyReceivedBatch(chain); 
                        if (valid) {
                            temp->delivered[pharmacyName] = true;
                            cout << " Delivery confirmed for pharmacy: " << pharmacyName << endl;
                            if (i + 1 < path.size()) 
                                temp->status = "Delivered at " + pharmacyName + ", moving to " + path[i + 1];
                            else 
                            temp->status = " Final Delivery Completed at " + pharmacyName;
                        }
                        else 
                            cout << "⚠️ Invalid batch! Delivery not confirmed.\n";    
                    }
                    else if (!temp->delivered[pharmacyName]) {
                        cout << "⏳ Batch " << temp->batchID << " will reach you soon. Waiting for delivery to " 
                             << path[i - 1] << " first.\n";
                    }
                    break; // Stop checking once match is found
                }
            }
            temp = temp->next; // ✅ Always move to next block outside for-loop
        }
    
        if (!found) {
            cout << "No batches assigned to your pharmacy at the moment.\n";
        }
    }

    void logout() {
        cout << "Logging out " << pharmacyName << ". Thank you for verifying your medicine.\n";
    }
};