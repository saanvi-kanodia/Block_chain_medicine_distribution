#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "blockchain.cpp"



class Customer {
private:
    string customerName;
    string pharmacyName;

public:
    void login() {
        cout << "\n👤 Customer Login\n";
        cout << "Enter your name: ";
        cin >> customerName;
        cout << "Enter the pharmacy name you are purchasing from: ";
        cin >> pharmacyName;
        cout << "Welcome, " << customerName << "!\n";
    }

    void verifyAuthenticity(Blockchain& chain) {
        string batchID, productName, mDate, eDate;
        cout << "\n🔍 Verifying Medicine Authenticity\n";
        cout << "Enter the batch details from the medicine label:\n";
        cout << "Batch ID: "; cin >> batchID;
        cout << "Product Name: "; cin >> productName;
        cout << "Manufacture Date: "; cin >> mDate;
        cout << "Expiry Date: "; cin >> eDate;
    
        Block* batch = chain.findBatch(batchID);
    
        if (batch == nullptr) {
            cout << "❌ Warning! This batch was not found in the blockchain.\n";
            return;
        }
    
        // First validate the rest of the fields
        if (batch->productName != productName || batch->manufactureDate != mDate || batch->expiryDate != eDate) {
            cout << "❌ Warning! Batch information doesn't match. Possible tampering.\n";
            return;
        }
    
        // Check if the pharmacy received this batch
        if (batch->delivered.count(pharmacyName) && batch->delivered[pharmacyName]) {
            cout << "✅ This medicine is authentic and was delivered to your pharmacy (" << pharmacyName << ").\n";
            cout << "🚚 Current Status: " << batch->status << "\n";
        } else {
            cout << "⚠️ This medicine is real, but was not delivered to " << pharmacyName << ".\n";
            cout << "🚫 You may be purchasing from an unauthorized source.\n";
        }
    }    

    void logout() {
        cout << "Logging out " << customerName << ". Thank you for verifying your medicine.\n";
    }
};
