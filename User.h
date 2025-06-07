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

	void Receiving(double Amount) { Balance += Amount; } // ���������

	void MakeTransaction(double SendedAmount, User* Receiver, double Amount) { 
		if (Amount > Balance || Amount<=0)
			return;

		PTransaction PTrans = new Transaction(this, Receiver, Amount); // ������ ���������
		HisBlockChain->GetPool()->AddTrans(PTrans);                    // ���������� � �������� ���
		TransHistory.push_back(PTrans);  // <- ������� � ������ �����! // ���� ������� ����� �������� ����� � ��������!

	}

	void AccountReplenishment(double Dodep) { // ���������� �����
		if (Dodep > 0) Balance += Dodep;
	}

	void WithdrawalFromAccount(double Amount) { // ������ �� �����
		if (Amount <= Balance) Balance -= Amount;
	}

};
typedef User* PUser;