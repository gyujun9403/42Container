#ifndef ITREE_HPP
# define ITREE_HPP

#include <memory>
#include "pair.hpp"

namespace ft
{


    template <typename T_key, typename T_val>
    void con_left(node<T_key, T_val>& parents, node<T_key, T_val>& child)
    {
        parents.child_left = &child;
        child.parents = &parents;
    }

    template <typename T_key, typename T_val>
    void con_right(node<T_key, T_val>& parents, node<T_key, T_val>& child)
    {
        parents.chlid_right = &child;
        child.parents = &parents;
    }

    template <typename T_key, typename T_val, typename Alloc = std::allocator<ft::node<T_key, T_val> > >
    class ITree
    {
        typedef node<T_key, T_val>* pointer;

        virtual void insert(pointer new_node) = 0;
        virtual bool erase(pointer ptr_node) = 0;
        virtual bool erase(T_key key) = 0;
        virtual pointer find(T_key key) const = 0;
        virtual size_t size() const = 0;
        virtual size_t max_size() const = 0;
        virtual void swap(ITree& other) = 0;
        virtual bool empty() const = 0;
        virtual void clear() = 0;
    };
}



#endif