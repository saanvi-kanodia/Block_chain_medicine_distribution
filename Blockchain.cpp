#include "blockchain.h"
#include "sha256.h"
using namespace std;

Blockchain::Blockchain() {
    head = nullptr;
}

string Blockchain::generateHash(const string &input) {
    return sha256(input);
}

Block *Blockchain::getHead() {
    return head;
}

void Blockchain::addBlock(Block *block) {
    block->next = head;
    head = block;
}

Block *Blockchain::createBatch(string batchID, string productName, string mDate, string eDate, string manufacturerID) {
    string input = batchID + productName + mDate + eDate;
    string hash = generateHash(input);
    Block *newBlock = new Block();
    newBlock->batchID = batchID;
    newBlock->productName = productName;
    newBlock->manufactureDate = mDate;
    newBlock->expiryDate = eDate;
    newBlock->hash = hash;
    newBlock->deliveryPath = {};
    newBlock->delivered.clear();
    newBlock->next = head;
    newBlock->status = "Created";
    head = newBlock;
    return newBlock;
}

Block *Blockchain::findBatch(string batchID) {
    Block *temp = head;
    while (temp != nullptr) {
        if (temp->batchID == batchID) return temp;
        temp = temp->next;
    }
    return nullptr;
}

bool Blockchain::verifyBatch(string batchID, string productName, string mDate, string eDate) {
    string input = batchID + productName + mDate + eDate;
    string computedHash = generateHash(input);

    Block *temp = head;
    while (temp != nullptr) {
        if (temp->batchID == batchID && temp->hash == computedHash)
            return true;
        temp = temp->next;
    }
    return false;
}