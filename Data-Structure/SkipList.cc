#include <iostream>
#include <stack>
#include <random>
#include <string>


std::string tosses = "TTHHTHTHHTHHTTHTHHTTHHHT";
int index = 0;

int heads()
{
	int result = 0;
	while (true)
	{
		if (tosses[index] == 'T')
		{
			index++;
			break;
		}
		else
		{
			index++;
			result++;
		}
	}
	return result;
}

int random_heads()
{
	int result = 0;
	while (rand() % 2 == 0)
	{
		result++;
	}
	return result;
}

struct Node
{
	int key;
	Node* after;
	Node* below;
	Node(int key, Node* after = nullptr, Node* below = nullptr) : key(key), after(after), below(below)
	{
	}
	~Node()
	{
	}
};


class SkipList
{
	Node* topLeft;
	int height;
public:
	SkipList();
	~SkipList();
	Node* SEARCH(int k);
	void INSERT(int k);
	void DELETE(int k);
	int getHeight() const;
private:
	std::stack<Node*> getPredecessors(int k);
};

SkipList::SkipList() : topLeft(new Node{ INT_MIN, new Node{INT_MAX} }), height(0)
{
}

SkipList::~SkipList()
{
	while (topLeft)
	{
		Node* temp1 = topLeft;
		topLeft = topLeft->below;
		while (temp1)
		{
			Node* temp2 = temp1;
			temp1 = temp1->after;
			delete(temp2);
		}
	}
}

Node* SkipList::SEARCH(int k)
{
	std::stack<Node*> predecessors = getPredecessors(k);
	Node* previous = predecessors.top();
	if (previous->after->key == k) return previous->after;
	else return nullptr;
}

void SkipList::INSERT(int k)
{
	int i = heads();
	while (height <= i)
	{
		topLeft = new Node{ INT_MIN, new Node{INT_MAX, nullptr, topLeft->after}, topLeft };
		height++;
	}
	std::stack<Node*> predecessors = getPredecessors(k);
	
	Node* base = nullptr;
	while (i >= 0)
	{
		Node* predecessor = predecessors.top();
		base = new Node{ k,predecessor->after,base };
		predecessor->after = base;
		predecessors.pop();
		i--;
	}
}

void SkipList::DELETE(int k)
{
	std::stack<Node*> predecessors = getPredecessors(k);
	while (!predecessors.empty())
	{
		Node* predecessor = predecessors.top();
		predecessors.pop();
		if (predecessor->after->key == k)
		{
			Node* temp = predecessor->after;
			predecessor->after = temp->after;
			delete(temp);
		}
		else break;
	}
	// remove extra layers
	while (height > 0 and topLeft->below->after->after == nullptr)
	{
		height--;
		Node* temp1 = topLeft->below;
		topLeft->below = temp1->below;
		topLeft->after->below = temp1->after->below;
		Node* temp2 = temp1->after;
		delete(temp1);
		delete(temp2);
	}
}

int SkipList::getHeight() const
{
	return height;
}

std::stack<Node*> SkipList::getPredecessors(int k)
{
	Node* p = topLeft;
	std::stack<Node*> predecessors;
	predecessors.push(p);
	while (p->below)
	{
		p = p->below;
		while (p->after->key < k) p = p->after;
		predecessors.push(p);
	}
	return predecessors;
}


int main()
{
	SkipList sl;
	sl.INSERT(67);
	sl.INSERT(28);
	sl.INSERT(64);
	sl.INSERT(66);
	sl.INSERT(60);
	sl.INSERT(81);
	sl.INSERT(49);
	std::cout << sl.getHeight();
}
