#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Transaction.h"

class BlockChain;

class User {
private:
    int UserID;
    std::string Name;
    double Balance;
    BlockChain* HisBlockChain;
    BlockChain CopyBlockChain;
    std::vector<Transaction*> TransHistory;
public:

    std::string GetName() { return Name; }

    void SetName(std::string NewName) { Name = NewName; }

    void SetID(int Number) { UserID = Number; }

    int GetID() { return UserID; }

    void SetBlockChain(BlockChain* NewBlockChain) {
        HisBlockChain = NewBlockChain;
    }
    
    BlockChain* GetBlockChain() { return HisBlockChain; }

    double GetBalance() { return Balance; }

    void Receiving(double Amount) { Balance += Amount; }

    void Withdrawal(double Amount) {
        if (Amount <= Balance) Balance -= Amount;
    }

    void MakeTransaction(User* Person, double Amount, Action Oper) {
        Transaction* PTrans;
        switch (Oper)
        {
        case Action::DEPOSIT:

            if (Person != this) return;
            PTrans = new Transaction(this->GetBlockChain()->GetBurse(), this, Amount);
            HisBlockChain->GetPool()->AddTrans(PTrans);

            break;
        case Action::WITHDRAW:

            if (Amount <= 0 || Amount > Balance || Person!=this) return;
            PTrans = new Transaction(this, this->GetBlockChain()->GetBurse(), Amount);

            break;
        case TRANSFER:

            if (Amount <= 0 || Amount > Balance) return;
            PTrans = new Transaction(this, Person, Amount);
            HisBlockChain->GetPool()->AddTrans(PTrans);

            break;
        default:
            break;
        }
        TransHistory.push_back(PTrans); // сделать это после принятие блока
    }

    ~User() {
        TransHistory.clear();
    }

};

#endif