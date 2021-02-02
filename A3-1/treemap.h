#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
#include <cassert>

using std::cout, std::endl;
using std::pair, std::shared_ptr, std::weak_ptr;
using std::make_pair, std::make_shared;

// forward declaration to resolve cross-referencing
namespace my
{
    template <typename K, typename T>
    class treemap;
}

// forward declaration to resolve cross-referencing
template <typename K, typename T>
void swap(my::treemap<K, T> &lhs, my::treemap<K, T> &rhs);

namespace my
{
    // MARK: Treemap
    // Binary search tree to find values for keys
    template <typename K, typename T>
    class treemap
    {
    protected:
        // MARK: Node
        // Node type for class treemap
        class node
        {
        public:
            node(pair<K, T> data)
                : data_(data)
            {
            }
            node(weak_ptr<node> parent_node, pair<K, T> data)
                : parent_node_(parent_node), data_(data)
            {
            }
            // Key-value pair of node data
            pair<K, T> data_;
            // Reference to parent node
            weak_ptr<node> parent_node_;
            shared_ptr<node> left_child_node_;
            shared_ptr<node> right_child_node_;
        }; // class node
        shared_ptr<node> root_;
        size_t size_;
    public:
        // MARK: Aliases
        using key_type = K;
        using mapped_type = T;
        using value_type = pair<K, T>;
        // MARK: Iterator class
        class iterator
        {
            using key_type = K;
            using mapped_type = T;
            using value_type = pair<K, T>;
        protected:
            // treemap is a friend, can call protected constructor
            friend class treemap;
            iterator(weak_ptr<node> root)
                : root_pointer_(root)
            {
            }
            iterator(weak_ptr<node> root, weak_ptr<node> node)
                : root_pointer_(root), iterator_pointer_(node)
            {
            }
        public:
            // Reference the current node
            weak_ptr<node> iterator_pointer_;
            // Reference the treemap
            weak_ptr<node> root_pointer_;

            // access data of referenced map element (node)
            
            pair<iterator, T>& operator*()
            {
                return &(iterator_pointer_.lock())->data_;
                // /* todo */
                // static value_type dummy;
                // return dummy;
            }
            value_type *operator->()
            {
                // Get node from weak_ptr
                return &(iterator_pointer_.lock())->data_;
            }

            // two iterators are equal if they point to the same node
            bool operator==(const iterator &) const
            {
                /* todo */
                return false;
            }

            bool operator!=(const iterator &) const
            {
                /* todo */
                return false;
            }

            // next element in map, pre-increment
            // note: must modify self!
            iterator &operator++()
            {
                /* todo */
                static iterator dummy;
                return dummy;
            }

            // prev element in map, pre-decrement
            // note: must modify self!
            iterator &operator--()
            {
                /* todo */
                static iterator dummy;
                return dummy;
            }
        }; // class iterator

        // used for copy&move
        template <typename KK, typename TT>
        friend void swap(treemap<KK, TT> &, treemap<KK, TT> &);

        // construct empty map
        treemap()
            : root_(nullptr), size_(0)
        {
        }

        // move ctor
        treemap(treemap<K, T> &&);

        // deep copy ctor
        treemap(const treemap<K, T> &);

        // how often is the element contained in the map?
        // (for this type of container, can only return 0 or 1)
        size_t count(const K &search_key) const 
        {
            // return true if the search equals end()
            return find(search_key, root_) == end();
        }

        // assignment (move & copy)
        treemap<K, T> &operator=(treemap<K, T>);

        // remove/destroy all elements
        void clear() 
        {
            root_(nullptr);
            size_(0);
        }

        // random read-only access to value by key, does not modify map
        T operator[](const K &) const;

        // random write access to value by key
        T &operator[](const K &);

        // std::shared_ptr<node<K, T>> root_;
        // size_t size_;

        // number of elements in map (nodes in tree)
        size_t size() const 
        {
            return size_;
        }

        // iterator referencing first element (node) in map
        iterator begin();

        // iterator referencing no element (node) in map
        iterator end() const 
        {
            return iterator(root_);
        }

        // add a new element into the tree
        // returns pair, consisting of:
        // - iterator to element
        // - bool
        //   - true if element was inserted;
        //   - false if key was already in map (will not overwrite existing value)
        pair<iterator, bool> insert(const K &new_key, const T &new_value)
        {
            if (root_ == nullptr) {
                // No nodes or root, create new node and set as root, increment size
                node new_node{make_pair(new_key, new_value)};
                root_ = make_shared<node>(new_node);
                size_++;
                // Return new iterator at new root
                iterator new_iterator{root_, root_};
                return pair<iterator, bool>(new_iterator, true);
            }
            return insert(new_key, new_value, root_);
        }

