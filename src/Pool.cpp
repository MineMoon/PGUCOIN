#include "../include/Pool.h"
#include <algorithm>

std::vector<Transaction*> Pool::GetTransactions(size_t Count) {
    std::vector<Transaction*> GettedTransactions;
    size_t numToGet = std::min(Count, TransPool.size());
    std::queue<Transaction*> TempPool = TransPool;
    for (size_t i = 0; i < numToGet; ++i) {
        GettedTransactions.push_back(TempPool.front());
        TempPool.pop();
    }
    return GettedTransactions;
}

void Pool::RemoveTransactions(size_t Count) {
    size_t NumToRemove = std::min(Count, TransPool.size());
    for (size_t i = 0; i < NumToRemove; ++i) {
        Transaction* Trans = TransPool.front();
        delete Trans;
        TransPool.pop();
    }
}