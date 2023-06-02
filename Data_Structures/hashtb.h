#ifndef hashtb_h
#define hashtb_h
#pragma once

#include<bits/stdc++.h>
using namespace std;

class HashTB 
{
private:
	static const int TABLESZ = 10;

	struct Entry
	{
		string key;
		int value;
		bool filled;

		Entry() : filled(false) {};
	};
	double A;
	vector<Entry> table;


public:
	HashTB() : table(TABLESZ) {
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<double> dis(0.0,1.0);
		A = dis(gen);
	};

	void print()
	{
		for(const auto& entry : table)
		{
			if(entry.filled)
				cout << entry.key << " " << entry.value <<  endl;
		}
	}

	int hashFunction(const string& key)
	{
		int sum = 0;
		for(char c : key)
			sum += c;
		// static_cast to cast the double into an integer ... kA - floor(kA) is same as kA%1
		return static_cast<int>(TABLESZ * ((sum*A) - floor(sum*A)));
		// return sum % TABLESZ;
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