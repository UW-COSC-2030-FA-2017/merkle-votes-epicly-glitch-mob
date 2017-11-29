#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class bTREE 
{
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
	treeNode *tree_;
	int size_;
	vector<treeNode*> leaves_;

	bool empty() const;
	void destroy(treeNode *subtree);
	void display(ostream &outfile) const;
	void displayRight(ostream &outfile, treeNode *subtree, string prefix) const;
	void displayLeft(ostream &outfile, treeNode *subtree, string prefix) const;
	vector<string> inorderString() const; 
	void inorderString(vector<string> &traversal, const treeNode *subtree) const;

public:
    bTREE();
    ~bTREE();
    
    int dataInserted();
    int numberOfNodes();
    
    int insert(string data, int time);
    int find(string data);
    string locate(string data);
    
    friend bool operator ==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator !=(const bTREE& lhs, const bTREE& rhs);
    friend ostream& operator <<(std::ostream& out, const bTREE& p);
};

