#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "./base_iterator.hpp"
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
        // 생성자
        Reverse_iterator() {}
        // 인자 : 반복자.
        explicit Reverse_iterator(iter x)
        : _origin_iter(x) {}
        // 복사생성자
        template<class T>
        Reverse_iterator(const Reverse_iterator<T>& x)
        : _origin_iter(x.base()) {}

        iter base() const
        {
            return _origin_iter;
        }
        
        reference operator*() const
        {
            // //iter temp_iter = _origin_iter;
            // return (*(_origin_iter - 1));
            iter tmp = _origin_iter;
            return *(--tmp);
        }

        pointer operator->() const
        {
            //iter temp_iter = _origin_iter;
            return _origin_iter - 1;
        }

        reference operator[] (difference_type n) const
        {
            return _origin_iter - n - 1;
        }

		Reverse_iterator& operator++()
		{
			--_origin_iter;
			return *this;
		}

		Reverse_iterator operator++(int) // 복사본을 던져주므로 레퍼런스 아님.
		{
			Reverse_iterator temp_riter = *this;
			--_origin_iter;
			return temp_riter;	
		}

        Reverse_iterator operator+(difference_type n) const
        {
            // 생성자를 이용.
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
            ++_origin_iter;
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
        return (lhs.base() < rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator< (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename iter>
    bool operator<= (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator<= (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename iter>
    bool operator> (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator> (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename iter>
    bool operator>= (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename iter_L, typename iter_R>
    bool operator>= (const Reverse_iterator<iter_L>& lhs, const Reverse_iterator<iter_R>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename iter>
    Reverse_iterator<iter> operator+ 
        (typename Reverse_iterator<iter>::difference_type n, const Reverse_iterator<iter>& x)
    {
	    return(x + n);
    }

    template <typename iter>
    typename Reverse_iterator<iter>::difference_type operator- 
        (const Reverse_iterator<iter>& lhs, const Reverse_iterator<iter>& rhs)
    {
        return(lhs.base() - rhs.base());
    }
}

#endif