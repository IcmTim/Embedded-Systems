#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
T average(T* arr, int n) {
    if (n == 0) throw runtime_error("Division by zero: no readings available.");
    T sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

class WeatherStation {
private:
    string location;
    float* readings;
    int size;
    int capacity;

public:
    WeatherStation(string loc, int initialCap = 5)
        : location(loc), size(0), capacity(initialCap) {
        readings = new float[capacity];
    }

    ~WeatherStation() {
        delete[] readings;
    }

    void addReading(float value) {
        if (size == capacity) {
            capacity *= 2; 
            float* newReadings = new float[capacity];
            for (int i = 0; i < size; i++) newReadings[i] = readings[i];
            delete[] readings;
            readings = newReadings;
        }
        readings[size++] = value;
    }

    void printReadings() const {
        cout << "Location: " << location << endl;
        cout << "Readings: ";
        for (int i = 0; i < size; i++) {
            cout << readings[i] << " ";
        }
        cout << endl;
    }

    void saveToFile(string filename) {
        ofstream out(filename);
        if (!out) {
            throw runtime_error("Error opening file for writing.");
        }
        out << location << endl;
        for (int i = 0; i < size; i++) {
            out << readings[i] << " ";
        }
        out << endl;
        out.close();
        cout << "Saved to file: " << filename << endl;
    }

    static WeatherStation loadFromFile(string filename, string loc) {
        ifstream in(filename);
        if (!in) {
            throw runtime_error("Error opening file for reading.");
        }
        WeatherStation ws(loc);
        string dummy;
        getline(in, dummy);
        float val;
        while (in >> val) {
            ws.addReading(val);
        }
        in.close();
        return ws;
    }

    void analyze(float threshold = 25.0f) {
        sort(readings, readings + size);
        try {
            float avg = average(readings, size);
            cout << "Average: " << avg << endl;
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        int countAbove = count_if(readings, readings + size,
                                  [threshold](float v) { return v > threshold; });
        cout << "Readings above " << threshold << "°C: " << countAbove << endl;
    }
};

int main() {
    try {
        WeatherStation ws("Lahti");
        ws.addReading(22.5f);
        ws.addReading(24.0f);
        ws.addReading(26.3f);
        ws.addReading(21.8f);
        ws.addReading(25.7f);

        ws.printReadings();
        ws.analyze();

        ws.saveToFile("lahti_readings.txt");

        cout << "\nReconstructing from file..." << endl;
        WeatherStation ws2 = WeatherStation::loadFromFile("lahti_readings.txt", "Lahti");
        ws2.printReadings();
        ws2.analyze();

    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
