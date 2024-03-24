
#ifndef G03_1_MENU_H
#define G03_1_MENU_H

#include "Dataset.h"
#include <limits>
#include

class Menu {
    void run();
    void clearScreen();
    void mainMenu(Dataset &objDataset);
    void maxFlowMenu(Dataset &objDataset);
    void isWaterSufficient(Dataset& objDataset);
    void wait(Dataset &objDataset);
    void isWaterSufficientMenu(Dataset &objDataset);
};


#endif //G03_1_MENU_H
