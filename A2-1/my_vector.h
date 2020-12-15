#pragma once

using std::fill;

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
            for (int i = 0; i < size; i++)
            {
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

        /**
         * Set all pointers to 0.
         * Set `size_` to 0
         * https://stackoverflow.com/questions/632846/clearing-a-char-array-c
         */
        void clear() 
        {
            ValueT *first = &pointer_;
            ValueT *last = first + sizeof(pointer_);
            fill(first, last, 0);
            this->size_ = 0;
        }

        // MARK: - Modifying C array

        /**
         * Adds `value` to existing `pointers_`.
         */
        void push_back(const ValueT &value)
        {
            /// Increments `size_` by 1.
            this->size_++;
            /// Overrides `pointers_` with new C array of size `size_ + 1`
            ValueT *tmp = new ValueT[size_];
            for (int i = 0; i < this->size_ - 1; i++) 
            {
                tmp[i] = this->pointer_[i];
            }
            delete[] this->pointer_;
            this->pointer_ = tmp;
            /// Add new `value`
            this->pointer_[size_ - 1] = value;
        }

        /**
         * Pops the last element of `pointer_` and returns it.
         */
        ValueT &pop_back()
        {
            ValueT &last = this->pointer_[size_ - 1];
            /// Increments `size_` by 1.
            this->size_--;
            /// Overrides `pointers_` with new C array of size `size_ - 1`
            ValueT *tmp = new ValueT[size_];
            for (int i = 0; i < this->size_; i++)
            {
                tmp[i] = this->pointer_[i];
            }
            delete[] this->pointer_;
            this->pointer_ = tmp;
            return last;
        }

        // MARK: - Overriding operators

        /**
         * Read from subscript.
         */
        void operator[](int index) const
        {
            return this->pointer_[index];
        }

        /**
         * Write to subscript.
         * Modifies `pointer_`
         */
        ValueT &operator[](int index)
        {
            return this->pointer_[index];
        }

    private:
        /// Size of `pointer_`
        size_t size_;
        /// Underlying C array
        ValueT *pointer_;
    };
}; // namespace my
