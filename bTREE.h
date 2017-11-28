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
        int time_;
		treeNode *root_;
		treeNode *left_;
		treeNode *right_;

		treeNode(string data = "", int time = 0, treeNode *root = NULL)
		{
			data_ = data;
			time_ = time;
			root_ = root;
			left_ = NULL;
			right_ = NULL;
		 }

		~treeNode()
		{ }

		bool leaf(const treeNode* node)
		{
			return (node->left_ == NULL && node->left_ == NULL);
		}
    };
    
private:
    //some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need
	treeNode *tree_;
	treeNode *last_;
	int size_;

	bool empty() const;
	int getHeight() const;
	void insertInorder(string data, int time);
	void destroy(treeNode *subtree);
	void display(ostream &outfile) const;
	void displayRight(ostream &outfile, treeNode *subtree, string prefix) const;
	void displayLeft(ostream &outfile, treeNode *subtree, string prefix) const;
	vector<string> inorder() const; 
	void inorder(vector<string> &traversal, const treeNode *subtree) const;
	bool find(string data, treeNode *subtree, int* ops);
	bool balanced();

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

