
#include<string>
#include<vector>
#include"Block.h"
#include"Transaction.h"
#include"User.h"
#include"Pool.h"

class BlockChain {
private:
	PBloke GenesisBlock;
	PBloke LastBlock;
	PPool TransactionsPool;
	int CountBlocks;
	std::string Name;

public:

	PPool GetPool() { return TransactionsPool; }

	PBloke GetGenesisBlock() { return GenesisBlock; };

	PBloke GetLastBlock() { return LastBlock; };

};
typedef BlockChain* PBlockChain;