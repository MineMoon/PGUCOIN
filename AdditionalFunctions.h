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


std::string GenerationName(std::vector<std::string> FirstNames, std::vector<std::string> SecondNames) {
    
    int Start = 0;
    int FistEnd = FirstNames.size()-1;
    int SecondEnd = SecondNames.size()-1;

    int FisrtNameInd = rand() % (FistEnd - Start + 1) + Start;
    int SecondNameInd = rand() % (SecondEnd - Start + 1) + Start;

    return FirstNames[FisrtNameInd] + " " + SecondNames[SecondNameInd];
}

bool CheckUserName(std::vector<User*> Users, std::string Name) {
    for (int i = 0; i < Users.size(); i++){
        if (Users[i]->GetName() == Name)
            return false;
    }
    return true;
}