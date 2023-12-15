#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;

using namespace std::chrono;

void staticMM(const int M, const double *A, const double *B, double *C){
	int i, j, k;
	for ( i = 0; i < M ; i++){
		for ( j = 0; j < M; j++){
			double cij = C[j*M+i];
			for (k = 0; k < M; k++){
				cij += A[k*M+i] * B[j*M+k];
			}
			C[j*M+i] = cij;
		}
	}
}

void partitionedMM(const int M, const double *A, const double *B, double *C){
	int i, j, k, blocksize, d, e, f;
	blocksize = M*.25;
	for (d = 0; d < M ; d += blocksize){
		for (e = 0; e < M ; e += blocksize){
			for ( f = 0; f < M ; f += blocksize){
				for ( i = 0; i < blocksize ; i++){
					for ( j = 0; j < blocksize ; j++){
						double cij = C[(e+j) * M + (d + i)];
						for (k = 0; k < blocksize; k++){
							cij += A[(f+k) * M + (d + i)] * B[(e+j) * M +( f + k )];
						}
						C[(j + e) * M + ( d + i)] = cij;
					}
				}
			}
		}
	}
}

int main()
{
	int M;
	double *A;
	double *B;
	double *C;
	
	cout << "What is size of Matrix: " << endl;
	cin >> M;
	A = (double*) malloc(M*M*sizeof(double));
	B = (double*) malloc(M*M*sizeof(double));
	C = (double*) malloc(M*M*sizeof(double));
	
	for (int i = 0; i < M*M; i++){
		A[i] = 2;
		B[i] = 2;
	}
	auto start = high_resolution_clock::now();
	staticMM(M,A,B,C);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop-start);
	cout << "Time taken by Naive Matrix Multiply is " << duration.count() << " microseconds." << endl;
	
	start = high_resolution_clock::now();
	partitionedMM(M,A,B,C);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop-start);
	cout << "Time taken by Partitioned Matrix Multiply is " << duration.count() << " microseconds." << endl;
	
	return 0;
}
	
	
