#ifndef AVL_ITERATOR_HPP
# define AVL_ITERATOR_HPP

#include "./traits.hpp"
#include "./utils.hpp"
#include "./node.hpp"

namespace ft
{
    template <typename N, typename P, typename Compare>
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
        Compare _comp;

    public:
        Avl_iterator(const Compare& comp = Compare())
        : _node(NULL), _comp(comp)
        {}
        Avl_iterator(const node_pointer node, const Compare& comp = Compare())
        : _node(static_cast<node_pointer>(node)), _comp(comp)
        {}
        Avl_iterator(const Avl_iterator<node_type, typename ft::remove_const<value_type>::type, Compare>& other)
        : _node(other.base()), _comp(other.get_compare())
        {}

        node_pointer base() const
        {
            return _node;
        }

        Compare get_compare() const
        {
            return _comp;
        }

        Avl_iterator& operator=(const Avl_iterator<node_type, typename remove_const<value_type>::type, Compare>& other)
        {
            if (this == &other)
            {
                return *this;
            }
            _node = other._node;
            _comp = other._comp;
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
                node_pointer now_node = _node;
                while(1)
                {
                    if (now_node->parents == NULL)
                    {
                        break ;
                    }
                    now_node = now_node->parents;
                    if (_comp(_node->data.first, now_node->data.first))
                    {
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
                node_pointer now_node = _node;
                while(1)
                {
                    if (now_node->parents == NULL)
                    {
                        break ;
                    }
                    now_node = now_node->parents;
                    if (_comp(now_node->data.first, _node->data.first))
                    {
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

    template <typename N, typename P, typename Compare >
	class Avl_const_iterator
	{
    public :
        typedef typename ft::Bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<P*>::difference_type difference_type;
        typedef typename ft::iterator_traits<P*>::value_type value_type;
        typedef typename ft::iterator_traits<P*>::pointer pointer;
        typedef typename ft::iterator_traits<P*>::reference reference;
        typedef ft::Avl_iterator<N, typename ft::remove_const<P>::type, Compare> org_iterator_type;
        typedef N node_type;
        typedef node_type* node_pointer;
        typedef std::size_t size_type;

    private:
        node_pointer _node;
        Compare _comp;

        public:
        Avl_const_iterator(const Compare& comp = Compare())
        : _node(), _comp(comp)
        {}

        Avl_const_iterator(const node_pointer node_p, const Compare& comp = Compare())
        : _node(node_p), _comp(comp)
        {}

        Avl_const_iterator(const Avl_const_iterator& other)
        : _node(other.base()), _comp(other.get_compare())
        {}

        Avl_const_iterator(const org_iterator_type& other)
        : _node(other.base()), _comp(other.get_compare())
        {}

        virtual ~Avl_const_iterator()
        {}

        node_pointer base() const
        {
            return _node;
        }

        Compare get_compare() const
        {
            return _comp;
        }            

        Avl_const_iterator &operator=(const Avl_const_iterator& other)
        {
            if (*this == other)
            {
                return *this;
            }
            this->_node = other._node;
            this->_comp = other._comp;
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
                node_pointer now_node = _node;
                while(1)
                {
                    if (now_node->parents == NULL)
                    {
                        break ;
                    }
                    now_node = now_node->parents;
                    if (_comp(_node->data.first, now_node->data.first))
                    {
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
                node_pointer now_node = _node;
                while(1)
                {
                    if (now_node->parents == NULL)
                    {
                        break ;
                    }
                    now_node = now_node->parents;
                    if (_comp(now_node->data.first, _node->data.first))
                    {
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