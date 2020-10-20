// AVLTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>


struct Node
{
	int key;
	Node* left;
	Node* right;
	Node* p;
	int height;
	int bf;

	Node(int key) : key(key), left(nullptr), right(nullptr), p(nullptr), height(0), bf(0)
	{
	}
	~Node()
	{
	}
	void pre_order_print()
	{
		std::cout << key << ", height: " << height << ", balance factor: " << bf << std::endl;
		if (left) left->pre_order_print();
		if (right) right->pre_order_print();
	}
};


class AVLTree
{
	Node* root;
	void leftRotate(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nullptr)
		{
			y->left->p = x;
		}

		y->p = x->p;
		if (x->p == nullptr)
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

		x->height = 1 + std::max(leftHeight(x), rightHeight(x));
		x->bf = rightHeight(x) - leftHeight(x);
		y->height = 1 + std::max(leftHeight(y), rightHeight(y));
		y->bf = rightHeight(y) - leftHeight(y);
	}
	void rightRotate(Node* y)
	{
		Node* x = y->left;
		y->left = x->right;
		if (x->right != nullptr)
		{
			x->right->p = y;
		}

		x->p = y->p;
		if (y->p == nullptr)
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

		y->height = 1 + std::max(leftHeight(y), rightHeight(y));
		y->bf = rightHeight(y) - leftHeight(y);
		x->height = 1 + std::max(leftHeight(x), rightHeight(x));
		x->bf = rightHeight(x) - leftHeight(x);
	}

	
	int leftHeight(Node* x)
	{
		if (x->left == nullptr) return -1;
		else return x->left->height;
	}
	int rightHeight(Node* x)
	{
		if (x->right == nullptr) return -1;
		else return x->right->height;
	}

	Node* successor(Node* n)
	{
		n = n->right;
		while (n->left != nullptr)
		{
			n = n->left;
		}
		return n;
	}

public:
	AVLTree()
	{
		root = nullptr;
	}

	void INSERT(int key)
	{
		Node* x = root;
		Node* y = nullptr;
		while (x)
		{
			y = x;
			if (x->key > key) x = x->left;
			else x = x->right;
		}

		Node* z = new Node{ key };

		if (y == nullptr) root = z;
		else if (y->key > z->key) y->left = z;
		else y->right = z;
		z->p = y;
		z->left = nullptr;
		z->right = nullptr;
		z->height = 0;
		z->bf = 0;

		// fixup height and balance factor and may rotate
		while (z != nullptr)
		{
			int lheight = leftHeight(z), rheight = rightHeight(z);

			z->bf = rheight - lheight; //set balance factor

			if (z->bf > 1 or z->bf < -1)
			{
				y = lheight > rheight ? z->left : z->right;

				int ylheight = leftHeight(y), yrheight = rightHeight(y);
				x = ylheight > yrheight ? y->left : y->right;

				// Now we have z,y,x up to down, and we are going to rotate based on their structure
				if (y == z->left and x == y->left)
					/*
							z
						  /
						y
					  /
					x
					*/
				{
					rightRotate(z);
				}
				else if (y == z->left and x == y->right)
					/*
							z
						  /
						y
						  \
							x
					*/
				{
					leftRotate(y);
					rightRotate(z);
				}
				else if (y == z->right and x == y->left)
					/*
						z
						  \
							y
						  /
						x
					*/
				{
					rightRotate(y);
					leftRotate(z);
				}
				else
					/*
					z
					  \
						y
						  \
							x
					*/
				{
					leftRotate(z);
				}

				break;
			}

			z->height = 1 + std::max(leftHeight(z), rightHeight(z)); //set height
			z = z->p;
		}
	}

	void DELETE(int key)
	{
		Node* z = root;
		while (z->key != key)
		{
			if (z->key > key) z = z->left;
			else z = z->right;
		}
		// BST delete
		if (z->left == nullptr and z->right)
		{
			z->right->p = z->p;
			if (z->p == nullptr) root = z->right;
			else if (z->p->left == z) z->p->left = z->right;
			else z->p->right = z->right;
			Node* temp = z->p;
			delete(z);
			z = temp;
		}
		else if (z->right == nullptr and z->left)
		{
			z->left->p = z->p;
			if (z->p == nullptr) root = z->left;
			else if (z->p->left == z) z->p->left = z->left;
			else z->p->right = z->left;
			Node* temp = z->p;
			delete(z);
			z = temp;
		}
		else if (z->left == nullptr and z->right == nullptr)
		{
			if (z->p == nullptr) root = nullptr;
			else if (z->p->left == z) z->p->left = nullptr;
			else z->p->right = nullptr;
			Node* temp = z->p;
			delete(z);
			z = temp;
		}
		else
		{
			Node* next = successor(z);
			if (next == z->right)
			{
				next->p = z->p;
				if (z->p == nullptr) root = next;
				else if (z->p->left == z) z->p->left = next;
				else z->p->right = next;

				next->left = z->left;
				z->left->p = next;
				delete(z);
				z = next;
			}
			else
			{
				z->key = next->key;
				
				if (next->right)
				{
					next->right->p = next->p;
				}
				if (next->p == nullptr) root = next->right;
				else if (next->p->left == next) next->p->left = next->right;
				else next->p->right = next->right;

				Node* temp = next->p;
				delete(next);
				z = temp;
			}
		}

		// fix bf, height
		while (z != nullptr)
		{
			int lheight = leftHeight(z), rheight = rightHeight(z);

			z->bf = rheight - lheight; //set balance factor

			if (z->bf > 1 or z->bf < -1)
			{
				Node* y = lheight > rheight ? z->left : z->right;

				int ylheight = leftHeight(y), yrheight = rightHeight(y);
				Node* x = ylheight > yrheight ? y->left : y->right;

				// Now we have z,y,x up to down, and we are going to rotate based on their structure
				if (y == z->left and x == y->left)
					/*
							z
						  /
						y
					  /
					x
					*/
				{
					rightRotate(z);
					z = y;
				}
				else if (y == z->left and x == y->right)
					/*
							z
						  /
						y
						  \
							x
					*/
				{
					leftRotate(y);
					rightRotate(z);
					z = x;
				}
				else if (y == z->right and x == y->left)
					/*
						z
						  \
							y
						  /
						x
					*/
				{
					rightRotate(y);
					leftRotate(z);
					z = x;
				}
				else
					/*
					z
					  \
						y
						  \
							x
					*/
				{
					leftRotate(z);
					z = y; 
				}
			}

			z->height = 1 + std::max(leftHeight(z), rightHeight(z)); //set height
			z = z->p;
		}
	}

	void PRE_ORDER_PRINT()
	{
		root->pre_order_print();
	}
};





int main()
{
	std::vector<int> treeNode{ 55, 46,82, 13,49,59,92,7,42,51,89,17,45 };
	//55,46,82,13,49,59,92,7,42,51,89,17,45
	AVLTree tree;
	
	for (auto tn : treeNode)
	{
		tree.INSERT(tn);
	}
	tree.DELETE(49);
	tree.PRE_ORDER_PRINT();
	tree.INSERT(49);
	for (auto tn : treeNode)
	{
		tree.DELETE(tn);
	}
	
}
