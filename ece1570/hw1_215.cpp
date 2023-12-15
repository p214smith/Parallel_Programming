#include <iomanip>
#include <iostream>
#include <string>
#include <bits/stdc++.h>


using namespace std;

double speedups(int n, int p)
{
	double T;
	T = ((n*n)/p) + (log(p)/log(2));
	return T;
}

int main()
{
	int n = 10, p =1;
	double speed;
cout << "n is fixed:" << endl << endl;
	for ( p = 1; p <= 128;)
	{
		speed = speedups(n,p);
		cout << speed << endl;
		p = p * 2;
	}
	cout << endl << "p is fixed:" << endl << endl;
	
	p = 2;
	for ( n = 10; n <= 320;)
	{
		speed = speedups(n,p);
		cout << speed << endl;
		n = n * 2;
	}
	
	return 0;
}
