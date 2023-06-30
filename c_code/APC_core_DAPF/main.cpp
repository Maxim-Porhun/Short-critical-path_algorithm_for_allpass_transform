#include <math.h>
#include <cstring>
#include "wav_lib.h"

void allpasschain_fast2(float *v, float *w, float alpha, float alpha_compl, float alpha_sq, float alpha3,  int N2p1);

void main(){

	// Declaration
	WAVInfo info;
	int *x_src;
	char file_wav[] = "test_sin.wav"; // Audio file
	char file_out_wav[] = "proc_test_sin.wav"; // Audio file
	x_src = wavread(file_wav, info);

	int Npt = info.NumberOfSamples;
	int N = 2048;
	int N2p1 = (N / 2) + 1;

	// convert to Float
	float* x = new float[Npt];
	for (int i = 0; i < Npt; i++) {
		x[i] = (float)(x_src[i] * 1.0f) / 32768;
	}

	float *b = new float[N];
	float *v = new float[N + 1];	// allpass chain outputs
	float *w = new float[N + 1];	// allpass chain memory elements
	float* v_N_out = new float[Npt];	// last allpass chain element output

	float alpha = 0.2;
	const float A = alpha*alpha;
	const float B = 1 - alpha*alpha;
	const float C = -alpha*(1 - alpha*alpha);

	memset(v, 0, sizeof(float)*N);
	memset(w, 0, sizeof(float)*N);

	//Processing cycle	
	// Allpass chain implementation	(State-space variable, 2 section at-a-time)

	for(int n=0; n<Npt; n++)
	{		
		v[0] = x[n];
		allpasschain_fast2(v, w, alpha, B, A, C, N2p1);
		v_N_out[n] = v[N - 1];
	}
	printf("End of processing \n");

	// convert to Int
	int* y = new int[Npt];
	for (int i = 0; i < Npt; i++) {
		y[i] = (int)(v_N_out[i] * 32768);
	}
	wavwrite(file_out_wav, info, y);

	// End of processing		
	getchar();

	delete[] w;
	delete[] v;
	delete[] v_N_out;
	delete[] y;
}

void allpasschain_fast2(float *v, float *w, float alpha, float B, float A, float C,  int N2p1)
{
	float r1, r2, r3, r4, r5, r6, r7;
	for (int i = 1; i < N2p1; i++)
	{			
		// First level
		r1 = v[2 * i - 2] * A;
		r2 = v[2 * i - 2] * alpha;
		r3 = w[2 * i - 1] * B;
		r4 = w[2 * i - 1] * alpha;
		r5 = w[2 * i - 1] * C;
		r6 = w[2 * i] * alpha;				
		r7 = w[2 * i] * B;						

		// Second level
		r3 = r3 - r2;
		r1           = r1 + r5;		
		w[2 * i - 1] = r4 + v[2 * i - 2];

		// 3rd level		
		r1       = r1 + r7;			
		w[2 * i] = r3 + r6;

		// Store
		v[2 * i - 1] = r3;
		v[2 * i]     = r1;
	}
}