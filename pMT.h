// pMT.h
// James Mock
// 2017-11-30
// pMT declartion

#ifndef _PMT_H_
#define _PMT_H_

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

	string hash(string data);
	int reHash(bTREE::treeNode *node);
    
public:
    pMT(int);
    ~pMT();
    
	string getRootHash() const;

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
#endif

