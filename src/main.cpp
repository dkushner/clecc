#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "FFUtil.hpp"
#include "FFEllipticCurve.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    typedef FFEllipticCurve<263> Curve;
    Curve curve(1, 1);

    return 0;
}
