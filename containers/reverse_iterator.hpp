#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "./traits.hpp"

namespace ft
{
    template <typename iter>
    class Reverse_iterator
    {
    public:
        typedef typename ft::iterator_traits<iter>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<iter>::difference_type difference_type;
        typedef typename ft::iterator_traits<iter>::value_type value_type;
		typedef typename ft::iterator_traits<iter>::pointer pointer;
		typedef typename ft::iterator_traits<iter>::reference reference;
    private:
        iter _origin_iter;
    public:
        Reverse_iterator() {}
        explicit Reverse_iterator(iter other)
        : _origin_iter(other) {}
        template<typename T>
        Reverse_iterator(const Reverse_iterator<T>& other)
        : _origin_iter(other.base()) {}

        iter base() const
        {
            return _origin_iter;
        }
        
        reference operator*() const
        {
            iter tmp = _origin_iter;
            return (*(--tmp));
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[] (difference_type n) const
        {
            return *(_origin_iter - n - 1);
        }

		Reverse_iterator& operator++()
		{
			--_origin_iter;
			return *this;
		}

		Reverse_iterator operator++(int)
		{
			Reverse_iterator temp_riter = *this;
			++(*this);
			return temp_riter;	
		}

        Reverse_iterator operator+(difference_type n) const
        {
            return Reverse_iterator(_origin_iter - n);
        }

        Reverse_iterator& operator+=(difference_type n)
        {
            _origin_iter -= n;
            return *this;
        }

        Reverse_iterator& operator--()
        {
            ++_origin_iter;
            return *this;
        }

        Reverse_iterator operator--(int)
        {
            Reverse_iterator temp_riter = *this;
            --(*this);
            return temp_riter;
        }

        Reverse_iterator operator-(difference_type n) const
        {
            return Reverse_iterator(_origin_iter + n);
        }

        Reverse_iterator& operator-=(difference_type n)
        {
            _origin_iter += n;
            return *this;
        }
    };

    template <typename iter>
    bool operator== (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator== (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename iter>
    bool operator!= (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator!= (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename iter>
    bool operator< (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator< (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename iter>
    bool operator<= (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator<= (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename iter>
    bool operator> (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator> (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename iter>
    bool operator>= (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator>= (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename iter>
    Reverse_iterator<iter>
        operator+ (typename Reverse_iterator<iter>::difference_type n, const Reverse_iterator<iter>& x)
    {
	    return(x + n);
    }

    template <typename iter_L, typename iter_R>
    typename Reverse_iterator<iter_L>::difference_type
        operator- (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return(rhs.base() - lhs.base());
    }
}

#endif