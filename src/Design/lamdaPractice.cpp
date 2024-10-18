//[capture](parameters) -> return_type { function_body }
#include <iostream>
using namespace std;
void lamdaTest()
{
    int x = 10;
    int y = 10;
    auto lamda = [&](int z)
    {
        x++;
        y++;
        cout << x + y + z << endl;
    };
    lamda(30);
    cout << "x:" << x << "y:" << y << endl;
}
class Lamda
{
};
int main()
{
    lamdaTest();
    return 0;
}