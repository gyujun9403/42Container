#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <typename Tp, typename Seqainer = ft::vector<Tp> >
    class stack
    {
    public:
        // for iterator_trains
		typedef			 Seqainer container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;
        // stack은 반복자가 없다.
        // typedef          Random_access_iterator<value_type> iterator;
        // //typedef          const Random_access_iterator<value_type> const_iterator; FIX!!!!
        // typedef          Random_access_iterator<const value_type> const_iterator;
        // typedef          Reverse_iterator<const_iterator> const_reverse_iterator;
		// typedef          Reverse_iterator<iterator> reverse_iterator;
	protected:
		Seqainer _c;

	public:
        explicit stack (const container_type& c = container_type())
		: _c(c) {}
	
		stack(const stack& other)
		: _c(other._c) {}

		stack& operator=(const stack& other)
		{
			_c = other._c;
			return *this;
		}

		bool empty() const
		{
			return _c.empty();
		}

		size_type size() const
		{
			return _c.size();
		}

		value_type& top()
		{
			return _c.back();
		}

		const value_type& top() const
		{
			return _c.back();
		}

		void push (const value_type& val)
		{
			_c.push_back(val);
		}

		void pop()
		{
			_c.pop_back();
		}

	template <typename Tf, typename Seqf> // TODO:이거 따로 하니까 됬음 왜?
	friend bool operator==(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);

	template <typename Tf, typename Seqf>
	friend bool operator!=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);

	template <typename Tf, typename Seqf>
	friend bool operator<(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);

	template <typename Tf, typename Seqf>
	friend bool operator<=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);

	template <typename Tf, typename Seqf>
	friend bool operator>(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);

	template <typename Tf, typename Seqf>
	friend bool operator>=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs);
		
	};

	template <typename Tf, typename Seqf>
	bool operator==(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c == rhs._c;
	}

	template <typename Tf, typename Seqf>
	bool operator!=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c != rhs._c;
	}

	template <typename Tf, typename Seqf>
	bool operator<(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c < rhs._c;
	}

	template <typename Tf, typename Seqf>
	bool operator<=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c <= rhs._c;
	}

	template <typename Tf, typename Seqf>
	bool operator>(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c > rhs._c;
	}

	template <typename Tf, typename Seqf>
	bool operator>=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs._c >= rhs._c;
	}
}

#endif