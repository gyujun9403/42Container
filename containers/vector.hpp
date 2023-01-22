#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory> // for allocator
#include <stdexcept> //for exception


#include "./random_access_iterator.hpp"
#include "./reverse_iterator.hpp"
#include "../utils/utils.hpp"

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

        // fill
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
        // range
        template <typename InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
        : _data_allocator(alloc)
        {
            // if the range specified by [first,last) is not valid, it causes undefined behavior.
            _size = last - first;
            _capacity = _size;
            _start = _data_allocator.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
            {
                _data_allocator.construct(_start + i, *(first + i));
            }
        }

        vector (const vector& x)
        : _size(0), _capacity(0), _data_allocator(x._data_allocator)
        {
            operator=(x);
        }

        ~vector()
        {
            this->clear();
            _data_allocator.deallocate(_start, this->capacity());
        }

        vector& operator= (const vector& x)
        {
            if (*this == x)
            {
                return *this;
            }
            this->clear();
            if (_capacity < x._size)
            {
                if (_capacity != 0)
                {
                    _data_allocator.deallocate(_start, _capacity);
                }
                _start = _data_allocator.allocate(x._size);
            }
            for (size_type i = 0; i < x._size; i++)
            {
                _data_allocator.construct(_start + i, *(x._start + i));
            }
            _size = x._size;
            _capacity = _size;
            _finish = _start + _size;
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
                this->clear(); // 이전꺼 남아 있어서 leak발생!
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
            return (iterator(_start)); // 반복자(임의접근)에 주소를 담음
            // ->
        }

        const_iterator begin() const
        {
            return (const_iterator(_start));
        }

        iterator end()
        {
            return (iterator(_start + _size));
        }

        const_iterator end() const
        {
            return (const_iterator(_start + _size));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator (begin()));
        }

        /*************[modifiers]*************/
        template <typename InputIterator>
        void assign (InputIterator first, InputIterator last,
            typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            if(first > last)
            {
                throw std::logic_error("vector"); // TODO
            }
            size_type size = static_cast<size_type>(last - first);
            this->clear();
            this->resize(size);
            for (size_type i = 0; i < size; i++)
            {
                _data_allocator.construct(_start + i, *first);
            }
        }

        void assign (size_type n, const value_type& val)
        {
			clear();
			if (n > _capacity)
            {
                this->resize(n);
			}
			for (size_type i = 0; i < n; i++)
            {
				_data_allocator.construct(_start + i, val);
            }

		}

        void push_back (const value_type& val)
        {
			if(_size == _capacity)
            {
                if (_capacity == 0)
                {
                    reserve(1);
                }
                else
                {
				    reserve(_capacity * 2);
                }
            }
			_data_allocator.construct(_start + _size, val);
			++_size;
		}

        void pop_back()
        {
			_data_allocator.destroy(_start + _size - 1);
			--_size;
		}

        iterator insert (iterator position, const value_type& val)
        {
			if (position < begin() || position > end())
            {
				throw std::logic_error("vector"); // TODO
            }
			size_type pos_len = static_cast<size_type>(position - begin());
            size_type target_len = _size + 1;
            // 꽉 차있을때
			if (_size == _capacity)
            {
				_capacity = _capacity * 2 + (_capacity == 0);
                // 새 공간
				pointer new_start = _data_allocator.allocate(_capacity);
                // 삽입 직전가지 복사
				for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
                // 삽입자리에 생성
				_data_allocator.construct(new_start + _start, val);
                // 삽입 뒤에  복사
                for (size_type i = pos_len; i + 1 < target_len; i++)
                {
                    _data_allocator.construct(new_start + i + 1, *(_start + i));
                }
                this->clear(); // 이전꺼 남아 있어서 leak발생!
				_start = new_start;
                _size = target_len;
                _finish = _start + _size;
                _capacity = target_len;
			}
			else
            {
                // 맨 뒤에서부터
				for (size_type i = _size; i > pos_len; i--)
                {
                    _data_allocator.construct(_start + i + 1, *(_start + 1));
                    _data_allocator.destroy(_start + i);
					// _data_allocator.destroy(_start + i);
					// _data_allocator.construct(_start + i, *(_start + i - 1));
				}
				//_data_allocator.destroy(&(*position));
				_data_allocator.construct(_start + pos_len, val);
				_size++;
                _finish++;
			}
			return (iterator(_start + pos_len));
		}

        void insert (iterator position, size_type n, const value_type& val)
        {
			if (n == 0)
            {
				return ; // TODO
            }
			else if (max_size() - _size < n)
            {
				throw std::length_error("vector"); // TODO
            }
			size_type pos_len = static_cast<size_type>(position - _start);
            size_type left_len = static_cast<size_type>(_finish - position);
            // 새 공간 할당해야할 때
			if (_size + n > _capacity)
            {
				size_type new_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer new_start = _data_allocator.allocate(new_capacity);
                // 시작부터 할당 전까지
                for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
                // 삽입할거
				pointer temp_start = new_start + pos_len;
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(temp_start + i, val);
                }
                // 이후 
                for (int i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(temp_start + position + i, *(_start + position + i));
                }
				for (size_type i = 0; i < _size; i++)
                {
					_data_allocator.destroy(_start + i);
                }
				_data_allocator.deallocate(_start, _capacity);
				_size += n;
				_capacity = new_capacity;
				_start = new_start;
                _finish = new_start + size;
			}
            // 공간할당 필요 없음
			else
            {
                // 맨 끝부분 부터 넣어야함.
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(_finish + n + i, *(position + n + i));
                    _data_allocator.destroy(position + n + i);
                }
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(position + i, val);
                }
				_size += n;
                _finish += n;
			}
		}


        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {

			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");
			size_type pos_len = static_cast<size_type>(position - begin());
            size_type n = static_cast<size_type>(last - first);
			size_type left_len = _size - pos_len;
			if (_size + n > _capacity)
            {
				size_type new_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer new_start = _data_allocator.allocate(new_capacity);
                for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
                // try catch???
                for (size_type i = 0; i < n; i)
                {
                    _data_allocator.construct(new_start + pos_len + i, *(_start + i));
                }
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(new_start + pos_len + n + i, *(new_start + pos_len + i));
                }
				for (size_type i = 0; i < _size; i++)
                {
					_data_allocator.destroy(_start + i);
                }
				_data_allocator.deallocate(_start, _capacity);
				_size += n;
				_capacity = new_capacity;
				_start = new_start;
			}
			else
            {
				for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(_finish + i, *(position + i));
					_data_allocator.destroy(position + i);
				}
				for (size_type i = 0; i < n; i++)
                {
					_data_allocator.construct(position + i, first + i);
				}
				_size += n;
                _finish += n;
			}
		}

        iterator erase (iterator position)
        {
            size_type left_len = _finish - position;
            _data_allocator.destroy(position);
            for (size_type i = 0; i < left_len - 1 ; i++)
            {
                _data_allocator.construct(position + i, *(position + i + 1));
                _data_allocator.destroy(position + i + 1);
            }
            --_size;
            --_finish;
		}


        iterator erase (iterator first, iterator last)
        {
            size_type n = last - first;
            size_type left_len = _size - n;
            for (size_type i = 0; i < n; i++)
            {
                _data_allocator.destroy(first + i);
            }
            for (size_type i = 0; i < left_len; i++)
            {
                _data_allocator.construct(first + i, *(last + i));
                _data_allocator.destroy(last + i);
            }
            //_data_allocator.destroy(_finish);
            --_size;
            --_finish;
		}

        void swap (vector& x)
        {
            size_type temp_size;
            pointer temp_point;
            allocator_type temp_allocator;

            temp_point = _start;
            _start = x._start;
            x._start = temp_point;

            temp_point = _finish;
            _finish = x._finish;
            x._finish = temp_point;
			
            temp_size = _size;
            _size = x._size;
            x.size = temp_size;
			
            temp_size = _capacity;
            _capacity = x._capacity;
            x.size = temp_size;

            temp_allocator = _data_allocator;
            _data_allocator = x._data_allocator;
            x._data_allocator = temp_allocator;
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
    
    template <typename T, typename Alloc>
	bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		if (lhs.size() != rhs.size())
        {
			return false;
        }
		for (size_t i = 0; i < rhs.size(); i++)
        {
			if (lhs[i] != rhs[i])
            {
				return false;
            }
        }
		return true;
	}

	template <typename T, typename Alloc>
	bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		return !(lhs == rhs);
	}

	template <typename T, typename Alloc>
	bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        if (lhs.size() < rhs.size())
        {
			return true;
        }
        else if (lhs.size() > rhs.size())
        {
            return false;
        }
		for (size_t i = 0; i < rhs.size(); i++)
        {
			if (lhs[i] != rhs[i])
            {
                if (lhs[i] < rhs[i])
                {
                    return true;
                }
				return false;
            }
        }
		return false;
	}
	
	template <typename T, typename Alloc >
	bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		return !(lhs > rhs);
	}
	
	template <typename T, typename Alloc >
	bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		return rhs < lhs;
	}

	template <typename T, typename Alloc >
	bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		return !(lhs < rhs);
	}

}


#endif