#pragma once

#include "bTREE.h"
#include <string>
using namespace std;
class pMT
{
	friend class bTREE;
private:
    int selectedHash;
    bTREE myMerkle;
    
    string hash_1(string);
    string hash_2(string);
    string hash_3(string);

	//int reHash(treeNode *node);
    
public:
    pMT(int);
    ~pMT();
    
    
    int insert(string vote, int time);
    int findData(string vote, int time, int hashSelect);
    int findHash(string);
    string locateData(string);
	string locateHash(string);
    
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    friend bool operator!=(const pMT& lhs, const pMT& rhs);
    //friend pMT operator^(const pMT& lhs, const pMT& rhs);
    friend ostream& operator<<(ostream& out, const pMT& p);
};

