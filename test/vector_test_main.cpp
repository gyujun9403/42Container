#include "../containers/vector.hpp"

int main()
{
    ft::vector<int> vec;
    ft::vector<int> vec1(10, 3);
    vec1.size();
    vec1.max_size();
    vec1.resize(2);
    vec1.capacity();
    vec1.capacity();
    vec1.empty();
    vec1.reserve(4);
    vec1[2];
    vec1.at(1);
    vec1.front();
    vec1.back();
    vec1.clear();
}