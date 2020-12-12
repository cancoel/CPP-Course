#include <iostream>
#include "vec.h"
#include "test11/test11.cpp"

using namespace std;
using namespace my;

int main()
{

    Vec<float, 3> x({3.0f, 2.0f, 3.0f});
    // Vec<float, 3> x({3.0f, 2.0f, 3.0f});
    // Vec<float, 3> x({3.0f, 2.0f, 3.0f});

    test_Vec(x);
    // test_Vec(x);
    // test_Vec(x);
    
}