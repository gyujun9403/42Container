#include "../containers/vector.hpp"

int main()
{
    ft::vector<int> vec;
    ft::vector<int> vec1(10, 5);
    size_t vec_size1 = vec1.size();
    size_t vec_csize1 = vec1.capacity();
    vec1.resize(3);
    size_t vec_size2 = vec1.size();
    size_t vec_csize2 = vec1.capacity();
    bool bo = vec1.empty();
    vec1.reserve(100);
    size_t vec_size3 = vec1.size();
    size_t vec_csize3 = vec1.capacity();
    int val = vec1[1];
    int val_at = vec1.at(0);
    int val_f = vec1.front();
    int val_b = vec1.back();
    vec1.clear();
    size_t vec_size4 = vec1.size();
    size_t vec_msize4 = vec1.capacity();
}