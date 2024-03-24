
#ifndef G03_1_MENU_H
#define G03_1_MENU_H

#include "Dataset.h"
#include "Parser.h"
#include <limits>

class Menu {
public:
    Menu();
    void run();
    void clearScreen();
    void mainMenu(Dataset &objDataset);
    void maxFlowMenu(Dataset &objDataset);
    void wait(Dataset &objDataset);
    void isWaterSufficientMenu(Dataset &objDataset);
    void betterMetricsMenu(Dataset &objDataset);
    void reliabilityMenu(Dataset &objDataset);
};


#endif //G03_1_MENU_H
