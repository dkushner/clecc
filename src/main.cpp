#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "FFUtil.hpp"
#include "FFEllipticCurve.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    typedef FFEllipticCurve<263> Curve;
    
    if(argc != 3)
    {
	cout << "Invalid number of arguments." << endl;
    }	
   
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    Curve curve(a, b);

    return 0;
}
