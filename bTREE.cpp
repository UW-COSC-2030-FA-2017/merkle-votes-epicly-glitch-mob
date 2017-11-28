#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	last_ = NULL;
	tree_ = NULL;
	size_ = 0;
}

bTREE::~bTREE()
{
	destroy(tree_);
}

bool bTREE::empty() const
{
	bool empty = false;
	if (tree_ == NULL)
	{
		empty = true;
	}

	return empty;
}

int bTREE::getHeight() const
{
	int height = 0;
	if (tree_ != NULL)
	{
		treeNode *ptr = tree_;
		while (ptr != NULL)
		{
			ptr = ptr->left_;
			height++;
		}
	}
	return height;
}

bool bTREE::balanced()
{

	bool result = true;
	//cout << pow(2, getHeight()) - 1 << endl;
	//cout << size_ << endl;
	if (pow(2, getHeight())-1 > size_)
	{
		result = false;
	}
	return result;

}

void bTREE::destroy(treeNode *subtree)
{
	if (subtree != NULL)
	{
		destroy(subtree->left_);
		destroy(subtree->right_);
		delete subtree;
		subtree = NULL;
	}
}

int bTREE::dataInserted()
{
	return 0;
}

int bTREE::numberOfNodes()
{
	return size_;
}

int bTREE::insert(string data, int time)
{
	int ops;
	if (empty())
	{
		//cout << "empty" << endl;
		tree_ = new treeNode(data, time);
		if (tree_ != NULL)
		{
			ops = 1;
			size_++;
			last_ = tree_;
		}
		else
		{
			ops = -1;
		}
	}
	else
	{
		insertInorder(data, time);
		if (last_ != NULL)
		{
			size_++;
			ops = 1;
		}
		else
		{
			ops = -1;
		}
	}
	return ops;
}

void bTREE::insertInorder(string data, int time)
{
	if (!balanced())
	{
		//cout << "not balanced" << endl;
		if (last_->root_->right_ == NULL)
		{
			last_->root_->right_ = new treeNode(data, time, last_->root_);
			last_ = last_->root_->right_;
			//cout << "right" << endl;
		}
		else
		{
			treeNode* ptr = last_->root_->root_->right_;
			int ht = 3;
			while (ptr->left_ != NULL)
			{
				ptr = last_;
				for (int i = 0; i < ht; i++)
				{
					ptr = ptr->root_;
				}
				ptr = ptr->right_;
				for (int i = 0; i < ht - 2; i++)
				{
					ptr = ptr->left_;
				}
				ht++;
			}
			ptr->left_ = new treeNode(data, time, ptr);
			last_ = ptr->left_;
			//cout << "left" << endl;
		}
	}
	else
	{
		//cout << "balanced" << endl;
		last_ = tree_;
		while (last_->left_ != NULL)
		{
			last_ = last_->left_;
		}
		last_->left_ = new treeNode(data, time, last_);
		last_ = last_->left_;
		//cout << "left" << endl;
	}
	return;
}

int bTREE::find(string data)
{
	int ops = 0;
	if (tree_ != NULL)
	{
		ops++;
		bool found = false;
		if (tree_->data_ != data)
		{
			if (tree_->left_ != NULL)
			{
				found = find(data, tree_->left_, &ops);
			}
			if (tree_->right_ != NULL && !found)
			{
				found = find(data, tree_->right_, &ops);
			}
		}
		else
		{
			found = true;
		}
		if (found == false)
		{
			ops = -1;
		}
	}
	return ops;
}

bool bTREE::find(string data, treeNode *subtree, int *ops)
{
	bool found = false;
	*ops += 1;
	if (subtree->data_ != data)
	{
		if (subtree->left_ != NULL)
		{
			found = find(data, subtree->left_, ops);
		}
		if (subtree->right_ != NULL && !found)
		{
			found = find(data, subtree->right_, ops);
		}
	}
	else
	{
		found = true;
	}
	return found;
}

string bTREE::locate(string data)
{
	return "";
}

vector<string> bTREE::inorder() const
{
	vector<string> traversal;
	inorder(traversal, tree_);
	return traversal;
}

void bTREE::inorder(vector<string> &traversal, const treeNode *subtree) const
{
	if (subtree != NULL)
	{
		inorder(traversal, subtree->left_);
		traversal.push_back(subtree->data_);
		traversal.push_back(to_string(subtree->time_));
		inorder(traversal, subtree->right_);
	}
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	bool result = false;
	if (lhs.inorder() == rhs.inorder())
	{
		result = true;
	}

	return result;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	bool result = false;
	if (lhs.inorder() != rhs.inorder())
	{
		result = true;
	}

	return result;
}

ostream& operator <<(ostream& out, const bTREE& p)
{
	p.display(out);
	return out;
}

void bTREE::display(std::ostream& outfile) const
{
	std::string prefix;
	if (tree_ == NULL)
	{
		outfile << "-" << std::endl;
	}
	else
	{
		displayLeft(outfile, tree_->left_, "    ");
		outfile << "---" << tree_->data_ << std::endl;
		displayRight(outfile, tree_->right_, "    ");
	}
	return;
}

// Display the nodes connected to subtree.
void bTREE::displayLeft(ostream &outfile, treeNode *subtree, string prefix) const
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "     ");
		outfile << prefix + "/---" << subtree->data_ << endl;
		displayRight(outfile, subtree->right_, prefix + "|    ");
	}
	return;
}

// Display the nodes connected to subtree.
void bTREE::displayRight(ostream &outfile, treeNode *subtree, string prefix) const
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "|    ");
		outfile << prefix + "\\---" << subtree->data_ << endl;
		displayRight(outfile, subtree->right_, prefix + "     ");
	}
	return;
}
