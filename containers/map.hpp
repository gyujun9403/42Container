#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "utils.hpp"
#include "traits.hpp"
#include "avl_iterator.hpp"
#include "reverse_iterator.hpp"
#include "avl_tree.hpp"

namespace ft
{
    template <typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    private:
        typedef typename ft::avl_tree<Key, T, Compare, Allocator> tree_type;
        typedef typename tree_type::node_pointer node_pointer;

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename ft::pair<const Key, T> value_type;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
		typedef typename tree_type::reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

    private:
		class value_compare
        {
        protected:
            Compare _comp;
		public:
            value_compare(Compare c)
            : _comp(c) {}

            bool operator()(const value_type& lhs, const value_type& rhs) const
            {
                return (_comp(lhs.first, rhs.first));
            }
		};
        allocator_type _data_allocator;
        key_compare _comp;
        tree_type _tree;
    
    public:
        map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : _data_allocator(alloc), _comp(comp), _tree(comp, alloc)
        {}

        template <typename InputIt>
        map(InputIt first, InputIt last,
            const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
        : _data_allocator(alloc), _comp(comp), _tree(comp, alloc)
        {
            this->insert(first, last);
        }

        map(const map& other)
        : _data_allocator(other._data_allocator), _comp(other._comp), _tree(other._tree)
        {
            this->insert(other.begin(), other.end());
        }

        ~map()
        {
            this->clear();
        }

        map& operator=(const map& other)
        {
            if (&other == this)
            {
                return *this;
            }
            this->clear();
            this->insert(other.begin(), other.end());
            return *this;
        }

        mapped_type& at(const Key& key)
        {
            node_pointer node = _tree.find(key);
            if (node == NULL)
            {
                // exception
            }
            return iterator(node);
        }

        const mapped_type& at(const Key& key) const
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
            node_pointer rt = _tree.find(key);
            if (rt == NULL)
            {
                this->insert(ft::make_pair(key, mapped_type()));
                rt = _tree.find(key);
            }
            return (rt->data.second);
        }

        iterator begin()
        {
            return _tree.get_min_iter();
        }

        const_iterator begin() const
        {
            return _tree.get_min_cosnt_iter();
        }

        iterator end()
        {
            return _tree.get_end_iter();
        }

        const_iterator end() const
        {
            return _tree.get_end_const_iter();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(_tree.get_end_iter());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(_tree.get_min_node());
        }

        bool empty() const
        {
            return _tree.empty();
        }

        size_type size() const
        {
            return _tree.size();
        }

        size_type max_size() const
        {
            return _tree.max_size();
        }

        void clear()
        {
            _tree.clear();
            return ;
        }

        ft::pair<iterator, bool> insert(const value_type& value)
        {
            bool rt_bool = false;
            node_pointer rt_ptr = _tree.find(value.first);
            if (rt_ptr == NULL)
            {
                rt_ptr = _tree.insert(value.first, value.second);
                rt_bool = true;
            }
            return ft::make_pair<iterator, bool>(iterator(&(*rt_ptr)), rt_bool);
        }


        iterator insert (iterator position, const value_type& value)
        {
            (void)position;
            node_pointer rt_ptr = _tree.find(value.first);
            if (rt_ptr == NULL)
            {
                rt_ptr = _tree.insert(value.first, value.second);
            }
            return iterator(&(*rt_ptr));
        }

        template<typename InputIt >
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
            _tree.erase(pos->first);
        }

        size_type erase(const Key& key)
        {
            return _tree.erase(key);
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

        size_type count(const Key& key) const
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
                if (_comp(begin->first, key) == false)
                {
                    break ;
                }
                begin++;
            }
            return begin;
        }

        const_iterator lower_bound(const Key& key) const
        {
            const_iterator begin = this->begin();
            const_iterator end = this->end();
            while (begin != end)
            {
                if (_comp(begin->first, key) == false)
                {
                    break ;
                }
                begin++;
            }
            return begin;
        }

        iterator upper_bound(const Key& key)
        {
            iterator begin = this->begin();
            iterator end = this->end();
            while (begin != end)
            {
                if (_comp(key, begin->first))
                {
                    return begin;
                }
                begin++;
            }
            return begin;
        }

        const_iterator upper_bound(const Key& key) const
        {
            const_iterator begin = this->begin();
            const_iterator end = this->end();
            while (begin != end)
            {
                if (_comp(key, begin->first))
                {
                    return begin;
                }
                begin++;
            }
            return begin;
        }

        ft::pair<iterator,iterator> equal_range(const Key& key)
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }

        ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }

        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(key_compare());
        }
    };

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        if (lhs.size() == rhs.size())
        {
            typename ft::map<Key,T,Compare,Alloc>::const_iterator lit = lhs.begin();
            typename ft::map<Key,T,Compare,Alloc>::const_iterator leit = lhs.end();
            typename ft::map<Key,T,Compare,Alloc>::const_iterator rit = lhs.begin();
            for (;lit != leit;++lit)
            {
                if (lit->first != rit->first || lit->second != rit->second )
                {
                    return false;
                }
                ++rit;
            }
            return true;
        }
        return false;
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif