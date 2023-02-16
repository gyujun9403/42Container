#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <typename Tp, typename Seqainer = ft::vector<Tp> >
    class stack
    {
    public:
		typedef			 Seqainer container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;
	protected:
		Seqainer c;

	public:
        explicit stack (const container_type& c = container_type())
		: c(c)
		{}
	
		explicit stack(const stack& other)
		: c(other.c)
		{}

		stack& operator=(const stack& other)
		{
			c = other.c;
			return *this;
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		value_type& top()
		{
			return c.back();
		}

		const value_type& top() const
		{
			return c.back();
		}

		void push (const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

		template <typename Tf, typename Seqf>
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
		return lhs.c == rhs.c;
	}

	template <typename Tf, typename Seqf>
	bool operator!=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs.c != rhs.c;
	}

	template <typename Tf, typename Seqf>
	bool operator<(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <typename Tf, typename Seqf>
	bool operator<=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs.c <= rhs.c;
	}

	template <typename Tf, typename Seqf>
	bool operator>(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs.c > rhs.c;
	}

	template <typename Tf, typename Seqf>
	bool operator>=(const stack<Tf, Seqf>& lhs, const stack<Tf, Seqf>& rhs)
	{
		return lhs.c >= rhs.c;
	}
}

#endif