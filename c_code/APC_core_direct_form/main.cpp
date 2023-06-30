#include <math.h>
#include <cstring>
#include "wav_lib.h"

void allpasschain_DirForm2(float& x, float alpha, float* v, int N);

void main(){

	// Declaration
	WAVInfo info;
	int *x_src;
	char file_wav[] = "test_sin.wav"; // Audio file
	char file_out_wav[] = "proc_test_sin.wav"; // Audio file
	x_src = wavread(file_wav, info);

	int Npt = info.NumberOfSamples;
	int N = 2048;

	// convert to Float
	float* x = new float[Npt];
	for (int i = 0; i < Npt; i++) {
		x[i] = (float)(x_src[i]*1.0f) / 32768;
	}

	float *v = new float[N + 1];	// allpass chain outputs
	memset(v, 0, sizeof(float) * N);

	float* v_N_out = new float[Npt];	// last allpass chain element output

	float alpha = 0.2;

	//Processing cycle	
	//Allpass chain implementation	(Direct-form II)
	for(int n=0; n<Npt; n++){
		allpasschain_DirForm2(x[n], alpha, v, N);
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
	delete[] v;
	delete[] v_N_out;
	delete[] y;
}

void allpasschain_DirForm2(float& x, float alpha, float* v, int N)
{
	float R1, R2, R3;

	R1 = x;
	R2 = v[0];
	v[0] = R1;

	for (int i = 1; i < N; i++) {
		R3 = R2;
		R2 = v[i];
		R1 = (R2 - R1) * alpha + R3;
		v[i] = R1;
	}
}