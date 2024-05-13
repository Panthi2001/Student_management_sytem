// Node.h
#pragma once
#ifndef NODE_H
#define NODE_H

#include <string> // Include necessary header

using namespace std;

class Node {
public:
    int id;
    string fName;
    string lName;
    string DOB;
    string street;
    string city;
    string state;
    string zip;

    Node* next;

    // Constructor
    Node(int r, const string& fn, const string& ln, const string& db, const string& sn, const string& cn, const string& stn, const string& zc)
        : id(r), fName(fn), lName(ln), DOB(db), street(sn), city(cn), state(stn), zip(zc), next(nullptr) {}

    // Destructor
    ~Node() {}
};

#endif // NODE_H
