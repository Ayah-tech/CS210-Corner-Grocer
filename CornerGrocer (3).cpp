// Corner Grocer Item Tracking Program
// CS 210 Project Three
// Reads purchase records, counts items, and saves a backup file.
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>
using namespace std;

class GroceryTracker {
private:
    map<string, int> itemCounts;

public:
    bool LoadItems(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error: Could not open " << filename << endl;
            return false;
        }
        string item;
        while (inputFile >> item) {
            ++itemCounts[item];
        }
        return true;
    }

    bool SaveBackup(const string& filename) const {
        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cerr << "Error: Could not create " << filename << endl;
            return false;
        }
        for (const auto& entry : itemCounts) {
            outputFile << entry.first << ' ' << entry.second << '\n';
        }
        return true;
    }

    int GetFrequency(const string& item) const {
        auto found = itemCounts.find(item);
        return found == itemCounts.end() ? 0 : found->second;
    }

    void PrintFrequencies() const {
        for (const auto& entry : itemCounts) {
            cout << entry.first << ' ' << entry.second << '\n';
        }
    }

    void PrintHistogram() const {
        for (const auto& entry : itemCounts) {
            cout << entry.first << ' ' << string(entry.second, '*') << '\n';
        }
    }
};

int main() {
    GroceryTracker tracker;
    const string inputFilename = "CS210_Project_Three_Input_File.txt";
    if (!tracker.LoadItems(inputFilename)) {
        cout << "Place the input file in the program's working directory and try again.\n";
        return 1;
    }
    // Create the required backup automatically before showing the menu.
    if (!tracker.SaveBackup("frequency.dat")) {
        return 1;
    }

    int choice = 0;
    while (choice != 4) {
        cout << "\nCORNER GROCER ITEM TRACKER\n"
             << "1. Search for an item\n"
             << "2. Display all item frequencies\n"
             << "3. Display histogram\n"
             << "4. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            continue;
        }
        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item name (case-sensitive): ";
            cin >> item;
            cout << item << " purchased " << tracker.GetFrequency(item) << " time(s).\n";
            break;
        }
        case 2:
            tracker.PrintFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Please select an option from 1 to 4.\n";
        }
    }
    return 0;
}
