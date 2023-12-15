#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <complex>

using namespace std;
#define PI 3.14159265358

void split_signal(complex<double> *sig, int len){
	complex<double>* even_sig = new complex<double>[len/2];
	complex<double>* odd_sig = new complex<double>[len/2];
	
	int even_i = 0, odd_i = 0;
	for ( int i = 0; i < len; i++)
	{
		if ( ( i % 2) == 0){
			even_sig[even_i] = sig[i];
			even_i++;
		}
		else
		{
			odd_sig[odd_i] = sig[i];
			odd_i++;
		}
	}
	int size = len/2;
	memcpy(sig, even_sig, sizeof(complex<double>)*size);
	memcpy(sig+size, odd_sig, sizeof(complex<double>)*size);

	delete[] even_sig;
	delete[] odd_sig;
}
void fast_fourier_transform(complex<double> *sig, double N){
	if (N == 1)
	return;
	
	int split = N/2;
	complex<double> imag(0,1);
	complex<double> h_n = exp((2*PI*imag)/N);
	complex<double> h = 1;
	
	split_signal(sig,split*2);
	
	fast_fourier_transform(sig,split);
	fast_fourier_transform(sig+split,split);
	
	complex<double> even(0,0), odd(0,0);
	for (int i = 0; i < split;i++){
		even = sig[i];
		odd = sig[i+split];
		sig[i] = even + h*odd;
		sig[i+split] = even - h*odd;
		
		h = h*h_n;
	}
}
int main(int argc, char * argv[])
{
	int samples = 1024;
	ifstream infile;
	complex<double>* signal = new complex<double>[samples];
	complex<double>* signal2 = new complex<double>[samples];
	complex<double>* signal3 = new complex<double>[samples];
	complex<double>* signal4 = new complex<double>[samples];
	infile.open("office.ascii");
	for (int i = 0; i < samples; i++)
		infile >> signal[i];
	for (int i = 0; i < samples; i++)
		infile >> signal2[i];
	for (int i = 0; i < samples; i++)
		infile >> signal3[i];
	for (int i = 0; i < samples; i++)
		infile >> signal4[i];
	infile.close();
	fast_fourier_transform(signal,samples);
	fast_fourier_transform(signal2,samples);
	fast_fourier_transform(signal3,samples);
	fast_fourier_transform(signal4,samples);
	ofstream outfile;
	for (int i = 0; i < samples;i++){
		signal2[i] = signal2[i] + signal[i];
		signal3[i] = signal3[i] + signal2[i];
		signal4[i] = signal4[i] + signal3[i];
	}
	outfile.open("result.txt");
	outfile << "Fast Fourier Transform Results:" << endl;
	outfile << "Frame 1 result: " << endl;
	for(int i = 0; i < samples;i++)
	outfile << signal[i] << endl;
	
	outfile << "Frame 2 result: " << endl;
	for(int i = 0; i < samples;i++)
	outfile << signal2[i] << endl;
	
	outfile << "Frame 3 result: " << endl;
	for(int i = 0; i < samples;i++)
	outfile << signal3[i] << endl;
	
	outfile << "Frame 4 result: " << endl;
	for(int i = 0; i < samples;i++)
	outfile << signal4[i] << endl;
	
	outfile.close();
	
	delete[] signal;
};
	
	
	
	

