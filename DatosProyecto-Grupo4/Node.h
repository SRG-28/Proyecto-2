#pragma once
#include <vector>
#include "Tools.h"
#include "NodeData.h"

class Node {
private:
    int numItems;
    Node* parent;
    static constexpr int order = 4;
    std::vector<Node*> childArray = std::vector<Node*>(order);
    std::vector<NodeData*> itemArray = std::vector<NodeData*>(order - 1);
public:
    virtual void connectChild(int, Node*); 
    virtual Node* disconnectChild(int);  
    virtual Node* getChild(int);
    virtual Node* getParent();
    virtual bool isLeaf();
    virtual int getNumItems();
    virtual void setNumItems(int);
    virtual NodeData* getItem(int);  
    virtual NodeData* setItem(int, NodeData*); 
    virtual bool isFull();
    virtual int insertItem(NodeData*);
    virtual void insertatfront(NodeData*);
    virtual NodeData* removeItem();
    virtual void displayNode();
    virtual void displayvalue(int);
    virtual void deletenodevalue(int);
    virtual void deletevalue(int, const std::wstring& side);
    virtual Node* getsibiling(int);
    virtual ~Node();
};