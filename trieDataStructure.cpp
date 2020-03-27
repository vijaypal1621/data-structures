#include<iostream>
#include<string>
using namespace std;

//properties of nodes
class TrieNode
{
public:  // so that these properties can be used to other classes as well
	char data;
	TrieNode** children;  // stores addresses of other trie nodes
	bool isTerminal;

	TrieNode(int data)
	{
		this->data = data;
		children = new TrieNode * [26];  // as considering only small case alphabets only
		for (int i = 0; i < 26; i++)
			children[i] = NULL;
		isTerminal = false;
	}

};

class Trie
{
	// maintaing the address of the root of trie class which only stores the addresses of the children nodes
private:
	TrieNode* root; // creating it as dynamically
public:
	Trie()
	{
		root = new TrieNode('\0'); // it reqires data as  parameterized constructor in TrieNode class 
	}
private:  // act as helper as we need root adresses too
	void insert(TrieNode *root,string word)
	{
		// base case
		if (word.size() == 0)
		{
			root->isTerminal = true;
			return;
		}
		// Small Calculation 
		int index = word[0] - 'a';
		TrieNode* child; // maintaing the address of the intial character of the word
		if (root->children[index] != NULL)
			child = root->children[index];
		else  // create a new node and stors its adddress in child
			child = new TrieNode(word[0]);

		// Recursive call

		insert(child, word.substr(1));

	}
	  
	bool search(TrieNode* root, string word)
	{
		// base case
		if (word.size() == 0)
		{
			if (root->isTerminal == true)
				return true;
			else
				return false;
		}
		 
		// small Calculation
		int index = word[0] - 'a';
		if (root->children[index] == NULL)
			return false; // not found
		else  // recursive call
			return search(root->children[index], word.substr(1));
	}

	void remove(TrieNode* root, string word)
	{
		// base case
		if (word.size() == 0)
		{
			root->isTerminal = false;
			return;
		}

		int index = word[0] - 'a';
		TrieNode* child; // maintaing address of the child

		if (root->children[index] == NULL)
			return;
		else
			remove(child, word.substr(1));

		// checking the child node if it can be removed
		if (child->isTerminal == false)
		{
			for (int i = 0; i < 26; i++)
			{
				if (child->children[i] != NULL) // that means it has some other child as well hence it cant be removed
					return;
			}
			// if control reaches here that means it has no other child
			delete child;
			root->children[index] = NULL;


		}


	}


public: // for user
	void insert(string word)
	{
		insert(root, word);
	}

	bool search(string word)
	{
		return search(root, word);
	}

	void remove(string word)
	{
		remove(root, word);
	}


};

int main()
{




}