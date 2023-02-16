#ifndef NODE_HPP
# define NODE_HPP

#include "utils.hpp"
#include "pair.hpp"

namespace ft
{
    template <typename Pair>
    class node
    {
    public:
        Pair data;
        node* parents;
        node* child_left;
        node* child_right;
        long long temp_height;
        int bf;

        node()
        : parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0)
        {}

        node(Pair fair)
        : data(fair), parents(NULL), child_left(NULL), child_right(NULL), temp_height(0), bf(0)
        {}
    };
}

#endif