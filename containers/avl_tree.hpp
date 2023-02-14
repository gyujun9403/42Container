#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include <memory>
#include <exception>
#include "utils.hpp"
#include "pair.hpp"
#include "node.hpp"
#include "avl_iterator.hpp"
#include "reverse_iterator.hpp"
#define LEFT 0
#define RIGHT 1

namespace ft
{
    template <typename T_key, typename T_val, class Compare = std::less<T_key>, typename Alloc = std::allocator< ft::node<ft::pair<const T_key, T_val> > > >
    class avl_tree
    {
    public:
        typedef ft::pair<const T_key, T_val> value_type;
        typedef node<value_type > node_type;
        //typedef node<const value_type > const_node_type;
        typedef node_type* node_pointer;
        //typedef const_node_type* const_node_pointer;
        //typedef node_type& node_reference;
        typedef typename std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef typename std::size_t size_type;
        typedef Compare value_compare;
        typedef Alloc allocator_type;

        typedef Avl_iterator<node_type, value_type, Compare> iterator;
		typedef Avl_iterator<node_type, const value_type, Compare> const_iterator;
		typedef	ft::Reverse_iterator<iterator> reverse_iterator;
		typedef	ft::Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename Alloc::template rebind<node_type>::other node_allocator;
    public:
        node_type _superior;
        size_t _size;
        node_allocator _node_allocator;
        value_compare _compare;

    private:
        node_pointer allocate_node(T_key& key, T_val& value)
        {
            node_pointer rt = _node_allocator.allocate(1);
            _node_allocator.construct(rt, ft::node<value_type >(ft::make_pair<const T_key, T_val>(key, value)));
            return rt;
        }

        void connect_node(node_pointer parents, node_pointer child, bool direction)
        {
            if (parents == NULL)
            {
                ;
            }
            else if (direction == LEFT)
            {
                parents->child_left = child;
            }
            else
            {
                parents->child_right = child;
            }

            if (child != NULL)
            {
                child->parents = parents;
            }
        }

        node_pointer take_successor(const node_pointer root)
        {
            node_pointer now_node = root->child_right;
            if (now_node == NULL)
            {
                return NULL;
            }
            while (1)
            {
                if (now_node->child_left == NULL)
                {
                    break ;
                }
                now_node = now_node->child_left;
            }
            connect_node(now_node->parents, now_node->child_right, get_direc_in_parents(now_node));
            now_node->parents = NULL;
            now_node->child_right = NULL;
            return now_node;
        }

        node_pointer take_predecessor(const node_pointer root)
        {
            node_pointer now_node = root->child_left;
            if (now_node == NULL)
            {
                return NULL;
            }
            while (1)
            {
                if (now_node->child_right == NULL)
                {
                    break ;
                }
                now_node = now_node->child_right;
            }
            connect_node(now_node->parents, now_node->child_left, get_direc_in_parents(now_node));
            now_node->parents = NULL;
            now_node->child_left = NULL;
            return now_node;
        }

        bool get_direc_in_parents(node_pointer node_ptr)
        {
            if (node_ptr->parents->child_left == node_ptr)
            {
                return LEFT;
            }
            else if (node_ptr->parents->child_right == node_ptr)
            {
                return RIGHT;
            }
            else
            {
                throw std::invalid_argument("avl_tree::get_direc_in_parents invalid_argument exceptin");
                return false;
            }
        }


        void recur_postorder_clear(node_pointer ptr_node)
        {
            if (ptr_node == NULL)
            {
                return ;
            }
            recur_postorder_clear(ptr_node->child_left);
            recur_postorder_clear(ptr_node->child_right);
            _node_allocator.destroy(ptr_node);
            _node_allocator.deallocate(ptr_node, 1);
        }

        void rotate_r(node_pointer x)
        {
            node_pointer y = x->child_left;
            node_pointer three = y->child_right;
            if (x != _superior.child_left)
            {
                connect_node(x->parents, y, get_direc_in_parents(x));
            }
            else
            {
                _superior.child_left = y;
                y->parents = &_superior;
            }
            connect_node(x, three, LEFT);
            connect_node(y, x, RIGHT);
            renewal_heights();
        }

