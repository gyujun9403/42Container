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
        typedef          T value_type;
        typedef          Alloc allocator_type;
        typedef typename allocator_type::pointer pointer;
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
        
// 생성자
    public:
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
            size_type val_size = sizeof(val);
            _start = _data_allocator.allocate(n);
            for (size_type i = 0; i < n; i++)
            {
                _data_allocator.construct(_start + (i * val_size), val);
                //_start + (i * val_size) = val;
            }
            _finish = _start + (n * val_size);
            _end_of_storage = _finish;
        }

        // 이건 enable_if를 쓰니 그거 참고하기.
        // template <class InputIterator>
        // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
        // {

        // }

        // vector (const vector& x)
        // {
            
        // }
        ~vector()
        {
            this->clear();
            _alloc.deallocate(_start, this->capacity());
        }

// 제공 함수들
/*
Iterators:
    begin	Return iterator to beginning (public member function)
    end	Return iterator to end (public member function)
    rbegin	Return reverse iterator to reverse beginning (public member function)
    rend	Return reverse iterator to reverse end (public member function)
    cbegin	Return const_iterator to beginning (public member function)
    cend	Return const_iterator to end (public member function)
    crbegin	Return const_reverse_iterator to reverse beginning (public member function)
    crend	Return const_reverse_iterator to reverse end (public member function)

Capacity:
    size	Return size (public member function)
    max_size	Return maximum size (public member function)
    resize	Change size (public member function)
    capacity	Return size of allocated storage capacity (public member function)
    empty	Test whether vector is empty (public member function)
    reserve	Request a change in capacity (public member function)
    shrink_to_fit	Shrink to fit (public member function)

Element access:
    operator[]	Access element (public member function)
    at	Access element (public member function)
    front	Access first element (public member function)
    back	Access last element (public member function)
    data	Access data (public member function)

Modifiers:
    assign	Assign vector content (public member function)
    push_back	Add element at the end (public member function)
    pop_back	Delete last element (public member function)
    insert	Insert elements (public member function)
    erase	Erase elements (public member function)
    swap	Swap content (public member function)
    clear	Clear content (public member function)
    emplace	Construct and insert element (public member function)
    emplace_back	Construct and insert element at the end (public member function)

Allocator:
    get_allocator	Get allocator (public member function)
*/
        void clear()
        {
            size_type data_size = _finish - _start;
            size_type val_size = sizeof(value_type);
            for (size_type i = 0; i < data_size; i++)
            {
                _alloc.destroy(_start + i * val_size);
            }
            _finish = _start;
        }

        /*************[Capacity]*************/
        size_type size(void) const
        {
            return (this->_end - this->_start);
        }

        size_type max_size(void) const
        {
            return allocator_type().max_size();
        }

        void resize(size_type n, value_type val = value_type())
        {
            if(n < _size)
            {
                for(size_type i = n; i < _size; i++)
                    _allocator.destroy(_first + i);
                _size = n;
            }
            else if (n > _size)
            {
                if (_capacity < n)
                    this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
                for (size_type i = _size; i < n; i++){
                    _allocator.construct(_first + i, val);
                    _size++;
                }
            }
        }

        size_type   capacity (void) const
        {
            return (this->_end_capacity - this->_start);
        }
        size_type   capacity (void) const
        {
            return (this->_end_capacity - this->_start);
        }
        bool empty (void) const
        {
            return (size() == 0 ? true : false);
        }
        void reserve (size_type n)
        {
            if (n > this->max_size())
                throw (std::length_error("vector::reserve"));
            else if (n > this->capacity())
            {
                pointer prev_start = _start;
                pointer prev_end = _end;
                size_type prev_size = this->size();
                size_type prev_capacity = this->capacity();
                
                _start = _alloc.allocate( n );
                _end_capacity = _start + n;
                _end = _start;
                while (prev_start != prev_end)
                {
                    _alloc.construct(_end, *prev_start);
                    _end++;
                    prev_start++;
                }
                _alloc.deallocate(prev_start - prev_size, prev_capacity);
            }
        }
    };
}


#endif