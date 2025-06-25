#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Block.h"
#include "Pool.h"
#include "User.h"

class BlockChain {
private:
    Block* GenesisBlock;
    Block* LastBlock;
    Pool* TransactionsPool;
    User* Burse;
    int CurrentHardMining;

    std::string Name;
    std::string SaveFileName;
    int CountBlocks;
    std::vector<User*>* AllUsers;

    void ClearChain();
    bool IsTransactionValid(Transaction* trans) const;
    bool SaveToFile() const;

    bool CheckSolution(std::string Solution) {
        for (int i = 0; i < CurrentHardMining; i++) {
            if (Solution[i] != '0') return false;
        }
        return true;
    }

public:
    // Конструктор принимает имя файла и указатель на вектор пользователей
    BlockChain(const std::string& Name, const std::string& SaveFileName, std::vector<User*>* Users);
    ~BlockChain();

    // Геттеры
    Pool* GetPool() const { return TransactionsPool; }
    Block* GetGenesisBlock() const { return GenesisBlock; }
    Block* GetLastBlock() const { return LastBlock; }
    User* GetBurse() const { return Burse; }
    int GetCountBlocks() const { return CountBlocks; }

    // Сеттеры
    void SetBurse(User* SetBurse) { Burse = SetBurse; }
    void SetHardMining(int NewHard) { CurrentHardMining = NewHard; }
    
    //Методы
    void CreateGenesisBlock(const std::vector<Transaction*>& InitialTransactions = {});
    bool MineBlock(int MaxTransactions = 10);
    double GetUserBalance(const User* CurUser) const;
    void PrintChain() const;

    // Метод загрузки
    bool LoadFromFile();
};

#endif