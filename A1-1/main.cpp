#include <iostream>
#include "test11/test11.cpp"
#include "vec3f.cpp"

using namespace std;
using namespace my;

int main()
{
    cout << sizeof(Vec3f) << endl;
    test_Vec3f();
    Vec3f x(3.0f, 2.0f, 3.0f);
    Vec3f y;
    x[0] = 4.f;
    cout << x[0] << endl;

    // bei Booleschen Ausdrücken runde Klammern beim cout
    cout << (x == y) << endl;
    Vec3f z(4.f, 2.f, 3.f);
    cout << (x == z) << endl;
    cout << (x != z) << endl;
    cout << (x[0] + 1) << endl;
    cout << (x[1] += 2) << endl;

    cout << (x[2] - 3) << endl;
}