#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;

#include "../vec.h"
using namespace my;

void test_Vec3f()
{

#ifndef NDEBUG
    using Vec3f = Vec<float, 3>;

    cout << "======================" << endl;
    cout << "     Testing Vec3f    " << endl;
    cout << "======================" << endl;

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec3f) == 3 bytes: ";
        assert(sizeof(Vec3f) == 3 * sizeof(float));
        cout << "passed." << endl;
    }

    {
        cout << "  constructor & index operator: ";
        Vec3f a({});
        assert(a[0] == 0 && a[1] == 0 && a[2] == 0);
        Vec3f b({1, 2, 3});
        assert(b[0] == 1 && b[1] == 2 && b[2] == 3);
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
        const Vec3f a({1, 2, 3});
        // the next line will throw a compiler error if there is no proper "operator[] const"
        assert(a[1] == 2);
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
        Vec3f a({1, 2, 3});
        a[1] = 4;
        assert(a[0] == 1 && a[1] == 4 && a[2] == 3);
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";
        Vec3f a({1, 2, 3}), b({1, 2, 3}), c({1, 2, 9}), d({4, 5, 6});
        assert(a == b);
        assert(a == a);
        assert(a != c);
        assert(b != d);
        assert(!(a != b));
        cout << "passed." << endl;
    }

    {
        // should work out of the box when using std container (!)
        cout << "  assignment: ";
        Vec3f a({1, 2, 3});
        cout << a[0] << " "; // to make sure these values are not optimized away!
        a = Vec3f({4, 5, 6});
        assert(a[0] == 4 && a[1] == 5 && a[2] == 6);
        cout << "passed." << endl;
    }

    {
        cout << "  addition: ";
        Vec3f a({1, 2, 3}), b({4, 5, 6});
        a += b;
        assert(a == Vec3f({5, 7, 9}));
        auto c = a + Vec3f({1, 1, 1});
        assert(c == Vec3f({6, 8, 10}));
        Vec3f one({1, 1, 1}), four({4, 4, 4});
        one += one + one + one;
        assert(one == four);
        Vec3f x({0, 0, 0}), y({1, 1, 1}), z({2, 2, 2});
        x += y += z;
        assert(y == Vec3f({3, 3, 3}));
        assert(x == y);
        cout << "passed." << endl;
    }

    {
        cout << "  unary minus: ";
        Vec3f a({1, 2, 3});
        assert(-a == Vec3f({-1, -2, -3}));
        cout << "passed." << endl;
    }

    {
        cout << "  dot product: ";
        Vec3f a({1, 2, 3});
        assert((dot(a, a) == 1 * 1 + 2 * 2 + 3 * 3));
        cout << "passed." << endl;
    }

    {
        // these tests will not compile if you forgot to declare
        // some methods const
        cout << "  constness: ";
        const Vec3f a({1, 2, 3});
        assert(a[1] == 2);
        assert(a == a);
        assert(!(a != a));
        assert(a + a == Vec3f({2, 4, 6}));
        assert(-a == Vec3f({-1, -2, -3}));
        assert((dot(a, a) == 1 * 1 + 2 * 2 + 3 * 3));
        cout << "passed." << endl;
    }

    cout << "all Vec tests passed." << endl
         << endl;

#endif // not NDEBUG
}

template <typename T, int N>
Vec<T, N> generate_vec(int start_at)
{
    Vec<T, N> v({});
    for (int i = 0; i < N; i++)
    {
        v[i] = i + start_at;
    }
}

