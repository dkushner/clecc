#include "FFUtil.hpp"

int FFUtil::extEuclideanGCD(int a, int b, int& x, int& y)
{
    x = 1;
    y = 0;

    int xx = 0;
    int yy = 1;

    int g = a;
    int gg = b;

    while(gg != 0)
    {
        int quotient = g / gg;
        int txx = x - quotient * xx;
        int tyy = y - quotient * yy;
        int tgg = g - quotient * gg;

        x = xx;
        y = yy;
        g = gg;

        xx = txx;
        yy = tyy;
        gg = tgg;
    }
    return g;
}

/*
 *  ModInverse
 *
 *  Description:
 *
 *      Finds the inverse of r mod n by solving the linear
 *      congruence defined by ri * r = 1 (mod n) where ri is
 *      the modular inverse of r and is unique for this modulus.
 *
 */
int FFUtil::modInverse(int r, int n)
{
    r = r % n;
    int x, y, gcd;

    gcd = FFUtil::extEuclideanGCD(r, n, x, y);
    return (gcd != 1) ? 0 : x % n;
}
