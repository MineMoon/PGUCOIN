#define _CRT_SECURE_NO_WARNINGS 
#include "../include/BlockChain.h"
#include <limits>
#include <iomanip>
#include <map>


// Конструктор
BlockChain::BlockChain(const std::string& Name, const std::string& SaveFileName, std::vector<User*>* Users)
    : Name(Name), SaveFileName(SaveFileName), GenesisBlock(nullptr), LastBlock(nullptr), Burse(nullptr), CountBlocks(0), AllUsers(Users) {
    TransactionsPool = new Pool();
    CurrentHardMining = 1;
    std::cout << "Blockchain '" << Name << "' system initiated.\n";
}

// Деструктор
BlockChain::~BlockChain() {
    delete TransactionsPool;
    ClearChain();
    std::cout << "Blockchain '" << Name << "' system shut down.\n";
}


void BlockChain::ClearChain() {
    Block* Current = GenesisBlock;
    while (Current != nullptr) {
        Block* Next = Current->GetNextBlock();
        delete Current;
        Current = Next;
    }
    GenesisBlock = nullptr;
    LastBlock = nullptr;
    CountBlocks = 0;
}

void BlockChain::CreateGenesisBlock(const std::vector<Transaction*>& InitialTransactions) {
    if (GenesisBlock) {
        std::cerr << "Genesis block already exists!\n";
        return;
    }

    GenesisBlock = new Block(0, nullptr, InitialTransactions);
    LastBlock = GenesisBlock;
    CountBlocks = 1;
    std::cout << "Genesis Block created with hash: " << GenesisBlock->GetHash() << std::endl;

    // Сохраняем сразу после создания генезис-блока
    SaveToFile();
}

bool BlockChain::IsTransactionValid(Transaction* Trans) const {
    if (!Trans) return false;

    if (Trans->GetSender() == Burse) {
        return true;
    }

    double SenderBalance = GetUserBalance(Trans->GetSender());
    if (SenderBalance < Trans->GetAmount()) {
        std::cerr << "Validation Error: Sender " << Trans->GetSender()->GetName()
                  << " has insufficient funds (" << SenderBalance << ") for transaction Amount "
                  << Trans->GetAmount() << std::endl;
        return false;
    }

    return true;
}

bool BlockChain::MineBlock(int MaxTransactions) {
    if (TransactionsPool->IsEmpty() && CountBlocks > 0) {
        std::cout << "No transactions in the pool to mine.\n";
        return false;
    }

    if (!GenesisBlock) {
        std::cout << "Creating Genesis Block first...\n";
        CreateGenesisBlock({});
        return true;
    }

    std::cout << "\nAttempting to mine a new block...\n";
    std::vector<Transaction*> TransactionsToMine;

    int ProcessedCount = 0;
    while (!TransactionsPool->IsEmpty() && ProcessedCount < MaxTransactions) {
        Transaction* Trans = TransactionsPool->TopTrans();
        TransactionsPool->DeleteTrans();

        if (IsTransactionValid(Trans)) {
            TransactionsToMine.push_back(Trans);
        } else {
            std::cerr << "Validation Error: Transaction " << Trans->ToString()
                      << " is invalid and will be discarded.\n";
            delete Trans;
        }
        ProcessedCount++;
    }

    if (TransactionsToMine.empty() && CountBlocks > 0) {
        std::cout << "No valid transactions found to mine a block.\n";
        return false;
    }
    if (TransactionsToMine.empty()) {
        std::cout << "No valid transactions found to mine a block.\n";
        return false;
    }
    else {
        for (auto i = 0; i < TransactionsToMine.size(); i++) { // Добавление транзакции в историю пользователей
            if (TransactionsToMine[i]->GetReceiver() != this->GetBurse()) {
                TransactionsToMine[i]->GetReceiver()->AddTransToHistory(TransactionsToMine[i]);
            }
            if (TransactionsToMine[i]->GetSender() != this->GetBurse()) {
                TransactionsToMine[i]->GetSender()->AddTransToHistory(TransactionsToMine[i]);
            }
        }
    }

    

    Block* NewBlock = new Block(CountBlocks, LastBlock, TransactionsToMine);

    //PoW
    std::string Solution;
    while (!CheckSolution(Solution)) {
        NewBlock->RiseNonce();
        Solution = sha256(NewBlock->ToString());
    }

    if (LastBlock) {
        LastBlock->SetNextBlock(NewBlock);
    }

    LastBlock = NewBlock;
    CountBlocks++;

    std::cout << "Block #" << NewBlock->GetNumber() << " mined!" << std::endl;
    std::cout << "  Hash: " << NewBlock->GetHash() << std::endl;
    std::cout << "  Merkle Root: " << NewBlock->GetHashMerkle() << std::endl;
    std::cout << "  Transactions: " << NewBlock->GetTransactionList().size() << std::endl;
    std::cout << "  Pool size remaining: " << TransactionsPool->GetSize() << std::endl;

    if (SaveToFile()) {
        std::cout << "Blockchain state automatically saved.\n";
    } else {
        std::cerr << "Warning: Failed to automatically save blockchain state.\n";
    }

    return true;
}

