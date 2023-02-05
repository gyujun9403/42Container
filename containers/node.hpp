#ifndef NODE_HPP
# define NODE_HPP

#include "utils.hpp"
#include "pair.hpp"

namespace ft
{
    template <typename T_key, typename T_val>
    class node
    {
    public:
    
        ft::pair<const T_key, T_val> data;
        node* parents;
        node* child_left;
        node* child_right;
        long long temp_height;
        int bf;

        node() : parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0) {}

        node(ft::pair<const T_key, T_val> fair)
        : data(fair), parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0)
        {
            //data = make_pair<const T_key, T_val>(key, data);
        }
    };
} // namespace ft

#endif