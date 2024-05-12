#include<bits/stdc++.h>
using namespace std;

struct HuffmanCode
{
	char data;
	unsigned  freq;
	HuffmanCode *left;
	HuffmanCode *right;

	HuffmanCode(char data,unsigned freq): data(data),freq(freq),left(nullptr),right(nullptr) {};
};

struct Compare
{
	bool operator()(HuffmanCode* left,HuffmanCode* right)
	{
		return left->freq > right->freq;
	}
};

void generatetree(HuffmanCode* root,string code,unordered_map<char,string>& mp)
{
	if(root)
	{
		if(!root->left && !root->right)
		{
			mp[root->data] = code;
		}
		generatetree(root->left,code+"0",mp);
		generatetree(root->right,code+"1",mp);
	}
}


void print(priority_queue<HuffmanCode*,vector<HuffmanCode*>,Compare> q)
{
	priority_queue<HuffmanCode*,vector<HuffmanCode *>,Compare> pq = q;
	while(!pq.empty())
	{
		HuffmanCode* tmp = pq.top();
		cout << tmp->data << " : " << tmp->freq << endl;
		pq.pop();
	}
	cout <<endl;
}

void printTree(HuffmanCode* root,unordered_map<char,string> mp)
{
	if(root)
	{
		if(root->data != '$')
			cout << root->data << " : " << mp[root->data]<< endl;
		printTree(root->left,mp);
		printTree(root->right,mp);
	}
}

HuffmanCode* root;
string buildHuffmanTree(string data)
{
	unordered_map<char,unsigned> freqtable;
	for(char c : data)
		freqtable[c]++;

	priority_queue<HuffmanCode*,vector<HuffmanCode*>,Compare> pq;

	for(auto&entry : freqtable)
		pq.push(new HuffmanCode(entry.first,entry.second));
	
	// int n = 0;
	while(pq.size() >1)
	{
		HuffmanCode * left = pq.top();
		pq.pop();
		HuffmanCode * right = pq.top();
		pq.pop();

		HuffmanCode* newnode = new HuffmanCode('$',left->freq + right->freq);
		newnode->left= left;
		newnode->right = right;
		pq.push(newnode);

		// cout << n++<<endl;
		// print(pq);
		// cout<<endl;
	}

	root = pq.top();

	unordered_map<char,string> huffcode;
	generatetree(root,"",huffcode);

	// for(const auto&i:huffcode)
	// 	cout << i.first << " : " << i.second<<endl;
	// cout << endl;
	
	printTree(root,huffcode);


	string enc = "";
	for(char c : data)
		enc += huffcode[c];
	cout << enc  << " " << enc.size() / 8<< endl;
	return enc;
}

string decodeHuffman(HuffmanCode* root,string code)
{
	HuffmanCode* temp = root;
	string ans = "";

	for(int i = 0;i<code.size();i++)
	{
		if(code[i] == '0')
			temp= temp->left;
		else
			temp = temp->right;

		if(temp->left == nullptr && temp->right == nullptr)
		{
			ans += temp->data;
			temp = root;
		}
	}

	return ans +'\0';
}

int main(int argc, char const *argv[])
{
	string data = "geeksforgeeks";
	// ifstream inputFile("sample.txt");
    // std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    // string data = fileContent;
	string ret = buildHuffmanTree(data);	
	// ofstream outputFile("output.txt");
 //    outputFile << ret ;
    // outputFile.close();
    string dec = decodeHuffman(root,ret);
    cout << dec <<endl;
	return 0;
}