#ifndef FFELEMENT_HPP
#define FFELEMENT_HPP

#include <ostream>

using namespace std;

template<int P>
class FFElement
{
    public:
        FFElement() : val(0){};
        FFElement(const FFElement<P>& elem) : val(elem.val){};
        explicit FFElement(int v)
        {
            setValue(v);
        }

        // Negation and Equivalency Operators
        FFElement operator-() const
        {
            return FFElement(-val);
        }
        FFElement& operator=(int i)
        {
            setValue(i);
            return *this;
        }
        FFElement<P>& operator=(const FFElement<P>& rhs)
        {
            val = rhs.val;
            return *this;
        }
        FFElement<P>& operator*=(const FFElement<P>& rhs)
        {
            val = (val * rhs.val) % P;
            return *this;
        }
        friend bool operator==(const FFElement<P>& lhs, const FFElement<P>& rhs)
        {
            return (lhs.val == rhs.val);
        }
        friend bool operator==(const FFElement<P>& lhs, int rhs)
        {
            return (lhs.val == rhs);
        }
        friend bool operator!=(const FFElement<P>& lhs, int rhs)
        {
            return (lhs.val != rhs);
        }

        // Arithmetic Operators
        //Subtraction
        friend FFElement<P> operator-(const FFElement<P>& lhs, const FFElement<P>& rhs)
        {
            return FFElement<P>(lhs.val - rhs.val);
        }

        // Addition
        friend FFElement<P> operator+(const FFElement<P>& lhs, const FFElement<P>& rhs)
        {
          return FFElement<P>(lhs.val + rhs.val);
        }
        friend FFElement<P> operator+(const FFElement<P>& lhs, int i)
        {
          return FFElement<P>(lhs.val + i);
        }
        friend FFElement<P> operator+(int i, const FFElement<P>& rhs)
        {
          return FFElement<P>(rhs.val + i);
        }

        // Multiplication
        friend FFElement<P> operator*(int n, const FFElement<P>& rhs)
        {
            return FFElement<P>(n * rhs.val);
        }
        friend FFElement<P> operator*(const FFElement<P>& lhs, const FFElement<P>& rhs)
        {
            return FFElement<P>(lhs.val * rhs.val);
        }
        
        // Division
        friend FFElement<P> operator/(const FFElement<P>& lhs, const FFElement<P>& rhs)
        {
            return FFElement<P>(lhs.val * FFUtil::modInverse(rhs.val, P));
        }

        int value() const
        {
            return val;
        }

        // Stream Handler
        template<int T>
        friend ostream& operator<<(ostream& o, const FFElement<T>& e)
        {
            return o << e.val;
        }

    private:
        int val;
        void setValue(int v)
        {
            val = v;
            if(v < 0)
            {
                val = (v % P) + 2 * P;
            }
            val = val % P;
        }

};

#endif // FFELEMENT_HPP
