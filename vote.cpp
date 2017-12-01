// vote.cpp
// James Mock
// 2017-11-30
// merkle tree driver

#include <stdio.h>
#include "pMT.h"
using namespace std;

int main(int argc, char **argv)
{

	pMT A(1);
	pMT B(2);
	pMT C(3);
	pMT D(1);
	pMT E(2);

	ifstream infile;
	infile.open("vote1.txt"); //open file
	string data; //string buffer
	int time; //int buffer
	infile >> data; 
	infile >> int(time);
	while (!infile.eof())
	{
		A.insert(data, time);
		infile >> data;
		infile >> int(time);
	}
	infile.close(); //close file

	infile.open("vote2.txt"); //open file
	infile >> data;
	infile >> int(time);
	while (!infile.eof())
	{
		B.insert(data, time);
		infile >> data;
		infile >> int(time);
	}
	infile.close(); //close file

	infile.open("vote3.txt"); //open file
	infile >> data;
	infile >> int(time);
	while (!infile.eof())
	{
		C.insert(data, time);
		infile >> data;
		infile >> int(time);
	}
	infile.close(); //close file

	infile.open("vote1.txt"); //open file
	infile >> data;
	infile >> int(time);
	while (!infile.eof())
	{
		D.insert(data, time);
		infile >> data;
		infile >> int(time);
	}
	infile.close(); //close file
	
	infile.open("vote3.txt"); //open file
	infile >> data;
	infile >> int(time);
	while (!infile.eof())
	{
		E.insert(data, time);
		infile >> data;
		infile >> int(time);
	}
	infile.close(); //close file

	cout << "A:" << A << "B:" << B << "C:" << C << "D:" << D << "E:" << E;
	cout << "Root Hash of A: " << A.getRootHash() << endl;
	cout << "Root Hash of B: " << B.getRootHash() << endl;
	cout << "Root Hash of C: " << C.getRootHash() << endl;
	cout << "Root Hash of D: " << D.getRootHash() << endl;
	cout << "Root Hash of E: " << E.getRootHash() << endl << endl;

	cout << "A and B: ";
	if (A == B)
	{
		cout << "VALIDATED\n";
	}
	else if (A != B)
	{
		cout << "NOT VALIDATED\n";
	}

	cout << "A and D: ";
	if (A == D)
	{
		cout << "VALIDATED\n";
	}
	else if (A != D)
	{
		cout << "NOT VALIDATED\n";
	}

	cout << "C and E: ";
	if (C == E)
	{
		cout << "VALIDATED\n";
	}
	else if (C != E)
	{
		cout << "NOT VALIDATED\n";
	}

	cout << "B and E: ";
	if (B == E)
	{
		cout << "VALIDATED\n";
	}
	else if (B != E)
	{
		cout << "NOT VALIDATED\n";
	}

	cout << "C and D: ";
	if (C == D)
	{
		cout << "VALIDATED\n";
	}
	else if (C != D)
	{
		cout << "NOT VALIDATED\n";
	}

	return 0;
}
