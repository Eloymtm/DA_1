//
// Created by eloy_mm2004 on 23-03-2024.
//

#include "Menu.h"
using namespace std;

bool isBalanced = false;

Menu::Menu(){}


void Menu::run(){
    Parser parser;
    list<vector<string>> rawReservoirs = parser.readFile("../dataset/ds/Reservoir.csv");
    list<vector<string>> rawStations = parser.readFile("../dataset/ds/Stations.csv");
    list<vector<string>> rawCities = parser.readFile("../dataset/ds/Cities.csv");
    list<vector<string>> rawPipes = parser.readFile("../dataset/ds/Pipes.csv");
    Dataset objDataset = Dataset(rawReservoirs, rawStations, rawCities, rawPipes);
    mainMenu(objDataset);

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
    cout << "|   3. Metrics               |" << endl;
    cout << "|   4. Reliability           |" << endl;
    cout << "|   5. Exit                  |" << endl;
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
            //isWaterSufficientMenu(objDataset);
            break;
        }
        case 3:{
            betterMetricsMenu(objDataset);
            break;
        }
        case 4:{
            reliabilityMenu(objDataset);
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

    cout << "Choose one option: \n";
    cin >> choice;

    switch (choice) {
        case 1:{
            string cidade;
            cout << "Introduza destino final: ";
            cin >> cidade;
            objDataset.edmondsKarp(objDataset.getNetwork(),"SuperSource", cidade);
            break;
        }
        case 2:{
            string cidadeinit;
            string cidadefinal;
            cout << "introduza cidade inicial: ";
            cin >> cidadeinit;
            cout << "Introduza cidade final: ";
            cin >> cidadefinal;
            objDataset.edmondsKarp(objDataset.getNetwork(),cidadeinit, cidadefinal);
            break;
        }
    }


}
void Menu::betterMetricsMenu(Dataset &objDataset) {
    int choice;

    if(isBalanced) {
        clearScreen(); // Limpa a tela antes de exibir o menu
        cout << "\033[1;32m"; // Define a cor verde brilhante para o texto
        cout << "==================================" << endl;
        cout << "|         ** Metrics **           |" << endl;
        cout << "==================================" << endl;
        cout << "|    Old Metrics                  |" << endl;
        cout << "|    Old Metrics                  |" << endl;
        cout << "|    Old Metrics                  |" << endl;
        cout << "|    New Metrics                  |" << endl;
        cout << "|    New Metrics                  |" << endl;
        cout << "|    New Metrics                  |" << endl;
        cout << "|   q. Sair                       |" << endl;
        cout << "==================================" << endl;
        cout << "\033[0m"; // Resetar a cor do texto

        cout << "Choose one option: \n";
        cin >> choice;
    }
    else{
        clearScreen(); // Limpa a tela antes de exibir o menu
        cout << "\033[1;32m"; // Define a cor verde brilhante para o texto
        cout << "==================================" << endl;
        cout << "|       ** Metrics Menu **        |" << endl;
        cout << "==================================" << endl;
        cout << "|   1. Balance                    |" << endl;
        cout << "|   2. Current Metrics            |" << endl;
        cout << "|   3. Sair                       |" << endl;
        cout << "==================================" << endl;
        cout << "\033[0m"; // Resetar a cor do texto

        isBalanced = true;
        cout << "Choose one option: \n";
        cin >> choice;

        switch (choice) {
            case 1:{
                //Função better metrics
                break;
            }
            case 2:{
                //Metrics
                break;
            }

        }
    }
}


void Menu::reliabilityMenu(Dataset &objDataset) {

    int choice;

    clearScreen(); // Limpa a tela antes de exibir o menu
    cout << "\033[1;32m"; // Define a cor verde brilhante para o texto
    cout << "==================================" << endl;
    cout << "|      ** Reliability Menu **     |" << endl;
    cout << "==================================" << endl;
    cout << "|   1. Reservoir                  |" << endl;
    cout << "|   2. Pumping Station            |" << endl;
    cout << "|   3. Pipeline                   |" << endl;
    cout << "|   4. Sair                       |" << endl;
    cout << "==================================" << endl;
    cout << "\033[0m"; // Resetar a cor do texto

    cout << "Choose one option: \n";
    cin >> choice;

    switch (choice) {
        case 1:{
            string reservoir;
            cout << "Reservoir: ";
            cin >> reservoir;
            objDataset.removeR_Or_PS_Effects(objDataset.getNetwork(),reservoir);
            break;
        }
        case 2:{
            string PumpingStation;
            cout << "Pumping Station: ";
            cin >> PumpingStation;
            objDataset.removeR_Or_PS_Effects(objDataset.getNetwork(),PumpingStation);
            break;
        }
        case 3:{
            string pipelineOrig;
            string pipelineDest;
            cout << "Pipeline Origin: ";
            cin >> pipelineOrig;
            cout << "Pipeline Destiny: ";
            cin >> pipelineDest;
            objDataset.removePipeline_Effects(objDataset.getNetwork(),pipelineOrig, pipelineDest);
        }
    }
}
void Menu::wait(Dataset &objDataset) {
    string o;
    cout << "Press ENTER to continue...";
    cin.get(); // Aguarda a entrada de uma tecla
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    mainMenu(objDataset);
}