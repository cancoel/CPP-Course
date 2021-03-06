#pragma once

using std::swap;
using std::move;
using std::fill;
using std::to_string;
using std::out_of_range;

namespace my
{
    template <typename ValueT>
    class vector
    {
    public:
        // Initialization
        vector(size_t size = 0, ValueT value = ValueT{});
        vector(const vector &rhs);
        vector(vector &&rhs);
        // Destruction
        ~vector();
        // Accessors
        size_t size() const;
        size_t capacity() const;
        // Accessing C array
        bool empty() const;
        ValueT &at(size_t index) const;
        // Modifying C array
        void shrink_to_fit();
        void reserve(size_t new_capacity);
        void clear();
        friend void swap(vector<ValueT> &rhs, vector<ValueT> &lhs);
        void push_back(const ValueT &value);
        ValueT pop_back();
        // Overriding operators
        vector &operator=(vector rhs);
        ValueT operator[](int index) const;
        ValueT &operator[](int index);

        // Prevent Copying and Assigning
        // vector(vector<ValueT> const &) = delete;
        // vector<ValueT>& operator=(vector<ValueT> const &) = delete;

    private:
        /// Stores number of elements in `pointer_`
        size_t size_;
        /// Storage space size for current `pointer_` memory allocation
        size_t capacity_;
        /// Underlying C array
        ValueT *pointer_;
    };

    // MARK: Initialization

    /*
     * Memeory of size `size_t` is allocated.
     * Initialization with a copy of `value`.
     */
    template <typename ValueT>
    vector<ValueT>::vector(size_t size, ValueT value)
        : size_(size), capacity_(size + 1)
    {
        void *memory = malloc(sizeof(ValueT) * capacity_);
        pointer_ = static_cast<ValueT *>(memory);
        /// Creates a `ValueT` instance for every `i` to enable `Payload::count()`
        for (int i = 0; i < size; i++)
        {
            float new_size = static_cast<float>(size);
            new (&pointer_[i]) ValueT{new_size};
        }
    }


    /*
     * Copy constructor for lvalues.
     * Copy and Swap
     */
    template <typename ValueT>
    vector<ValueT>::vector(const vector &rhs)
    {
        void *memory = malloc(sizeof(ValueT) * rhs.capacity_);
        ValueT *value = static_cast<ValueT *>(memory);
        for (int i = 0; i < rhs.size_; i++)
        {
            new (&value[i]) ValueT{rhs[i]};
        }
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        pointer_ = value;
    }

    /*
     * Move constructor for rvalues.
     * Move by Swapping
     */
    template <typename ValueT>
    vector<ValueT>::vector(vector &&rhs)
        : vector()
    {
        swap(*this, rhs);
    }

    // MARK: Destruction

    /*
     * Clears and frees `pointer_` memory
     */
    template <typename ValueT>
    vector<ValueT>::~vector()
    {
        clear();
        free(pointer_);
    }

    // MARK: Accessors

    /*
    * Returns `size_`
    */
    template <typename ValueT>
    size_t vector<ValueT>::size() const
    {
        return size_;
    }

    /*
     * Returns `capacity_`
     */
    template <typename ValueT>
    size_t vector<ValueT>::capacity() const
    {
        return capacity_;
    }

    // MARK: Accessing the C array

    /*
     * Returns true if `size_` is 0
     */
    template <typename ValueT>
    bool vector<ValueT>::empty() const
    {
        return size_ == 0;
    }

    /*
     * Returns element of `pointer_` at `index`.
     * Throws `out_of_range` if `index` is out of bounds of `pointer_`
     */
    template <typename ValueT>
    ValueT &vector<ValueT>::at(size_t index) const
    {
        /// Check index for range
        if (index < size_ && index >= 0)
        {
            return pointer_[index];
        }
        /// Throw exception
        std::string message = "Unexpectedly found illegal index " + to_string(index);
        throw out_of_range{message};
    }

    // MARK: Modifying the C array

    /*
     * Reserves memory exactly for the current `size_`
     */
    template <typename ValueT>
    void vector<ValueT>::shrink_to_fit()
    {
        reserve(size_);
    }

    /*
     * Reserves memeory of size `new_capacity`.
     * Keeps elements in `pointer_` within `new_capacity`
     */
    template <typename ValueT>
    void vector<ValueT>::reserve(size_t new_capacity)
    {
        /// Allocate new memory
        size_t size = size_;
        void *memory = malloc(sizeof(ValueT) * new_capacity);
        ValueT *value = static_cast<ValueT*>(memory);
        for (int i = 0; i < size && i < new_capacity; i++) 
        {
            /// Place old value in new memory
            ValueT current_value = move(pointer_[i]);
            new (&value[i]) ValueT{current_value};
        }
        /// Remove excess values from `pointer_`
        clear();
        free(pointer_);
        capacity_ = new_capacity;
        pointer_ = value;
        size_ = size;
    }


    /*
     * Destroy all elements in `pointer_`
     * Set `size_` to 0
     */
    template <typename ValueT>
    void vector<ValueT>::clear()
    {
        for (int i = 0; i < size_; i++)
        {
            ValueT *current_value = pointer_ + i;
            current_value->~ValueT();
        }
        size_ = 0;
    }

    /*
     * Swap all attributes from this class.
     * Takes care of deletion and deallocation
     */
    template <typename ValueT>
    void swap(vector<ValueT> &rhs, vector<ValueT> &lhs)
    {
        swap(lhs.size_, rhs.size_);
        swap(lhs.capacity_, rhs.capacity_);
        swap(lhs.pointer_, rhs.pointer_);
    }

    /*
     * Adds `value` to existing `pointers_`.
     * Reservation strategy: double `capacity_`
     */
    template <typename ValueT>
    void vector<ValueT>::push_back(const ValueT& value)
    {
        /// Reserve `size_ * 2` amount of new memory
        if (capacity_ <= size_) 
        {
            reserve(capacity_ * 2);
        }
        /// Allocate new memory
        ValueT new_value = pointer_[size_];
        new (&new_value) ValueT{move(value)};
        size_++;
    }

    /*
     * Pops the last element of `pointer_` and returns it.
     */
    template <typename ValueT>
    ValueT vector<ValueT>::pop_back()
    {
        /// Destroy last value
        size_t last = size_ - 1;
        ValueT last_value = pointer_[last];
        (pointer_ + last)->~ValueT();
        /// Update size
        size_--;
        return last_value;
    }


    // MARK: Overriding operators

    /*
     * Overrides assign operator.
     * Move by Swapping
     */
    template <typename ValueT>
    vector<ValueT> &vector<ValueT>::operator=(vector rhs)
    {
        swap(*this, rhs);
        return *this;
    }

    /*
     * Read from subscript.
     * Returns element of `pointer_` at `index`
     */
    template <typename ValueT>
    ValueT vector<ValueT>::operator[](int index) const
    {
        return pointer_[index];
    }

    /*
     * Write to subscript.
     * Modifies `pointer_`
     */
    template <typename ValueT>
    ValueT &vector<ValueT>::operator[](int index)
    {
        return pointer_[index];
    }

}; // namespace my
