#include "bTREE.h"


string hash_1(string text)
{
	static const char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	unsigned long hash;
	int strlen = text.length();
	string hexHash;

	char character;
	for (int i = 0; i < 32; i++)
	{
		character = text.at(i%strlen);
		hash = (17 *i* character)%16;
		hexHash.push_back(hexmap[hash]);
	}
	return hexHash;
}

int main()
{
	
	bTREE A;
	
	A.insert("1", 1);
	A.insert("2", 2);
	A.insert("3", 3);
	A.insert("4", 4);
	A.insert("5", 5);
	A.insert("6", 6);
	A.insert("7", 7);
	A.insert("8", 8);
	A.insert("9", 9);
	A.insert("10", 10);
	A.insert("11", 11);
	A.insert("12", 12);
	A.insert("13", 13);
	A.insert("14", 14);
	A.insert("15", 15);
	
	bTREE B; 
	B.insert("14", 14);
	B.insert("17", 17);
	B.insert("5", 5);
	B.insert("14", 14);
	B.insert("5", 5);
	B.insert("19", 19);
	B.insert("9", 9);
	B.insert("12", 12);
	B.insert("2", 2);
	B.insert("32", 32);
	B.insert("31", 31);
	B.insert("36", 36);
	B.insert("27", 27);
	B.insert("28", 28);
	B.insert("18", 18);
	B.insert("29", 29);
	B.insert("6", 6);
	B.insert("15", 15);
	B.insert("7", 7);
	B.insert("8", 8);
	B.insert("24", 24);
	B.insert("8", 8);
	B.insert("11", 11);
	B.insert("19", 19);
	B.insert("20", 20);
	B.insert("17", 17);
	B.insert("22", 22);
	B.insert("12", 12);
	B.insert("3", 3);
	B.insert("9", 9);
	B.insert("2", 2);
	B.insert("14", 14);
	B.insert("5", 5);
	B.insert("1", 1);
	B.insert("4", 4);
	B.insert("9", 9);
	B.insert("1", 1);
	B.insert("14", 14);
	B.insert("16", 16);
	B.insert("4", 4);

	cout << A;
	cout << B;

	cout << "Nodes in A: " << A.numberOfNodes() << endl;
	cout << "Inserted: " << A.dataInserted() << endl << endl;
	cout << "Nodes in B: " << B.numberOfNodes() << endl;
	cout << "Inserted: " << B.dataInserted() << endl << endl;

	cout << "Operations to find 12: " << B.find("32") << endl;
	cout << "Path to 12: " << B.locate("12") << endl;

	if (A != B)
	{
		cout << "A not equal to B" << endl;
	}
	cout << hash_1("tex") << endl;

	return 0;
}