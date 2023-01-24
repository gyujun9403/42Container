#ifndef FAIR_HPP
#define FAIR_HPP

namespace ft
{
    template <typename T1, typename T2>
    struct pair
    {
        //typedef T1 first_type;
        //typedef T2 second_type;

        T1	first;
        T2	second;
        
        pair()
        : first(), second() {}

        template <typename U, typename V>
        pair(const pair<U, V>& pr)
        : first(pr.first), second(pr.second) {}

        pair(const pair& pr)
        : first(pr.first), second(pr.second) {}

        pair(const T1& a, const T2& b)
        : first(a), second(b) {}

        pair& operator=(const pair& pr)
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };

    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        if (lhs.first == rhs.first && lhs.second == rhs.second)
        {
            return true;
        }
        return false;
    }

    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        if (lhs.first < rhs.first)
        {
            return true;
        }
        else
        {
            if (lhs.second < rhs.first)
            {
                return true;
            }
        }

        return false;
    }

    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }

    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 first, T2 second)
    {
        return pair<T1, T2>(first, second);
    }
}

#endif