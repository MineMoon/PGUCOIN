#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"
#include "sha256.h"

class Block {
private:
    int Number;
    std::string Hash;
    std::string HashMerkle;
    Block* PrevBlock;
    Block* NextBlock;
    time_t TimeStamp;
    std::vector<Transaction*> TransactionList;
    int Nonce;

public:
    // Конструктор для создания нового блока
    Block(int Number, Block* PrevBlock, const std::vector<Transaction*>& Transactions);
    // Новый конструктор для загрузки блока из файла
    Block(int Number, time_t Timestamp, std::string Hash, std::string HashMerkle, Block* PrevBlock, const std::vector<Transaction*>& Transactions);

    // Геттеры
    std::string GetHash() const { return Hash; }
    int GetNumber() const { return Number; }
    Block* GetPrevBlock() const { return PrevBlock; }
    Block* GetNextBlock() const { return NextBlock; }
    time_t GetTimeStamp() const { return TimeStamp; }
    const std::vector<Transaction*>& GetTransactionList() const { return TransactionList; }
    std::string GetHashMerkle() const { return HashMerkle; }
    int GetNonce() const { return Nonce; }

    // Сеттер
    void SetNextBlock(Block* NewNextBlock) { NextBlock = NewNextBlock; }

    // Методы
    std::string CalculateHash();
    static std::string CalculateMerkleRoot(const std::vector<Transaction*>& Transactions);
    std::string ToString() const;
    void RiseNonce() { Nonce++; }

    // Деструктор
    ~Block();
};

#endif // BLOCK_H