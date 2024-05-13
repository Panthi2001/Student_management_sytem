// Standard C++ libraries
#include <iostream>   // For input and output operations
#include <string>     // For string manipulation
#include <fstream>    // For file input and output operations
#include <sstream>    // For string stream processing
#include <chrono>     // For time-related functions

//including all the necessary headers 
#include "housekeeping.h"
#include "LinkedList.h"
#include "Filereader.h"

using namespace std;

// Function to measure execution time of a specific operation and print it
void print_execution_time(const string& operation_name,  chrono::nanoseconds duration) {
    cout << "Operation '" << operation_name << "' took " << duration.count() << " nanoseconds" << endl;
}

int main()
{
    int choice;
    LinkedList studentList;
    int iD;
    string fName, lName, dBirth, addrStreet, addrCity, addrState, zip;
    string filename = "students.txt";
    readandInsert(studentList, filename);
    studentList.SaveToFile(filename);

    while (true) {
        housekeeping();
        cin >> choice;
        string yn;

        if (choice == 1) {
            cout << "\n============================================================================" << endl;
            cout << "\nAdding a student to the existing database...\n" << endl;
            cout << "\tID: ";
            cin >> iD;
            cout << "\tFirst Name: ";
            cin >> fName;
            cout << "\tLast Name: ";
            cin >> lName;
            cout << "\tDate of Birth: [MM-DD-YYY] :";
            cin >> dBirth;
            cin.ignore(); // to clear the buffer
            cout << "\tAddress: street: ";
            getline(cin, addrStreet);

            cout << "\tAddress: City: ";
            getline(cin, addrCity);

            cout << "\tAddress: State: ";
            cin >> addrCity;
            cout << "\tAddress: Zip code: ";
            cin >> zip;

            auto start_time = chrono::high_resolution_clock::now();
            studentList.Insert_Record(iD, fName, lName, dBirth, addrStreet, addrCity, addrState, zip);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            print_execution_time("Insert_Record", duration);

            cout << "Update the original file[y/n]: ";
            cin >> yn;
            if (yn == "y") {
                studentList.SaveToFile(filename);
            }
        }
        else if (choice == 2) {
            cout << "\n============================================================================" << endl;
            cout << "\nDeleting a student to the existing database..." << endl;
            cout << "ID: ";
            cin >> iD;

            auto start_time = chrono::high_resolution_clock::now();
            studentList.Delete_Record(iD);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast< chrono::nanoseconds>(end_time - start_time);
            print_execution_time("Delete_Record", duration);

            cout << "Save changes to original file[y/n]? If ID is not found press any key to continue: ";
            cin >> yn;
            if (yn == "y") {
                studentList.SaveToFile(filename);
            }
        }
        else if (choice == 3) {
            cout << "\n============================================================================" << endl;
            cout << "\nSearching a student in the existing database with ID..." << endl;
            cout << "ID: ";
            cin >> iD;

            auto start_time =  chrono::high_resolution_clock::now();
            studentList.Search_Record(iD);
            auto end_time =  chrono::high_resolution_clock::now();
            auto duration =  chrono::duration_cast< chrono::nanoseconds>(end_time - start_time);
            print_execution_time("Search_Record", duration);
        }
        else if (choice == 4) {
            cout << "\n============================================================================" << endl;
            cout << "\nSearching a student in the existing database with Name..." << endl;
            cout << "First Name: ";
            cin >> fName;
            auto start_time = chrono::high_resolution_clock::now();
            studentList.Search_Record_fname(fName);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            print_execution_time("\nSearch_Record_with_Name", duration);
        }

        else if (choice == 5) {
            cout << "\n============================================================================" << endl;
            cout << "\nUpdating a student in the existing database..." << endl;
            cout << "ID: ";
            cin >> iD;

            
            studentList.Update_record(iD);
            

            cout << "Update changes to original file[y/n] if ID is not found press any key to continue:";
            cin >> yn;
            if (yn == "y") {
                studentList.SaveToFile(filename);
                
            }
            

        }
        else {
            cout << "\nExiting the program...." << endl;
            exit(0);
        }
    }
    return 0;
}
