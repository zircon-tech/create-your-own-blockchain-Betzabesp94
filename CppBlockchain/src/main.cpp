// CppBlockchain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning (disable : 4996) // This line to solve error C4996 

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <openssl/sha.h>

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

int main() {
    std::string secretWord = "Zircon";
    std::cout << sha256(secretWord) << std::endl; // Hashing "Zircon" 
    std::cout << sha256("Betzachain in progress...") << std::endl;
    std::cin.get();
    return 0;
}