template <typename T, int N>
void test_Vec(Vec<T, N> vector)
{

#ifndef NDEBUG

    cout << "======================" << endl;
    cout << "     Testing Vec    " << endl;
    cout << "======================" << endl;
#if 0
    {
        // do not tolerate any memory overhead
        cout << "  sizeof(T) : ";
        assert( sizeof(T) == N*sizeof(T) );
        cout << "passed." << endl;
    }
#endif

    {
        cout << "  constructor & index operator: ";
        Vec<T, N> a({});
        for (int i = 0; i < N; i++)
        {
            assert(a[i] == 0);
        }

        array<T, N> arr;
        for (int i = 0; i < N; i++)
        {
            arr[i] = i + 1;
        }

        for (int i = 0; i < N; i++)
        {
            assert(arr[i] == i + 1);
        }
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
        Vec<T, N> a({});
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }
        // the next line will throw a compiler error if there is no proper "operator[] const"
        assert(a[1] == 2);
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
        Vec<T, N> a({});
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }
        a[1] = 4;
        for (int i = 0; i < N; i++)
        {
            if (i == 1)
            {
                assert(a[i] == 4);
            }
            else
            {
                assert(a[i] == i + 1);
            }
        }
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";
        Vec<T, N> a({});
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }
        Vec<T, N> b({});
        for (int i = 0; i < N; i++)
        {
            b[i] = i + 1;
        }
        Vec<T, N> c({});
        for (int i = 0; i < N; i++)
        {
            c[i] = i + 3;
        }
        Vec<T, N> d({});
        for (int i = 0; i < N; i++)
        {
            d[i] = i + 4;
        }
        assert(a == b);
        assert(a == a);
        assert(a != c);
        assert(b != d);
        assert(!(a != b));
        cout << "passed." << endl;
    }

    {
        // should work out of the box when using std container (!)
        cout << "  assignment: ";
        Vec<T, N> a({});
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }
        cout << a[0] << " "; // to make sure these values are not optimized away!
        Vec<T, N> b({});
        for (int i = 0; i < N; i++)
        {
            b[i] = i + 4;
        }
        a = b;
        for (int i = 0; i < N; i++)
        {
            assert(a[i] == i + 4);
        }
        cout << "passed." << endl;
    }

    {
        cout << "  addition: ";
        Vec<T, N> a({}); // 1,2,3, ...
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }

        Vec<T, N> b({}); // 4,5,6,...
        for (int i = 0; i < N; i++)
        {
            b[i] = i + 4;
        }
        Vec<T, N> c = a + b;
        a += b;

        assert(a == c);

        Vec<T, N> d({}); // 1,1,1,...
        for (int i = 0; i < N; i++)
        {
            d[i] = 1;
        }
        auto autoc = a + d;
        Vec<T, N> e({}); // 6,8,10, ...
        for (int i = 0; i < N; i++)
        {
            e[i] = a[i] + d[i];
        }
        assert(autoc == e);

        Vec<T, N> one({}); // 1,1,1,...
        for (int i = 0; i < N; i++)
        {
            one[i] = 1;
        }
        Vec<T, N> four({}); // 4,4,4,...
        for (int i = 0; i < N; i++)
        {
            four[i] = 4;
        }
        one += one + one + one;
        assert(one == four);
        Vec<T, N> x({}); // 0,0,0,...
        for (int i = 0; i < N; i++)
        {
            x[i] = 0;
        }
        Vec<T, N> y({}); // 1,1,1,...
        for (int i = 0; i < N; i++)
        {
            y[i] = 1;
        }
        Vec<T, N> z({}); // 2,2,2,...
        for (int i = 0; i < N; i++)
        {
            z[i] = 2;
        }
        Vec<T, N> xyz = x + y + z; // 3,3,3,...
        x += y += z;

        assert(y == xyz);
        assert(x == y);
        cout << "passed." << endl;
    }

    {
        cout << "  unary minus: ";
        Vec<T, N> a({}); // 1,2,3,...
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }
        Vec<T, N> b({});
        for (int i = 0; i < N; i++)
        {
            b[i] = -a[i];
        }
        assert(-a == b);
        cout << "passed." << endl;
    }

    {
        cout << "  dot product: ";
        Vec<T, N> a({}); // 1,2,3,...
        for (int i = 0; i < N; i++)
        {
            a[i] = i + 1;
        }

        T dot_product = 0;
        for (int i = 0; i < N; i++)
        {
            dot_product += a[i] * a[i];
        }
        assert((dot(a, a) == dot_product));
        cout << "passed." << endl;
    }
#if 0
    {
        // these tests will not compile if you forgot to declare
        // some methods const
        
        cout << "  constness: ";
        const Vec3f a({1, 2, 3});
        assert(a[1] == 2);
        assert(a == a);
        assert(!(a != a));
        assert(a + a == Vec3f({2, 4, 6}));
        assert(-a == Vec3f({-1, -2, -3}));
        assert((dot(a, a) == 1 * 1 + 2 * 2 + 3 * 3));
        cout << "passed." << endl;
    }
#endif
#endif
}
