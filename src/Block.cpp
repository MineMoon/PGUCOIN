#include "../include/Block.h"
#include <sstream>
#include <algorithm>

// Основной конструктор
Block::Block(int Number, Block* PrevBlock, const std::vector<Transaction*>& Transactions)
    : Number(Number), PrevBlock(PrevBlock), NextBlock(nullptr), TransactionList(Transactions) {
    TimeStamp = time(nullptr);
    HashMerkle = CalculateMerkleRoot(TransactionList);
    Nonce = 1;
    Hash = CalculateHash();
}

// Конструктор по умолчанию (для загрузки)
Block::Block(int Number, time_t Timestamp, std::string Hash, std::string HashMerkle,  Block* PrevBlock, const std::vector<Transaction*>& Transactions)
    : Number(Number), TimeStamp(Timestamp), Hash(Hash), HashMerkle(HashMerkle), Nonce(0), PrevBlock(PrevBlock), NextBlock(nullptr), TransactionList(Transactions) {
    // Здесь мы не вычисляем хеш, а присваиваем тот, что был сохранен
}


std::string Block::CalculateHash() {
    return sha256(ToString());
}

std::string Block::CalculateMerkleRoot(const std::vector<Transaction*>& Transactions) {
    if (Transactions.empty()) {
        return sha256("");
    }

    std::vector<std::string> Hashes;
    for (const auto& Trans : Transactions) {
        Hashes.push_back(sha256(Trans->ToString()));
    }

    while (Hashes.size() > 1) {
        if (Hashes.size() % 2 != 0) {
            Hashes.push_back(Hashes.back());
        }
        std::vector<std::string> NewHashes;
        for (size_t i = 0; i < Hashes.size(); i += 2) {
            NewHashes.push_back(sha256(Hashes[i] + Hashes[i+1]));
        }
        Hashes = NewHashes;
    }
    return Hashes[0];
}

std::string Block::ToString() const {
    std::stringstream ss;
    ss << Number
       << (PrevBlock ? PrevBlock->GetHash() : "0")
       << TimeStamp
       << HashMerkle
       << Nonce;
    return ss.str();
}

Block::~Block() {
    for (Transaction* trans : TransactionList) {
        delete trans;
    }
    TransactionList.clear();
}