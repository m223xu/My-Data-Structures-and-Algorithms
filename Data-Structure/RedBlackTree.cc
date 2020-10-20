#include <iostream>

struct Node
{
	enum struct Color
	{
		RED = 0,
		BLACK = 1
	};
	Color color;
	int key;
	Node* left;
	Node* right;
	Node* p;

	Node(int key, Color color = Color::BLACK) : color(color), key(key), left(nullptr), right(nullptr), p(nullptr)
	{
	}
	~Node();
};

class RBTree
{
	Node* root;
	Node* nil;
	void leftRotate(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nil)
		{
			y->left->p = x;
		}

		y->p = x->p;
		if (x->p == nil)
		{
			root = y;
		}
		else if (x == x->p->left)
		{
			x->p->left = y;
		}
		else x->p->right = y;
		
		y->left = x;
		x->p = y;
	}
	void rightRotate(Node* y)
	{
		Node* x = y->left;
		y->left = x->right;
		if (x->right != nil)
		{
			x->right->p = y;
		}

		x->p = y->p;
		if (y->p == nil)
		{
			root = x;
		}
		else if (y == y->p->left)
		{
			y->p->left = x;
		}
		else y->p->right = x;

		x->right = y;
		y->p = x;
	}
	void insertFixup(Node* z)
	{
		while (z->p->color == Node::Color::RED)
		{
			if (z->p == z->p->p->left)
			{
				Node* y = z->p->p->right;
				if (y->color == Node::Color::RED)
				{
					z->p->color = Node::Color::BLACK;
					y->color = Node::Color::BLACK;
					z->p->p->color = Node::Color::RED;
					z = z->p->p;
					continue;
				}
				else if (z == z->p->right)
				{
					z = z->p;
					leftRotate(z);
				}
				z->p->color = Node::Color::BLACK;
				z->p->p->color = Node::Color::RED;
				rightRotate(z->p->p);
			}
			else
			{
				Node* y = z->p->p->left;
				if (y->color == Node::Color::RED)
				{
					y->color = Node::Color::BLACK;
					z->p->color = Node::Color::BLACK;
					z->p->p->color = Node::Color::RED;
					z = z->p->p;
					continue;
				}
				else if (z = z->p->left)
				{
					z = z->p;
					rightRotate(z);
				}
				z->p->color = Node::Color::BLACK;
				z->p->p->color = Node::Color::RED;
				leftRotate(z->p->p);
			}
		}
	}
	void deleteFixup(Node* x)
	{
		while (x != root and x->color == Node::Color::BLACK)
		{
			if (x == x->p->left)
			{
				Node* y = x->p->right; //必然有兄弟节点，否则黑高不同
				if (y->color == Node::Color::RED)
				{
					y->color = Node::Color::BLACK;
					x->p->color = Node::Color::RED;
					leftRotate(x->p);
					y = x->p->right;
				}
				if (y->left->color == Node::Color::BLACK and y->right->color == Node::Color::BLACK)
				{
					y->color = Node::Color::RED;
					x = x->p;
				}
				else
				{
					if (y->right->color == Node::Color::BLACK)
					{
						y->left->color = Node::Color::BLACK;
						y->color = Node::Color::RED;
						rightRotate(y);
						y = x->p->right;
					}
					y->color = x->p->color;
					y->right->color = Node::Color::BLACK;
					x->p->color = Node::Color::BLACK;
					leftRotate(x->p);
					x = root;
				}
			}
			else
			{
				Node* y = x->p->left;
				if (y->color == Node::Color::RED)
				{
					y->color = Node::Color::BLACK;
					x->p->color = Node::Color::RED;
					rightRotate(x->p);
					y = x->p->left;
				}
				if (y->right->color == Node::Color::BLACK and y->left->color == Node::Color::BLACK)
				{
					y->color = Node::Color::RED;
					x = x->p;
				}
				else
				{
					if (y->left->color == Node::Color::BLACK)
					{
						y->right->color = Node::Color::BLACK;
						y->color = Node::Color::RED;
						leftRotate(y);
						y = x->p->left;
					}
					y->color = x->p->color;
					y->left->color = Node::Color::BLACK;
					x->p->color = Node::Color::BLACK;
					rightRotate(x->p);
					x = root;
				}
			}
		}
		x->color = Node::Color::BLACK;
	}
	void transplant(Node* u, Node* v)
	{
		if (u->p == nil) root = v;
		else if (u == u->p->left) u->p->left = v;
		else u->p->right = v;
		v->p = u->p;
	}
	Node* minimum(Node* n)
	{
		while (n->left != nil)
		{
			n = n->left;
		}
		return n;
	}
public:
	void INSERT(Node* z)
	{
		Node* y = nil;
		Node* x = root;
		while (x != nil)
		{
			y = x;
			if (x->key > z->key) x = x->left;
			else x = x->right;
		}
		z->p = y;
		if (y == nil) root = z;
		else if (z->key < y->key) y->left = z;
		else y->right = z;
		z->left = nil;
		z->right = nil;
		z->color = Node::Color::RED;
		insertFixup(z);
	}
	void DELETE(Node* z)
	{
		Node* x = nullptr;
		Node* y = z;
		Node::Color original = y->color;
		if (z->left == nil)
		{
			x = z->right;
			transplant(z, x);
		}
		else if (z->right == nil)
		{
			x = z->left;
			transplant(z, x);
		}
		else
		{
			y = minimum(z->right);
			original = y->color;
			x = y->right;
			if (y->p != z)
			{
				transplant(y, x);
				y->right = z->right;
				y->right->p = y;
				transplant(z, y);
			}
			y->left = z->left;
			y->left->p = y;
			y->color = z->color;
		}
		if (original == Node::Color::BLACK)
		{
			deleteFixup(x);
		}
	}
};

int main()
{
    std::cout << "Hello World!\n"; 
}
