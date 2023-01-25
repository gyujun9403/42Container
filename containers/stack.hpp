#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template<typename T, typename Container = ft::vector<T> >
    class stack
    {
    public:
        // for iterator_trains
        typedef          T value_type;
        typedef typename Container::allocator_type allocator_type;
        typedef typename Container::pointer pointer;
        typedef typename Container::const_pointer const_pointer;
        typedef typename Container::size_type size_type;
        typedef typename Container::difference_type difference_type;

        typedef          value_type& reference; //FIX!!
        typedef          const value_type& const_reference;

        // stack은 반복자가 없다.
        // typedef          Random_access_iterator<value_type> iterator;
        // //typedef          const Random_access_iterator<value_type> const_iterator; FIX!!!!
        // typedef          Random_access_iterator<const value_type> const_iterator;
        // typedef          Reverse_iterator<const_iterator> const_reverse_iterator;
		// typedef          Reverse_iterator<iterator> reverse_iterator;

        explicit stack (const container_type& cont = container_type()) : _container(cont){}
	
	stack(const stack& other): _container(other._container) {}

	stack& operator=(const stack& other){
		_container = other._container;
		return (*this);
	}

	bool empty() const{
		return (_container.empty());
	}

	size_type size() const{
		return (_container.size());
	}

	value_type& top(){
		return (_container.back());
	}

	const value_type& top() const{
		return (_container.back());
	}

	void push (const value_type& val){
		_container.push_back(val);
	}

	void pop(){
		_container.pop_back();
	}

	};

	template <class A, class Cont>
	bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container == rhs._container);
			 }
	template <class A, class Cont>
	bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container != rhs._container);
			 }
	template <class A, class Cont>
	bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container < rhs._container);
			 }
	template <class A, class Cont>
	bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container <= rhs._container);
		  }
	template <class A, class Cont>
	bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container > rhs._container);
		  }
	template <class A, class Cont>
	bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container >= rhs._container);
			}

}

#endif