#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "utils.hpp"
#include "traits.hpp"
#include "bidirectional_iterator_avl.hpp"
#include "reverse_iterator.hpp"
#include "avl_tree.hpp"

namespace ft
{
    // less -> 함수객체에 대한 공부 필요.
    template <typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    private:
        typedef typename ft::avl_tree<Key, T, Compare, Allocator> tree_type;
        //typedef typename tree_type* tree_pointer;
        typedef typename tree_type::node_pointer node_pointer;

    public:
    // for iterator_trains
        typedef Key key_type; //✅
        typedef T mapped_type; //✅
        typedef Compare key_compare; //✅
        typedef Allocator allocator_type; //✅, 
        //typedef typename tree_type::value_type value_type; //✅
        typedef typename ft::pair<const Key, T> value_type; //✅
        //typedef          value_type node_type; ❌
        //typedef typename tree_type::size_type size_type; //✅
        typedef typename std::size_t size_type; //✅
        //typedef typename tree_type::difference_type difference_type; //✅
        typedef typename std::ptrdiff_t difference_type; //✅
        typedef typename allocator_type::pointer pointer; //✅
        typedef typename allocator_type::const_pointer const_pointer; //✅
        typedef value_type& reference; //✅
        typedef const value_type& const_reference; //✅

        typedef typename tree_type::iterator iterator; //✅
        typedef typename tree_type::const_iterator const_iterator; //✅
		typedef typename tree_type::reverse_iterator reverse_iterator; //✅
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator; //✅

    private:
        // 사용법?
        // value_type : pair<key, value>
        // value_compare : key_compare를 이용하여 key()값을 비교하여, 
        //          value_type의 순서를 결정하는 함수객체 
        //friend class Bidirectional_iterator_avl;
		class value_compare //: ft::binary_function<value_type, value_type, bool>
        {
        protected:
            // 내부에 key값을 비교 하는 함수객체를 정의
			Compare _comp; // Compare -> ft::less<Key> : binary_function<Key, Key, bool>
        public:
            // bool result_type;
            // value_type first_argument_type;
            // value_type second_argument_type; 
		public:
				value_compare(Compare c)
                : _comp(c) {}

				bool operator()(const value_type& lhs, const value_type& rhs) const
                {
                    // 비교연산 수행시, 맴버인 함수객체를 이용하여 
                    // value_type(= ft::pair<const Key, T>)의 first끼리 비교 연산을 하게 함.
                    // Compare가 less인 경우,,,
					return (_comp(lhs.first, rhs.first)); 
				}
		};
        allocator_type _data_allocator;
        key_compare _comp;
        tree_type _tree;
    
    public:
        map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _comp(comp), _tree(comp, alloc) {}

        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
        : _data_allocator(alloc), _comp(comp), _tree(comp, alloc)
        {
            // bool is_valid;
            // if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
            //     throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
            this->insert(first, last);
        }
        ~map()
        {
            this->clear();
        }

        map& operator=(const map& other)
        {
            if (&other == this)
            {
                return this;
            }
            this->clear();
            this->insert(other.begin(), other.end());
        }

        // allocator_type get_allocator() const
        // {
        //     return 
        // }        

        //Element access
        T& at(const Key& key)
        {
            node_pointer node = _tree.find(key);
            if (node == NULL)
            {
                // exception
            }
            return iterator(node);
        }

        const T& at(const Key& key) const
        {
            node_pointer node = _tree.find(key);
            if (node == NULL)
            {
                // exception
            }
            return const_iterator(node);
        }

        T& operator[](const Key& key)
        {
            return _tree.find(key)->data.second;
        }
        //Iterators
        iterator begin()
        {
            return _tree.get_min_iter();
        }

        const_iterator begin() const
        {
            return const_iterator(_tree.get_min_iter());
        }

        iterator end()
        {
            return _tree.get_max_iter();
        }

        const_iterator end() const
        {
            return const_iterator(_tree.get_max_iter());
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(_tree.get_max_node());
        }

        // const_reverse_iterator rbegin() const
        // {
        //     return const_reverse_iterator(_tree.get_max_node());
        // }

        reverse_iterator rend()
        {
            return reverse_iterator(_tree.get_min_node());
        }

        // const_reverse_iterator rend() const
        // {
        //     return const_reverse_iterator(_tree.get_min_node());
        // }

        //Capacity
        bool empty() const
        {
            return _tree.empty();
        }

        size_type size() const
        {
            return _tree.size();
        }

        size_type max_size() const; // 최대 저장 가능 횟수...?
        //Modifiers
        void clear()
        {
            _tree.clear();
            return ;
        }

        ft::pair<iterator, bool> insert(const value_type& value)
        {
            bool rt_bool = false;
            node_pointer rt_ptr = _tree.insert(value.first, value.second);
            if (rt_ptr != NULL)
            {
                rt_bool = true;
            }
            return ft::make_pair<iterator, bool>(iterator(&(*rt_ptr)), rt_bool);
        }

        template< class InputIt >
        void insert(InputIt first, InputIt last)
        {
            while (first != last)
            {
                _tree.insert(first->first, first->second);
                first++;
            }
        }

        void erase(iterator pos)
        {
            _tree.erase((*pos)->data.first);
        }

        size_type erase(const Key& key)
        {
            _tree.erase(key);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                erase(first++);
            }
        }

        void swap(map& other)
        {
            _tree.swap(other._tree);
        }

        //Lookup
        size_type count(const Key& key) const //Returns the number of elements with key that compares equivalent to the specified argument.
        {
            if (_tree.find(key) == NULL)
            {
                return 0;
            }
            return 1;
        }

        iterator find(const Key& key)
        {
            return iterator(_tree.find(key));
        }

        const_iterator find(const Key& key) const
        {
            return const_iterator(_tree.find(key));
        }

        iterator lower_bound(const Key& key)
        {
            iterator begin = this->begin();
            iterator end = this->end();
            while (begin != end)
            {
                if (!_compare(*begin, key))
                {
                    return begin;
                }
                begin++;
            }
            return end;
        }

        const_iterator lower_bound(const Key& key) const
        {
            const_iterator begin = this->begin();
            const_iterator end = this->end();
            while (begin != end)
            {
                if (!_compare(*begin, key))
                {
                    return begin;
                }
                begin++;
            }
            return end;
        }

        iterator upper_bound(const Key& key)
        {
            iterator begin = this->begin();
            iterator end = this->end();
            while (begin != end)
            {
                if (_compare(*begin, key))
                {
                    return begin;
                }
                begin++;
            }
            return end;
        }

        const_iterator upper_bound(const Key& key) const
        {
            const_iterator begin = this->begin();
            const_iterator end = this->end();
            while (begin != end)
            {
                if (_compare(*begin, key))
                {
                    return begin;
                }
                begin++;
            }
            return end;
        }

        ft::pair<iterator,iterator> equal_range(const Key& key)
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }

        ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }

        //Observers
        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(key_compare());
        }
    };
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    // template <typename Key, typename T, typename Compare, typename Alloc>
    // bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
}

#endif