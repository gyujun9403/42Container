#ifndef BIDIRECTIONAL_ITERATORE_avl_HPP
# define BIDIRECTIONAL_ITERATORE_avl_HPP

#include "./base_iterator.hpp"
#include "./traits.hpp"
#include "./utils.hpp"
#include "./node.hpp"

namespace ft
{
    // template<typename Tf, typename Comparef>
    // class Avl_const_iterator;

    template <typename T, typename Compare> // T : node<T_key, T_val>
    class Avl_iterator //: Base_iterator<T>
    {
    public:
        typedef typename ft::Bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::difference_type difference_type; // FIX!
        typedef typename ft::iterator_traits<T*>::value_type value_type;
        typedef typename ft::iterator_traits<T*>::pointer pointer; //  TODO!!!!!!!!!!!!// node -> pair
        typedef typename ft::iterator_traits<T*>::reference reference;
        typedef node<T>* node_pointer; //  TODO!!!!!!!!!!!!// node -> pair
        typedef node<T>& node_reference;
        typedef std::size_t size_type;

        // template<typename Tf, typename Comparef>
        // friend class ft::Avl_const_iterator<Tf, Comparef>;
        //typedef typename ft::iterator_traits<T*>::difference_type difference_type; // FIX!
        // typedef typename ft::iterator_traits<T*>::value_type value_type;
        // typedef typename ft::iterator_traits<T*>::pointer pointer; //  TODO!!!!!!!!!!!!// node -> pair
        // typedef typename ft::iterator_traits<T*>::reference reference;
        //typedef typename ft::iterator_traits<T*>::node_pointer node_pointer; //  TODO!!!!!!!!!!!!// node -> pair
        //typedef typename ft::iterator_traits<T*>::node_reference node_reference;
        //typedef typename ft::iterator_traits<T*>::size_type size_type;
    //private:
        node_pointer _node;
        Compare _comp;

    public:
        Avl_iterator(const Compare& comp = Compare())
        : _node(NULL), _comp(comp) {}
        Avl_iterator(const node_pointer node, const Compare& comp = Compare())
        : _node(node), _comp(comp) {}
        // Avl_iterator(const Avl_iterator<typename ft::remove_const<value_type>::type, Compare>& other)
        // : _node(other.base()), _comp() {}

        node_pointer base() const
        {
            return (_node);
        }

        Avl_iterator& operator=(const Avl_iterator<typename remove_const<value_type>::type, Compare>& other)
        {
            if (this == &other)
            {
                return *this;
            }
            //_ptr = other->base();
            _node = other._node;
            _comp = other._comp;

            return *this;
        }

        reference operator*(void) const
        {
            return _node->data; //node::data (ft::pair<const T_key, T_val> 타입)
        }

        pointer operator->(void) const
        {
            return &(_node->data);
        }

