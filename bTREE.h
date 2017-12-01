// bTREE.h
// James Mock
// 2017-11-30
// bTREE declartion

#ifndef _BTREE_H_
#define _BTREE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class bTREE 
{
public:
    struct treeNode
	{
        string data_;
        int timeStamp_;
		bool leaf_;
		treeNode *root_;
		treeNode *left_;
		treeNode *right_;

		treeNode(string data = "", int time = 0, bool leaf = true, treeNode *root = NULL)
		{
			//cout << "treeNode created" << endl;
			data_ = data;
			timeStamp_ = time;
			leaf_ = leaf;
			root_ = root;
			left_ = NULL;
			right_ = NULL;
		 }

		~treeNode()
		{ }
    };
    
private:
    //some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need

	void destroy(treeNode *subtree);
	void display(ostream &outfile) const;
	void displayRight(ostream &outfile, treeNode *subtree, string prefix) const;
	void displayLeft(ostream &outfile, treeNode *subtree, string prefix) const;
	vector<string> inorderString() const; 
	void inorderString(vector<string> &traversal, const treeNode *subtree) const;

public:
    bTREE();
    ~bTREE();

	treeNode *tree_; //root node
	int size_; //number of nodes
	vector<treeNode*> leaves_; //cheating
	vector<treeNode*> branches_; //cheating again
    
	bool empty() const;
    int dataInserted();
    int numberOfNodes();
	string getRootData() const; //returns root node data
	string getBranchData(treeNode *node); //retruns combined data of left and right nodes
	void setData(string hash, treeNode *node); //set data to some hash value
    
    int insert(string data, int time);
    int findLeaf(string data);
	int findBranch(string data);
    string locateLeaf(string data);
	string locateBranch(string data);
    
    friend bool operator ==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator !=(const bTREE& lhs, const bTREE& rhs);
    friend ostream& operator <<(ostream& out, const bTREE& p);
};
#endif

