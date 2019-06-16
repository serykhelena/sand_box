#include <iostream>
#include <cstdint>

using namespace std; 

uint32_t factorial(const uint32_t& n)
{
	if (n == 0 )
		return 1; 
	else if( n < 13 )	// limitation of type uint32_t 
		return n * factorial(n - 1);
	else
	{
		cout << "Sorry, the result cannot be obtained" << endl; 
		return 0;
	} 
}

uint32_t calBinominalCoeff(const uint32_t& n, const uint16_t& k)
{
	if( n <= 12 )
		return factorial(n) / (factorial(k) * factorial(n - k));
	else if( n < 31 ) // in case of caclulation 13! and more => overflowing of uint32_t
	{
		uint32_t res = 1; 
		for( uint32_t i = 1; i <= k; i++ )
		{
			res *= n - k + i; 	// zB. 	13!/(6!7!) * 7!/7! 
			res /= i;			// 		8*9*10*11*12*13 / 1*2*3*4*5*6 			
		}
		return res; 
	}
	else
	{
		cout << "Sorry, the result cannot be obtained" << endl; 
		return 0;  
	} 
}

int main()
{
	for (uint32_t n = 1; n <= 31; n++)
	{
	    cout << n << " : ";
		cout << calBinominalCoeff(n, n / 2) << endl; 
	}

	return 0; 
}