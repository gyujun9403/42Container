#include "../containers/avl_tree.hpp"
#include "../containers/Itree.hpp"



int main()
{
    ft::avl_tree<int, int> tree;
    tree.insert(13, 13);
    tree.insert(6, 6);
    tree.insert(3, 3);
    tree.insert(10, 10);
    tree.insert(17, 17);
    tree.insert(14, 14);
    tree.insert(15, 15);
    tree.insert(5, 5);
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(0, 0);
    tree.insert(18, 18);
    tree.insert(19, 19);
    tree.insert(20, 20);
    tree.insert(21, 21);
    tree.insert(22, 22);
    tree.insert(23, 23);
    tree.insert(24, 24);
    tree.insert(25, 25);
    ft::node<int, int>* node = tree.find(3);
    ft::node<int, int>* node2 = tree.find(42);
    // tree.erase(13);
    // tree.erase(14);
    tree.erase(5);
    tree.erase(6);
    tree.erase(2);
    tree.erase(10);
    // tree.erase(15);
    tree.clear();
    return 0;
}
