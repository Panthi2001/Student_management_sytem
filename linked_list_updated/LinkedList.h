#pragma once
#ifndef LINK_LST
#define LINK_LST
#include "Node.h"

#include <iostream>

using namespace std;

class LinkedList {
public:
	Node* head;
	LinkedList() : head(nullptr) {}
	~LinkedList();
	
	void Insert_Record(int id, const string& fName, const string& lName, const string& DOB, const string& street, const string& city, const string& state, const string& zip);
	void Search_Record(int id);
	void Search_Record_fname(string fName);
	int Delete_Record(int id);
	void Update_record(int id);
	void SaveToFile(const string& filename);

};

#endif // !


