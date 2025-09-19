#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

int main() {
    string name = "Tima";
    vector<int> scores = {85, 90, 95};
    map<string, int> ageMap;
    ageMap["Ksy"] = 18;
    ageMap["Rolands"] = 20;

    tuple<string, int, bool> person = {"Makar", 18, true};

    cout << "Name: " << name << endl;
    cout << "First score: " << scores[0] << endl;
    cout << "Ksy's age: " << ageMap["Ksy"] << endl;
    cout << "Tuple name: " << get<0>(person) <<endl;

    return 0;
}