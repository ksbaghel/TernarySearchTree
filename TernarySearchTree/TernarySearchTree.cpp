// TernarySearchTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct Node {
	char data;
	bool isWord;
	Node* left;
	Node* eq;
	Node* right;
	Node(char x) : data(x), isWord(false), left(nullptr), eq(nullptr), right(nullptr) {  }
};

Node* newNode(char x)
{
	return (new Node(x));
}

Node* insert(Node* root, char* word)
{
	if (!root)
	{
		root = newNode(*word);
		root = insert(root, word);
	}
	else {
		if (*word < root->data)
		{
			//insert it into left
			root->left = insert(root->left, word);
		}
		else if (*word > root->data)
		{
			//insert it into right
			root->right = insert(root->right, word);
		}
		else //root->data == *word
		{
			if (*(word + 1))
			{
				root->eq = insert(root->eq, word + 1);
			}
			else {
				root->isWord = true;
			}
		}
	}
	return root;
}

bool search(Node* root, char* word)
{
	if (!root) return false;
	if (*word < root->data)
	{
		return search(root->left, word);
	}
	else if (*word > root->data)
	{
		return search(root->right, word);
	}
	else //
	{
		if (*(word + 1))
		{
			return search(root->eq, word + 1);
		}
		else {
			return root->isWord;
		}
	}
	return false;
}
void traversal(Node* root, string curr_str, int& count)
{
	if (!root) return;
	traversal(root->left, curr_str, count);
	if (root->isWord)
	{
		cout << (++count) << ". "<< (curr_str + root->data) << endl;
	}
	traversal(root->eq, curr_str+root->data, count);
	traversal(root->right, curr_str, count);
}
void prefixSearch(Node* root, char* prefix)
{
	if (!root) return;
	Node* curr = root;
	string str = "";
	str += (*prefix);
	while (curr)
	{
		if (*prefix < curr->data)
		{
			curr = curr->left;
		}
		else if (*prefix > curr->data)
		{
			curr = curr->right;
		}
		else
		{
			if (*(prefix + 1))
			{
				curr = curr->eq;
				prefix++;
				str += (*prefix);
			}
			else {
				//end of prefix
				break;
			}
		}
	}
	
	if (!curr) return;
	int count = 0;
	if(curr->isWord)
	{
		cout << (++count) << ". " << str << endl;
	}
	traversal(curr->eq, str, count);

}
void printDictionary(Node* root)
{
	int count = 0;
	traversal(root, "", count);
}

int main()
{
	//create a TST:
	Node* root = nullptr;
	while (1)
	{
		cout << "Enter Choice : 1. Insert 2. Print Dictionary  3. Search 4. Prefix Search" << endl;
		int x;
		cin >> x;
		if (x == 1)
		{
			cout << "Enter Word to be inserted in dictionary : ";
			string word;
			cin >> word;
			root = insert(root, (const_cast<char*>(word.c_str())));
			//printDictionary(root);
		}
		else if (x == 2)
		{
			cout << "Printing Dictionary...." << endl;
			printDictionary(root);
		}
		else if (x == 3) //Search
		{
			cout << "Enter word to be searched : ";
			string word;
			cin >> word;
			cout << word << " found in dictionary ? " << search(root, const_cast<char*>(word.c_str())) << endl;
		}
		else if(x==4) 
		{
			cout << "Enter prefix : ";
			string prefix;
			cin >> prefix;
			prefixSearch(root, const_cast<char*>(prefix.c_str()));
		}
		else {
			cout << "Invalid Input !!!!";
		}
	}
    return 0;
}

