#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"BlockChain.h"
#include"User.h"

std::vector<std::string> ReadNames(const std::string& FileName) {

    std::ifstream File(FileName);

    if (!File.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл: " << FileName << std::endl;
        return {};
    }

    std::vector<std::string> names;
    std::string Input;
    while (File >> Input) {
        names.push_back(Input);
    }

    File.close();
    return names;
}


std::vector<User> CreateUsers(std::string& FileFirstName, std::string& FileSecondName, int Count, PBlockChain BC) {

}