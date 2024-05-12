#include<bits/stdc++.h>
using namespace std;

void increment(vector<int>& arr,int k)
{
    int i =0;
    while(i<k && arr[i] == 1)
    {
        arr[i] = 0;
        i += 1;
    }
    if(i<k)
        arr[i] = 1;
}

void print(vector<int> arr)
{
    for(const auto&i:arr)
    {
        cout <<  i << "\t";
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    int k = 16;
    vector<int> arr(k,0);

    for(int i = 0;i<pow(2,16)-1;i++){
        increment(arr,k);
        cout << i+1 << '\t';
        print(arr);
    }
    return 0;
}
