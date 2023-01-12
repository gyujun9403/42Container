#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // for allocator

#include "./random_access_iterator.hpp"

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
        typedef typename allocator::pointer pointer;
        typedef          std::size_t size_type;
        typedef          std::ptrdiff_t difference_type;

        typedef          value_type reference;
        typedef          const value_type const_reference;

        typedef          Random_access_iterator<value_type> iterator;
        typedef          const Random_access_iterator<value_type> const_iterator;

    // 외부로 부터 숨기는 맴버.
    private:
        allocator_type  _data_allocator; // 외부로 부터 받아온 할당기 *인스턴스*
        pointer         _start; // 원소 시작 위치
        pointer         _finish;   // 마지막 원소 위치
        pointer         _end_of_storage; // 실제 저장공간 마지막 위치.
    public:
        // 생성자
        /*
        default (1)	
            explicit vector (const allocator_type& alloc = allocator_type());
        fill (2)	
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        range (3)	
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
        copy (4)	
            vector (const vector& x);
        */
        explicit vector(const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _start(0), _finish(0), _end_of_storage(0)
        {
            // 디폴트 및 alloc만 넣었을 때 생성자.
            // 시작 및 끝 위치는 0(null), 크기를 표시할 포인터도 0 
        }

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc)
        {
            // 할당 크기 n만 들어오거나, val을 n개 채우는 경우.
            size_type val_size = sizeof(var);
            _start = _data_allocator.allocate(n);
            for (int i = 0; i < n; i++)
            {
                _start + (i * val_size) = val;
            }
            _finish = _start + (n * val_size);
            _end_of_storage = _finish;
        }

        // template <class InputIterator>
        // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
        // {

        // }

        // vector (const vector& x)
        // {
            
        // }
    };
}


#endif