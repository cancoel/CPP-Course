#pragma once

namespace my
{
    template <typename ValueT>
    class vector
    {
    public:
        // MARK: - Constructors 
        /**
         * No memory is reserved and no values are stored
         */
        vector()
            : size_(0), pointer_(nullptr)
        {
        }

        /**
         * Memeory of size `size_t` is allocated.
         * Initialization with default value for `ValueT`
         */
        vector(size_t size) 
            : size_(size), pointer_(new ValueT[size])
        {
        }

        /**
         * Memeory of size `size_t` is allocated.
         * Initialization with a copy of `value`
         */
        vector(size_t size, ValueT value) 
            : size_(size)
        {
            this->pointer_ = new ValueT[size];
            for (int i = 0; i < size; i++) {
                this->pointer_[i] = ValueT{value};
            }
        }

        // MARK: - Destructor
        ~vector() 
        {
            delete[] this->pointer_;
        }

        //MARK: - Methods
        /**
         * Returns size of underlying C array
         */
        size_t size()
        {
            return this->size_;
        }

        /**
         * Returns true if `size_` is 0
         */
        bool empty() 
        {
            return this->size_ == 0;
        }

    private: 
        /// Size of `pointer_`
        size_t size_;
        /// Underlying C array
        ValueT* pointer_;
    };
}; // namespace my
