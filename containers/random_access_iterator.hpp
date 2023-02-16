#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "./traits.hpp"
#include "./utils.hpp"

namespace ft
{
    template <typename T>
    class Random_access_iterator
    {
    public:
        typedef typename ft::Random_access_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::difference_type difference_type;
        typedef typename ft::iterator_traits<T*>::value_type value_type;
        typedef typename ft::iterator_traits<T*>::pointer pointer;
        typedef typename ft::iterator_traits<T*>::reference reference;
    private:
        pointer _ptr;
    public:
        Random_access_iterator()
        : _ptr(NULL)
        {}

        Random_access_iterator(pointer ptr)
        : _ptr(ptr)
        {}

        Random_access_iterator(const Random_access_iterator<typename remove_const<value_type>::type >& op)
        : _ptr(op.base())
        {}

        virtual ~Random_access_iterator()
        {}

        pointer base() const
        {
            return _ptr;
        }

        Random_access_iterator& operator=(const Random_access_iterator& op)
        {
            if (this == &op)
            {
                return *this;
            }
            _ptr = op.base();
            return *this;
        }

        reference operator*(void) const
        {
            return *_ptr;
        }

        pointer operator->(void)
        {
            return _ptr;
        }

        Random_access_iterator& operator++(void)
        {
            ++_ptr;
            return *this;
        }

        Random_access_iterator operator++(int)
        {
            Random_access_iterator rtn(*this);
            this->operator++();
            return rtn;
        }

        Random_access_iterator& operator--(void)
        {
            --_ptr;
            return *this;
        }

        Random_access_iterator operator--(int)
        {
            Random_access_iterator rtn(*this);
            operator--();
            return rtn;
        }

        Random_access_iterator operator+(const difference_type n) const
        {
            return _ptr + n;
        }

        Random_access_iterator operator-(const difference_type n) const
        {
            return _ptr - n;
        }

        Random_access_iterator& operator+=(const difference_type n)
        {
            _ptr += n;
            return *this;
        }

        Random_access_iterator& operator-=(const difference_type n)
        {
            _ptr -= n;
            return *this;
        }

        reference operator[](difference_type n)
        {
            return *(operator+(n));
        }
    };

    template <typename T>
    bool operator==(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename T_L, typename T_R>
    bool operator==(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename T>
    bool operator!=(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename T_L, typename T_R>
    bool operator!=(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename T>
    bool operator<(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename T_L, typename T_R>
    bool operator<(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename T>
    bool operator<=(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename T_L, typename T_R>
    bool operator<=(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename T>
    bool operator>(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename T_L, typename T_R>
    bool  operator>(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename T>
    bool operator>=(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename T_L, typename T_R>
    bool operator>=(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename T>
    ft::Random_access_iterator<T> 
        operator+(typename ft::Random_access_iterator<T>::difference_type n, typename ft::Random_access_iterator<T>& i)
    {
        return &(*i) + n;
    }

    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type 
        operator-(const ft::Random_access_iterator<T>& lhs, const ft::Random_access_iterator<T>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    template <typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type
        operator-(const ft::Random_access_iterator<T_L>& lhs, const ft::Random_access_iterator<T_R>& rhs)
    {
        return lhs.base() - rhs.base();
    }
}

#endif