        // 순회 방식 -> 정렬 순서대로 순회 = 중위순회.
        Avl_iterator& operator++(void)
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
                    while (_comp(now_node->data.first, _node->data.first)) // _node->data.first < now_node->data.first인 동안 반복
                    {
                        now_node = now_node->parents;
                        if (now_node == NULL)
                        {
                            _node = NULL;
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

        Avl_iterator operator++(int)
        {
            Avl_iterator tmp(*this);
            this->operator++();
            return tmp;
        }

        Avl_iterator& operator--(void)
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
                    while (_comp(now_node->data.first, _node->data.first)) // _node->data.first > now_node->data.first인 동안 반복
                    {
                        now_node = now_node->parents;
                        if (now_node == NULL)
                        {
                            _node = NULL;
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

        Avl_iterator operator--(int)
        {
            Avl_iterator tmp(*this);
            this->operator--();
            return tmp;
        }

        bool operator==(const Avl_iterator& other)
        { return (this->_node == other._node); }

        bool operator!=(const Avl_iterator& other)
        { return (this->_node != other._node); }
    };

    // template <typename T_L, typename T_R>
    // typename ft::Avl_iterator<T_L>
    //     operator== (const ft::Avl_iterator<T_L> lhs, const ft::Avl_iterator<T_R> rhs)
    //     {
    //         // 내용물을 비교하는게 아니라, 포인터의 주소가 같은지 비교하는 연산인듯...?
    //         return (lhs.base() == rhs.base());
    //     }

    // template <typename T_L, typename T_R>
    // typename ft::Avl_iterator<T_L>
    //     operator!= (const ft::Avl_iterator<T_L> lhs, const ft::Avl_iterator<T_R> rhs)
    //     {
    //         return (lhs.base() != rhs.base());
    //     }
    template <typename T, class Compare > // value_type : ft::pair<const T_key, T_val>
	class Avl_const_iterator // : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
            typedef typename ft::Bidirectional_iterator_tag iterator_category;
            typedef typename ft::iterator_traits<T*>::difference_type difference_type; // FIX!
            typedef typename ft::iterator_traits<T*>::value_type value_type;
            typedef typename ft::iterator_traits<T*>::pointer pointer; //  TODO!!!!!!!!!!!!// node -> pair
            typedef typename ft::iterator_traits<T*>::reference reference;
            typedef node<T>* node_pointer; //  TODO!!!!!!!!!!!!// node -> pair
            typedef node<T>& node_reference;
            typedef std::size_t size_type;

        // private:
            node_pointer _node;
            Compare _comp;

        public:
			Avl_const_iterator(const Compare& comp = Compare())
			: _node(), _comp(comp)
			{}

			Avl_const_iterator(node_pointer node_p, const Compare& comp = Compare())
			: _node(node_p), _comp(comp)
			{}

			Avl_const_iterator(const Avl_const_iterator& other)
			: _node(other._node), _comp()
			{}

            Avl_const_iterator(const Avl_iterator<T, Compare>& other)
			: _node(other._node), _comp()
			{}

			// Avl_const_iterator(const Avl_const_iterator<T, Compare>& other)
			// : _node(other._node), _comp()
			// {}

			virtual ~Avl_const_iterator() { }

			Avl_const_iterator &operator=(const Avl_const_iterator& other)
			{
				if (*this == other)
                {
					return (*this);
                }
				this->_node = other._node;
				this->_comp = other._comp;
				return *this;
			}

			bool operator==(const Avl_const_iterator& other)
			{
                return (this->_node == other._node);
            }

			bool operator!=(const Avl_const_iterator& other)
			{
                return (this->_node != other._node);
            }

			reference operator*() const
			{
                return (this->_node->data);
            }

			pointer operator->() const
			{
                return (&this->_node->data);
            }

			Avl_const_iterator& operator++(void)
			{
                if (_node == NULL)
                {
                    return *this;
                }
                // 오른쪽에 없으면 부모로.
                if (_node->child_right == NULL)
                {
                    node_pointer now_node = _node->parents;
                    if (now_node != NULL)
                    {
                        // 부모로 가서
                        // 부모가 자기보다 크면 그게 노드
                        // 부모가 자기보다 작으면 클 때 까지 반복
                        while (_comp(now_node->data.first, _node->data.first)) // _node->data.first < now_node->data.first인 동안 반복
                        {
                            //std::cout << "_node: " << _node->data.first << ",now_node: " << now_node->data.first << std::endl;
                            now_node = now_node->parents;
                            if (now_node == NULL)
                            {
                                //std::cout << "7";
                                //_node = NULL;
                                //return *this;
                                break ;
                            }
                        }
                        //std::cout << "8";
                    }
                    _node = now_node;
                }
                // 오른쪽 있으면 오른쪽으로
                else
                {
                    _node = _node->child_right;
                }
                return *this;
			}

			Avl_const_iterator operator++(int)
			{
				Avl_const_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			Avl_const_iterator& operator--(void)
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
                        while (_comp(_node->data.first, now_node->data.first)) // _node->data.first > now_node->data.first인 동안 반복
                        {
                            now_node = _node->parents;
                            if (now_node == NULL)
                            {
                                break ;
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

			Avl_const_iterator operator--(int)
			{
				Avl_const_iterator tmp(*this);
				operator--();
				return (tmp);
			}
	};
}


#endif