double BlockChain::GetUserBalance(const User* CurUser) const {
    if (!CurUser) return 0.0;
    double Balance = 0.0;

    Block* Current = GenesisBlock;
    while (Current != nullptr) {
        for (const auto& Trans : Current->GetTransactionList()) {
            if (Trans->GetReceiver() == CurUser) {
                Balance += Trans->GetAmount();
            }
            if (Trans->GetSender() == CurUser) {
                Balance -= Trans->GetAmount();
            }
        }
        Current = Current->GetNextBlock();
    }
    return Balance;
}

void BlockChain::PrintChain() const {
    std::cout << "\n--- BLOCKCHAIN: " << Name << " ---\n";
    if (!GenesisBlock) {
        std::cout << "Blockchain is empty.\n";
        return;
    }

    Block* Current = GenesisBlock;
    while (Current != nullptr) {
        std::cout << "Block #" << Current->GetNumber() << "\n";
        std::cout << "  Hash: " << Current->GetHash() << "\n";
        std::cout << "  Previous Hash: " << (Current->GetPrevBlock() ? Current->GetPrevBlock()->GetHash() : "N/A (Genesis)") << "\n";
        std::cout << "  Merkle Root: " << Current->GetHashMerkle() << "\n";
        time_t TimestampVal = Current->GetTimeStamp();
        std::cout << "  Timestamp: " << ctime(&TimestampVal);
        std::cout << "  Transactions (" << Current->GetTransactionList().size() << "):" << "\n";
        for (const auto& Trans : Current->GetTransactionList()) {
            std::cout << "    - From: " << (Trans->GetSender() ? Trans->GetSender()->GetName() : "Burse")
                      << " To: " << (Trans->GetReceiver() ? Trans->GetReceiver()->GetName() : "Burse")
                      << " Amount: " << std::fixed << std::setprecision(2) << Trans->GetAmount() << "\n";
        }
        std::cout << "\n";
        Current = Current->GetNextBlock();
    }
    std::cout << "--- END OF CHAIN ---\n";
}

// Сохранение блокчейна в файл
bool BlockChain::SaveToFile() const {
    std::ofstream OutFile(SaveFileName, std::ios::binary);
    if (!OutFile) {
        std::cerr << "Error: Could not open file for writing: " << SaveFileName << std::endl;
        return false;
    }

    const std::vector<User*>& Users = *AllUsers;
    size_t UserCount = Users.size();
    OutFile.write(reinterpret_cast<const char*>(&UserCount), sizeof(UserCount));
    for (const auto& CurUser : Users) {
        int Id = CurUser->GetID();
        std::string UsName = CurUser->GetName();
        size_t NameLen = UsName.length();
        OutFile.write(reinterpret_cast<const char*>(&Id), sizeof(Id));
        OutFile.write(reinterpret_cast<const char*>(&NameLen), sizeof(NameLen));
        OutFile.write(UsName.c_str(), NameLen);
    }

    OutFile.write(reinterpret_cast<const char*>(&CountBlocks), sizeof(CountBlocks));
    Block* Current = GenesisBlock;
    while (Current != nullptr) {
        int Num = Current->GetNumber();
        time_t Ts = Current->GetTimeStamp();
        std::string CurHash = Current->GetHash();
        size_t HashLen = CurHash.length();
        std::string Merkle = Current->GetHashMerkle();
        size_t MerkleLen = Merkle.length();
        //
        int WriteNonce = Current->GetNonce();

        OutFile.write(reinterpret_cast<const char*>(&Num), sizeof(Num));
        OutFile.write(reinterpret_cast<const char*>(&Ts), sizeof(Ts));
        OutFile.write(reinterpret_cast<const char*>(&HashLen), sizeof(HashLen));
        OutFile.write(CurHash.c_str(), HashLen);
        OutFile.write(reinterpret_cast<const char*>(&MerkleLen), sizeof(MerkleLen));
        OutFile.write(Merkle.c_str(), MerkleLen);
        //
        OutFile.write(reinterpret_cast<const char*>(&WriteNonce), sizeof(WriteNonce));

        const auto& WriteTransactions = Current->GetTransactionList();
        size_t TransCount = WriteTransactions.size();
        OutFile.write(reinterpret_cast<const char*>(&TransCount), sizeof(TransCount));

        for (const auto& Trans : WriteTransactions) {
            int SenderId = Trans->GetSender() ? Trans->GetSender()->GetID() : 0; // 0 для фонда
            int ReceiverId = Trans->GetReceiver() ? Trans->GetReceiver()->GetID() : 0;
            double Amount = Trans->GetAmount();
            time_t TransTs = Trans->GetTimeStamp();

            OutFile.write(reinterpret_cast<const char*>(&SenderId), sizeof(SenderId));
            OutFile.write(reinterpret_cast<const char*>(&ReceiverId), sizeof(ReceiverId));
            OutFile.write(reinterpret_cast<const char*>(&Amount), sizeof(Amount));
            OutFile.write(reinterpret_cast<const char*>(&TransTs), sizeof(TransTs));
        }
        Current = Current->GetNextBlock();
    }

    OutFile.close();
    return true;
}

