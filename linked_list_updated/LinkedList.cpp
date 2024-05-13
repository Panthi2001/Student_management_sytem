#include "LinkedList.h"
#include <fstream> // Include the necessary header file for ofstream
#include <iostream>
#include <string>
#include <chrono>

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::Insert_Record(int id, const string& fName, const string& lName, const string& DOB, const string& street, const string& city, const string& state, const string& zip) {
    // Check for duplicate ID
    bool duplicateFound = false;
    Node* duplicateCheck = head;
    while (duplicateCheck != nullptr) {
        if (duplicateCheck->id == id) {
            cout << "Error: ID already exists in the database." << endl;
            duplicateFound = true;
            break; // Exit the loop
        }
        duplicateCheck = duplicateCheck->next;
    }

    // If duplicate found, exit the function
    if (duplicateFound) {
        return;
    }

    // If no duplicate ID found, proceed with insertion
    Node* newNode = new Node(id, fName, lName, DOB, street, city, state, zip);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


void LinkedList::Search_Record(int id) {
    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->id == id) {
            cout << "Record found:" << endl;
            cout << "ID: " << current->id << endl;
            cout << "First Name: " << current->fName << endl;
            cout << "Last Name: " << current->lName << endl;
            cout << "Date of Birth: " << current->DOB << endl;
            cout << "Address: " << current->street << ", " << current->city << ", " << current->state << ", " << current->zip << endl;
            found = true;
            break;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Record with ID " << id << " not found." << endl;
    }
}

void LinkedList::Search_Record_fname(string fName) {
    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->fName == fName) {
            cout << "--------------------------------" << endl;
            cout << "\nRecord found:" << endl;
            cout << "ID: " << current->id << endl;
            cout << "First Name: " << current->fName << endl;
            cout << "Last Name: " << current->lName << endl;
            cout << "Date of Birth: " << current->DOB << endl;
            cout << "Address: " << current->street << ", " << current->city << ", " << current->state << ", " << current->zip << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Record with First Name " << fName << " not found." << endl;
    }
}

int LinkedList::Delete_Record(int id) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }

    Node* temp = head;
    Node* prev = nullptr;

    if (temp != nullptr && temp->id == id) {
        head = temp->next;
        delete temp;
        cout << "Record with ID " << id << " deleted successfully." << endl;
        return 0;
    }

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Record with ID " << id << " not found." << endl;
        return -1;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Record with ID " << id << " deleted successfully." << endl;
    return 0;
}

void LinkedList::Update_record(int id) {
    auto start = std::chrono::steady_clock::now(); // Record start time
    Node* current = head;
    bool found = false;
    
    while (current != nullptr) {
        if (current->id == id) {
            found = true;
            break;
        }
        current = current->next;
    }

    if (found) {
        // Prompt the user for updated details
        cout << "Enter updated details for student with ID " << id << endl;
        cout << "You are changing data of " << current->fName << endl;
        cout << "First Name: ";
        string newFirstName;
        cin >> newFirstName;
        cout << "Last Name: ";
        string newLastName;
        cin >> newLastName;
        cout << "Date of Birth: [MM-DD-YYYY]: ";
        string newDOB;
        cin >> newDOB;
        cout << "Address: street: ";
        string newStreet;
        cin.ignore(); // to clear the buffer
        getline(cin, newStreet);
        cout << "Address: city: ";
        string newCity;
        getline(cin, newCity);
        cout << "Address: State: ";
        string newState;
        cin >> newState;
        cout << "Address: Zip code: ";
        string newZip;
        cin >> newZip;

        

        // Update the record with the new details
        current->fName = newFirstName;
        current->lName = newLastName;
        current->DOB = newDOB;
        current->street = newStreet;
        current->city = newCity;
        current->state = newState;
        current->zip = newZip;

        auto end = std::chrono::steady_clock::now(); // Record end time
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        cout << "Time taken to update record: " << duration.count() << " nanoseconds" << endl;
    }
    if (!found) {
        cout << "Record with ID " << id << " not found." << endl;
        
    }
}

void LinkedList::SaveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->id << "," << current->fName << "," << current->lName << "," << current->DOB << "," << current->street << "," << current->city << "," << current->state << "," << current->zip << endl;
        current = current->next;
    }

    file.close();
}