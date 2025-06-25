#include "../include/User.h"
#include "../include/BlockChain.h"
#include "../include/Pool.h"
#include <iostream>

User::User() : UserID(0), Name(""), HisBlockChain(nullptr) {} // Конструктор по умолчанию для обработки пустых пользователей

User::User(int Id, const std::string& Name, BlockChain* Bc) : UserID(Id), Name(Name), HisBlockChain(Bc) {} // Основной конструктор

bool User::MakeTransaction(User* Person, double Amount, Action Oper) {
    if (!HisBlockChain || !HisBlockChain->GetPool() || !HisBlockChain->GetBurse()) {
        std::cerr << "Error: Blockchain or Pool or Burse not properly set for user " << Name << ".\n";
        return false;
    }

    if (Amount <= 0) {
        std::cerr << "Error: Transaction amount must be positive.\n";
        return false;
    }

    Transaction* PTrans = nullptr;
    bool Success = true;

    switch (Oper) {

        // Операции с фондом

        case Action::DEPOSIT:
            if (Person != this) {
                std::cerr << "Error: Deposit must be to self.\n";
                Success = false;
            } else {
                PTrans = new Transaction(HisBlockChain->GetBurse(), this, Amount);
                HisBlockChain->GetPool()->AddTrans(PTrans);
            }
            break;
        case Action::WITHDRAW:
            if (Person != this) {
                std::cerr << "Error: Withdrawal must be from self.\n";
                Success = false;
            } else {
                // Смотрим по последнему блоку, для улучшения безопасности можем допилить локальную проверку в будущем
                PTrans = new Transaction(this, HisBlockChain->GetBurse(), Amount);
                HisBlockChain->GetPool()->AddTrans(PTrans);
            }
            break;

        // Операции между пользователями

        case Action::TRANSFER:
            if (this == Person) {
                std::cerr << "Error: Cannot transfer to self.\n";
                Success = false;
            } else if (!Person) {
                 std::cerr << "Error: Receiver is null.\n";
                Success = false;
            }
            else {
                PTrans = new Transaction(this, Person, Amount);
                HisBlockChain->GetPool()->AddTrans(PTrans);
            }
            break;

        default:
            std::cerr << "Error: Unknown action type.\n";
            Success = false;
            break;
    }

    if (PTrans && Success) {
        TransHistory.push_back(PTrans);

    } else {
        delete PTrans; // Удаляем невалидную транзакцию, чтобы избежать утечки
    }
    return Success;
}

User::~User() {
    TransHistory.clear();
}