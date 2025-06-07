#include<string>
#include<vector>
#include"Transaction.h"
#include"Pool.h"

class BlockChain{}; typedef BlockChain* PBlockChain;

class User {
private:
	int UserID;
	std::string Name;
	double Balance;
	BlockChain CopyBlockChain;
	PBlockChain HisBlockChain;
	std::vector<PTransaction> TransHistory;
public:

	void Receiving(double Amount) { Balance += Amount; } // получение

	void MakeTransaction(double SendedAmount, User* Receiver, double Amount) { 
		if (Amount > Balance || Amount<=0)
			return;

		PTransaction PTrans = new Transaction(this, Receiver, Amount); // Создаёт транзакию
		HisBlockChain->GetPool()->AddTrans(PTrans);                    // Отправляет в открытый пул
		TransHistory.push_back(PTrans);  // <- Сделать в другом месте! // Надо сделать после приянтия блока в блокчейн!

	}

	void AccountReplenishment(double Dodep) { // Пополнение счета
		if (Dodep > 0) Balance += Dodep;
	}

	void WithdrawalFromAccount(double Amount) { // Снятие со счета
		if (Amount <= Balance) Balance -= Amount;
	}

};
typedef User* PUser;