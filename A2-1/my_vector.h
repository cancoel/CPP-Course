#pragma once

namespace my
{
 template<typename T>

    class my_vector
    {

    public:

    Vector() {} // Default constructor
    Vector(size_t t_size) {}  
 

    Vector& operator=(const Vector& other) {} // kopieren
    Vector& operator=(Vector&& other) {} // bewegen 

    vector(vector<ValueT> const &) = delete;
    vector<ValueT>& operator=(vector<ValueT> const &) = delete;

    private:

  
};

}
