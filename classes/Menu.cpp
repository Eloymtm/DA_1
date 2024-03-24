//
// Created by eloy_mm2004 on 23-03-2024.
//

#include "Menu.h"
using namespace std;



void Menu::run(){
    Dataset objDataset = Dataset();

}
void Menu::clearScreen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
void Menu::mainMenu(Dataset &objDataset) {

    int choice;

    clearScreen(); // Limpa a tela antes de exibir o menu
    cout << "\033[1;32m"; // Define a cor verde brilhante para o texto
    cout << "==============================" << endl;
    cout << "|       ** Main Menu **      |" << endl;
    cout << "==============================" << endl;
    cout << "|   1. MaxFlow               |" << endl;
    cout << "|   2. IsWaterSufficient     |" << endl;
    cout << "|   3. Opção 3               |" << endl;
    cout << "|   4. Sair                  |" << endl;
    cout << "==============================" << endl;
    cout << "\033[0m"; // Resetar a cor do texto

    cout << "Choose one option: \n";
    cin >> choice;

    switch (choice) {
        case 1: {
            maxFlowMenu(objDataset);
            break;
        }
        case 2:{
            isWaterSufficientMenu(objDataset);
            break;
        }
    }
}

void Menu::maxFlowMenu(Dataset &objDataset) {

    int choice;

    clearScreen(); // Limpa a tela antes de exibir o menu
    cout << "\033[1;32m"; // Define a cor verde brilhante para o texto
    cout << "==================================" << endl;
    cout << "|     ** Max Flow Menu **         |" << endl;
    cout << "==================================" << endl;
    cout << "|   1. To a Target                |" << endl;
    cout << "|   2. From a source to a target  |" << endl;
    cout << "|   3. Best Max Flow              |" << endl;
    cout << "|   4. Sair                       |" << endl;
    cout << "==================================" << endl;
    cout << "\033[0m"; // Resetar a cor do texto


    switch (choice) {
        case 1:{

            break;
        }
    }
}

void Menu::isWaterSufficient(Dataset &objDataset) {
    clearScreen();
    bool res = objDataset.waterNeeds();
    clearScreen(); //testar de da clear rapido o suficiente

    switch (res) {
        case true: {
            cout << "\033[1;32m";
            cout << "==================================" << endl;
            cout << "|     **  Is water enough? **     |" << endl;
            cout << "==================================" << endl;
            cout << "|    At the moment our network    |" << endl;
            cout << "|    is capable of fulfilling     |" << endl;
            cout << "|    every city's water needs!    |" << endl;
            cout << "|                                 |" << endl;
            cout << "==================================" << endl;
            cout << "\033[0m";
            break;
        }
        case false:{
            cout << "\033[1;32m";
            cout << "==================================" << endl;
            cout << "|     **  Is water enough? **     |" << endl;
            cout << "==================================" << endl;
            cout << "|    At the moment our network    |" << endl;
            cout << "|   isn't capable of fulfilling   |" << endl;
            cout << "|    every city's water needs!    |" << endl;
            cout << "|                                 |" << endl;
            cout << "|    The cities we can't give     |" << endl;
            cout << "|   the desired flow right now:   |" << endl;

            objDataset.waterNeeds();

            cout << "==================================" << endl;
            cout << "\033[0m";
            break;
        }

    }

    clearScreen();
}


void Menu::wait(Dataset &objDataset) {
    string o;
    cout << "Press ENTER to continue...";
    cin.get(); // Aguarda a entrada de uma tecla
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    mainMenu(objDataset);
}