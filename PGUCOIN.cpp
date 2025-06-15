#include <iostream>
#include<iomanip>
#include<ctime>
#include"sha256.h"
#include"BlockChain.h"
#include"AdditionalFunctions.h"

std::vector<std::string> FirstNames = ReadNames("FirstNames.txt");
std::vector<std::string> SecondNames = ReadNames("SecondNames.txt");

int main(){
    srand(time(nullptr));

    BlockChain* PGUCOIN = new BlockChain;
    Pool* PguCoinPool = new Pool;
    PGUCOIN->SetPool(PguCoinPool);
    
    int CountOfUsers = 3;

    std::vector<User*> Users;
    User Burse;
    Burse.SetID(0);
    Burse.SetBlockChain(PGUCOIN);
    Burse.SetName("Burse");


    for (int i = 0; i < CountOfUsers; i++){
        std::string Name = GenerationName(FirstNames, SecondNames);
        while(!CheckUserName(Users,Name))
            std::string Name = GenerationName(FirstNames, SecondNames);
        User* PUser = new User;
        PUser->SetID(i+1);
        PUser->SetName(Name);
        PUser->SetBlockChain(PGUCOIN);
        Users.push_back(PUser);
    }
    
    int RandomUser;
    int Choice;
    int Value;

    int countras = 0;


    while (countras!=3) {
        countras++;
        int Start = 0;
        int End = Users.size()-1;

        RandomUser = rand() % (End - Start + 1) + Start;
        Start = 0;
        End = 2;
        Choice = rand() % (End - Start + 1) + Start;
        std::cout << countras << ": ";
        switch (Choice){
        case Action::DEPOSIT:
            Start = 1;
            End = 1000;
            Value = rand() % (End - Start + 1) + Start;

            Users[RandomUser]->MakeTransaction(Users[RandomUser], Value, DEPOSIT);
            
            std::cout << "Account: " << Users[RandomUser]->GetName() << std::endl;
            std::cout << "  Operation: Deposit\n";
            std::cout << "  Value: " << Value << std::endl;
            std::cout << "  Balance: " << Users[RandomUser]->GetBalance() << std::endl;

            break;
        case Action::WITHDRAW:
            Start = 1;
            End = 1000;
            Value = rand() % (End - Start + 1) + Start;
            std::cout << "Account: " << Users[RandomUser]->GetName() << std::endl;
            Users[RandomUser]->MakeTransaction(Users[RandomUser], Value, WITHDRAW);
            std::cout << "  Operation: Withdraw\n";
            std::cout << "  Value: " << Value << std::endl;
            std::cout << "  Balance: " << Users[RandomUser]->GetBalance() << std::endl;
            break;
        case Action::TRANSFER:
            int Start = 0;
            int End = Users.size() - 1;
            int RandomUser2 = rand() % (End - Start + 1) + Start;
            Start = 1;
            End = 1000;
            Value = rand() % (End - Start + 1) + Start;
            Users[RandomUser]->MakeTransaction(Users[RandomUser2], Value, TRANSFER);
             

            std::cout << "Account: " << Users[RandomUser]->GetName() << std::endl;
            std::cout << "  Operation: Transfer\n";
            std::cout << "  Value: " << Value << std::endl;
            std::cout << "  Receiver: " << Users[RandomUser2]->GetName() << std::endl;

            break;
        }
        
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "POOL:\n";
    /*PguCoinPool->Print();*/


    delete PGUCOIN;
    for (int i = 0; i < Users.size(); i++){
        delete Users[i];
    }

}