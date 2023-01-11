#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // for allocator


namespace ft
{
    template<typename T, typename Alloc = std::allocator<T> >
    class vector
    {

    // 기본 제공 멤버 타입 들.
    public:
    // for iterator_trains
    typedef typename T value_type;
    typedef typename allocator allocator_type;
    typedef          std::size_t size_type;
    typedef          std::ptrdiff_t difference_type;
    typedef          value_type reference;
    typedef          const value_type const_reference;
    typedef          All

    // 외부로 부터 숨기는 맴버.
    private:


        // 생성자


    }
}


#endif