#ifndef AVL_ITERATOR_HPP
# define AVL_ITERATOR_HPP

#include "./traits.hpp"
#include "./utils.hpp"
#include "./node.hpp"

namespace ft
{
    template <typename N, typename P>
    class Avl_iterator
    {
    public:
        typedef typename ft::Bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<P*>::difference_type difference_type;
        typedef typename ft::iterator_traits<P*>::value_type value_type;
        typedef typename ft::iterator_traits<P*>::pointer pointer;
        typedef typename ft::iterator_traits<P*>::reference reference;
        typedef N node_type;
        typedef node_type* node_pointer;
        typedef node_type& node_reference;
        typedef std::size_t size_type;

    private:
        node_pointer _node;

    public:
        Avl_iterator()
        : _node(NULL)
        {}
        Avl_iterator(const node_pointer node)
        : _node(node)
        {}
        Avl_iterator(const Avl_iterator<node_type, typename ft::remove_const<value_type>::type>& other)
        : _node(other.base())
        {}

        node_pointer base() const
        {
            return _node;
        }

        Avl_iterator& operator=(const Avl_iterator<node_type, typename remove_const<value_type>::type>& other)
        {
            if (this == &other)
            {
                return *this;
            }
            _node = other._node;
            return *this;
        }

        reference operator*(void) const
        {
            return _node->data;
        }

        pointer operator->(void) const
        {
            return &(_node->data);
        }

        Avl_iterator& operator++(void)
        {
            if (_node->child_right == NULL)
            {
                node_pointer now_node;
                node_pointer parent_node = _node;
                while(1)
                {
                    now_node = parent_node;
                    parent_node = now_node->parents;
                    if (parent_node == NULL)
                    {
                        break ;
                    }
                    if (now_node == parent_node->child_left)
                    {
                        now_node = parent_node;
                        break ;
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_right;
                while (_node->child_left != NULL)
                {
                    _node = _node->child_left;
                }
            }
            return *this;
        }

        Avl_iterator operator++(int)
        {
            Avl_iterator tmp(*this);
            this->operator++();
            return tmp;
        }

        Avl_iterator& operator--(void)
        {
            if (_node->child_left == NULL)
            {
                node_pointer now_node;
                node_pointer parent_node = _node;
                while(1)
                {
                    now_node = parent_node;
                    parent_node = now_node->parents;
                    if (parent_node == NULL)
                    {
                        break ;
                    }
                    if (now_node == parent_node->child_right)
                    {
                        now_node = parent_node;
                        break ;
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_left;
                while (_node->child_right != NULL)
                {
                    _node = _node->child_right;
                }
            }
            return *this;
        }

        Avl_iterator operator--(int)
        {
            Avl_iterator tmp(*this);
            this->operator--();
            return tmp;
        }

        bool operator==(const Avl_iterator& other)
        {
            return this->_node == other._node;
        }

        bool operator!=(const Avl_iterator& other)
        {
            return this->_node != other._node;
        }
    };

    template <typename N, typename P>//, typename Compare >
	class Avl_const_iterator
	{
    public :
        typedef typename ft::Bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<P*>::difference_type difference_type;
        typedef typename ft::iterator_traits<P*>::value_type value_type;
        typedef typename ft::iterator_traits<P*>::pointer pointer;
        typedef typename ft::iterator_traits<P*>::reference reference;
        typedef ft::Avl_iterator<N, typename ft::remove_const<P>::type> org_iterator_type;
        typedef N node_type;
        typedef node_type* node_pointer;
        typedef std::size_t size_type;

    private:
        node_pointer _node;

    public:
        Avl_const_iterator()
        : _node()
        {}

        Avl_const_iterator(const node_pointer node_p)
        : _node(node_p)
        {}

        Avl_const_iterator(const Avl_const_iterator& other)
        : _node(other.base())
        {}

        Avl_const_iterator(const org_iterator_type& other)
        : _node(other.base())
        {}

        virtual ~Avl_const_iterator()
        {}

        node_pointer base() const
        {
            return _node;
        }         

        Avl_const_iterator &operator=(const Avl_const_iterator& other)
        {
            if (*this == other)
            {
                return *this;
            }
            this->_node = other._node;
            return *this;
        }

        bool operator==(const Avl_const_iterator& other)
        {
            return this->_node == other._node;
        }

        bool operator!=(const Avl_const_iterator& other)
        {
            return this->_node != other._node;
        }

        reference operator*() const
        {
            return this->_node->data;
        }

        pointer operator->() const
        {
            return &this->_node->data;
        }

        Avl_const_iterator& operator++(void)
        {
            if (_node->child_right == NULL)
            {
                node_pointer now_node;
                node_pointer parent_node = _node;
                while(1)
                {
                    now_node = parent_node;
                    parent_node = now_node->parents;
                    if (parent_node == NULL)
                    {
                        break ;
                    }
                    if (now_node == parent_node->child_left)
                    {
                        now_node = parent_node;
                        break ;
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_right;
                while (_node->child_left != NULL)
                {
                    _node = _node->child_left;
                }
            }
            return *this;
        }

        Avl_const_iterator operator++(int)
        {
            Avl_const_iterator tmp(*this);
            operator++();
            return tmp;
        }

        Avl_const_iterator& operator--(void)
        {
            if (_node->child_left == NULL)
            {
                node_pointer now_node;
                node_pointer parent_node = _node;
                while(1)
                {
                    now_node = parent_node;
                    parent_node = now_node->parents;
                    if (parent_node == NULL)
                    {
                        break ;
                    }
                    if (now_node == parent_node->child_right)
                    {
                        now_node = parent_node;
                        break ;
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_left;
                while (_node->child_right != NULL)
                {
                    _node = _node->child_right;
                }
            }
            return *this;
        }

        Avl_const_iterator operator--(int)
        {
            Avl_const_iterator tmp(*this);
            operator--();
            return tmp;
        }
	};
}


#endif