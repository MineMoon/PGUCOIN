#include<string>
#include<vector>
#include<iostream>
#include"sha256.h"
class Block {
private:
	int Number;
	std::string Hash;
	std::string HashMerkle;
	std::string Data;
	Block* PrevBlock;
	Block* NextBlock;
	time_t Time;
	std::vector<PTransaction> TransactionList;
public:
	
	std::string GetHash() const { return Hash; }

	int GetNumber() const { return Number; }

	PBloke GetPrevBlock() const {
		if (!PrevBlock) {
			std::cout << "It's Genesis Block!\n";
			return nullptr;
		}
		return PrevBlock;
	}

	PBloke GetNextBlock() const {
		if (!NextBlock) {
			std::cout << "It's last Block!\n";
			return nullptr;
		}
		return NextBlock;
	}

	void AddTransaction(PTransaction Trans) {TransactionList.push_back(Trans);}

	std::string Hash() { return sha256(std::to_string(Number) + Data + PrevBlock->GetHash() ); }

};
typedef Block* PBloke;