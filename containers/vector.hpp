#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "./random_access_iterator.hpp"
#include "./reverse_iterator.hpp"
#include "./utils.hpp"

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef Random_access_iterator<value_type> iterator;
        typedef Random_access_iterator<const value_type> const_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Reverse_iterator<iterator> reverse_iterator;

    private:
        allocator_type  _data_allocator;
        pointer         _start;
        pointer         _finish;
        size_type       _size;
        size_type       _capacity;

    public:
        explicit vector(const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _start(NULL), _finish(NULL), _size(0), _capacity(0) 
        {}

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _size(n), _capacity(n)
        {
            _start = _data_allocator.allocate(n);
            for (size_type i = 0; i < n; i++)
            {
                _data_allocator.construct(_start + i, val);
            }
            _finish = _start + n;
        }

        template <typename InputIt>
        explicit vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0)
        : _data_allocator(alloc)
        {
            difference_type n = ft::distance(first, last);
            _size = n;
            _capacity = _size;
            _start = _data_allocator.allocate(_capacity);
            _finish = _start;
            while (n--)
            {
                _data_allocator.construct(_finish, *(first++));
                _finish++;
            }
        }

        vector (const vector& x)
        : _data_allocator(x._data_allocator) , _start(NULL), _size(0), _capacity(0)
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
            return *this;
        }

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
            if(n < _size)
            {
                for (size_type i = n; i < _size ; i++)
                {
                    _data_allocator.destroy(_finish--);
                }
                _size = n;
            }
            else if (n > _size)
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
                for (size_type i = _size; i < n; i++)
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
            if (n > this->_capacity)
            {
                pointer new_start = _data_allocator.allocate(n);
                size_type new_size = this->_size;
                for (size_type i = 0; i < new_size; i++)
                {
                    this->_data_allocator.construct(new_start + i, *(this->_start + i));
                }
                this->clear();
                this->_data_allocator.deallocate(_start, _capacity);
                this->_start = new_start;
                this->_finish = new_start + new_size;
                this->_size = new_size;
                this->_capacity = n;
            }
        }

        reference operator[] (size_type n)
        {
            return *(_start + n);
        }

        const_reference operator[] (size_type n) const
        {
            return *(_start + n);
        }

        reference at (size_type n)
        {
            if (n >= this->size())
            {
                throw std::out_of_range("ft::at() out of range");
            }
            return *(_start + n);
        }

        const_reference at (size_type n) const
        {
            if (n >= this->size())
            {
                throw std::out_of_range("ft::at() const out of range");
            }
            return *(_start + n);
        }

        reference front ()
        {
            return *_start;
        }

        const_reference front () const
        {
            return *_start;
        }

        reference back ()
        {
            return *(_finish - 1);
        }

        const_reference back () const
        {
            return *(_finish - 1);
        }

        iterator begin()
        {
            return iterator(_start);
        }

        const_iterator begin() const
        {
            return const_iterator(_start);
        }

        iterator end()
        {
            return iterator(_start + _size);
        }

        const_iterator end() const
        {
            return const_iterator(_start + _size);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator (begin());
        }

        template <typename InputIt>
        void assign (InputIt first, InputIt last,
            typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0)
        {
            difference_type n = ft::distance(first, last);
            _size = n;
            this->clear();
            this->resize(n);
            while (n--)
            {
                _data_allocator.construct(_finish, *(first++));
                _finish++;
            }
        }

        void assign (size_type n, const value_type& val)
        {
			this->clear();
			if (n > _capacity)
            {
                this->resize(n);
			}
			for (size_type i = 0; i < n; i++)
            {
				_data_allocator.construct(_finish, val);
                _finish++;
            }
            _size = n;
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
            ++_finish;
		}

        void pop_back()
        {
			_data_allocator.destroy(_start + _size - 1);
			--_size;
            --_finish;
		}

        iterator insert (iterator position, const value_type& val)
        {
			size_type pos_len = static_cast<size_type>(position - begin());
            size_type left_len = _size - pos_len;

			if (_size == _capacity)
            {
                size_type new_capacity = _capacity * 2 + (_capacity == 0);
				pointer new_start = _data_allocator.allocate(new_capacity);
				for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
				_data_allocator.construct(new_start + pos_len, val);
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(new_start + pos_len + i + 1, *(_start + pos_len + i));
                }
                //this->clear();
                for (size_type i = 0; i < _size; i++)
                {
					_data_allocator.destroy(_start + i);
                }
                this->_data_allocator.deallocate(_start, _capacity);
				_start = new_start;
                _size += 1;
                _finish = _start + _size;
                _capacity = new_capacity;
			}
			else
            {
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(_finish - i, *(_finish - i - 1));
					_data_allocator.destroy(_finish - i - 1);
                }
				_data_allocator.construct(_start + pos_len, val);
				_size++;
                _finish++;
			}
			return iterator(_start + pos_len);
		}

        void insert (iterator position, size_type n, const value_type& val)
        {
			if (n == 0)
            {
				return ;
            }
			size_type pos_len = static_cast<size_type>(&(*position) - _start);
            size_type left_len = static_cast<size_type>(_finish - &(*position));
			if (_size + n > _capacity)
            {
				size_type new_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer new_start = _data_allocator.allocate(new_capacity);
                for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
				pointer temp_start = new_start + pos_len;
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(temp_start + i, val);
                }
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(temp_start + n + i, *(&(*position) + i));
                }
				for (size_type i = 0; i < _size; i++)
                {
					_data_allocator.destroy(_start + i);
                }
				_data_allocator.deallocate(_start, _capacity);
				_size += n;
				_capacity = new_capacity;
				_start = new_start;
                _finish = new_start + _size;
			}
			else
            {
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(_finish + n - i - 1, *(_finish - i - 1));
					_data_allocator.destroy(_finish - i - 1);
                }
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(&(*position) + i, val);
                }
				_size += n;
                _finish += n;
			}
		}


        template <typename InputIt>
        void insert (iterator position, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0)
        {
  			if (position < this->begin() || position > this->end())
            {
				return ;
            }
            size_type n = static_cast<size_type>(ft::distance(first, last));
			size_type pos_len = static_cast<size_type>(&(*position) - _start);
            size_type left_len = static_cast<size_type>(_finish - &(*position));
			if (_size + n > _capacity)
            {
				size_type new_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer new_start = _data_allocator.allocate(new_capacity);
                for (size_type i = 0; i < pos_len; i++)
                {
                    _data_allocator.construct(new_start + i, *(_start + i));
                }
				pointer temp_start = new_start + pos_len;
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(temp_start + i, *(first + i));
                }
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(temp_start + n + i, *(&(*position) + i));
                }
				for (size_type i = 0; i < _size; i++)
                {
					_data_allocator.destroy(_start + i);
                }
				_data_allocator.deallocate(_start, _capacity);
				_size += n;
				_capacity = new_capacity;
				_start = new_start;
                _finish = new_start + _size;
			}
			else
            {
                for (size_type i = 0; i < left_len; i++)
                {
                    _data_allocator.construct(_finish + n - i - 1, *(_finish - i - 1));
					_data_allocator.destroy(_finish - i - 1);
                }
                for (size_type i = 0; i < n; i++)
                {
                    _data_allocator.construct(&(*position) + i, *(first + i));
                }
				_size += n;
                _finish += n;
			}
		}

        iterator erase (iterator position)
        {
            size_type left_len = _finish - &(*position);
            _data_allocator.destroy(&(*position));
            for (size_type i = 0; i < left_len - 1 ; i++)
            {
                _data_allocator.construct(&(*position) + i, *(&(*position) + i + 1));
                _data_allocator.destroy(&(*position) + i + 1);
            }
            --_size;
            --_finish;
            return &(*position);
		}


        iterator erase (iterator first, iterator last)
        {
            size_type n = last - first;
            size_type left_len = _size - n;
            for (size_type i = 0; i < n; i++)
            {
                _data_allocator.destroy(&(*first) + i);
            }
            for (size_type i = 0; i < left_len; i++)
            {
                _data_allocator.construct(&(*first) + i, *(&(*last) + i));
                _data_allocator.destroy(&(*last) + i);
            }
            _size -= n;
            _finish = _start + _size;
            return &(*first);
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
            x._size = temp_size;
			
            temp_size = _capacity;
            _capacity = x._capacity;
            x._size = temp_size;

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
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <typename T, typename Alloc >
	bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
		return !(rhs < lhs);
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