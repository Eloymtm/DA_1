//
// Created by eloy_mm2004 on 05-03-2024.
//

#ifndef PROJ_1_PARSER_H
#define PROJ_1_PARSER_H

#include <string>
#include <list>
#include <vector>
#include <fstream>

using namespace std;
/**
 * The parser class is responsible for reading the given CSV files and creating the corresponding objects.
 */
class Parser {
public:
    static list<std::vector<std::string>> readFile(const std::string &file);
    static vector<std::string> splitLine(std::string line,const std::string& delimiter);
};

#endif //PROJ_1_PARSER_H
