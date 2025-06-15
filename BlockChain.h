#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include "Pool.h"
class User;

class BlockChain {
private:
    Block* GenesisBlock;
    Block* LastBlock;
    Pool* TransactionsPool;
    User* Burse;

    int CountBlocks;
    std::string Name;
public:
    Pool* GetPool() { return TransactionsPool; }
    void SetPool(Pool* NewPool) { TransactionsPool=NewPool; }
    Block* GetGenesisBlock() { return GenesisBlock; }
    Block* GetLastBlock() { return LastBlock; }

    void SetBurse(User* SetBurse) { Burse = SetBurse; }
    User* GetBurse() { return Burse; }

    ~BlockChain() {
        delete TransactionsPool;
        Block* current = GenesisBlock;
        while (current != nullptr) {
            Block* next = current->GetNextBlock();
            delete current;
            current = next;
        }

        GenesisBlock = nullptr;
        LastBlock = nullptr;
    }
};

#endif 