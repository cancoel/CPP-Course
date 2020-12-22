#pragma once

#include <memory>

namespace my {
template <typename ValueT>
class Vector {
public:
    //RAI-Semantics
    Vector(int n = 0, ValueT t = ValueT());
    Vector(const Vector& rhs);
    Vector(Vector&& rhs);
    Vector& operator=(Vector rhs);
    ~Vector();
    //Methods
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void reserve(size_t capacity);
    void shrink_to_fit();
    void clear();
    void push_back(const ValueT& t);
    ValueT pop_back();
    //Operator
    ValueT operator[](size_t t) const;
    ValueT& operator[](size_t t);
    ValueT at(size_t t) const;
    ValueT& at(size_t t);

    friend void swap(Vector<ValueT>& rhs, Vector<ValueT>& lhs)
    {
        /*
        ValueT* temp_p = lhs.p_;
        lhs.p_ = rhs.p_;
        rhs.p_ = temp_p;

        size_t temp_size = lhs.size_;
        lhs.size_ = rhs.size_;
        rhs.size_ = temp_size;

        size_t temp_capac = lhs.capacity_;
        lhs.capacity_ = rhs.capacity_;
        rhs.capacity_ = temp_capac;
        */
        std::swap(lhs.p_, rhs.p_);
        std::swap(lhs.size_, rhs.size_);
        std::swap(lhs.capacity_, rhs.capacity_);
    }

private:
    size_t size_;
    size_t capacity_;
    ValueT* p_;
};
//RAI-Semantics
template <typename ValueT>
Vector<ValueT>::Vector(int n, ValueT t)
{
    if (n == 0) {
        p_ = static_cast<ValueT*>(malloc(sizeof(ValueT) * 1));
        capacity_ = 1;
        size_ = 0;
    } else {
        p_ = static_cast<ValueT*>(malloc(sizeof(ValueT) * n));
        for (int i = 0; i < n; i++) {
            new (&p_[i]) ValueT(t);
        }
        capacity_ = n;
        size_ = n;
    }
}
template <typename ValueT>
Vector<ValueT>::Vector(const Vector& rhs)
{
    ValueT* memory = static_cast<ValueT*>(malloc(sizeof(ValueT) * rhs.capacity_));
    for (size_t i = 0; i < rhs.size_; i++) {
        new (&memory[i]) ValueT(rhs[i]);
    }
    p_ = memory;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
}

template <typename ValueT>
Vector<ValueT>::Vector(Vector&& rhs)
    : Vector()
{
    swap(*this, rhs);
}
template <typename ValueT>
Vector<ValueT>& Vector<ValueT>::operator=(Vector rhs)
{
    swap(*this, rhs);
    return *this;
}
template <typename ValueT>
Vector<ValueT>::~Vector()
{
    clear();
    free(p_);
}

//Methods
template <typename ValueT>
bool Vector<ValueT>::empty() const
{
    return (size_ == 0);
}
template <typename ValueT>
size_t Vector<ValueT>::size() const
{
    return size_;
}
template <typename ValueT>
size_t Vector<ValueT>::capacity() const
{
    return capacity_;
}
template <typename ValueT>
void Vector<ValueT>::reserve(size_t new_capacity)
{
    size_t cap = size_;
    ValueT* memory = static_cast<ValueT*>(malloc(sizeof(ValueT) * new_capacity));
    for (size_t i = 0; i < cap && i < new_capacity; i++) {
        new (&memory[i]) ValueT(std::move(p_[i]));
    }
    clear();
    free(p_);
    p_ = memory;
    capacity_ = new_capacity;
    size_ = cap;
}
template <typename ValueT>
void Vector<ValueT>::shrink_to_fit()
{
    reserve(size_);
}
template <typename ValueT>
void Vector<ValueT>::clear()
{
    for (int i = 0; i < size_; i++) {
        (p_ + i)->~ValueT();
    }
    size_ = 0;
}
template <typename ValueT>
void Vector<ValueT>::push_back(const ValueT& t)
{
    if (capacity_ <= size_) {
        reserve(capacity_ * 2);
    }
    new (&p_[size_]) ValueT(std::move(t));
    size_++;
}
template <typename ValueT>
ValueT Vector<ValueT>::pop_back()
{
    ValueT t = p_[size_ - 1];
    (p_ + size_ - 1)->~ValueT();
    size_--;
    return t;
}

//Operator
template <typename ValueT>
ValueT Vector<ValueT>::operator[](size_t t) const
{
    return p_[t];
}
template <typename ValueT>
ValueT& Vector<ValueT>::operator[](size_t t)
{
    return p_[t];
}
template <typename ValueT>
ValueT Vector<ValueT>::at(size_t t) const
{
    if (t >= size_) {
        throw std::out_of_range("Index out of range");
    } else {
        return p_[t];
    }
}
template <typename ValueT>
ValueT& Vector<ValueT>::at(size_t t)
{
    if (t >= size_) {
        throw std::out_of_range("Index out of range");
    } else {
        return p_[t];
    }
}

//Static
template <typename ValueT>
std::ostream& operator<<(std::ostream& os, const Vector<ValueT>& rhs)
{
    os << "{ ";
    for (int i = 0; i < rhs.size(); i++) {
        os << rhs[i] << " ";
    }
    os << "}";
    return os;
}
}