#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	//last_ = NULL;
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
	return leaves_.size();
}

int bTREE::numberOfNodes()
{
	return size_;
}

int bTREE::insert(string data, int time)
{
	int ops;
	if (empty()) //first node
	{
		tree_ = new treeNode(data, time);
		if (tree_ != NULL)
		{
			ops = 1;
			size_++;
			leaves_.insert(leaves_.begin(), tree_);
		}
		else
		{
			ops = -1;
		}
	}
	else
	{
		vector<treeNode*>::iterator it = leaves_.begin();
		while( it != leaves_.end())
		{
			if (time <= (*it)->timeStamp_)
			{
				break;
			}
			it++;
		}
		
		if (it == leaves_.end()) // if largest timeStamp add to right side of last node
		{
			it--;
			treeNode *temp = NULL;
			temp = new treeNode("hash", -1, false, (*it)->root_); //create branch node
			if (temp != NULL) //check if memory allocated
			{
				//setup pointers
				temp->left_ = *it;
				(*it)->root_ = temp;
				if (*it != tree_)
				{
					if (temp->root_->left_ == *it)
					{
						temp->root_->left_ = temp;
					}
					else
					{
						temp->root_->right_ = temp;
					}
				}

				temp->right_ = new treeNode(data, time, true, temp); //create new leaf node
				if (temp->right_ != NULL) //check if memory allocated
				{
					temp->right_->root_ = temp;
					leaves_.push_back(temp->right_); //add new leaf to end of leaves vector
					size_ += 2;
					ops = 1;
				}
				else
				{
					ops = -1;
				}
			}
			else
			{
				ops = -1;
			}
		}

		else //add to left side of node
		{
			treeNode *temp = NULL;
			temp = new treeNode("hash", -1, false, (*it)->root_); //create branch node
			if (temp != NULL) //check if memory allocated
			{
				//setup pointers
				temp->right_ = *it;
				(*it)->root_ = temp;
				if (temp->root_->left_ == *it)
				{
					temp->root_->left_ = temp;
				}
				else
				{
					temp->root_->right_ = temp;
				}

				temp->left_ = new treeNode(data, time, true, *it); //create new leaf node
				if (temp->left_ != NULL) //check if memory allocated
				{
					temp->left_->root_ = temp;
					leaves_.insert(it, temp->left_); //add new leaf to leaves vector
					size_ += 2;
					ops = 1;
				}
				else
				{
					ops = -1;
				}
			}
			else
			{
				ops = -1;
			}
		}
	}
	while (tree_->root_ != NULL) //make sure tree_ = root node
	{
		tree_ = tree_->root_;
	}
	return ops;
}

int bTREE::find(string data)
{
	int ops = 0;
	vector<treeNode*>::iterator it = leaves_.begin();
	while (it != leaves_.end())
	{
		ops++;
		if ((*it)->data_ == data)
		{
			break;
		}
		it++;
	}
	return ops;
}

string bTREE::locate(string data)
{
	string path;
	vector<treeNode*>::iterator it = leaves_.begin();
	while (it != leaves_.end()) //find leaf node in leaves vector
	{
		if ((*it)->data_ == data)
		{
			break;
		}
		it++;
	}
	if (it == leaves_.end()) //string not found
	{
		path = ".";
	}
	else
	{
		treeNode *ptr1 = *it;
		treeNode *ptr2 = (*it)->root_;
		while (ptr2 != NULL)
		{
			if (ptr2->left_ == ptr1)
			{
				path.insert(path.begin(), 'L');
			}
			else
			{
				path.insert(path.begin(), 'R');
			}
			ptr1 = ptr2;
			ptr2 = ptr2->root_;
		}

	}
	return path;
}

vector<string> bTREE::inorderString() const
{
	vector<string> traversal;
	inorderString(traversal, tree_);
	return traversal;
}

void bTREE::inorderString(vector<string> &traversal, const treeNode *subtree) const
{
	if (subtree != NULL)
	{
		inorderString(traversal, subtree->left_);
		traversal.push_back(subtree->data_);
		traversal.push_back(to_string(subtree->timeStamp_));
		inorderString(traversal, subtree->right_);
	}
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	bool result = false;
	if (lhs.inorderString() == rhs.inorderString())
	{
		result = true;
	}

	return result;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	bool result = false;
	if (lhs.inorderString() != rhs.inorderString())
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

void bTREE::display(ostream& outfile) const
{
	string prefix;
	if (tree_ == NULL)
	{
		outfile << "-" << endl;
	}
	else
	{
		displayLeft(outfile, tree_->left_, "    ");
		outfile << "---" << tree_->data_ << endl;
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
