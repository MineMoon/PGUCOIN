#ifndef POOL_H
#define POOL_H

#include <queue>
#include "Transaction.h"

class Pool {
private:
    std::queue<Transaction*> TransPool;
public:
    void AddTrans(Transaction* AddedTrans) { TransPool.push(AddedTrans); }
    void DeleteTrans() { TransPool.pop(); }
    Transaction* TopTrans() { return TransPool.front(); }
};

#endif