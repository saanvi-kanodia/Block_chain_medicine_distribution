// blockchain.h
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <map>
using namespace std;

class Block {
public:
    string batchID;
    string productName;
    string manufactureDate;
    string expiryDate;
    string manufacturerID;
    string hash; 
    string status;

    vector<string> deliveryPath;
    map<string, bool> delivered;

    Block *next;

    Block() { next = nullptr; }
};

class Blockchain {
private:
    Block *head;
    string generateHash(const string &input);
public:
    Blockchain();
    Block *getHead();
    void addBlock(Block *block);
    Block *createBatch(string batchID, string productName, string mDate, string eDate, string manufacturerID);
    Block *findBatch(string batchID);
    bool verifyBatch(string batchID, string productName, string mDate, string eDate);
};

#endif // BLOCKCHAIN_H
