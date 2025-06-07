#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include "Pool.h"

class BlockChain {
private:
    Block* GenesisBlock;
    Block* LastBlock;
    Pool* TransactionsPool;
    int CountBlocks;
    std::string Name;
public:
    Pool* GetPool() { return TransactionsPool; }
    void SetPool(Pool* NewPool) { TransactionsPool=NewPool; }
    Block* GetGenesisBlock() { return GenesisBlock; }
    Block* GetLastBlock() { return LastBlock; }
};

#endif 