        void rotate_l(node_pointer x)
        {
            node_pointer y = x->child_right;
            node_pointer two = y->child_left;
            if (x != _superior.child_left)
            {
                connect_node(x->parents, y, get_direc_in_parents(x));
            }
            else
            {
                _superior.child_left = y;
                y->parents = &_superior;
            }
            connect_node(x, two, RIGHT);
            connect_node(y, x, LEFT);
            renewal_heights();
        }

        long long get_height(node_pointer ptr_node)
        {
            if (ptr_node == NULL)
            {
                return -1;
            }
            else
            {
                return ptr_node->temp_height;
            }
        }

        void recur_set_height(node_pointer ptr_node)
        {
            if (ptr_node == NULL)
            {
                return ;
            }
            recur_set_height(ptr_node->child_left);
            recur_set_height(ptr_node->child_right);
            long long left_height = get_height(ptr_node->child_left);
            long long right_height = get_height(ptr_node->child_right);
            ptr_node->temp_height = (left_height > right_height) ? (left_height + 1) : (right_height + 1);
            ptr_node->bf = left_height - right_height;
        }

        void recur_set_balace(node_pointer ptr_node)
        {
            if (ptr_node == NULL) // 가장 끝  노드에 도달
            {
                return ;
            }
            recur_set_balace(ptr_node->child_left);
            recur_set_balace(ptr_node->child_right);
            if (ptr_node->bf > 1)
            {
                long long lleft_height = get_height(ptr_node->child_left->child_left);
                long long lright_height = get_height(ptr_node->child_left->child_right);
                if (lleft_height > lright_height)
                {
                    // ll
                    rotate_r(ptr_node);
                }
                else
                {
                    // lr
                    rotate_l(ptr_node->child_left);
                    rotate_r(ptr_node);
                }
            }
            else if (ptr_node->bf < -1)
            {
                long long rleft_height = get_height(ptr_node->child_right->child_left);
                long long rright_height = get_height(ptr_node->child_right->child_right);
                if (rleft_height > rright_height)
                {
                    // rl
                    rotate_r(ptr_node->child_right);
                    rotate_l(ptr_node);
                }
                else
                {
                    // rr
                    rotate_l(ptr_node);
                }
            }
            else
            {
                return ;
            }
            recur_set_height(_superior.child_left);
        }

        void renewal_heights()
        {
            recur_set_height(_superior.child_left);
        }

