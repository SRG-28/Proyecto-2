#pragma once
#include "Tools.h"
#include "Node.h"

class TwoFour {
private:
    Node* root = new Node(); // make root node
    void recDisplayTree(Node* thisNode, int level, int childNumber) {
        cout << "level=" << +level << +" child=" << +childNumber << +" ";
        thisNode->displayNode(); // display this node
        cout << endl;
        // call ourselves for each child of this node
        int numItems = thisNode->getNumItems();
        for (int j = 0; j < numItems + 1; j++) {
            Node* nextNode = thisNode->getChild(j);
            if (nextNode != nullptr)
                recDisplayTree(nextNode, level + 1, j);
            else
                return;
        }
    } // end recDisplayTree()

public:
    virtual void insert(int);
    virtual void split(Node*);
    virtual Node* getNextChild(Node*, int);
    virtual void displayTree(int);
    virtual Node* find(int);
    virtual Node* findvalue(Node*, int);
    virtual Node* deleteD(Node*, int);
    virtual Node* deleteleaf_cases(Node*, int);
    virtual Node* balancetree(Node*);
    virtual Node* getinordernode(Node*);
    virtual void inorderdisplay(Node*, int, int);
    virtual ~TwoFour();
};