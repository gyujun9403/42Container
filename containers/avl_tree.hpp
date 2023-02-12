#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include <memory>
#include <exception>
#include <iostream>
//#include "Itree.hpp"
#include "utils.hpp"
#include "pair.hpp"
#include "node.hpp"
#include "avl_iterator.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#define LEFT 0
#define RIGHT 1

#define COUNT 5

namespace ft
{
    template <typename T_key, typename T_val, class Compare = std::less<T_key>, typename Alloc = std::allocator< ft::node<ft::pair<const T_key, T_val> > > >
    class avl_tree // : public ITree<T_key, T_val, Alloc>
    {
    public:

        typedef node<ft::pair<const T_key, T_val> > node_type;
        typedef node<ft::pair<const T_key, T_val> >* node_pointer;
        typedef node<ft::pair<const T_key, T_val> >& node_reference;
        //typedef typename T* pointer;
        typedef typename std::ptrdiff_t difference_type;
        typedef ft::pair<const T_key, T_val> value_type;
        typedef ft::pair<const T_key, T_val>* pointer;
        typedef ft::pair<const T_key, T_val>& reference;
        typedef const node_pointer const_node_pointer;
        typedef const pointer const_pointer;
        typedef typename std::size_t size_type;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef Avl_iterator<value_type, Compare> iterator;
		typedef Avl_const_iterator<value_type, Compare> const_iterator;
		typedef	ft::Reverse_iterator<iterator> reverse_iterator;
		typedef	ft::Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename Alloc::template rebind<node_type>::other node_allocator;
    public: // TODO: for debug
        node_pointer _root;
        size_t _size;
        //allocator_type _node_allocator;
        node_allocator _node_allocator;
        value_compare _compare;

    private:
        node_pointer make_node(T_key& key, T_val& value)
        {
            node_pointer rt = _node_allocator.allocate(1);
            //_node_allocator.construct(rt, ft::make_pair<const T_key, T_val>(key, value));
            _node_allocator.construct(rt, ft::node<ft::pair<const T_key, T_val> >(ft::make_pair<const T_key, T_val>(key, value)));
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
            if (x != _root)
            {
                connect_node(x->parents, y, get_direc_in_parents(x));
            }
            else
            {
                _root = y;
                y->parents = NULL;
            }
            connect_node(x, three, LEFT);
            connect_node(y, x, RIGHT);
            //renewal_heights(three);
            renewal_heights();
        }

        void rotate_l(node_pointer x)
        {
            node_pointer y = x->child_right;
            node_pointer two = y->child_left;
            if (x != _root)
            {
                connect_node(x->parents, y, get_direc_in_parents(x));
            }
            else
            {
                _root = y;
                y->parents = NULL;
            }
            connect_node(x, two, RIGHT);
            connect_node(y, x, LEFT);
            //renewal_heights(two);
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
            if (ptr_node == NULL)
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
            recur_set_height(_root);
        }

        //void renewal_heights(node_pointer From_node)
        void renewal_heights()
        {
            recur_set_height(_root);
        }

