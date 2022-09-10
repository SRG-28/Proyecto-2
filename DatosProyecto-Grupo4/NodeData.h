#pragma once
#include"Tools.h"
using namespace std;

class NodeData {
public:
	int dData; 
	NodeData(int dd) {
		dData = dd;
	}

	void displayItem() const { 
		cout << dData << ",";
	}

};
