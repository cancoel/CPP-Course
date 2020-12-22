// Testtreiber für Aufgabe 2: my::vector
// Autor: Hartmut Schirmacher

#include "payload.h"
#include "trackmymoves.h"
#include "vector.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;
using namespace my;

void test_22();
void test_21();

int main()
{

    cout << "----------------------" << endl;

#if 1
    cout << "Starting tests (2.1) --------------------" << endl;
    test_21();
    cout << "Starting tests (2.2) --------------------" << endl;
    test_22();
#endif

    cout << "End of tests ----------------------------" << endl;
}
