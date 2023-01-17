#include "./base_iterator.hpp"
#include "../utils/traits.hpp"

namespace ft
{
    template <typename T>
    class Random_access_iterator : public Base_iterator<T>
    {
    public:
        typedef typename ft::iterator_traits<T>::difference_type difference_type;
        typedef typename ft::iterator_traits<T>::value_type value_type;
        typedef T*               pointer;
        typedef T&             reference;
        typedef typename ft::Random_access_iterator_tag iterator_category;
    private:
        pointer _ptr;
    public:
        Random_access_iterator()
        : _ptr(0) {}
        // 포인터(T*)를 통해 생성하는 생성자
        Random_access_iterator(pointer ptr)
        : _ptr(ptr) {}
        // 이터레이터 복사 생성자.
        Random_access_iterator(const Random_access_iterator& op)
        : _ptr(op._ptr) {}
        // 소멸자
        virtual ~Random_access_iterator() {}

        /**********연산자***********/
        Random_access_iterator& operator=(const Random_access_iterator& op)
        {
            // op 임의접근반복자 참조.
            if (this == &op)
            {
                return (*this);
            }
            this->_ptr = op._ptr; // _ptr이 뭐든간에 =가 정의되어 있어야함.
            return (*this); // 반복자원본반환. 반환자도 참조형.
        }
        // 포인터 연산자. 원소 반환.
        reference operator*(void) const
        {
            return (*_ptr); // 원소의 원본반환.
        }
        // 화살표 연산자, 포인터 멤버 연산자.
        // 원소의 맴버(변수나 함수)로 접근할때 사용
        pointer operator->(void)
        {
            //return &(this->operator*());
            //return &(operator*());
            return _ptr; //?
        }
        // 후위 증가 연산자. 다음 원소로.
        Random_access_iterator& operator++(void)
        {
            _ptr++; // 연산자가 정의가 되어 있어야함. -> 컴파일 에러 발생.
            return (*this);
        }
        // 전위 증가 연산자.
        Random_access_iterator operator++(int)
        {
            Random_access_iterator rtn(*this); // 복사본
            this->operator++();
            return (rtn);
        }
        // 후위 감소
        Random_access_iterator& operator--(void)
        {
            _ptr--;
            return (*this);
        }
        // 전위 감소
        Random_access_iterator operator--(int)
        {
            Random_access_iterator rtn(*this);
            operator--();
            return (rtn);
        }
        // typename ft::Random_access_iterator<T>::difference_type
        // 덧샘 연산 -> n번째 뒤의 원소 접근
        Random_access_iterator operator+(difference_type n) const
        {
            return (_ptr + n); // T 포인터에 대한 +연산이 정의되어 있어야함.
        }
        // 뺄샘 연산
        Random_access_iterator operator-(difference_type n) const
        {
            return (_ptr - n);
        }
        // 더하고 대입.연산한 원소를 반환.
        Random_access_iterator& operator+=(difference_type n)
        {
            _ptr += n;
            return (*this);
        }
        // 빼고 대입
        Random_access_iterator& operator-=(difference_type n)
        {
            _ptr -= n; //
            return (*this);
        }
        // [연산.]
        reference operator[](difference_type n)
        {
            return (*(operator+(n))); // *(_ptr + n)
        }
    };

    /* For iterator == const_iterator */
    // L과 R이 서로 다르지만, 원소끼리 비교 연산이 정의 되어 있을 때.
    template<typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type
    operator==(const ft::Random_access_iterator<T_L> lhs,
            const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    // != 비교 연산
    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type
    operator!=(const ft::Random_access_iterator<T> lhs,
            const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }
    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type
    operator!=(const ft::Random_access_iterator<T_L> lhs,
            const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }
    // 비교연산
    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type
    operator<(const ft::Random_access_iterator<T> lhs,
            const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }
    // 서로 다른거
    template<typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type
    operator<(const ft::Random_access_iterator<T_L> lhs,
            const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type
    operator<=(const ft::Random_access_iterator<T> lhs,
            const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type
    operator<=(const ft::Random_access_iterator<T_L> lhs,
            const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type operator>
        (const ft::Random_access_iterator<T> lhs, const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::Random_access_iterator<T_L>::difference_type operator>
        (const ft::Random_access_iterator<T_L> lhs, const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type
    operator>=(const ft::Random_access_iterator<T> lhs,
            const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    ft::Random_access_iterator<T> operator+(
        typename ft::Random_access_iterator<T>::difference_type n,
        typename ft::Random_access_iterator<T>& rai)
    {
        return (&(*rai) + n);
    }

    template <typename T>
    typename ft::Random_access_iterator<T>::difference_type operator-
        (const ft::Random_access_iterator<T> lhs, const ft::Random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template<typename T_L, typename T_R>
        typename ft::Random_access_iterator<T_L>::difference_type
        operator-(const ft::Random_access_iterator<T_L> lhs,
                const ft::Random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }
}