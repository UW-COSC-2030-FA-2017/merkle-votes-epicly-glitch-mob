#include "bTREE.h"


string hash_1(string key)
{
	static const char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	unsigned long hash = 0;
	int strlen = key.length();
	string hashKey;

	char character;
	for (int i = 0; i < 64; i++)
	{
		character = key.at(i%strlen);
		hash += (i + character);
		if (i % 2 == 1)
		{
			hashKey.push_back(hexmap[hash % 16]);
		}
		
	}
	return hashKey;
}

string hash_2(string key)
{
	static const char charmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	unsigned long hash;
	int strlen = key.length();
	string hashKey;

	for (int i = 0; i < 32; i++)
	{
		hash = ((key.at(i%strlen)*(key.at((i + 1) % strlen)))); //product of every two characters
		hashKey.push_back(charmap[hash % 36]); //convert to character and add to string
		hash = 0;
	}
	return hashKey;
}

string hash_3(string key)
{
	static const char charmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	unsigned long hash = 0;
	int strlen = key.length();
	string hashKey;

	for (int i = 0; i < 32; i++)
	{
		hash += (31 * (key.at(i%strlen))*(key.at((i+1)%strlen)) ^ i); //use XOR operator
		hash = hash % 36;
		hashKey.push_back(charmap[hash]); //convert to character and add to string
	}
	return hashKey;
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

	cout << "Operations to find 12: " << B.findLeaf("12") << endl;
	cout << "Path to 12: " << B.locateLeaf("12") << endl;

	if (A != B)
	{
		cout << "A not equal to B" << endl;
	}
	cout << hash_1("A02BB2124:Candidate1") << endl;
	cout << hash_1("1348937365:Candidate3") << endl;
	cout << hash_1("1348937365:Candidate3 ") << endl;

	cout << endl << hash_2("A02BB2124:Candidate1") << endl;
	cout << hash_2("1348937365:Candidate3") << endl;
	cout << hash_2("1348937365:Candidate3 ") << endl;

	cout << endl << hash_3("A02BB2124:Candidate1") << endl;
	cout << hash_3("1348937365:Candidate3") << endl;
	cout << hash_3("1348937365:Candidate3 ") << endl;

	return 0;
}