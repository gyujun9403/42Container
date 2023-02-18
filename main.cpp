#include <iostream>
#include "containers/vector.hpp"

#ifdef FAST
int _ratio = 1;
#else
int _ratio = 10000;
#endif

int _allocator_used = 0;

#include <array>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <fstream>
#include <execinfo.h>
#include <iomanip>
#include <sys/time.h>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>

time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template <typename T>
std::vector<int> insert_test_2(std::vector<T> vector)
{
    std::vector<int> v;
    // std::vector<int> tmp;
    // tmp.assign(2600 * _ratio, 1);
    // vector.assign(4200 * _ratio, 1);
    // vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // v.push_back(vector[3]);
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;
	
    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try
	{
		vv.insert(vv.begin(), v1.begin(), v1.end());
	}
    catch (...)
	{
		std::cout << "STDERRORRRRRRRRRRRRRRRR" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    return v;
}

template <typename T>
std::vector<int> insert_test_3(ft::vector<T> vector)
{
    std::vector<int> v;
    // ft::vector<int> tmp;
    // tmp.assign(2600 * _ratio, 1);
    // vector.assign(4200 * _ratio, 1);
    // vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // v.push_back(vector[3]);
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> v1;
	
    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try
	{
		vv.insert(vv.begin(), v1.begin(), v1.end());
	}
    catch (...)
	{
		std::cout << "FTERRORRRRRRRRRRRRRRRR" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    return v;
}

int main()
{
	std::vector<int> std_vector;
	ft::vector<int> ft_vector;
	//std::vector<int> rt = insert_test_2(std_vector);
	// std::cout << "****************STD****************" << std::endl;
	// system("leaks unit_main_test.out");
    std::vector<int> rt2 = insert_test_3(ft_vector);
	std::cout << "****************FD****************" << std::endl;
	system("leaks unit_main_test.out");
	//system("leaks unit_main_test.out");
	return 0;
}