#include "TwoFour.h"

void TwoFour::insert(int dValue) {
	Node* curNode = root;
	auto* tempItem = new NodeData(dValue);
	while (true) {
		if (curNode->isFull()) {
			split(curNode);
			curNode = curNode->getParent();
			curNode = getNextChild(curNode, dValue);
		}
		else if (curNode->isLeaf())
			break;
		else
			curNode = getNextChild(curNode, dValue);
	}
	curNode->insertItem(tempItem);
}

void TwoFour::split(Node* thisNode) {
	NodeData* itemB;
	NodeData* itemC;
	Node* parent;
	Node* child2;
	Node* child3;
	int itemIndex;
	itemC = thisNode->removeItem();
	itemB = thisNode->removeItem();
	child2 = thisNode->disconnectChild(2);
	child3 = thisNode->disconnectChild(3);
	Node* newRight = new Node();
	if (thisNode == root) {
		root = new Node();
		parent = root;
		root->connectChild(0, thisNode);
	}
	else {
		parent = thisNode->getParent();
	}
	itemIndex = parent->insertItem(itemB);
	int n = parent->getNumItems();
	for (int j = n - 1; j > itemIndex; j--) {
		Node* temp = parent->disconnectChild(j);
		parent->connectChild(j + 1, temp);
	}
	parent->connectChild(itemIndex + 1, newRight);
	newRight->insertItem(itemC);
	newRight->connectChild(0, child2);
	newRight->connectChild(1, child3);
}

Node* TwoFour::getNextChild(Node* theNode, int theValue) {
	int j;
	int numItems = theNode->getNumItems();
	for (j = 0; j < numItems; j++)
	{
		if (theValue < theNode->getItem(j)->dData)
			return theNode->getChild(j);
	}
	return theNode->getChild(j);
}

void TwoFour::displayTree(int i) {
	if (i == 0) {
		recDisplayTree(root, 0, 0);
	}
	else
		inorderdisplay(root, 0, 0);
	cout << endl;
}

void TwoFour::inorderdisplay(Node* thisNode, int level, int childNumber) {
	int numItems = thisNode->getNumItems();
	for (int j = 0; j < numItems + 1; j++) {
		Node* nextNode = thisNode->getChild(j);
		if (nextNode != nullptr)
			inorderdisplay(nextNode, level + 1, j);
		else {
			thisNode->displayNode();
			return;
		}
		if (j < thisNode->getNumItems())
			thisNode->displayvalue(j);
	}
}


Node* TwoFour::find(int theValue) {
	return findvalue(root, theValue);
}

Node* TwoFour::findvalue(Node* theNode, int theValue) {
	Node* l = nullptr;
	int numItems = theNode->getNumItems();
	for (int j = 0; j < numItems; j++) {
		if (theValue == theNode->getItem(j)->dData) {
			l = theNode;
			break;
		}
		else if (theValue < theNode->getItem(j)->dData && !theNode->isLeaf()) {
			l = findvalue(theNode->getChild(j), theValue);
			break;
		}
		else if (theValue > theNode->getItem(j)->dData && !theNode->isLeaf()) {
			l = findvalue(theNode->getChild(j + 1), theValue);
		}
	}
	return l;
}

Node* TwoFour::deleteD(Node* currnode, int theValue) {
	Node* y = nullptr;
	if (currnode->isLeaf()) {
		if (currnode->getNumItems() > 1) {
			currnode->deletenodevalue(theValue);
			return currnode;
		}
		else {
			y = deleteleaf_cases(currnode, theValue);
			return y;
		}
	}
	else {
		Node* n = getNextChild(currnode, theValue);
		Node* c = getinordernode(n);
		NodeData* d = c->getItem(0);
		int k = d->dData;
		deleteD(c, d->dData);

		Node* found = find(theValue);
		for (int i = 0; i < found->getNumItems(); i++) {
			if (found->getItem(i)->dData == theValue) {
				found->getItem(i)->dData = k;
			}
		}
		return found;
	}
}

Node* TwoFour::deleteleaf_cases(Node* thisNode, int theValue) {
	std::wstring sibling_side = L"l";
	Node* p = thisNode->getParent();
	Node* sibling = thisNode->getsibiling(theValue);
	if (sibling == nullptr) {
		sibling_side = L"r";
		sibling = p->getChild(1);
	}
	if (sibling->getNumItems() == 1) {
		for (int i = 0; i <= p->getNumItems(); i++) {
			if (p->getChild(i) == sibling && sibling_side == L"l") {
				thisNode->setItem(thisNode->getNumItems() - 1, nullptr);
				thisNode->setNumItems(thisNode->getNumItems() - 1);
				NodeData* d = p->getItem(i);
				sibling->insertItem(d);
				p->disconnectChild(i + 1);
				for (int j = i; j < p->getNumItems(); j++) {
					if (j + 1 < p->getNumItems()) {
						p->setItem(j, p->getItem(j + 1));
						if (j + 2 <= p->getNumItems()) {
							p->connectChild(j + 1, p->disconnectChild(j + 2));
						}
					}
				}
				p->setItem(p->getNumItems() - 1, nullptr);
				p->setNumItems(p->getNumItems() - 1);
				if (p->getNumItems() == 0) {
					if (p != root) {
						p = balancetree(p);
					}
					else {
						root = sibling;
					}
				}
				return p;
			}
			else if (p->getChild(i) == sibling && sibling_side == L"r") {
				thisNode->setItem(thisNode->getNumItems() - 1, nullptr);
				thisNode->setNumItems(thisNode->getNumItems() - 1);
				NodeData* d = p->getItem(i - 1);
				sibling->insertItem(d);
				p->disconnectChild(0);
				p->connectChild(0, p->disconnectChild(1));

				for (int j = i; j < p->getNumItems(); j++) {
					p->setItem(j - 1, p->getItem(j));
					if (j + 1 <= p->getNumItems()) {
						p->connectChild(j, p->disconnectChild(j + 1));
					}
				}
				p->setItem(p->getNumItems() - 1, nullptr);
				p->setNumItems(p->getNumItems() - 1);
				if (p->getNumItems() == 0) {
					if (p != root) {
						p = balancetree(p);
					}
					else {
						root = sibling;
					}
				}
				return p;

			}
		}
	}
	else if (sibling->getNumItems() > 1) {
		int f = 0;
		if (sibling_side == L"r") {
			f = 0;
		}
		else {
			f = sibling->getNumItems() - 1;
		}

		for (int i = 0; i <= p->getNumItems(); i++) {
			if (p->getChild(i) == sibling && sibling_side == L"l") {
				thisNode->getItem(0)->dData = p->getItem(i)->dData;
				p->getItem(i)->dData = sibling->getItem(f)->dData;
				sibling->deletenodevalue(sibling->getItem(f)->dData);
				return p;
			}

			if (p->getChild(i) == sibling && sibling_side == L"r") {
				thisNode->getItem(0)->dData = p->getItem(i - 1)->dData;
				p->getItem(i - 1)->dData = sibling->getItem(f)->dData;
				sibling->deletenodevalue(sibling->getItem(f)->dData);
				return p;
			}
		}
	}
	return nullptr;
}

