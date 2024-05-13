#include "Filereader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono> // For measuring execution time

using namespace std;

// Function to measure execution time of a specific operation and print it
void a_print_execution_time(const string& operation_name, std::chrono::nanoseconds duration) {
    cout << "Operation '" << operation_name << "' took " << duration.count() << " nanoseconds" << endl;
}

void readandInsert(LinkedList& list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Assuming the txt fields are in the order: ID, FName, LName, DOB, Street, City, State, Zip
        if (fields.size() == 8) {
            try {
                int id = std::stoi(fields[0]);
                string fName = fields[1];
                string lName = fields[2];
                string dob = fields[3];
                string street = fields[4];
                string city = fields[5];
                string state = fields[6];
                string zip = fields[7];

                // Insert the record into the linked list
                list.Insert_Record(id, fName, lName, dob, street, city, state, zip);
            }
            catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid argument: " << e.what() << endl;
                // Handle the error gracefully (e.g., skip the invalid record)
            }
        }
        else {
            cerr << "Warning: Invalid record found in Students.txt file" << endl;
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    a_print_execution_time("readandInsert", duration);

    cout << "Data Read From Students.txt \n";
    file.close();
}
