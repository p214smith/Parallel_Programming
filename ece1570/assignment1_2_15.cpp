#include <iomanip>
#include <iostream>
#include <string>
#include <bits/stdc++.h>


using namespace std;

double speedups(int n, int p)
{
	double T,S;
	S = n*n;
	T = ((n*n)/p) + (log(p)/log(2));
	T = S/T;
	return T;
}

double efficiency(int n, int p)
{
	double T,S;
	S = n*n;
	T = ((n*n)/p) + (log(p)/log(2));
	T = S/(T*p);
	return T;
}

int main()
{
	int n = 10, p =1;
	double speed,eff;
	cout << "n is fixed:" << endl<< "\tspeed:\tefficiency:" << endl;
	for ( p = 1; p <= 128;)
	{
		speed = speedups(n,p);
		eff = efficiency(n,p);
		cout << "\t"<< speed << "\t"<<eff<< endl;
		p = p * 2;
	}
	cout << endl << "p is fixed:" << endl << "\tspeed:\tefficiency:"<< endl;
	
	p = 2;
	for ( n = 10; n <= 320;)
	{
		speed = speedups(n,p);
		eff = efficiency(n,p);
		cout << "\t"<< speed << "\t"<<eff<< endl;
		n = n * 2;
	}
	
	return 0;
}
