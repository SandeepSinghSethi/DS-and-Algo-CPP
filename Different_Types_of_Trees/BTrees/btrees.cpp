#include"bt.h"

int main(int argc, char const *argv[])
{
    BTree t(2);

    // for(int i = 1;i<=15;i++)
    // {
    //     t.insert(i);
    // }
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(67);
    t.insert(37);
    t.insert(13);
    t.insert(19);
    t.insert(78);
    t.insert(17);
    t.traverse();
    cout << endl;


    string inkey;

    while(true)
    {
        cout << "Enter q to quit ! " << endl;
        cin >> inkey;

        if(inkey == "q")
            break;
        else if(typeid(stoi(inkey)) == typeid(int))
        {
            int k = stoi(inkey);
            t.remove(k);
            t.traverse();
            cout << endl;
        }
        else
            break;
    }


    (t.search(13) != NULL) ? cout <<  "yes " : cout << "no " << endl;
    // cout << "hello" << endl;
    return 0;
}
