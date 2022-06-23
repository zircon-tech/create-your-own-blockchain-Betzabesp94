// CppBlockchain.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Notes : 

#pragma warning (disable : 4996) // This line to solve error C4996 

// Standard libraries
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
// standard to get the current Time
#include <ctime> 
// Openssl library 
#include <openssl/sha.h>

// Declearing Functions
void Print();
std::string sha256(const std::string str);

// Structs and classes
struct Block
{
    std::string data;
    std::string hash;
    Block* link;
};
// Pointer to Block (The head)
// Two operations
// 1. Insert a Block to the link list
// 2. Travelsal the link list
Block* head;

class Transaction
{
private:
    std::string transactionHash;
public:
    std::string sender;
    std::string receiver;
    int amount;
    std::string transactionString = "default";
    Transaction(std::string aSender, std::string aReceiver, int aAmount) {
        sender = aSender;
        receiver = aReceiver;
        amount = aAmount;
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::string timeNow = std::to_string(now->tm_mday) + '-' + std::to_string(now->tm_mon + 1) + '-' + std::to_string(now->tm_year + 1900);
        transactionString = aSender + aReceiver + std::to_string(aAmount) + "_" + timeNow;
        transactionHash = sha256(transactionString);
    }
    std::string getTransactionHash() {
        return transactionHash;
    }
};

void Insert(Transaction &sTransaction);

int main()
{
    head = NULL;
    int numbers;
    std::string aSender;
    std::string aReceiver;
    int aAmount;
    std::cout << "How many Transactions? " << std::endl;
    std::cin >> numbers;
    for (int i = 0; i < numbers; i++)
    {
        std::cout << "Enter the sender: " << std::endl;
        std::cin >> aSender;
        std::cout << "Enter the receiver: " << std::endl;
        std::cin >> aReceiver;
        std::cout << "Enter the amount: " << std::endl;
        std::cin >> aAmount;
        Transaction t(aSender, aReceiver, aAmount);
        Insert(t);
        Print();
    }
    std::cout << "Press Any key to exit and hit enter";
    std::string anyKey;
    std::cin>>anyKey;
    std::cout << "Goodbye!";
}

// Insert a new Block at the begining of the list
void Insert(Transaction &sTransaction)
{
    Block* temp = new Block();
    (*temp).data = sTransaction.transactionString;
    (*temp).hash = sTransaction.getTransactionHash();
    (*temp).link = head;
    head = temp;

    // std::cout << head << std::endl;
}

void Print()
{
    Block* temp = new Block();
    temp = head;
    int blockNumber = 0;
    std::cout << "The blocks are: " << std::endl;
    while (temp != NULL)
    {
        std::cout << "Data: "<< (*temp).data << " ";
        std::cout <<" Block number: "<<(blockNumber+1)<<" and the hash: "<< (*temp).hash << std::endl;
        temp = (*temp).link;
        blockNumber++;
    }
    std::cout << "" << std::endl;
}




// Creation of a function to hash using library 
std::string sha256(const std::string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}