#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Transaction.h"

class BlockChain;
class Pool;

class User {
private:
    int UserID;
    std::string Name;
    double Balance;
    BlockChain* HisBlockChain;
    std::vector<Transaction*> TransHistory;
public:
    void Receiving(double Amount) { Balance += Amount; }

    void MakeTransaction(double Amount, User* Receiver) {
        if (Amount <= 0 || Amount > Balance) return;

        Transaction* PTrans = new Transaction(this, Receiver, Amount);
        HisBlockChain->GetPool()->AddTrans(PTrans);
        TransHistory.push_back(PTrans);
    }

    void AccountReplenishment(double Dodep) {
        if (Dodep > 0) Balance += Dodep;
    }

    void WithdrawalFromAccount(double Amount) {
        if (Amount <= Balance) Balance -= Amount;
    }
};

#endif