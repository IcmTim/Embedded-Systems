#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    vector<double> temps = {5.5, 12.3, 18.0, 22.5, 9.8, 25.6, 15.2};

    tuple<string, double> warmestDay = make_tuple(days[0], temps[0]);

    for (size_t i = 0; i < days.size(); i++) {
        cout << days[i] << ": " << temps[i] << "°C - ";

        if (temps[i] < 10)
            cout << "Cold";
        else if (temps[i] <= 20)
            cout << "Ok";
        else
            cout << "Warm";

        cout << endl;

        if (temps[i] > get<1>(warmestDay)) {
            warmestDay = make_tuple(days[i], temps[i]);
        }
    }

    cout << "\nWarmest Day: " << get<0>(warmestDay) 
         << " with " << get<1>(warmestDay) << "°C" << endl;

    return 0;
}
