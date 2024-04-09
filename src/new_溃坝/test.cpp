#include <cstdlib>
#include <iostream>
using namespace std;
int main()
{
    int a = 2 % 2 + 1;
    cout << a << endl;
    cout << "进入了exit" << endl;
    exit(0);

    cout << a << endl;
    return 0;
}
