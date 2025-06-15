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


    /*void Print() {
        while (!TransPool.empty()) {
            Transaction* Trans = TransPool.front();
            std::cout << "    Sender: " << Trans->GetSender()->GetName() << std::endl;
            std::cout << "    Receiver: " << Trans->GetReceiver()->GetName() << std::endl;
            std::cout << "    Amount: " << Trans->GetAmount() << std::endl;

        }
    }*/

    ~Pool() {
        while (!TransPool.empty()) {
            Transaction* trans = TransPool.front();
            delete trans;
            TransPool.pop();
        }
    }
};

#endif