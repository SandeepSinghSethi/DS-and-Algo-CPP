#include<bits/stdc++.h>
using namespace std;

struct CacheItem{
	int data;
	time_t lasttime;

	CacheItem(int d) : data(d),lasttime(time(nullptr)) {}
};

struct Compare{
	bool operator()(const CacheItem& a,const CacheItem& b) const{
		return a.lasttime > b.lasttime;
	}
};

class LRUCache{
private:
	int maxsize;
	unordered_map<int,CacheItem> cmap;
	priority_queue<CacheItem ,vector<CacheItem >,Compare> pq;

public:
	LRUCache(int size) : maxsize(size){};

	int get(int key)
	{
		if(cmap.find(key) != cmap.end())
		{
			cmap[key].lasttime = time(nullptr);
			return cmap[key].data;
		}
		return -1;
	}

	void put(int key,int value)
	{	
		if(cmap.size() >= maxsize)
		{
			CacheItem retval = pq.top();
			pq.pop();
			cmap.erase(retval.data);
		}

		CacheItem newvalue(value);
		cmap[key] = newvalue;
		pq.push(newvalue);
	}
};

int main(int argc, char const *argv[])
{
	LRUCache cache(3);

	cache.put(1,10);
	cache.put(2,10);
	cache.put(3,10);

	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;
	cout << cache.get(3) << endl;
	// cout << cache.get(4) << endl;
	return 0;
}