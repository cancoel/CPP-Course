// Testtreiber für Aufgabe 2.1: my::vector
// Autor: Hartmut Schirmacher

#include "payload.h"
#include "vector.h"
#include <cassert>
#include <iostream>

using my::Vector;
using std::cout;
using std::endl;

void test_21()
{

    {
        cout << "construction/destruction/Move, size() ... ";
        Vector<Payload> v0;
        assert(v0.size() == 0);
        assert(Payload::count() == 0);

        {
            // are the elements created?
            Vector<Payload> v1(3, Payload(-1, -1, -1));
            assert(v1.size() == 3);
            assert(Payload::count() == v1.size());
        }
        {
            Vector<Payload> y(2);
            assert(y.size() == 2);
            Vector<Payload> x(std::move(y));
            assert(x.size() == 2);
        }

        // are the elements destroyed?
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }
    {
        cout << "push_back(), pop_back(), size(), empty() ... ";
        {
            Vector<Payload> v;
            assert(v.size() == 0);
            assert(v.empty());
            v.push_back(Payload(0, 0, 0));
            v.push_back(Payload(1, 1, 1));
            v.push_back(Payload(2, 2, 2));
            assert(v.size() == 3);
            assert(!v.empty());
            assert(Payload::count() == 3);

            assert(v.pop_back() == Payload(2, 2, 2));
            assert(v.size() == 2);
            assert(Payload::count() == 2);

            assert(v.pop_back() == Payload(1, 1, 1));
            assert(v.size() == 1);
            assert(Payload::count() == 1);

            assert(v.pop_back() == Payload(0, 0, 0));
            assert(v.size() == 0);
            assert(v.empty());
            assert(Payload::count() == 0);
        }
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }

    {
        cout << "operator[] ... ";
        {
            Vector<Payload> v;
            v.push_back(Payload(1, 2, 3));
            v.push_back(Payload(7, 8, 9));
            assert(v.size() == 2);

            // check reading
            assert(v[0] == Payload(1, 2, 3));
            assert(v[1] == Payload(7, 8, 9));

            // check writing
            v[1] = Payload(-1, -1, -1);
            assert(v[1] == Payload(-1, -1, -1));
        }
        cout << " done." << endl;
    }

    {
        cout << "at() ... ";
        {
            Vector<Payload> v;
            v.push_back(Payload(1, 2, 3));
            v.push_back(Payload(7, 8, 9));
            assert(v.size() == 2);

            // check reading
            assert(v.at(0) == Payload(1, 2, 3));
            assert(v.at(1) == Payload(7, 8, 9));

            // check writing
            v.at(1) = Payload(-1, -1, -1);
            assert(v.at(1) == Payload(-1, -1, -1));

            // check exception
            try {
                v.at(2) = Payload(0, 0, 0);
                assert(!"should have thrown exception");
            } catch (std::out_of_range ex) {
                cout << "exception: " << ex.what();
            }
        }
        cout << " done." << endl;
    }

    {
        cout << "constness... ";
        {
            Vector<Payload> v;
            v.push_back(Payload(1, 2, 3));
            v.push_back(Payload(7, 8, 9));

            // const ref (read-only ref)
            const Vector<Payload>& vconst = v;

            // all this must compile without problems, else you are missing const :-)
            assert(!vconst.empty());
            assert(vconst.size() == 2);
            assert(vconst[0] == Payload(1, 2, 3));
            assert(vconst.at(0) == Payload(1, 2, 3));
        }
        cout << " done." << endl;
    }

    {
        // mal ausprobieren - soll vorerst nicht (!) kompilieren
        Vector<Payload> v1;
        v1 = v1;
        //Was genau soll denn hier passieren?
        //Vector<Payload> v2 = v2;
    }
}

void test_22()
{

    {
        cout << "Reserve/Pushback ... ";
        Vector<Payload> v0;
        assert(v0.size() == 0);
        assert(Payload::count() == 0);

        {
            // are the elements created?
            Vector<Payload> v1(3, Payload(-1, -1, -1));
            assert(v1.size() == 3);
            assert(Payload::count() == v1.size());
            assert(v1.capacity() == v1.size());

            //Test reserve
            v1.reserve(100);
            assert(v1.capacity() == 100);
            assert(v1.size() == 3);
            assert(Payload::count() == v1.size());

            //Test pushback
            v1.push_back(Payload(1, 1, 1));
            assert(v1.capacity() == 100);
            assert(v1.size() == 4);
            assert(Payload::count() == v1.size());

            //Check if elements are in right order and with right values
            assert(v1[0].x == -1);
            assert(v1[1].x == -1);
            assert(v1[2].x == -1);
            assert(v1[3].x == 1);
        }
        {
            //Test over bounds push_back
            Vector<Payload> v2(2);
            assert(v2.size() == 2);
            assert(v2.capacity() == 2);
            v2.push_back(Payload(1, 1, 1));
            assert(v2.capacity() == 4);
            assert(v2.size() == 3);
            assert(Payload::count() == v2.size());
        }

        // are the elements destroyed?
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }

    {
        cout << "ShrinkToFit/Clear/Popback ... ";

        {
            // are the elements created?
            Vector<Payload> v1(3, Payload(-1, -1, -1));
            assert(v1.size() == 3);
            assert(Payload::count() == v1.size());
            assert(v1.capacity() == v1.size());

            //Test Popback
            v1.reserve(100);
            assert(v1.size() == 3);
            {
                v1[2] = Payload(100, 100, 100);
                auto x = v1[2];
                assert(x == v1.pop_back());
            }
            assert(v1.capacity() == 100);
            assert(v1.size() == 2);
            assert(Payload::count() == v1.size());

            //Test shrink_to_fit
            v1.shrink_to_fit();
            assert(v1.size() == 2);
            assert(v1.capacity() == v1.size());
            assert(Payload::count() == v1.size());

            //Test clear
            v1.clear();
            assert(v1.capacity() == 2);
            assert(v1.size() == 0);
            assert(Payload::count() == v1.size());
        }

        // are the elements destroyed?
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }
    {
        cout << "Copy-/Move-Constructor ... ";

        //Copy
        {

            // Copy-Constructor are the elements created?
            Vector<Payload> v1(3, Payload(-1, -1, -1));
            assert(Payload::count() == v1.size());
            Vector<Payload> v2(v1);
            assert(Payload::count() == 2 * v1.size());
            assert(v2.size()==v1.size());
            assert(v2.capacity()==v1.capacity());
            assert(v1[1]==v2[1]);
            //Independance
            v2[0] = Payload(1, 1, 1);
            assert(v1[0] != v2[0]);
            v2.push_back(Payload(2, 2, 2));
            assert(Payload::count() == 2 * v1.size() + 1);
            assert(Payload::count() == v1.size() + v2.size());
            //Copy-assignment
            v1 = v2;
            assert(Payload::count() == 2 * v1.size());
            //Independance
            v2[0] = Payload(2, 2, 2);
            assert(v1[0] != v2[0]);
            v2.push_back(Payload(2, 2, 2));
            assert(Payload::count() == 2 * v1.size() + 1);
            assert(Payload::count() == v1.size() + v2.size());
        }
        //Move-assignment
        {
            Vector<Payload> v1(3, Payload(-1, -1, -1));
            Vector<Payload> v2(3, Payload(2, 2, 2));
            assert(Payload::count() == 6);
            v2 = std::move(v1);
            assert(Payload::count() == 3);
        }

        // are the elements destroyed?
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }
}
