#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> x;
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    int y = x[0];
    x.erase(x.begin());
    x.pop_back();

    if (!x.empty())
    {

        for (int i = 0; i < x.size(); i++)
        {
            cout << x[i] << " ";
        }
        cout << endl;
        cout << y << endl;
    }

    return 0;
}
