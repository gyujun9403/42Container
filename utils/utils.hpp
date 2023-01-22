#ifndef UTILLS_HPP
# define UTILLS_HPP

namespace ft
{
    // v값에 따라 서로 다른 구조체를 만들어주는 탬플릿
    // 여기서는 
    template<typename T, T v>
	struct integral_constant
    {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const
        {
            return value;
        }
	};

    // is_integral -> int로 처리할 수 있는지 확인.
    // 아래 탬플릿들에서 안걸리는 경우, ft::integral_constant<bool, false>형을 상속받는 구조체 정의.
    template <typename T>
    struct is_integral : public ft::integral_constant<T, false> {}; // T대신 bool쓰면 에러남.
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
    struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
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

}

#endif