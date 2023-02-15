#ifndef UTILLS_HPP
# define UTILLS_HPP

#include "traits.hpp"

namespace ft
{
    // v값에 따라 서로 다른 구조체를 만들어주는 탬플릿
    // 여기서는 
    template<typename T, bool v>
	struct integral_constant
    {
		static const bool value = v;
		typedef bool value_type;
		typedef integral_constant type;
		operator value_type() const
        {
            return value;
        }
	};

    template <typename T>
    struct is_integral : public ft::integral_constant<bool, false> {};
    template <>
    struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<short> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned short> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<int> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<long long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};

    template<bool B, typename T = void>
	struct enable_if {typedef T nope;};

    template<typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template<typename T>
    struct remove_const
    {
        typedef T type;
    };

    template<typename T>
    struct remove_const <const T>
    {
        typedef T type;
    };
    
    /*
    ** @brief Give a difference_type defined in ft::iterator_traits
    ** that's the difference of address in memory
    ** between last and first iterator.
    **
    ** @param first The first iterator.
    ** @param last The last iterator.
    ** @return The difference.
    */
    template<class InputIterator>
        typename ft::iterator_traits<InputIterator>::difference_type
            distance (InputIterator first, InputIterator last)
        {
            typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
            while (first != last)
            {
                first++;
                rtn++;
            }
            return (rtn);
        }

    /*
    ** Base class for standard binary function objects.
    ** (Doc = http://www.cplusplus.com/reference/functional/binary_function/?kw=binary_function)
    ** It have no operator "()" like functin objects, 
    ** it is up to the class deriving from it to define it.
    ** It just has 3 public data memebers that are typedefs of the
    ** template parameters.
    ** (the operator "()", permet to use a class with the same syntax
    ** as a function call).
    */
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    /*
    ** A binary function object class who will return
    ** whether the first arguement compares less than the second.
    ** (using "<" operator).
    */
    template <typename T>
    struct less : binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };


    /* Lexicographical comparison */

    /*
    ** @brief Return true if the range [first1, last2) compare
    ** lexicographically lest than the range [first2, last2).
    **
    ** @param first1, last1 the start and the end of the first range.
    ** @param first2, last2 the start and the end of the second range.
    ** @return true if the first range compares lexicographically less
    ** than the second, false otherwise.
    */
    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) return false;
                else if (*first1 < *first2) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }

    /*
    ** @brief Return true if the range [first1, last2) compare
    ** lexicographically lest than the range [first2, last2).
    ** The comparision is effectued by "comp".
    **
    ** @param first1, last1 the start and the end of the first range.
    ** @param first2, last2 the start and the end of the second range.
    ** @param comp the function that will compare.
    ** @return true if the first range compares lexicographically less
    ** than the second, false otherwise.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2,
                                        Compare comp)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || comp(*first2, *first1)) return false;
                else if (comp(*first1, *first2)) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }

    long long max(long long a, long long b)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    long long min(long long a, long long b)
    {
        if (a > b)
        {
            return b;
        }
        else
        {
            return a;
        }
    }
}

#endif