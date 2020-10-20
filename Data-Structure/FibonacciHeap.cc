#include <iostream>
#include <vector>
#include <cmath>

struct Node
{
	Node(int key) : key(key), degree(0), mark(false),
	parent(nullptr), child(nullptr), left(nullptr), right(nullptr) {}
	~Node()
	{
		delete child;
		left->right = nullptr;
		delete right;
	}
	int key;
	int degree;
	bool mark;
	Node* parent;
	Node* child;
	Node* left;
	Node* right;
};


class FibonacciHeap
{
	Node* min; // points to the root node with minimum key
	int n; // number of nodes in heap

	void link(Node* y, Node* x);
	void consolidate();
	void cut(Node* x, Node* y);
	void cascading_cut(Node* y);

public:
	FibonacciHeap();
	~FibonacciHeap();
	void INSERT(Node* x);
	Node* MINIMUM();
	Node* EXTRACT_MIN();
	void UNION(FibonacciHeap* H);
	void DECREASE_KEY(Node* x, int k);
	void DELETE(Node* x);
};

void FibonacciHeap::link(Node* y, Node* x)
{
	y->left->right = y->right;
	y->right->left = y->left;
	y->parent = nullptr;
	y->left = nullptr;
	y->right = nullptr;

	if (x->degree == 0)
	{
		x->child = y;
		y->parent = x;
		x->degree = 1;
	}
	else
	{
		y->parent = x;
		Node* z = x->child;
		y->left = z->left;
		y->right = z;
		y->left->right = y;
		y->right->left = y;
		x->degree++;
	}

	y->mark = false;
}

void FibonacciHeap::consolidate()
{
	int max_degree = static_cast<int> (log2(n)/log2((1+sqrt(5))/2));
	std::vector<Node*> rootlist (max_degree+1, nullptr);
	
	min->left->right = nullptr;
	while (min)
	{
		Node* x = min;
		int d = x->degree;
		while (rootlist[d])
		{
			Node* y = rootlist[d];
			if (x->key > y->key)
			{
				Node* temp = x;
				x = y;
				y = temp;
			}
			link(y,x);
			rootlist[d] = nullptr;
			d++;
		}
		rootlist[d] = x;

		min = min->right;
	}

	min = nullptr;

	for (int i = 0; i <= max_degree; i++)
	{
		if (rootlist[i])
		{
			if (min == nullptr)
			{
				min = rootlist[i];
			}
			else
			{
				rootlist[i]->left = min->left;
				rootlist[i]->right = min;
				rootlist[i]->left->right = rootlist[i];
				rootlist[i]->right->left = rootlist[i];
				if (rootlist[i]->key < min->key)
				{
					min = rootlist[i];
				}
			}
		}
	}
}

void FibonacciHeap::cut(Node* x, Node* y)
{
	// remove x from child list of y
	if (x->right == x)
	{
		y->degree = 0;
		y->child = nullptr;
	}
	else
	{
		y->degree--;
		y->child = x->right;
		x->left->right = x->right;
		x->right->left = x->left;
	}
	x->left = min->left;
	x->right = min;
	x->left->right = x;
	x->right->left = x;

	x->parent = nullptr;
	x->mark = false;
}

void FibonacciHeap::cascading_cut(Node* y)
{
	Node* z = y->parent;
	if (z)
	{
		if (!(y->mark))
		{
			y->mark = true;
		}
		else
		{
			cut(y,z);
			cascading_cut(z);
		}
	}
}

FibonacciHeap::FibonacciHeap() : min(nullptr), n(0) {}

FibonacciHeap::~FibonacciHeap()
{
	delete min;
}

void FibonacciHeap::INSERT(Node* x)
{
	if (min == nullptr)
	{
		min = x;
		x->left = x;
		x->right = x;
	}
	else
	{
		x->left = min->left;
		x->right = min;
		min->left = x;
		x->left->right = x;
		if (x->key < min->key) min = x;
	}
	n++;
}

Node* FibonacciHeap::MINIMUM()
{
	return min;
}

Node* FibonacciHeap::EXTRACT_MIN()
{
	Node* z = min;
	if (z)
	{
		Node* child = z->child;
		z->child = nullptr;
		z->degree = 0;
		if (child)
		{	
			Node* l = child->right;
			l->left = z->left;
			child->right = z;
			l->left->right = l;
			child->right->left = child;
			
			// set parents null
			for (Node* i = child; i != l->left; i = i->left)
			{
				i->parent = nullptr;
			}
		}

		// remove z
		if (z == z->right)
		{
			min = nullptr;
		}
		else
		{
			min = z->right;
			Node* l = z->left;
			l->right = min;
			min->left = l;

			z->left = nullptr;
			z->right = nullptr;

			consolidate();
		}
		n--;
	}
	return z;
}

void FibonacciHeap::UNION(FibonacciHeap* H)
{
	if (H == nullptr) return;
	if (H->min == nullptr) return;
	if (min == nullptr)
	{
		min = H->min;
		n = H->n;
	}
	else
	{
		H->min->left->right = min->right;
		min->right->left = H->min->left;
		H->min->left = min;
		min->right = H->min;
		if (H->min->key < min->key) min = H->min;
		n += H->n;
	}
	H->min = nullptr;
	delete H;	
}


void FibonacciHeap::DECREASE_KEY(Node* x, int k)
{
	if (k > x->key) return;
	x->key = k;
	Node* y = x->parent;
	if (y and x->key < y->key)
	{
		cut(x,y);
		cascading_cut(y);
	}
	if (x->key < min->key)
	{
		min = x;
	}
}

void FibonacciHeap::DELETE(Node* x)
{
	DECREASE_KEY(x, INT_MIN);
	EXTRACT_MIN();
}


int main()
{
    std::cout << "Hello World!\n";
}
