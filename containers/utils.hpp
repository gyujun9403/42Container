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

    // is_integral -> int로 처리할 수 있는지 확인.
    // 아래 탬플릿들에서 안걸리는 경우, ft::integral_constant<bool, false>형을 상속받는 구조체 정의.
    template <typename T>
    struct is_integral : public ft::integral_constant<bool, false> {}; // T대신 bool쓰면 에러남.
    // 탬플릿 특수화를 하여 bool, char, ... 등
    // int로 쓸 수 있는것들이 탬플릿으로 들어온 경우 
    // ft::integral_constant<bool, true>를 상속받는 구조체 정의
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