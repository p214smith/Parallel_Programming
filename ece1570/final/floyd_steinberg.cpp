#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>
using namespace std;

int main()
{
	
	int N = 512;
	int image[N][N];
	
	srand((unsigned) time(NULL));
	
#pragma omp parallel for
	for (int i = 0; i < N*N ;i++){
		image[i/512][i%512] = (rand() %256);
	}

	for (int i = 0 ;i < N-1;i++){
		for (int j = 1; j < N - 1; j++){
	#pragma oss task      									\
			
			int old_pixel = image[i][j];
			int new_pixel = trunc(image[i][j]+0.5);
            image[i][j] = new_pixel;
            int quant_error = old_pixel - new_pixel;				\
          image[i][j+1] = image[i][j+1] + (quant_error * 7/16);		\
          image[i+1][j-1] = image[i+1][j-1] + (quant_error * 3/16); \
          image[i+1][j] = image[i+1][j] + (quant_error * 5/16);		\
          image[i+1][j+1] = image[i+1][j+1] + (quant_error * 1/16);	\
			}
		}
		return 0;
};
