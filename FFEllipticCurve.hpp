#ifndef FFELLIPTICCURVE_H
#define FFELLIPTICCURVE_H

#include <vector>
#include <iostream>
#include <limits.h>

#include "FFElement.hpp"

using namespace std;

template<int P>
class FFEllipticCurve
{
    public:
        typedef FFElement<P> Element;
        class Point
        {
            public:
                static Point One;

                Point(const Point& rhs)
                {
                    cx = rhs.cx;
                    cy = rhs.cy;
                    curve = rhs.curve;
                }

                // Equivalence and Negation
                Point& operator=(const Point& rhs)
                {
                    cx = rhs.cx;
                    cy = rhs.cy;
                    curve = rhs.curve;
                    return *this;
                }
                Point operator-()
                {
                    return Point(cx, -cy);
                }
                friend bool operator==(const Point& lhs, const Point& rhs)
                {
                    return (lhs.curve == rhs.curve) && (lhs.cx == rhs.cx) && (lhs.cy == rhs.cy);
                }
                friend bool operator!=(const Point& lhs, const Point& rhs)
                {
                    return (lhs.curve != rhs.curve) || (lhs.cx != rhs.cx) || (lhs.cy != rhs.cy);
                }
                friend Point operator+(const Point& lhs, const Point& rhs)
                {
                    Element xR, yR;
          lhs.addPoint(lhs.cx, lhs.cy, rhs.cx, rhs.cy, xR, yR);
          return Point(xR, yR, *lhs.curve);

                }
                friend Point operator*(int k, const Point& rhs)
                {
                    return Point(rhs).operator*=(k);
                }
                Point& operator+=(const Point& rhs)
                {
                    addPoint(cx, cy, rhs.cx, rhs.cy, cx, cy);
                    return *this;
                }
                Point& operator*=(int k)
                {
                    *this = multiplyPoint(k, *this);
                    return *this;
                }
                friend ostream& operator<<(ostream& o, const Point& p)
                {
                    return o << "(" << p.cx << ", " << p.cy << ")";
                }

                // Accessors
                Element getX() const
                {
                    return cx;
                }
                Element getY() const
                {
                    return cy;
                }

                unsigned int order()
                {
                  Point r = *this;
                  unsigned int n = 0;
                  while(r.getX() != 0 && r.getY() != 0)
                  {
                    n++;
                    r += *this;
                    if(n == UINT_MAX) break;
                  }
                  return n;
                }

            private:
                friend class FFEllipticCurve<P>;
                Element cx;
                Element cy;
                FFEllipticCurve* curve;

                Point(int x, int y) : cx(x), cy(y), curve(0){}
                Point(int x, int y, FFEllipticCurve<P>& ec) : cx(x), cy(y), curve(&ec){}
                Point(const Element& x, const Element& y, FFEllipticCurve<P>& ec) : cx(x), cy(y), curve(&ec){}

                void addPoint(Element x, Element y, Element xx, Element yy, Element& xR, Element& yR) const
                {

                    // Addition Identity
                    if(x == 0 && y == 0)
                    {
                        xR = xx;
                        yR = yy;
                        return;
                    }
                    if(xx == 0 && yy == 0)
                    {
                        xR = x;
                        yR = y;
                        return;
                    }

                    // J + -J = O (point at infinity)
                    if(y == -yy)
                    {
                        xR = yR = 0;
                        return;
                    }

                    // s = (yj - yk)/(xj - xk)
                    Element slope;
                    if(x == xx && y == yy)
                    {
                        slope = (3 * (x.value() * x.value()) + curve->getA()) / (2 * y);
                        xR = (slope * slope) - (2 * x);
                    }
                    else
                    {
                      slope = (y - yy) / (x - xx);
                      xR = (slope * slope) - x - xx;
                    }


                    if(slope != 0)
                    {
                        yR = -y + slope * (x - xR);
                    }
                    else
                    {
                        xR = 0;
                        yR = 0;
                    }
                }
                Point multiplyPoint(int k, const Point& a)
                {
                    Point prod = a;
                    Point result = Point(0, 0, *curve);

                    int i = 0;
                    int j = 0;
                    int bits = k;

                    while(bits)
                    {
                        if(bits & 1)
                        {
                            doublePoint(i - j, prod);
                            result += prod;
                            j = i;
                        }
                        bits >>= 1;
                        i++;
                    }
                    return result;
                }
                void doublePoint(int m, Point& acc)
                {
                    if( m > 0 )
                    {
                        Point r = acc;
                        for(int i = 0; i < m; i++)
                        {
                            r += r;
                        }
                        acc = r;
                    }
                }
        };

        FFEllipticCurve(int a, int b) : ca(a), cb(b)
        {
            generateCurve();
        }
        Point operator[](int n)
        {
            return points[n];
        }
        FFElement<P> getA() const
        {
            return ca;
        }
        FFElement<P> getB() const
        {
            return cb;
        }
        int degree() const
        {
            return P;
        }
        size_t size() const
        {
            return points.size();
        }
        ostream& printPoints(ostream& o, int columns)
        {
            int curCol = 0;
            typename FFEllipticCurve::CurveList::iterator iter = points.begin();
            for(; iter != points.end(); iter++)
            {
                o << "(" << (*iter).getX().value() << ", " << (*iter).getY().value() << ") ";
                curCol++;
                if(curCol > columns)
                {
                    o << "\n";
                    curCol = 0;
                }
            }
            return o;
        }

    private:
        typedef vector<Point> CurveList;

        Element ca;
        Element cb;
        CurveList points;

        void generateCurve()
        {
            int xValues[P];
            int yValues[P];

            for(int i = 0; i < P; i++)
            {
                int sqr = i * i;
                xValues[i] = ((i * sqr) + (ca.value() * i) + cb.value()) % P;
                yValues[i] = sqr % P;
            }

            for(int x = 0; x < P; x++)
            {
                for(int y = 0; y < P; y++)
                {
                    if(xValues[x] == yValues[y])
                    {
                      cout << x << " " << y << endl;
                      points.push_back(Point(x, y, *this));
                    }
                }
            }
        }
};

template<int T>
typename FFEllipticCurve<T>::Point FFEllipticCurve<T>::Point::One(0, 0);

#endif // FFELLIPTICCURVE_H
