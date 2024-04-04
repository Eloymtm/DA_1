//
// Created by eloy_mm2004 on 23-03-2024.
//

#include "Menu.h"
using namespace std;

bool isBalanced = false;

Menu::Menu(){}

void Menu::run(){
    Parser parser;
    list<vector<string>> rawReservoirs = parser.readFile("../dataset/small_ds/Reservoirs_Madeira.csv");
    list<vector<string>> rawStations = parser.readFile("../dataset/small_ds/Stations_Madeira.csv");
    list<vector<string>> rawCities = parser.readFile("../dataset/small_ds/Cities_Madeira.csv");
    list<vector<string>> rawPipes = parser.readFile("../dataset/small_ds/Pipes_Madeira.csv");
    Dataset objDataset = Dataset(rawReservoirs, rawStations, rawCities, rawPipes);
    mainMenu(objDataset);

}

/**
 * Displays the main menu
 */
void Menu::mainMenu(Dataset &objDataset) {
    string choice;

    do{
        cout << "==============================" << endl;
        cout << "|       ** Main Menu **      |" << endl;
        cout << "==============================" << endl;
        cout << "|   1. MaxFlow               |" << endl;
        cout << "|   2. IsWaterSufficient     |" << endl;
        cout << "|   3. Metrics               |" << endl;
        cout << "|   4. Reliability           |" << endl;
        cout << "|   5. Exit                  |" << endl;
        cout << "==============================" << endl;

        cout << "Choose one option: \n";
        cin >> choice;

        while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> choice;
        }

        switch (stoi(choice)) {
            case 1: {
                maxFlowMenu(objDataset);
                break;
            }
            case 2:{
                isWaterSufficientMenu(objDataset);
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
            case 5: {
                exit(0);
            }
        }
    }while(choice != "5");
}

/**
 * Displays the max flow menu and its functions
 */
void Menu::maxFlowMenu(Dataset &objDataset) {
    string choice;

    do{
        cout << "==================================" << endl;
        cout << "|     ** Max Flow Menu **        |" << endl;
        cout << "==================================" << endl;
        cout << "|   1. To a City                 |" << endl;
        cout << "|   2. To each City              |" << endl;
        cout << "|   3. Best Max Flow             |" << endl;
        cout << "|   4. Sair                      |" << endl;
        cout << "==================================" << endl;

        cout << "Choose one option: \n";
        cin >> choice;
        while(choice != "1" && choice != "2" && choice != "3" && choice != "4"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> choice;
        }

        switch (stoi(choice)) {
            case 1:{
                string cidade;
                while(true){
                    cout << "Introduza destino final: \n(id = C_(1-22))\n";
                    cin >> cidade;
                    if(cidade.substr(0, 2) == "C_"){
                        break;
                    }
                    else{
                        cout << "You entered the City ID incorrectly, try again\n"<< endl;
                    }
                }
                auto it = objDataset.cityMaxFlowOriginalGraph.find(cidade);
                if(it == objDataset.cityMaxFlowOriginalGraph.end()){
                    cout << "City's ID doesn't exist!\n";
                    break;
                }
                cout << it->first << " --> " << it->second << "\n";

                break;
            }
            case 2:{
                auto it = objDataset.cityMaxFlowOriginalGraph.begin();
                while(it != objDataset.cityMaxFlowOriginalGraph.end()){
                    cout << it->first << " --> " << it->second << "\n";
                    it++;
                }

                break;
            }
            case 3:
                cout << "Max flow --> " << objDataset.maxFlow() << "\n";
                break;
            case 4:
                break;
        }
    }while(choice != "4");

    mainMenu(objDataset);
}

/**
 * Displays the metrics menu and its functions
 */
