#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"

#include <iostream>
#include <vector>
#include "my_vector.h"

using std::cout, std::endl;
using my::vector;

void test_22();

int main()
{
    // testing without test driver
    {
        vector<float> foo;
        // cout << foo.size() << endl;
        // cout << "empty " << foo.empty() << endl;
        // try {
        //     auto should_throw =  foo.at(100);
        // } catch(std::out_of_range exception) {
        //     cout << "oops" << endl;
        // }

        // vector<int> bar{ 1 };
        // cout << bar.size() << endl;
        // cout << "empty " << bar.empty() << endl;

        // vector<double> baz{ 300 };
        // cout << baz.size() << endl;

        // vector<long> wobble{ 2 };
        // cout << wobble.size() << endl;
    }

    // testing with test driver
    {
        cout << "Starting tests (2.1) --------------------" << endl;
        test_21();
        // cout << "Starting tests (2.2) --------------------" << endl;
        // test_22();
        cout << "End of tests ----------------------------" << endl;
    }

    return 0;
}

#pragma clang diagnostic pop