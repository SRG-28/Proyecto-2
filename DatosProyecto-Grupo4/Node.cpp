#include "Node.h"

void Node::connectChild(int childNum, Node* child) {
	childArray[childNum] = child;
	if (child != nullptr)
		child->parent = this;
}

Node* Node::disconnectChild(int childNum) {
	Node* tempNode = childArray[childNum];
	childArray[childNum] = nullptr;
	return tempNode;
}

Node* Node::getChild(int childNum) {
	return childArray[childNum];
}

Node* Node::getParent() {
	return parent;
}

bool Node::isLeaf() {
	return (childArray[0] == nullptr) ? true : false;
}

int Node::getNumItems() {
	return numItems;
}

void Node::setNumItems(int theValue) {
	numItems = theValue;
}

NodeData* Node::getItem(int index) {
	return itemArray[index];
}

NodeData* Node::setItem(int index, NodeData* theValue) {
	itemArray[index] = theValue;
	return itemArray[index];
}

bool Node::isFull() {
	return (numItems == order - 1) ? true : false;
}

int Node::insertItem(NodeData* newItem) {
	numItems++;
	int newKey = newItem->dData;
	for (int j = order - 2; j >= 0; j--) {
		if (itemArray[j] == nullptr) {
			continue;
		}
		else {
			int itsKey = itemArray[j]->dData;
			if (newKey < itsKey) {
				itemArray[j + 1] = itemArray[j];
			}
			else {
				itemArray[j + 1] = newItem;
				return j + 1;
			}
		}
	}
	itemArray[0] = newItem;
	return 0;
}

void Node::insertatfront(NodeData* newItem) {
	int newKey = newItem->dData;
	numItems++;
	for (int j = numItems - 1; j > 0; j--) {
		itemArray[j] = itemArray[j - 1];
		connectChild(j + 1, disconnectChild(j));
	}
	connectChild(1, disconnectChild(0));
	itemArray[0] = newItem;
	connectChild(0, nullptr);
}

NodeData* Node::removeItem() {
	NodeData* temp = itemArray[numItems - 1];
	itemArray[numItems - 1] = nullptr;
	numItems--;
	return temp;
}

void Node::displayNode() {
	for (int j = 0; j < numItems; j++)
		itemArray[j]->displayItem();
}

void Node::displayvalue(int j) {
	itemArray[j]->displayItem();
}

void Node::deletenodevalue(int theValue) {
	int flag = -1;
	for (int i = 0; i < numItems; i++) {
		if (theValue == itemArray[i]->dData) {
			flag = i;
		}
		if (flag != -1 && i + 1 < numItems) {
			itemArray[i]->dData = itemArray[i + 1]->dData;
		}
	}
	itemArray[numItems - 1] = nullptr;
	numItems--;

}

void Node::deletevalue(int theValue, const std::wstring& side) {
	int flag = -1;
	for (int i = 0; i < numItems; i++) {
		if (theValue == itemArray[i]->dData) {
			flag = i;
		}
		if (flag != -1 && i + 1 < numItems) {
			itemArray[i]->dData = itemArray[i + 1]->dData;
		}
	}
	itemArray[numItems - 1] = nullptr;
	numItems--;
}

Node* Node::getsibiling(int theValue) {
	Node* x = nullptr;
	Node* p = getParent();
	if (numItems != 0) {
		for (int i = 0; i <= p->numItems; i++) {
			if (p->childArray[i]->itemArray[0]->dData < theValue) {
				//cout << p->childArray[i]->getNumItems();
				//cout << p->childArray[i]->itemArray[0]->dData;
				x = p->childArray[i];
			}
		}
	}
	else if (numItems == 0) {
		for (int i = 0; i <= p->numItems; i++) {
			if (p->childArray[i]->itemArray[0] == nullptr) {
				//cout << p->childArray[i]->getNumItems();
				//cout << p->childArray[i]->itemArray[0]->dData;
				if (i != 0) {
					x = p->childArray[i - 1];
				}
			}
		}
	}
	return x;
}

Node::~Node() {
	delete parent;
}