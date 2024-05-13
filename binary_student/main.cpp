#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono> // For timing
using namespace std;
using namespace std::chrono;


struct Student {
    int id;
    string name;
    string dob;
    string street;
    string city;
    string state;
    string zip;
    int height;
    Student *left;
    Student *right;
};

// Function to create a new student node
Student* createStudent(int id, const string& name, const string& dob, const string& street, const string& city, const string& state, const string& zip) {
    Student *newStudent = new Student;
    newStudent->id = id;
    newStudent->name = name;
    newStudent->dob = dob;
    newStudent->street = street;
    newStudent->city = city;
    newStudent->state = state;
    newStudent->zip = zip;
    newStudent->height = 1;
    newStudent->left = nullptr;
    newStudent->right = nullptr;
    return newStudent;
}

// Function to get the height of a node
int height(Student *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int balanceFactor(Student *node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to perform right rotation
Student* rightRotate(Student *y) {
    Student *x = y->left;
    Student *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to perform left rotation
Student* leftRotate(Student *x) {
    Student *y = x->right;
    Student *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Function to insert a student into the AVL tree
Student* insertStudent(Student *root, Student *newStudent) {
    // Perform the normal BST insertion
    if (root == nullptr)
        return newStudent;

    if (newStudent->id < root->id)
        root->left = insertStudent(root->left, newStudent);
    else if (newStudent->id > root->id)
        root->right = insertStudent(root->right, newStudent);
    else // Equal keys are not allowed in AVL
        return root;

    // Update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = balanceFactor(root);

    // If this node becomes unbalanced, then there are four cases

    // Left Left Case
    if (balance > 1 && newStudent->id < root->left->id)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && newStudent->id > root->right->id)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && newStudent->id > root->left->id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && newStudent->id < root->right->id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // return the (unchanged) node pointer
    return root;
}

// Function to find the student with minimum ID in the AVL tree

Student* minValueStudent(Student *node) {
    Student *current = node;

    // Loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Function to delete a student by ID from the AVL tree
Student* deleteStudentByID(Student *root, int id) {
    // Perform standard BST delete
    if (root == nullptr)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (id < root->id)
        root->left = deleteStudentByID(root->left, id);

    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (id > root->id)
        root->right = deleteStudentByID(root->right, id);

    // If the key is the same as the root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Student *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Student *temp = minValueStudent(root->right);

            // Copy the inorder successor's data to this node
            root->id = temp->id;

            // Delete the inorder successor
            root->right = deleteStudentByID(root->right, temp->id);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node (to check whether this node became unbalanced)
    int balance = balanceFactor(root);

    // If this node becomes unbalanced, then there are four cases

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a student by ID
Student* searchStudentByID(Student *root, int id) {
    if (root == nullptr || root->id == id)
        return root;

    // Key is greater than root's key
    if (root->id < id)
        return searchStudentByID(root->right, id);

    // Key is smaller than root's key
    return searchStudentByID(root->left, id);
}

// Function to display student details
void displayStudent(Student *student) {
    if (student != nullptr) {
        cout << "ID: " << student->id << endl;
        cout << "Name: " << student->name << endl;
        cout << "DOB: " << student->dob << endl;
        cout << "Address: " << student->street << ", " << student->city << ", " << student->state << ", " << student->zip << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

// Function to search for a student by name
Student* searchStudentByName(Student *root, const string& name) {
    if (root == nullptr || root->name == name) {
        return root;
    }
    Student *found = searchStudentByName(root->left, name);
    if (found == nullptr) {
        found = searchStudentByName(root->right, name);
    }
    return found;
}

// Function to update student records
void updateStudent(Student *student) {
    cout << "Current student details:" << endl;
    displayStudent(student); // Assume you have a displayStudent function
    // Allow the user to modify the student information except for ID
    cout << "Enter updated student details:" << endl;
    cout << "Name: ";
    getline(cin, student->name); // Update name
    cout << "DOB: ";
    getline(cin, student->dob); // Update DOB
    cout << "Street: ";
    getline(cin, student->street); // Update street
    cout << "City: ";
    getline(cin, student->city); // Update city
    cout << "State: ";
    getline(cin, student->state); // Update state
    cout << "ZIP: ";
    getline(cin, student->zip); // Update ZIP
    cout << "Student details updated successfully." << endl;
}

// Function to read data from students.txt and insert into AVL tree
Student* readStudentsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return nullptr;
    }

    Student *root = nullptr;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, dob, street, city, state, zip;
        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, dob, ',');
        getline(iss, street, ',');
        getline(iss, city, ',');
        getline(iss, state, ',');
        getline(iss, zip, ',');
        int studentID = stoi(id);
        root = insertStudent(root, createStudent(studentID, name, dob, street, city, state, zip));
    }
    file.close();
    return root;
}

void writeStudentNodeToFile(ofstream& file, const Student* node);

// Function to write student data to students.txt
void writeStudentToFile(const string& filename, const Student* root) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << " for writing." << endl;
        return;
    }

    // Traverse the tree and write each student's data to the file
    writeStudentNodeToFile(file, root);

    file.close();
}

// Helper function to write student data recursively
void writeStudentNodeToFile(ofstream& file, const Student* node) {
    if (node == nullptr) {
        return;
    }

    // Write student data to the file
    file << node->id << "," << node->name << "," << node->dob << "," << node->street << ","
         << node->city << "," << node->state << "," << node->zip << endl;

    // Traverse left and right children
    writeStudentNodeToFile(file, node->left);
    writeStudentNodeToFile(file, node->right);
}

void housekeeping() {
    cout << "\n============================================================================" << endl;
    cout << "\n\t\tWELCOME TO STUDENT MANAGEMENT SYSTEM(BST)" << endl;
    cout << "\n============================================================================\n" << endl;
    cout << "Select one of the following options:\n" << endl;
    cout << "\tPress '1': To Add a student to the existing database." << endl;
    cout << "\tPress '2': To Delete a student from the database [student ID is required]." << endl;
    cout << "\tPress '3': To Search for a student with an ID." << endl;
    cout << "\tPress '4': To Search for a student with a Name in case the student ID is not available." << endl;
    cout << "\tPress '5': To Update student records [student ID is required]." << endl;
    cout << "\tPRESS Any other key to EXIT.\n" << endl;
    cout << "Action selected is: ";
}

int main() {
    auto start = high_resolution_clock::now(); // Start the timer
    Student *root = readStudentsFromFile("students.txt");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast <nanoseconds>(stop-start);
    cout <<"Time taken to read the input file: "<< duration.count() <<" nanoseconds"<<endl;
    char choice;
    do {
        housekeeping();
        cin >> choice;
        cin.ignore(); // Clear the input buffer



        switch(choice) {
            case '1': {
                // Add a student to the database
                int id;
                string name, dob, street, city, state, zip;
                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student full name: ";
                getline(cin, name);
                cout << "Enter student date of birth: ";
                getline(cin, dob);
                cout << "Enter student street: ";
                getline(cin, street);
                cout << "Enter student city: ";
                getline(cin, city);
                cout << "Enter student state: ";
                getline(cin, state);
                cout << "Enter student zip: ";
                getline(cin, zip);
                auto insertStart = high_resolution_clock::now();
                root = insertStudent(root, createStudent(id, name, dob, street, city, state, zip));
                auto insertStop = high_resolution_clock::now();
                auto insertDuration = duration_cast<nanoseconds>(insertStop - insertStart);
                cout << "Time taken for deletion: " << insertDuration.count() << " nanoseconds" << endl;
                // Write changes to file
                // Write changes to file
                writeStudentToFile("students.txt", root);
                break;
            }
            case '2': {
                // Delete a student from the database
                int id;
                cout << "Enter student ID to delete: ";
                cin >> id;
                auto deleteStart = high_resolution_clock::now();
                root = deleteStudentByID(root, id);
                auto deleteStop = high_resolution_clock::now();
                auto deleteDuration = duration_cast<nanoseconds>(deleteStop - deleteStart);
                cout << "Time taken for deletion: " << deleteDuration.count() << " nanoseconds" << endl;
                // Write changes to file
                writeStudentToFile("students.txt", root);
                break;
            }
            case '3': {
                // Search for a student by ID
                int id;
                cout << "Enter student ID to search: ";
                cin >> id;
                auto searchStart = high_resolution_clock::now();
                Student *foundStudent = searchStudentByID(root, id);
                cout << "Searching for student with ID " << id << ":" << endl;
                displayStudent(foundStudent);
                auto searchStop = high_resolution_clock::now();
                auto searchDuration = duration_cast<nanoseconds>(searchStop - searchStart);
                cout << "Time taken for search: " << searchDuration.count() << " nanoseconds" << endl;
                break;
            }
            case '4': {
                // Search for a student by name
                string name;
                cout << "Enter student name to search: ";
                getline(cin, name);
                auto searchStart = high_resolution_clock::now();
                Student *foundStudent = searchStudentByName(root, name);
                cout << "Searching for student with name " << name << ":" << endl;
                displayStudent(foundStudent);
                auto searchStop = high_resolution_clock::now();
                auto searchDuration = duration_cast<nanoseconds>(searchStop - searchStart);
                cout << "Time taken for search: " << searchDuration.count() << " nanoseconds" << endl;
                break;
            }
            case '5': {
                // Update student records
                int id;
                cout << "Enter student ID to update: ";
                cin >> id;
                cin.ignore(); // Clear input buffer
                auto stop = high_resolution_clock::now();
                Student *foundStudent = searchStudentByID(root, id);
                if (foundStudent != nullptr) {
                    auto updateStart = high_resolution_clock::now();
                    updateStudent(foundStudent);
                    auto updateStop = high_resolution_clock::now();
                    auto updateDuration = duration_cast<nanoseconds>(updateStop - updateStart);
                    cout << "Time taken for update: " << updateDuration.count() << " nanoseconds" << endl;
                    // Write changes to file
                    writeStudentToFile("students.txt", root);
                } else {
                    cout << "Student with ID " << id << " not found." << endl;
                }
                break;

            }
            default: {
                cout << "Exiting program. Goodbye!" << endl;
                break;
            }
        }



    } while (choice >= '1' && choice <= '5');

    return 0;
}
