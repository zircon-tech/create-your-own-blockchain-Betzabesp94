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


std::string sha256(const std::string str);

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
        transactionString = aSender + aReceiver + std::to_string(aAmount) +"_"+ timeNow;
        transactionHash = sha256(transactionString);
    }
    std::string getTransactionHash() {
        return transactionHash;
    }
};

int main() {
    Transaction t1("Tyrion", "Sansa", 50);
    std::cout << t1.transactionString << std::endl; // returns the concatenated string (sender, receiver, amount, currentTime) 
    std::cout << t1.getTransactionHash() << std::endl; // returns the hash of the previous string 
    Transaction t2("Jamie", "Daenerys", 25);
    std::cout << t2.transactionString << std::endl;
    std::cout << t2.getTransactionHash() << std::endl;
    std::cin.get();
    return 0;
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