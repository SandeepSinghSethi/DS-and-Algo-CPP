#ifndef hashtb_h
#define hashtb_h
#pragma once

#include<bits/stdc++.h>
// #ifdef HAS_OPENSSL
// 	#include<openssl/sha.h>	
// #endif
using namespace std;

class HashTB 
{
private:
	static const int l = 14;
	static const int TABLESZ = pow(2,l);

	struct Entry
	{
		string key;
		int value;
		bool filled;

		Entry() : filled(false) {};
	};
	double A;
	double goldenratio;
	int choice;
	vector<Entry> table;


public:
	HashTB() : table(TABLESZ) {
		// random_device rd;
		// mt19937 gen(rd());
		// uniform_real_distribution<double> dis(0.0,1.0);
		srand(static_cast<unsigned int>(time(nullptr)));
		A = static_cast<double>(rand()) / RAND_MAX;
		goldenratio = 1.6180339887;
		
		srand(static_cast<unsigned int>(time(nullptr)));
		
		for(int i = 1 ;i<100;i++)
			choice = rand() % 4;	
		cout << "INDEX : " << choice << " is getting used " << endl;
	};

	void print()
	{
		for(const auto& entry : table)
		{
			if(entry.filled)
				cout << entry.key << " " << entry.value <<  endl;
		}
	}

	int divisionhashing(int sum)
	{
		// multiplication hashing technique -> static_cast to cast the double into an integer ... kA - floor(kA) is same as kA%1
		// return static_cast<int>(TABLESZ * ((sum*A) - floor(sum*A)));
		return sum % TABLESZ;
	}

	int multiplicative_hashing(int sum)
	{	
		// division hashing techinique 
		// return sum % TABLESZ;
		return static_cast<int>(TABLESZ * (sum*A - floor(sum*A)) );
	}

	int multiplicative_shift_hashing(int sum)
	{
		// multiplicative shift hashing -> taking l = hash length , w = word size (32/64) , k = key , m = 2**14 , a = should be the prime number such that r - 2**32 where r = (goldenratio - 2**32) , it would yield -> 2654435769 <(a good prime number for hashing , search for knuth [261])
		//
		// where eg =
		// 		l = 14 (which will be used to determine the load factor of the hash table - m = pow(2,14))
		//		m = pow(2,l)
		//		k = key
		//		a = 2654435769 -> (pow(2,32) - (goldenratio - pow(2,32)))
		//		ka = k*a
		//		r1 = first 32 bit of ka	(ka[:32])
		//		r0 = last 32 bit of ka	(ka[32:])
		// 		hashval = most significant bits of r0 ( r0[:14])
		// 		  (ka mod pow(2,32)) >> (w-l)

		auto a = pow(2,32);
		a = (goldenratio * a) -a;
		auto k = sum;
		auto ka = k*a;
		auto w = 32;
		auto pow32 = 1ULL << 32;

		auto x = fmod(ka,pow32);
		auto index = static_cast<unsigned int>(x) >> (w-l);
		return index;
	}

	int modpmodm(int sum)
	{
		// this type of hashing is known as universal hashing method , and consists of a set of hash functions which create universally independent hash results , the probability of collision of two hashes is atmost (1/TABLESZ) , 
		// H = h(k) { ((ak + b) % p) % TABLESZ  } for any random a in range 0->(p-1) and for any b in range 1->(p-1) 
		// there are total p(p-1) hash functions in this single hash family.

		auto p = pow(2,32);
		p = (goldenratio * p) - p;

		srand(static_cast<unsigned int>(time(nullptr)));

		unsigned int a =  rand() % static_cast<unsigned int>(p-1);	// a E (0 ... (p-1))
		unsigned int b = (rand() % static_cast<unsigned int>(p-2)) + 1; // b E (1 ... (p-1))

		unsigned int k = sum;

		unsigned index = ((a*k + b) % static_cast<unsigned int>(p)) % TABLESZ;

		return index;
	}


	// commented for if openssl not installed , it will generate errors;
	// string sha256(const string& key)
	// {
	// 	unsigned char hash[SHA256_DIGEST_LENGTH];
	// 	SHA256_CTX sha256;
	// 	SHA256_Init(&sha256);
	// 	SHA256_Update(&sha256,key.c_str(),key.length());
	// 	SHA256_Final(hash,&sha256);

	// 	stringstream ss;
	// 	for(int i= 0;i<SHA256_DIGEST_LENGTH;++i)
	// 	{
	// 		ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
	// 	}

	// 	return ss.str();
	// }


	int hashFunction(const string& key)
	{

		int sum = 0;
		for(char c : key)
			sum += c;

		int index;

		switch (choice)
		{
		case 0:
			index=divisionhashing(sum);
			break;
		case 1:
			index =multiplicative_hashing(sum);
			break;
		case 2:
			index =multiplicative_shift_hashing(sum);
			break;
		case 3:
			index = modpmodm(sum);
			break;
		// case 4:
		// 	string hashval = sha256(key);
		// 	unsigned long long hash = stoull(hashval,nullptr,16);
		// 	index = hash % TABLESZ;
		// 	break;
		default:
			break;
		}
		// to print the hash of the index
		//
		// bitset<sizeof(int) * 8> binary(index);
		// cout << index << ":" << binary << endl;
		return index;

		
	}

	void insert(const string& key,int value)
	{
		int index = hashFunction(key);

		while(table[index].filled)
		{
			if(table[index].key == key)
			{
				cout << "Key already exists ,updating the value .." << endl;
				table[index].value = value;
				return;
			}
			index = (index+1) % TABLESZ;
		}

		table[index].key = key;
		table[index].value = value;
		table[index].filled = true;
	}

	void remove(const string& key)
	{
		int index = hashFunction(key);

		while(table[index].filled)
		{
			if(table[index].key == key)
			{
				table[index].filled=false;
				return;
			}
			index = (index+1) % TABLESZ;
		}

		cout << "No key found .." <<endl;
	}

	int retreive(const string& key)
	{
		int index = hashFunction(key);

		while(table[index].filled)
		{
			if(table[index].key == key)
			{
				return table[index].value;
			}
			index = (index+1) % TABLESZ;
		}

		return -1;
	}	
};



#endif