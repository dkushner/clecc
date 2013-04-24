#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include <cuda.h>

#include "FFUtil.hpp"
#include "FFEllipticCurve.hpp"

using namespace std;

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
	// Init Elliptic Curve
	typedef FFEllipticCurve<263> Curve;

    int a;
    int b;

    cout << "Please enter the specified domain variable." << endl;
    cout << "A: ";
    cin >> a;
    cout << "B: ";
    cin >> b;

    Curve curve(a, b);

    return 0;
}
