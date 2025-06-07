#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class User; // Предварительное объявление

class Transaction {
private:
    User* Sender;
    User* Receiver;
    double Amount;
public:
    Transaction(User* SetSender, User* SetReceiver, double SetAmount) :
        Sender(SetSender), Receiver(SetReceiver), Amount(SetAmount) {}

    User* GetSender() const { return Sender; }
    User* GetReceiver() const { return Receiver; }
    double GetAmount() const { return Amount; }

    void SetSender(User* SetSender) { Sender = SetSender; }
    void SetReceiver(User* SetReceiver) { Receiver = SetReceiver; }
    void SetAmount(double SetAmount) { Amount = SetAmount; }
};

#endif // TRANSACTION_H