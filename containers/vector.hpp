#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // for allocator
#include <stdexcept> //for exception


#include "./random_access_iterator.hpp"
#include "./reverse_iterator.hpp"

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
        typedef          Reverse_iterator<const_iterator> const_reverse_iterator;
		typedef          Reverse_iterator<iterator> reverse_iterator;

    // 외부로 부터 숨기는 맴버.
    //private:
        allocator_type  _data_allocator; // 외부로 부터 받아온 할당기 *인스턴스*
        pointer         _start; // 원소 시작 위치. T*
        pointer         _finish;   // 마지막 원소 위치 + 1, T*
        //pointer         _end_of_storage; // 실제 저장공간 마지막 위치.
        size_type       _size;
        size_type       _capacity;
        
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
        : _data_allocator(alloc), _start(0), _finish(0), _size(0), _capacity(0) //_end_of_storage(0), 
        {
            // 디폴트 및 alloc만 넣었을 때 생성자.
            // 시작 및 끝 위치는 0(null), 크기를 표시할 포인터도 0 
        }

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _size(n), _capacity(n)
        {
            // 할당 크기 n만 들어오거나, val을 n개 채우는 경우.
            size_type val_size = sizeof(val);
            _start = _data_allocator.allocate(n);
            for (size_type i = 0; i < n; i++)
            {

                _data_allocator.construct(_start + i, val);
                //_start + (i * val_size) = val;
            }
            _finish = _start + n;
            //_end_of_storage = _finish;
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
            _data_allocator.deallocate(_start, this->capacity());
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

        /*************[Capacity]*************/
        size_type size(void) const
        {
            return this->_size;
        }

        size_type max_size(void) const
        {
            return allocator_type().max_size();
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n > this->max_size())
            {
                throw (std::length_error("vector::resize"));
            }
            else if(n < this->_size)
            {
                for (size_type i = n; i < this->_size ; i++)
                {
                    _data_allocator.destroy(--_finish);
                }
                _size = n;
            }
            else if (n > this->size())
            {
                if (this->_capacity < n)
                {
                    if (n > 2 * (this->_capacity))
                    {
                        this->reserve(n);
                    }
                    else
                    {
                        this->reserve(2 * _capacity);
                    }
                }
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(this->_start + i, val);
                }
                _size = n;
            }
        }

        size_type capacity (void)
        {
            return this->_capacity;
        }

        size_type capacity (void) const
        {
            return this->_capacity;
        }

        bool empty (void) const
        {
            if (this->_size == 0)
            {
                return true;
            }
            return false;
        }

        void reserve (size_type n)
        {
            if (n > this->max_size())
            {
                throw (std::length_error("vector::reserve"));
            }
            else if (n > this->_capacity)
            {
                // pointer prev_start = _start;
                // pointer prev_end = _end;
                // size_type prev_size = this->size();
                // size_type prev_capacity = this->capacity();
                
                pointer new_start = _data_allocator.allocate(n);
                size_type new_size = this->_size;
                //_end_capacity = _start + n;
                //_end = _start;
                for (int i = 0; i < new_size; i++)
                {
                    this->_data_allocator.construct(new_start + i, *this->_start);
                }
                this->clear();
                this->_start = new_start;
                this->_finish = new_start + new_size;
                //this->_end_of_storage = new_finish + new_capacity;
                this->_size = new_size;
                this->_capacity = n;
                //_alloc.deallocate(prev_start - prev_size, prev_capacity);
            }
        }

        /*************[access]*************/
        reference operator[] (size_type n)
        {
            return (*(_start + n));
        }

        const_reference operator[] (size_type n) const
        {
            return (*(_start + n));
        }

        reference at (size_type n)
        {
            if (n >= this->size())
            {
                throw std::out_of_range("ft::at() out of range");
            }
            return (*(_start + n));
        }

        const_reference at (size_type n) const
        {
            if (n >= this->size())
            {
                throw std::out_of_range("ft::at() const out of range");
            }
            return (*(_start + n));
        }

        reference front ()
        {
            return (*_start);
        }

        const_reference front () const
        {
            return (*_start);
        }

        reference back ()
        {
            return (*(_finish - 1));
        }

        const_reference back () const
        {
            return (*(_finish - 1));
        }

        /*************[iterator]*************/
        iterator begin()
        {
            return (iterator(_first)); // 반복자(임의접근)에 주소를 담음
            // ->
        }

        const_iterator begin()
        {
            return (const_iterator(_first));
        }

        iterator end()
        {
            return (iterator(_first + _size));
        }

        const_iterator end()
        {
            return (const_iterator(_first + _size));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin()
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend()
        {
            return (const_reverse_iterator (begin()));
        }

        /*************[modifiers]*************/
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
         typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
				if(first > last)
					throw std::logic_error("vector");
				difference_type count = last - first;
				clear();
				if (count > static_cast<difference_type>(capacity())){
					_allocator.deallocate(_first, _capacity);
					_first = _allocator.allocate(count);
					_capacity = count;
				}
				iterator pos = begin();
				while (first < last)
				{
					_allocator.construct(&(*pos), *first);
					pos++;
					first++;
				}
				_size = count;
			}
        void assign (size_type n, const value_type& val)
        {
			clear();
			if (n > _capacity){
				_allocator.deallocate(_first, _capacity);
				_first = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				_allocator.construct(_first + i, val);
			_size = n;
		}

        void push_back (const value_type& val)
        {
			if(_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			_allocator.construct(_first + _size, val);
			_size++;
		}

        void pop_back()
        {
			_allocator.destroy(_first + _size - 1);
			_size--;
		}

        iterator insert (iterator position, const value_type& val)
        {
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			difference_type start = position - begin();
			if (_size == _capacity){
				_capacity = _capacity * 2 + (_capacity == 0);
				pointer new_arr = _allocator.allocate(_capacity);
				std::uninitialized_copy(begin(), position, iterator(new_arr));
				_allocator.construct(new_arr + start, val);
				std::uninitialized_copy(position, end(), iterator(new_arr + start + 1));
				for (size_t i = 0; i < _size; i++)
					_allocator.destroy(_first + i);
				if(_size)
					_allocator.deallocate(_first, _size);
				_size++;
				_first = new_arr;
			}
			else {
				for (size_type i = _size; i > static_cast<size_type>(start); i--){
					_allocator.destroy(_first + i);
					_allocator.construct(_first + i, *(_first + i - 1));
				}
				_allocator.destroy(&(*position));
				_allocator.construct(&(*position), val);
				_size++;
			}
			return (begin() + start);
		}

        void insert (iterator position, size_type n, const value_type& val)
        {
			if (n == 0)
				return ;
			else if (max_size() - _size < n)
				throw std::length_error("vector");
			difference_type start = position - begin();
			if (_size + n > _capacity){
				size_type new_cap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer new_arr = _allocator.allocate(new_cap);
				std::uninitialized_copy(begin(), position, iterator(new_arr));
				for (size_type i = 0; i < n; i++)
					_allocator.construct(new_arr + start + i, val);
				std::uninitialized_copy(position, end(), iterator(new_arr + start + n));
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_first + i);
				_allocator.deallocate(_first, _capacity);
				_size += n;
				_capacity = new_cap;
				_first = new_arr;
			}
			else {
				for (size_type i = _size; i > static_cast<size_type>(start); i--) {
					_allocator.destroy(_first + i + n - 1);
					_allocator.construct(_first + i + n - 1, *(_first + i - 1));
				}
				for (size_type i = 0; i < n; i++){
					_allocator.destroy(_first + i + start);
					_allocator.construct(_first + i + start, val);
				}
				_size += n;
			}
		}


        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {

				if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");
			size_type start = static_cast<size_type>(position - begin());
			size_type count = static_cast<size_type>(last - first);
			if (_size + count > _capacity) {
				size_type new_cap = _capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
				pointer new_arr = _allocator.allocate(new_cap);
				std::uninitialized_copy(begin(), position, iterator(new_arr));
				try {
					for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
						_allocator.construct(new_arr + start + i, *first);
				}
				catch (...){
					for (size_type i = 0; i < count + start; ++i)
						_allocator.destroy(new_arr + i);
					_allocator.deallocate(new_arr, new_cap);
					throw;
				}
				std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_first + i);
				_allocator.deallocate(_first, _capacity);
				_size += count;
				_capacity = new_cap;
				_first = new_arr;
			}
			else {
				for (size_type i = _size; i > static_cast<size_type>(start); i--) {
					_allocator.destroy(_first + i + count - 1);
					_allocator.construct(_first + i + count - 1, *(_first + i - 1));
				}
				for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
					_allocator.destroy(_first + i + count);
					_allocator.construct(_first + start + i, *first);
				}
				_size += count;
			}
		}

        iterator erase (iterator position)
        {
			size_type d = static_cast<size_type>(std::distance(begin(), position));
			for (size_type i = d; i < _size - 1; ++i){
				_allocator.destroy(_first + i);
				_allocator.construct(_first + i, *(_first + i + 1));
			}
			_size--;
			_allocator.destroy(_first + _size - 1);
			return iterator(_first + d);
		}


        iterator erase (iterator first, iterator last)
        {
			difference_type start = std::distance(begin(), first);
			difference_type need_to_copy = std::distance(last, end());
			bool last_is_end = (last == end());
			while (first != last){
				_allocator.destroy(&(*first));
				first++;
			}
			size_type i = start;
			while (last < end()){
				if (this->_first + start)
					_allocator.destroy(_first + i);
				_allocator.construct(_first + i, *last);
				i++;
				last++;
			}
			for (size_type i = start + need_to_copy; i < _size; i++)
				_allocator.destroy(_first + i);
			_size = start + need_to_copy;
			return last_is_end ? end() : iterator(_first + start);
		}

        void swap (vector& x)
        {
			std::swap(_first, x._first);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_allocator, x._allocator);

		}

        void clear()
        {
            for (size_type i = 0; i < _size; i++)
            {
                _data_allocator.destroy(_start + i);
            }
            _finish = _start;
            _size = 0;
        }
    };
}


#endif