    public:
        avl_tree (const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
        : _size(0), _node_allocator(alloc), _compare(comp)
        {
            _superior.child_left = NULL;
            _superior.child_right = NULL;
            _superior.parents = NULL;
        }

        avl_tree (const avl_tree& other)
        : _size(0), _node_allocator(other._node_allocator), _compare(other._compare)
        {
            _superior.child_left = NULL;
            _superior.child_right = NULL;
            _superior.parents = NULL;
        }

        ~avl_tree ()
        {
            clear();
        }

        node_pointer insert(T_key key, T_val value)
        {
            node_pointer now_node = _superior.child_left;
            if (_superior.child_left == NULL)
            {
                _superior.child_left = allocate_node(key, value);
                _superior.child_left->parents = &_superior;
                ++_size;
                return _superior.child_left;
            }
            while (1)
            {
                if (_compare(key, now_node->data.first))
                {
                    if (now_node->child_left == NULL)
                    {
                        connect_node(now_node, allocate_node(key, value), LEFT);
                        renewal_heights();
                        recur_set_balace(_superior.child_left);
                        now_node = now_node->child_left;
                        ++_size;
                        break ;
                    }
                    else
                    {
                        now_node = now_node->child_left;
                    }
                }
                else if (_compare(now_node->data.first, key))
                {
                    if (now_node->child_right == NULL)
                    {
                        connect_node(now_node, allocate_node(key, value), RIGHT);
                        renewal_heights();
                        recur_set_balace(_superior.child_left);
                        now_node = now_node->child_right;
                        ++_size;
                        break ;
                    }
                    else
                    {
                        now_node = now_node->child_right;
                    }
                }
                else
                {
                    break ;
                }
            }
            return now_node;
        }

        void erase(node_pointer ptr_node)
        {
            node_pointer substitute_node;
            node_pointer parents = ptr_node->parents;
            if (ptr_node->child_left == NULL)
            {
                if (ptr_node->child_right == NULL)
                {
                    substitute_node = NULL;
                }
                else
                {
                    substitute_node = take_successor(ptr_node);
                }
            }
            else
            {
                if (ptr_node->child_right == NULL)
                {
                    substitute_node = take_predecessor(ptr_node);
                }
                else
                {
                    substitute_node = take_successor(ptr_node);
                }
            }
            if (ptr_node != _superior.child_left)
            {
                connect_node(parents, substitute_node, get_direc_in_parents(ptr_node));
            }
            else
            {
                _superior.child_left = substitute_node;
                if (substitute_node != NULL)
                {
                    substitute_node->parents = &_superior;
                }
            }
            connect_node(substitute_node, ptr_node->child_left, LEFT);
            connect_node(substitute_node, ptr_node->child_right, RIGHT);
            _node_allocator.destroy(ptr_node);
            _node_allocator.deallocate(ptr_node, 1);
            renewal_heights();
            recur_set_balace(_superior.child_left);
            --_size;
            return ;
        }

        size_type erase(T_key key)
        {
            node_pointer finded = find(key);
            if (finded == NULL)
            {
                return 0;
            }
            erase(finded);
            return 1;
        }

        node_pointer find(T_key key) const
        {
            node_pointer now_node = _superior.child_left;
            if (_superior.child_left == NULL)
            {
                return NULL;
            }
            while (1)
            {
                if (_compare(key, now_node->data.first))
                {
                    if (now_node->child_left == NULL)
                    {
                        return NULL;
                    }
                    else
                    {
                        now_node = now_node->child_left;
                    }
                }
                else if (_compare(now_node->data.first, key))
                {
                    if (now_node->child_right == NULL)
                    {
                        return NULL;
                    }
                    else
                    {
                        now_node = now_node->child_right;
                    }
                }
                else
                {
                    return now_node;
                }
            }
        }

        node_pointer get_min_node() const
        {
            node_pointer now_node = _superior.child_left;
            if (_superior.child_left == NULL)
            {
                return NULL;
            }
            while (now_node->child_left != NULL)
            {
                now_node = now_node->child_left;
            }
            return (now_node);
        }

        iterator get_min_iter() const
        {
            return iterator(this->get_min_node());
        }

        const_iterator get_min_cosnt_iter() const
        {
            return const_iterator(get_min_iter());
        }

        iterator get_end_iter() const
        {
            if (_superior.child_left == NULL)
            {
                return iterator(NULL);
            }
            return iterator(const_cast<node_pointer>(&_superior));
        }

        const_iterator get_end_const_iter() const
        {
            if (_superior.child_left == NULL)
            {
                return const_iterator(NULL);
            }
            return const_iterator(get_end_iter());
        }

        size_t size() const
        {
            return _size;
        }

        size_t max_size() const
        {
            return _node_allocator.max_size();
        }

        void swap(avl_tree& other)
        {
            if (&other == this)
            {
                return ;
            }
            node_pointer temp_node_ptr = _superior.child_left;
            size_type temp_size = _size;
            connect_node(&_superior, other._superior.child_left, LEFT);
            _size = other._size;
            connect_node(&(other._superior), temp_node_ptr, LEFT);
            other._size = temp_size;
        }

        bool empty() const
        {
            if (_size == 0)
            {
                return true;
            }
            return false;
        }

        void clear()
        {
            recur_postorder_clear(_superior.child_left);
            _superior.child_left = NULL;
            _size = 0;
        }

    };
}
#endif