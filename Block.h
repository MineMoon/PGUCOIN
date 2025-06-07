#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include"iostream"
#include <vector>
#include <ctime>
#include "Transaction.h"

class Block {
private:
    int Number;
    std::string Hash;
    std::string HashMerkle;
    Block* PrevBlock;
    Block* NextBlock;
    time_t Time;
    std::vector<Transaction*> TransactionList;
public:
    std::string GetHash() const { return Hash; }
    int GetNumber() const { return Number; }

    Block* GetPrevBlock() const {
        if (!PrevBlock) {
            std::cerr << "It's Genesis Block!\n";
            return nullptr;
        }
        return PrevBlock;
    }

    Block* GetNextBlock() const {
        if (!NextBlock) {
            std::cerr << "It's last Block!\n";
            return nullptr;
        }
        return NextBlock;
    }

    void AddTransaction(Transaction* Trans) {
        TransactionList.push_back(Trans);
    }

};

#endif // BLOCK_H