// Загрузка блокчейна из файла
bool BlockChain::LoadFromFile() {
    std::ifstream InFile(SaveFileName, std::ios::binary);
    if (!InFile) {
        return false;
    }

    ClearChain();
    AllUsers->clear();
    std::map<int, User*> UserMap;
    UserMap[Burse->GetID()] = Burse;

    size_t UserCount;
    InFile.read(reinterpret_cast<char*>(&UserCount), sizeof(UserCount));
    if (InFile.fail()) return false;
    for (size_t i = 0; i < UserCount; ++i) {
        int CurId;
        size_t NameLen;
        InFile.read(reinterpret_cast<char*>(&CurId), sizeof(CurId));
        InFile.read(reinterpret_cast<char*>(&NameLen), sizeof(NameLen));
        if (InFile.fail()) return false;
        std::string CurName(NameLen, '\0');
        InFile.read(&CurName[0], NameLen);
        if (InFile.fail()) return false;

        User* NewUser = new User(CurId, CurName, this);
        AllUsers->push_back(NewUser);
        UserMap[CurId] = NewUser;
    }

    InFile.read(reinterpret_cast<char*>(&CountBlocks), sizeof(CountBlocks));
    if (InFile.fail()) return false;
    for (int i = 0; i < CountBlocks; ++i) {
        int Num;
        time_t Ts;
        size_t HashLen, MerkleLen;
        int ReadHard;

        InFile.read(reinterpret_cast<char*>(&Num), sizeof(Num));
        InFile.read(reinterpret_cast<char*>(&Ts), sizeof(Ts));

        InFile.read(reinterpret_cast<char*>(&HashLen), sizeof(HashLen));
        if (InFile.fail()) return false;
        std::string CurHash(HashLen, '\0');
        InFile.read(&CurHash[0], HashLen);

        InFile.read(reinterpret_cast<char*>(&MerkleLen), sizeof(MerkleLen));
        if (InFile.fail()) return false;
        std::string Merkle(MerkleLen, '\0');
        InFile.read(&Merkle[0], MerkleLen);
        if (InFile.fail()) return false;
        
        //
        InFile.read(reinterpret_cast<char*>(&ReadHard), sizeof(ReadHard));

        std::vector<Transaction*> LoadedTransactions;
        size_t TransCount;
        InFile.read(reinterpret_cast<char*>(&TransCount), sizeof(TransCount));
        if (InFile.fail()) return false;
        for (size_t j = 0; j < TransCount; ++j) {
            int SenderId, ReceiverId;
            double Amount;
            time_t TransTs;

            InFile.read(reinterpret_cast<char*>(&SenderId), sizeof(SenderId));
            InFile.read(reinterpret_cast<char*>(&ReceiverId), sizeof(ReceiverId));
            InFile.read(reinterpret_cast<char*>(&Amount), sizeof(Amount));
            InFile.read(reinterpret_cast<char*>(&TransTs), sizeof(TransTs));
            if (InFile.fail()) return false;

            User* CurSender = UserMap[SenderId];
            User* CurReceiver = UserMap[ReceiverId];

            LoadedTransactions.push_back(new Transaction(CurSender, CurReceiver, Amount, TransTs));
        }

        Block* NewBlock = new Block(Num, Ts, CurHash, Merkle, LastBlock, LoadedTransactions);

        if (!GenesisBlock) {
            GenesisBlock = NewBlock;
        }
        if (LastBlock) {
            LastBlock->SetNextBlock(NewBlock);
        }
        LastBlock = NewBlock;
    }

    InFile.close();
    std::cout << "Blockchain state loaded from " << SaveFileName << std::endl;
    return true;
}