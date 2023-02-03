#include "../containers/map.hpp"

int main()
{
    ft::map<int, int> test1;
    test1.insert(ft::make_pair<int, int>(1, 1));
    test1.insert(ft::make_pair<int, int>(2, 2));
    test1.insert(ft::make_pair<int, int>(3, 3));
    test1.insert(ft::make_pair<int, int>(4, 4));
    test1.insert(ft::make_pair<int, int>(5, 5));
    //test1.clear();
}