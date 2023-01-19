#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "./base_iterator.hpp"
#include "../utils/traits.hpp"

namespace ft
{
    template <typename T>
    class Reverse_iterator : Base_iterator<T>
    {
    public:
        typedef typename ft::Reverse_iterator iterator_category;
        typedef typename ft::iterator_traits<T>::difference_type difference_type;
        typedef typename ft::iterator_traits<T>::value_type value_type;
        typedef T*  pointer;
        typedef T&  reference;
    };
}

#endif