#include <iostream>
#include <map>
#include <string>

struct TrieNode
{
	std::map<char, TrieNode*> nodes;
	bool leaf;
	TrieNode() : leaf(false)
	{
	}
	~TrieNode()
	{
		for (auto node : nodes) delete node.second;
	}
	
};


class Trie
{
	TrieNode* root;

	bool DELETE_helper(TrieNode* cur, std::string word, int index)
	{
		// base case
		if (index == word.length())
		{
			if (not cur->leaf) return false;
			cur->leaf = false;
			return cur->nodes.size() == 0;
		}
		char c = word[index];
		if (cur->nodes.count(c) == 0) return false;
		bool result = DELETE_helper(cur->nodes[c], word, index + 1);
		if (result)
		{
			delete cur->nodes[c];
			cur->nodes.erase(c);
			return cur->nodes.size() == 0;
		}
		return false;
	};

	void PRINT_helper(TrieNode* cur, std::string prefix)
	{
		if (cur->leaf) std::cout << prefix << std::endl;
		for (auto c : cur->nodes)
			PRINT_helper(c.second, prefix + c.first);
	}

public:
	Trie() : root(new TrieNode{})
	{
	}
	~Trie()
	{
		delete root;
	}
	bool SEARCH(std::string word);
	void INSERT(std::string word);
	void DELETE(std::string word);
	void PRINT();
};


bool Trie::SEARCH(std::string word)
{
	TrieNode* cur = root;
	for (char c : word)
	{
		if (cur->nodes.count(c) == 0)
			return false;
		cur = cur->nodes[c];
	}
	return cur->leaf;
}

void Trie::INSERT(std::string word)
{
	TrieNode* cur = root;
	for (char c : word)
	{
		if (cur->nodes.count(c) == 0)
			cur->nodes[c] = new TrieNode;
		cur = cur->nodes[c];
	}
	cur->leaf = true;
}

void Trie::DELETE(std::string word)
{
	DELETE_helper(root, word, 0);
}

void Trie::PRINT()
{
	PRINT_helper(root, "");
}


int main()
{
	Trie t;
	t.INSERT("abandone");
	t.INSERT("boost");
	t.INSERT("about");
	t.PRINT();
	std::cout << std::endl;
	std::cout << t.SEARCH("abandone") << std::endl;
	std::cout << t.SEARCH("ab") << std::endl;
	t.DELETE("abandone");
	t.INSERT("ab");
	t.PRINT();
	std::cout << t.SEARCH("abandone");
}

