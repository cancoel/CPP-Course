#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"

#include <iostream>
#include <vector>
#include "my_vector.h"

using std::cout, std::endl;
using my::vector;

void test_21();
void test_22();

int main()
{
    // testing without test driver
    {
        
    }

    // testing with test driver
    {
        cout << "Starting tests (2.1) --------------------" << endl;
        test_21();
        cout << "Starting tests (2.2) --------------------" << endl;
        test_22();
        cout << "End of tests ----------------------------" << endl;
    }

    return 0;
}

#pragma clang diagnostic pop