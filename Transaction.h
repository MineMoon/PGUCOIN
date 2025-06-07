#include<string>

class User {}; typedef User* PUser;

class Transaction {
	PUser Sender;
	PUser Receiver;
	double Amount;
public:
	
	Transaction(PUser SetSender, PUser SetReceiver, double SetAmount):
		Sender(SetSender), Receiver(SetReceiver), Amount(SetAmount) {}

	PUser GetSender() const { return Sender; }

	PUser GetResiver() const { return Receiver; }

	double GetAmount() const { return Amount; };

	void SetSender(PUser SetSender) { Sender = SetSender; }

	void SetResiver(PUser SetReceiver) { Receiver = SetReceiver; }

	void SetAmount(double SetAmount) { Amount = SetAmount; }

};
typedef Transaction* PTransaction;