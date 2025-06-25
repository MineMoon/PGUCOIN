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
    bool IsEmpty() const { return TransPool.empty(); }

    // Геттер
    size_t GetSize() const { return TransPool.size(); }

    std::vector<Transaction*> GetTransactions(size_t Count);
    void RemoveTransactions(size_t Count);

    ~Pool() {
        while (!TransPool.empty()) {
            Transaction* Trans = TransPool.front();
            delete Trans;
            TransPool.pop();
        }
    }
};

#endif