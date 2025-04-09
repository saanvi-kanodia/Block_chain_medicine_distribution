#include<iostream>
#include<string>
#include<random> // for random number generation
#include<vector>
#include<map> // for map data structure
using namespace std;

class Block{
public:
    string batchID;
    string productName;
    string manufactureDate;
    string expiryDate;
    string manufacturerID;
    unsigned long long hash;
    string status;         // NEW: status field

    vector<string> deliveryPath;             // 🚚 The route decided by manufacturer
    map<string, bool> delivered;         // 📦 Delivery status for each pharmacy
    
    Block* next;

    Block() {
        next = nullptr;
    }
};

class Blockchain{
private:
    Block*head;

    unsigned long long generateHash(string input){
        random_device rd;            // Get a random seed from hardware
        mt19937 gen(rd());           // Use Mersenne Twister random number generator, seeded with rd
        uniform_int_distribution<> distr(1000000000000000, 2550000000000000); // Define range from 0 to 255
        unsigned long long hash = distr(gen);
        for (char c : input) {
            hash ^= (unsigned char)c;
            hash ^= (hash >> 13);
            hash ^= (hash << 7);
        }
        return hash;
    }

public:
    Blockchain(){
        head = nullptr;
    }

    Block* getHead() {
        return head;
    }    

    void addBlock(Block* block) {
        block->next = head;
        head = block;
    }

    Block* createBatch(string batchID, string productName, string mDate, string eDate, string manufacturerID) {
        string input = batchID + productName + mDate + eDate ;
        unsigned long long hash = generateHash(input);
    
        Block* newBlock = new Block();
        newBlock->batchID = batchID;
        newBlock->productName = productName;
        newBlock->manufactureDate = mDate;
        newBlock->expiryDate = eDate;
        newBlock->hash = hash;
        newBlock->deliveryPath = {};             // Empty initially
        newBlock->delivered.clear();             // No confirmations yet
        newBlock->next = head;
        head = newBlock;
        newBlock->status = "Created";

        return newBlock; // Return pointer to newly created block
    }

    Block* findBatch(string batchID) {
        Block* temp = head;
        while (temp != nullptr) {
            if (temp->batchID == batchID) {
                return temp;  // Batch found
            }
            temp = temp->next;
        }
        return nullptr;  // Batch not found
    }

    bool verifyBatch(string batchID, string productName, string mDate, string eDate) {
        string input = batchID + productName + mDate + eDate;
    unsigned long long computedHash = generateHash(input);

    Block* temp = head;
    while (temp != nullptr) {
        if (temp->batchID == batchID && temp->hash == computedHash) {
            return true; // Valid batch found
        }
        temp = temp->next;
    }
    return false; // No matching batch found
    }
};

