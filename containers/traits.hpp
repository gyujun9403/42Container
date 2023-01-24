#ifndef TRAITS_HPP
# define TRAITS_HPP

#include <cstddef>

namespace ft
{
    // 빈 클래스들.
    class Input_iterator_tag { };
    class Output_iterator_tag { };
    class Forward_iterator_tag : public Input_iterator_tag {};
    class Bidirectional_iterator_tag  : public Forward_iterator_tag { };
    class Random_access_iterator_tag : public Bidirectional_iterator_tag { };

    template <typename Iterator>
    class iterator_traits
    {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category	iterator_category;
    };

    // 특수화. 포인터인 경우
    template <typename T>
    class iterator_traits<T*>
    {
    public:
        typedef std::ptrdiff_t  difference_type;
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef	ft::Random_access_iterator_tag	iterator_category;
    };

    // 특수화. 상수 포인터인 경우.
    template <typename T>
    class iterator_traits<const T*>
    {
    public:
        typedef std::ptrdiff_t  difference_type;
        typedef const T         value_type;
        typedef const T*        pointer;
        typedef const T&        reference;
        typedef	ft::Random_access_iterator_tag	iterator_category;
    };

    // // bool값을 담는 클래스. 진짜 그냥 true/false를 담기 위해 사용.
    // template <bool is_valid, typename T>
    // struct valid_iterator_tag_res
    // {
    //     typedef T type; // TODO: 없어도 될듯?
    //     const static bool value = is_valid;
    // };

    // // 번용 탬플릿 -> 
    // template <typename T>
    // struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

    // template <>
    // struct is_input_iterator_tagged<ft::random_access_iterator_tag>
    //     : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    // template <>
    // struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
    //     : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    // template <>
    // struct is_input_iterator_tagged<ft::forward_iterator_tag>
    //     : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    // template <>
    // struct is_input_iterator_tagged<ft::input_iterator_tag>
    //     : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };


    // /*
    // ** @brief This will return a structure
    // ** that contain a boolean "value" true if the
    // ** iterator given is tagged with a ft iterator
    // ** tag, otherwise "value" is false.
    // */
    // template <typename T>
    //     struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    
    // /* Check is_ft_iterator_tagged from ft::random_access_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::bidirectional_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::forward_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::input_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::input_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::output_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::output_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

}


#endif