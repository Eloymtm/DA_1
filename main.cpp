#include "classes/Parser.h"
#include "classes/Dataset.h"
#include "vector"

using namespace std;


int main() {
    Parser parser;
    list<vector<string>> rawReservoirs = parser.readFile("../dataset/ds/Reservoir.csv");
    list<vector<string>> rawStations = parser.readFile("../dataset/ds/Stations.csv");
    list<vector<string>> rawCities = parser.readFile("../dataset/ds/Cities.csv");
    list<vector<string>> rawPipes = parser.readFile("../dataset/ds/Pipes.csv");

    Dataset dataset = Dataset(rawReservoirs, rawStations, rawCities, rawPipes);

    return 0;
}