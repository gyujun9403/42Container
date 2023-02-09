#ifndef NODE_HPP
# define NODE_HPP

#include "utils.hpp"
#include "pair.hpp"

namespace ft
{
    //template <typename T_key, typename T_val>
    template <class Pair>
    class node
    {
    public:
    
        Pair data;
        node* parents;
        node* child_left;
        node* child_right;
        long long temp_height;
        int bf;

        node() : parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0) {}

        node(Pair fair)
        : data(fair), parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0)
        {
            //data = make_pair<const T_key, T_val>(key, data);
        }
    };
} // namespace ft

#endif