void Menu::betterMetricsMenu(Dataset &objDataset) {
    string choice;

    do{
        cout << "===================================" << endl;
        cout << "|        ** Metrics Menu **       |" << endl;
        cout << "===================================" << endl;
        cout << "|  1. Old Metrics                 |" << endl;
        cout << "|  2. New Metrics after balancing |" << endl;
        cout << "|  3. Sair                        |" << endl;
        cout << "===================================" << endl;

        cout << "Choose one option: \n";
        cin >> choice;
        while(choice != "1" && choice != "2" && choice != "3"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> choice;
        }

        switch (stoi(choice)) {
            case 1: {
                Metrics oldMetrics = objDataset.getMetrics(objDataset.getNetwork());
                cout << "Actual average = " << oldMetrics.average << " Actual maximum difference = "
                     << oldMetrics.max_difference << " Actual variance = " << oldMetrics.variance << "\n";
                break;
            }
            case 2: {
                objDataset.balanceNetwork(objDataset.getNetwork());
                cout << "\n";
                break;
            }
            case 3: {
                break;
            }
        }
    }while(choice != "3");

    mainMenu(objDataset);
}

/**
 * Displays the reliability menu and its functions
 */
void Menu::reliabilityMenu(Dataset &objDataset) {

    string choice;

    do{
        cout << "==================================" << endl;
        cout << "|      ** Reliability Menu **     |" << endl;
        cout << "==================================" << endl;
        cout << "|   1. Reservoir                  |" << endl;
        cout << "|   2. Pumping Station            |" << endl;
        cout << "|   3. Pipeline                   |" << endl;
        cout << "|   4. Sair                       |" << endl;
        cout << "==================================" << endl;

        cout << "Choose one option: \n";
        cin >> choice;

        while(choice != "1" && choice != "2" && choice != "3" && choice != "4"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> choice;
        }

        switch (stoi(choice)) {
            case 1:{
                string reservoir;
                while(true){
                    cout << "Reservoir: \n(id = R_(1-24))\n";
                    cin >> reservoir;
                    if(reservoir.substr(0, 2) == "R_"){
                        break;
                    }
                    else{
                        cout << "Introduziu mal o ID da Cidade tente novamente\n"<< endl;
                    }
                }

                objDataset.removeR_Or_PS_Effects(objDataset.getNetwork(),reservoir);
                break;
            }
            case 2:{
                string PumpingStation;

                while(true){
                    cout << "Pumping Station: \n(id = PS_(1-81))\n";
                    cin >> PumpingStation;
                    if(PumpingStation.substr(0,3) == "PS_"){
                        break;
                    }
                    else{
                        cout << "Introduziu mal o ID da Cidade tente novamente\n"<< endl;
                    }
                }

                objDataset.removeR_Or_PS_Effects(objDataset.getNetwork(),PumpingStation);
                break;
            }
            case 3:{
                Graph<string> g = objDataset.getNetwork();
                string pipelineOrig;
                string pipelineDest;
                string keepON;
                
                while(true){
                    cout << "Pipeline Origin:";
                    cin >> pipelineOrig;
                    cout << "Pipeline Destiny: ";
                    cin >> pipelineDest;

                    objDataset.removePipelines_auxiliar(g,pipelineOrig,pipelineDest);

                    cout << "\nDo you want to remove one more pipeline?[Y/N]";
                    cin >> keepON;
                    cout << "\n";
                    if(keepON == "N"){
                        break;
                    }
                    else{
                        continue;
                    }
                }

                objDataset.removePipeline_Effects(g);
                break;
            }
            case 4: {
                break;
            }
        }
    }while(choice != "4");

    mainMenu(objDataset);
}

/**
 * Displays the is Water Sufficient menu and its functions
 */
void Menu::isWaterSufficientMenu(Dataset &objDataset) {
    string choice;

    do{
        cout << "==================================" << endl;
        cout << "|      ** Water sufficient **     |" << endl;
        cout << "==================================" << endl;
        cout << "|   1. Is Water sufficient?       |" << endl;
        cout << "|   2. Sair                       |" << endl;
        cout << "==================================" << endl;

        cout << "Choose one option: \n";
        cin >> choice;

        while(choice != "1" && choice != "2"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> choice;
        }

        switch (stoi(choice)) {
            case 1:{
                if(objDataset.waterNeeds(objDataset.getNetwork(), objDataset.rawCities)){
                    cout << "All the water reservoirs supply enough water to all its delivery sites!!\n";
                }
                else{
                    cout << "There isn't enough water to all its delivery sites!!\n";
                }
                break;
            }
            case 2: {
                break;
            }
        }
    }while(choice != "2");

    mainMenu(objDataset);
}
