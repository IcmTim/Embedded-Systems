#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, double> weather = {
        {"Monday", 5.5},
        {"Tuesday", 12.3},
        {"Wednesday", 18.0},
        {"Thursday", 22.5},
        {"Friday", 9.8},
        {"Saturday", 25.6},
        {"Sunday", 15.2}
    };

    map<string, char> conditions = {
        {"Monday", 'R'},
        {"Tuesday", 'C'}, 
        {"Wednesday", 'S'},
        {"Thursday", 'S'},
        {"Friday", 'R'},
        {"Saturday", 'S'},
        {"Sunday", 'C'}
    };

    double total = 0;
    double warmestTemp = -1000;
    string warmestDay;

    for (auto &entry : weather) {
        cout << entry.first << ": " << entry.second << "°C"
             << " (" << conditions[entry.first] << ")" << endl;

        total += entry.second;

        if (entry.second > warmestTemp) {
            warmestTemp = entry.second;
            warmestDay = entry.first;
        }
    }

    double average = total / weather.size();

    cout << "\nAverage Temperature: " << average << "°C" << endl;
    cout << "Warmest Day: " << warmestDay << " with " << warmestTemp << "°C" << endl;

    return 0;
}
