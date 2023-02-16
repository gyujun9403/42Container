#ifndef TRAITS_HPP
# define TRAITS_HPP

#include <cstddef>

namespace ft
{
    class Input_iterator_tag { };
    class Output_iterator_tag { };
    class Forward_iterator_tag : public Input_iterator_tag {};
    class Bidirectional_iterator_tag  : public Forward_iterator_tag { };
    class Random_access_iterator_tag : public Bidirectional_iterator_tag { };

    template <typename Iterator>
    struct iterator_traits
    {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category	iterator_category;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
    public:
        typedef std::ptrdiff_t  difference_type;
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef	ft::Random_access_iterator_tag	iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
    public:
        typedef std::ptrdiff_t  difference_type;
        typedef const T         value_type;
        typedef const T*        pointer;
        typedef const T&        reference;
        typedef	ft::Random_access_iterator_tag	iterator_category;
    };
}


#endif