    public:
        avl_tree (const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
        : _root(NULL), _size(0), _node_allocator(alloc), _compare(comp) {}

        ~avl_tree ()
        {
            clear();
        }

        node_pointer insert(T_key key, T_val value)
        {
            node_pointer now_node = _root;
            if (_root == NULL)
            {
                _root = make_node(key, value);
                return _root;
            }
            while (1)
            {
                //if (key < now_node->data.first)
                if (_compare(key, now_node->data.first))
                {
                    if (now_node->child_left == NULL)
                    {
                        connect_node(now_node, make_node(key, value), LEFT);
                        //renewal_heights(now_node->child_left);
                        renewal_heights();
                        recur_set_balace(_root);
                        break ;
                    }
                    else
                    {
                        now_node = now_node->child_left;
                    }
                }
                //else if (key > now_node->data.first)
                else if (_compare(now_node->data.first, key))
                {
                    if (now_node->child_right == NULL)
                    {
                        connect_node(now_node, make_node(key, value), RIGHT);
                        //renewal_heights(now_node->child_right);
                        renewal_heights();
                        recur_set_balace(_root);
                        break ;
                    }
                    else
                    {
                        now_node = now_node->child_right;
                    }
                }
                else //일치
                {
                    now_node->data.second = value;
                    break ;
                }
            }
            ++_size;
            //print2D(_root);
            return now_node;
        }

        void erase(node_pointer ptr_node)
        {
            node_pointer substitute_node;
            node_pointer parents = ptr_node->parents;
            if (ptr_node->child_left == NULL)
            {
                // 자식 노드가 없는 경우 -> 그냥 삭제
                if (ptr_node->child_right == NULL)
                {
                    substitute_node = NULL;
                }
                // 오른쪽 자식만 있는 경우 -> 서브노드의 successor으로 대체.
                else
                {
                    substitute_node = take_successor(ptr_node);
                }
            }
            else
            {
                // 왼쪽 자식만 있는 경우 -> 서브노드의 predecessor으로 대체.
                if (ptr_node->child_right == NULL)
                {
                    substitute_node = take_predecessor(ptr_node);
                }
                // 양쪽 자식 모두 있는 경우 ->  서브 노드의 successor으로 대체.
                else
                {
                    substitute_node = take_successor(ptr_node);
                }
            }
            if (ptr_node != _root) // parents == NULL인 경우, _root
            {
                connect_node(parents, substitute_node, get_direc_in_parents(ptr_node));
            }
            else
            {
                _root = substitute_node;
            }
            // 없앨 노드가 가지고 있는 좌우 붙여주기
            connect_node(substitute_node, ptr_node->child_left, LEFT);
            connect_node(substitute_node, ptr_node->child_right, RIGHT);
            _node_allocator.destroy(ptr_node);
            _node_allocator.deallocate(ptr_node, 1);
            //renewal_heights(_root);
            renewal_heights();
            recur_set_balace(_root);
            --_size;
            //print2D(_root);
            return ;
        }

        size_t erase(T_key key)
        {
            // 찾고
            node_pointer finded = find(key);
            if (finded == NULL)
            {
                return 0;
            }
            // 찾은거 지우기
            erase(finded);
            return 1;
        }

        node_pointer find(T_key key) const
        {
            node_pointer now_node = _root;
            while (1)
            {
                //if (key < now_node->data.first)
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
                //else if (key > now_node->data.first)
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
                else //일치
                {
                    return now_node;
                }
            }
        }

        node_pointer get_min_node() const
        //node_reference get_min_node()
        {
            node_pointer now_node = _root;
            if (_root == NULL)
            {
                return NULL;
            }
            while (now_node->child_left != NULL)
            {
                // std::cout << "?????!!!" << std::endl;
                // if (now_node->child_left == NULL)
                // {
                //     break ;
                // }
                //std::cout << "?????" << std::endl;
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
            return const_iterator(this->get_min_node());
        }

        node_pointer get_max_node() const
        //node_reference get_max_node()
        {
            node_pointer now_node = _root;
            if (_root == NULL)
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
            return (now_node);
        }

        iterator get_max_iter() const
        {
            return iterator(this->get_max_node());
        }

        const_iterator get_max_const_iter() const
        {
            return const_iterator(this->get_max_node());
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
            /*
                    node_pointer _root;
        size_t _size;
        //allocator_type _node_allocator;
        node_allocator _node_allocator;
        value_compare _compare;
            */
            if (&other == this)
            {
                return ;
            }
            node_pointer temp_node_ptr = _root;
            size_type temp_size = _size;
            _root = other->_root;
            _size = other->_size;
            other->_root = temp_node_ptr;
            other->_size = temp_size;
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
            // 후위 순회 : 왼쪽자식 -> 오른자식 -> 본체 제거.
            recur_postorder_clear(_root);
            _root = NULL;
            _size = 0;
        }

    };

    // template <typename T_key, typename T_value>
    // void print2DUtil(ft::node<T_key, T_value>* root, int space)
    // {

    //     // Base case
    //     if (root == NULL)
    //         return;
    
    //     // Increase distance between levels
    //     space += COUNT;
    
    //     // Process right child first
    //     print2DUtil(root->child_right, space);
    
    //     // Print current node after space
    //     // count
    //     std::cout << std::endl;
    //     for (int i = COUNT; i < space; i++)
    //         std::cout << " ";
    //     std::cout << root->data.second << "\n";
    
    //     // Process left child
    //     print2DUtil(root->child_left, space);
    // }
    
    // Wrapper over print2DUtil()
    // template <typename T_key, typename T_value>
    // void print2D(ft::node<T_key, T_value>* root)
    // {
    //     static size_t i = 0;
    //     // Pass initial space count as 0
    //     std::cout << "-----------------["<< i++ <<"]----------------" << std::endl;
    //     print2DUtil(root, 0);
    //     std::cout << "------------------------------------" << std::endl;
    // }
}

#endif