Node* TwoFour::balancetree(Node* currnode) {
	std::wstring sibling_side = L"l";
	Node* p = currnode->getParent();
	Node* sibling = currnode->getsibiling(-1);
	if (sibling == nullptr) {
		sibling_side = L"r";
		sibling = p->getChild(1);
	}
	if (sibling->getNumItems() == 1) {
		for (int i = 0; i <= p->getNumItems(); i++) {
			if (p->getChild(i) == sibling && sibling_side == L"l") {
				NodeData* d = p->getItem(i);
				sibling->insertItem(d);
				sibling->connectChild(sibling->getNumItems(), currnode->disconnectChild(0));
				p->disconnectChild(i + 1);
				for (int j = i; j < p->getNumItems(); j++) {
					if (j + 1 < p->getNumItems()) {
						p->setItem(j, p->getItem(j + 1));
						if (j + 2 <= p->getNumItems()) {
							p->connectChild(j + 1, p->disconnectChild(j + 2));
						}
					}
				}
				p->setItem(p->getNumItems() - 1, nullptr);
				p->setNumItems(p->getNumItems() - 1);
				if (p->getNumItems() == 0) {
					if (p != root) {
						p = balancetree(p);
					}
					else {
						root = sibling;
					}
				}
				return p;
			}
			else if (p->getChild(i) == sibling && sibling_side == L"r") {
				NodeData* d = p->getItem(i - 1);
				sibling->insertatfront(d);
				sibling->connectChild(0, currnode->disconnectChild(0));
				p->disconnectChild(0);
				p->connectChild(0, p->disconnectChild(1));
				for (int j = i; j < p->getNumItems(); j++) {
					p->setItem(j - 1, p->getItem(j));
					if (j + 1 <= p->getNumItems()) {
						p->connectChild(j, p->disconnectChild(j + 1));
					}
				}
				p->setItem(p->getNumItems() - 1, nullptr);
				p->setNumItems(p->getNumItems() - 1);
				if (p->getNumItems() == 0) {
					if (p != root) {
						p = balancetree(p);
					}
					else {
						root = sibling;
					}
				}
				return p;
			}

		}
	}
	else if (sibling->getNumItems() > 1) {
		int f = 0;
		if (sibling_side == L"r") {
			f = 0;
		}
		else {
			f = sibling->getNumItems() - 1;
		}
		for (int i = 0; i <= p->getNumItems(); i++) {
			if (p->getChild(i) == sibling && sibling_side == L"l") {
				currnode->setNumItems(currnode->getNumItems() + 1);
				currnode->connectChild(1, currnode->disconnectChild(0));
				currnode->connectChild(0,
					sibling->disconnectChild(sibling->getNumItems()));
				currnode->setItem(0, p->getItem(i));
				p->setItem(i, sibling->getItem(f));
				sibling->setItem(sibling->getNumItems() - 1, nullptr);
				sibling->setNumItems(sibling->getNumItems() - 1);
				return p;
			}
			if (p->getChild(i) == sibling && sibling_side == L"r") {
				currnode->setNumItems(currnode->getNumItems() + 1);
				currnode->setItem(0, p->getItem(i - 1));
				p->setItem(i - 1, sibling->getItem(f));
				currnode->connectChild(1, sibling->disconnectChild(f));
				for (int j = 0; j < sibling->getNumItems(); j++) {
					if (j + 1 < sibling->getNumItems()) {
						sibling->setItem(j, sibling->getItem(j + 1));
					}
					sibling->connectChild(j, sibling->disconnectChild(j + 1));
				}
				sibling->setItem(sibling->getNumItems() - 1, nullptr);
				sibling->setNumItems(sibling->getNumItems() - 1);
				return p;
			}
		}
	}
	return nullptr;
}

Node* TwoFour::getinordernode(Node* thisNode) {
	Node* c = nullptr;
	if (thisNode->isLeaf()) {
		c = thisNode;
	}
	else {
		c = getinordernode(thisNode->getChild(0));
	}
	return c;
}

TwoFour::~TwoFour() {
	delete root;
}