        pair<iterator, bool> insert(const K &new_key, const T &new_value, shared_ptr<node> start_node)
        {
            if (new_key < start_node->data_.first) 
            {
                if (start_node->left_child_node_ != nullptr)
                {
                    // search recursively for the left child node
                    return insert(new_key, new_value, start_node->left_child_node_);
                }
                // no nodes with smaller key, return iterator for node
                node new_node{start_node, make_pair(new_key, new_value)};
                start_node->left_child_node_ = make_shared<node>(new_node);
                size_++;
                iterator new_iterator{root_, start_node->left_child_node_};
                return pair<iterator, bool>(new_iterator, true);
            }
            if (new_key > start_node->data_.first)
            {
                if (start_node->right_child_node_ != nullptr)
                {
                    // search recursively for the right child node
                    return insert(new_key, new_value, start_node->right_child_node_);
                }
                // no nodes with larger key, return iterator for node
                node new_node{start_node, make_pair(new_key, new_value)};
                start_node->right_child_node_ = make_shared<node>(new_node);
                size_++;
                iterator new_iterator{root_, start_node->right_child_node_};
                return pair<iterator, bool>(new_iterator, true);
            }
            // Key equals current key because it is already in map, return false
            return make_pair<iterator, bool>(iterator{start_node}, false);
        }

        // add a new element into the tree, or overwrite existing element if key already in map
        // returns:
        // - iterator to element
        // - true if element was newly created; false if existing element was overwritten
        pair<iterator, bool> insert_or_assign(const K& new_key, const T & value)
        {
            iterator iter = find (new_key);
            if (iter.iterator_pointer_.lock() != nullptr){
                (iter.iterator_pointer_.lock())->data_ = make_pair(new_key, value);

            } else {
                return insert (new_key, value);
            }
            return pair<iterator, bool> (iter, false);
        }
        
        // find element with specific key. returns end() if not found.
        iterator find(const K &search_key, shared_ptr<node> start_node) const 
        {
            if (start_node != nullptr) 
            {
                if (start_node->data_.first == search_key) 
                {
                    // start node has desired key
                    return iterator(root_, start_node);
                }
                if (start_node->data_.first > search_key) 
                {
                    // search left child of start node
                    return find(search_key, start_node->left_child_node_);
                }
                if (start_node->data_.first < search_key) 
                {
                    // search right child of start node
                    return find(search_key, start_node->right_child_node_);
                }
            }
            return end();
        }
    };

    // random read-only access to value by key
    template <typename K, typename T>
    T treemap<K, T>::operator[](const K & search_key) const
    {
        /* checky */
        return find (search_key)->second;
    }

    // random write access to value by key
    template <typename K, typename T>
    T &treemap<K, T>::operator[](const K & new_key)
    {

        auto node = find (new_key);
        if (node == end()){
            return insert (new_key, T()).left_child_node->right_child_node;
        } else{
            return node -> right_child_node;
        }
        /* todo */
        // static T dummy;
        // return dummy;
    }

    // move ctor
    template <typename K, typename T>
    treemap<K, T>::treemap(treemap<K, T> &&)
    {
        /* todo */
    }

    // deep copy ctor
    template <typename K, typename T>
    treemap<K, T>::treemap(const treemap<K, T> &)
    {
        /* todo */
    }

    // assignment (move & copy)
    template <typename K, typename T>
    treemap<K, T> &treemap<K, T>::operator=(treemap<K, T>)
    {
        /* todo, use copy&swap */
        return *this;
    }

    // iterator referencing first element (node) in map
    template <typename K, typename T>
    typename treemap<K, T>::iterator treemap<K, T>::begin()
    {
        
            if (root_ == nullptr){
                return iterator (root_);
            }
            auto node = root_;
            while (node->left_child_node_ != nullptr){
                    node = node->left_child_node_;
            }
            return iterator (root_, node);
        

        /* todo */
        // return iterator();
    }

    // add a new element into the tree, or over fwrite existing element if key already in map
    // returns:
    // - iterator to element
    // - true if element was newly created; false if value for existing key was overwritten
    // template <typename K, typename T>
    // pair<iterator, bool> treemap<K, T>::insert_or_assign(const K & new_key, const T & value)
    // {



    //     /* todo */
    //     return make_pair();
    // }

}

// namespace my
// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
template <typename K, typename T>
void swap(my::treemap<K, T> &, my::treemap<K, T> &)
{
}
