#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<iostream>
#include <string>


enum Action {
    DEPOSIT,      // Пополнение счета
    WITHDRAW,     // Снятие со счета
    TRANSFER,     // Перевод другому человеку
};

class User;

class Transaction {
private:
    User* Sender;
    User* Receiver;
    double Amount;
public:
    Transaction(User* SetSender, User* SetReceiver, double SetAmount) :
        Sender(SetSender), Receiver(SetReceiver), Amount(SetAmount){}

    User* GetSender() const { return Sender; }
    User* GetReceiver() const { return Receiver; }
    double GetAmount() const { return Amount; }

    void SetSender(User* SetSender) { Sender = SetSender; }
    void SetReceiver(User* SetReceiver) { Receiver = SetReceiver; }
    void SetAmount(double SetAmount) { Amount = SetAmount; }


};

#endif // TRANSACTION_H