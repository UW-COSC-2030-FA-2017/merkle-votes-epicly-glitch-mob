// pMT.cpp
// James Mock
// 2017-11-30
// pMT defintions

#include "pMT.h"

pMT::pMT(int hashSelect)
/**
 * @brief 
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return 
 */
{
	if (hashSelect <= 1)
	{
		selectedHash = 1;
	}
	else if (hashSelect >= 3)
	{
		selectedHash = 3;
	}
	else
	{
		selectedHash = 2;
	}
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}

string pMT::getRootHash() const
{
	return myMerkle.getRootData();
}

string pMT::hash(string data)
{
	string hash;
	if (selectedHash == 1)
	{
		hash = hash_1(data);
	}
	else if (selectedHash == 2)
	{
		hash = hash_2(data);
	}
	else
	{
		hash = hash_3(data);
	}
	return hash;
}

int pMT::reHash(bTREE::treeNode *node)
{
	int ops = 0;
	while (node != NULL)
	{
		myMerkle.setData(hash(myMerkle.getBranchData(node)), node);
		node = node->root_;
		ops++;
	}
	return ops;
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time 
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
	int ops;
	if (myMerkle.empty()) //first node
	{
		myMerkle.tree_ = new bTREE::treeNode(vote, time);
		if (myMerkle.tree_ != NULL)
		{
			ops = 1;
			myMerkle.size_++;
			myMerkle.leaves_.insert(myMerkle.leaves_.begin(), myMerkle.tree_);
		}
		else
		{
			ops = -1;
		}
	}
	else
	{
		vector<bTREE::treeNode*>::iterator it = myMerkle.leaves_.begin();
		while (it != myMerkle.leaves_.end())
		{
			if (time <= (*it)->timeStamp_)
			{
				break;
			}
			it++;
		}

		if (it == myMerkle.leaves_.end()) // if largest timeStamp add to right side of last node
		{
			it--;
			bTREE::treeNode *temp = NULL;
			temp = new bTREE::treeNode("hash", -1, false, (*it)->root_); //create branch node
			if (temp != NULL) //check if memory allocated
			{
				//setup pointers
				temp->left_ = *it;
				(*it)->root_ = temp;
				if (*it != myMerkle.tree_) //don't setup root pointer for temp if it's the root node
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

				temp->right_ = new bTREE::treeNode(vote, time, true, temp); //create new leaf node
				if (temp->right_ != NULL) //check if memory allocated
				{
					temp->right_->root_ = temp;
					myMerkle.leaves_.push_back(temp->right_); //add new leaf to end of leaves vector
					myMerkle.size_ += 2;
					ops = 1;
				}
				else
				{
					ops = -1;
				}
				myMerkle.branches_.push_back(temp);
				ops += reHash(temp);
			}
			else
			{
				ops = -1;
			}
		}

		else //add to left side of node
		{
			bTREE::treeNode *temp = NULL;
			temp = new bTREE::treeNode("hash", -1, false, (*it)->root_); //create branch node
			
			if (temp != NULL) //check if memory allocated
			{
				//setup pointers
				temp->right_ = *it;
				(*it)->root_ = temp;

				if (*it != myMerkle.tree_) //don't setup root pointer for temp if it's the root node
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
				temp->left_ = new bTREE::treeNode(vote, time, true, *it); //create new leaf node
				if (temp->left_ != NULL) //check if memory allocated
				{
					temp->left_->root_ = temp;
					myMerkle.leaves_.insert(it, temp->left_); //add new leaf to leaves vector
					myMerkle.size_ += 2;
					ops = 1;
				}
				else
				{
					ops = -1;
				}
				myMerkle.branches_.push_back(temp);
				ops += reHash(temp);
			}
			else
			{
				ops = -1;
			}
		}
	}
	while (myMerkle.tree_->root_ != NULL) //make sure tree_ = root node
	{
		myMerkle.tree_ = myMerkle.tree_->root_;
	}
	return ops;
}

int pMT::findData(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
	return myMerkle.findLeaf(vote);
}

int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
	return myMerkle.findBranch(mhash);
}


string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param vote, the data to search for 
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	return myMerkle.locateLeaf(vote);
}

string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param mhash, the hash to search for 
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	return myMerkle.locateBranch(mhash);
}

string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	static const char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	unsigned long hash = 0;
	int strlen = key.length();
	string hexHash;

	char character;
	for (int i = 0; i < 64; i++)
	{
		character = key.at(i%strlen); //if string is less than 64 character repeat
		hash += (character*i); //sum of every character times its position
		if (i % 2 == 1) 
		{
			hexHash.push_back(hexmap[hash % 16]); //convert to hexadecimal and add to string
		}
	}
	return hexHash;
}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	static const char charmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	unsigned long hash;
	int strlen = key.length();
	string hashKey;

	for (int i = 0; i < 32; i++)
	{
		hash = (key.at(2*i%strlen))*(key.at((2*i + 1) % strlen))+i*i; //product of every two characters plus i squared
		hashKey.push_back(charmap[hash % 36]); //convert to character and add to string
	}
	return hashKey;
}

string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	static const char charmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	unsigned long hash = 0;
	int strlen = key.length();
	string hashKey;

	for (int i = 0; i < 32; i++)
	{
		hash += ((key.at(i%strlen))*(key.at((i + 1) % strlen))) ^ i; //product of every two characters XOR i
		hash = hash % 36;
		hashKey.push_back(charmap[hash]); //convert to character and add to string
	}
	return hashKey;
}

bool operator ==(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	bool result = false;
	if (lhs.myMerkle == rhs.myMerkle)
	{
		result = true;
	}
		return result;
}

bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	bool result = false;
	if (lhs.myMerkle.getRootData() != rhs.myMerkle.getRootData())
	{
		result = true;
	}
	return result;
}

ostream& operator <<(ostream& out, const pMT& p)
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	out << p.myMerkle;
	return out;
}


//pMT operator ^=(const pMT& lhs, const pMT& rhs)
/**
* @brief XOR between two merkle trees
* @param lhs, the left hand side of the equality statment
* @param rhs, the right hand side of the equality statement
* @return true if not equal, false otherwise
*/


//pMT operator ^(const pMT& lhs, const pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
