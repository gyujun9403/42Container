#ifndef BIDIRECTIONAL_ITERATORE_avl_HPP
# define BIDIRECTIONAL_ITERATORE_avl_HPP

#include "./base_iterator.hpp"
#include "./traits.hpp"
#include "./utils.hpp"
#include "./node.hpp"

namespace ft
{
    template <typename T, typename Compare> // T : node<T_key, T_val>
    class Bidirectional_iterator_avl : Base_iterator<T>
    {
    public:
        typedef typename ft::Bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::difference_type difference_type; // FIX!
        typedef typename ft::iterator_traits<T*>::value_type value_type;
        typedef typename ft::iterator_traits<T*>::pointer node_pointer; // FIX! 이걸 쌩으로 T*, T&으로 쓰면
        typedef typename ft::iterator_traits<T*>::reference node_reference;
        //typedef typename ft::iterator_traits<T*>::size_type size_type;
    private:
        node_pointer _node;
        Compare _comp;

    public:
        Bidirectional_iterator_avl(const Compare& comp = Compare())
        : _node(NULL), _comp(comp) {}
        Bidirectional_iterator_avl(node_pointer node, const Compare& comp = Compare())
        : _node(node), _comp(comp) {}
        Bidirectional_iterator_avl(const Bidirectional_iterator_avl<typename ft::remove_const<value_type>::type, Compare>& other)
        : _node(other.base()), _comp() {}

        node_pointer base() const
        {
            return (_node);
        }

        Bidirectional_iterator_avl& operator=(const Bidirectional_iterator_avl<typename remove_const<value_type>::type, Compare>& other)
        {
            if (this == &other)
            {
                return this;
            }
            //_ptr = other->base();
            _node = other->_node;
            _comp = other->_comp;

            return *this;
        }

        node_reference operator*(void) const
        {
            return _node->data; //node::data (ft::pair<const T_key, T_val> 타입)
        }

        node_pointer operator->(void) const
        {
            return &_node->data;
        }

        // 순회 방식 -> 정렬 순서대로 순회 = 중위순회.
        Bidirectional_iterator_avl& operator++(void)
        {
            if (_node == NULL)
            {
                return *this;
            }
            if (_node->child_right == NULL)
            {
                node_pointer now_node = _node->parents;
                if (now_node != NULL)
                {
                    while (_compare(_node->data.first, now_node->data.first)) // _node->data.first < now_node->data.first인 동안 반복
                    {
                        now_node = _node->parents;
                        if (now_node == NULL)
                        {
                            _node == NULL;
                            return *this;
                        }
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_right;
            }
            return *this;
        }

        Bidirectional_iterator_avl operator++(int)
        {
            Bidirectional_iterator_avl tmp(*this);
            this->operator++();
            return tmp;
        }

        Bidirectional_iterator_avl& operator--(void)
        {
            if (_node == NULL)
            {
                return *this;
            }
            if (_node->child_left == NULL)
            {
                node_pointer now_node = _node->parents;
                if (now_node != NULL)
                {
                    while (_compare(now_node->data.first, _node->data.first)) // _node->data.first > now_node->data.first인 동안 반복
                    {
                        now_node = _node->parents;
                        if (now_node == NULL)
                        {
                            _node == NULL;
                            return *this;
                        }
                    }
                }
                _node = now_node;
            }
            else
            {
                _node = _node->child_left;
            }
            return *this;
        }

        Bidirectional_iterator_avl operator--(int)
        {
            Bidirectional_iterator_avl tmp(*this);
            this->operator--();
            return tmp;
        }

        bool operator==(const Bidirectional_iterator_avl& other)
        { return (this->_node == other._node); }

        bool operator!=(const Bidirectional_iterator_avl& other)
        { return (this->_node != other._node); }
    };

    // template <typename T_L, typename T_R>
    // typename ft::Bidirectional_iterator_avl<T_L>
    //     operator== (const ft::Bidirectional_iterator_avl<T_L> lhs, const ft::Bidirectional_iterator_avl<T_R> rhs)
    //     {
    //         // 내용물을 비교하는게 아니라, 포인터의 주소가 같은지 비교하는 연산인듯...?
    //         return (lhs.base() == rhs.base());
    //     }

    // template <typename T_L, typename T_R>
    // typename ft::Bidirectional_iterator_avl<T_L>
    //     operator!= (const ft::Bidirectional_iterator_avl<T_L> lhs, const ft::Bidirectional_iterator_avl<T_R> rhs)
    //     {
    //         return (lhs.base() != rhs.base());
    //     }    
}

#endif