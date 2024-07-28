#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct base64 {
	char* a;
	size_t b;
};

struct base64 encode(char*, size_t);
struct base64 decode(char*, size_t);
struct base64 alloc(size_t);
uint8_t test(char*, size_t);

struct base64 allocBase64(size_t size){
	struct base64 ret;
	size_t x = size-1;
	size_t m = ((x/3)*4) + (4*((x%3)!=0));
	char* p = malloc(m);
	ret.a = p;
	ret.b = m;
	return ret;
}

struct base64 encode(char* input, size_t size){
	struct base64 x = allocBase64(size);
	size_t i = 0;
	size_t j = 0;
	char* p = x.a;

	while(i < (x.b)){
		p[i+0] = input[j+0] >> 2;
		
		if(input[j+1] == '\0'){
			p[i+1] = (input[j+0] << 4) & 63;
			p[i+2] = '@';
			p[i+3] = '@';
			i += 4;
			j += 3;
		}
		
		p[i+1] = ((input[j+0] << 4) + (input[j+1] >> 4)) & 63;
		
		if(input[j+2] == '\0'){
			p[i+2] = ((input[j+1] & 15) << 2) & 63;
			p[i+3] = '@';
			i += 4;
			j += 3;
		}
		
		p[i+2] = ((input[j+1] & 15) << 2) + (input[j+2] >> 6);
		p[i+3] = input[j+2] & 63;
		i += 4;
		j += 3;
	}
	return x;
}

struct base64 decode(char* input, size_t size){
	struct base64 x = allocBase64(size);
	char* f = x.a;
	for(size_t i = 0; i < x.b; ++i){
		if(input[i] <= 25) f[i] = input[i] + 65;
		else if(input[i] <= 51) f[i] = input[i] + 71;
		else if(input[i] <= 61) f[i] = input[i] - 4;
		else if(input[i] == 62) f[i] = '+';
		else if(input[i] == 63) f[i] = '/';
		else if(input[i] >= 64) f[i] = '=';
	}
	return x;
}

uint8_t test(char* input, size_t size){
	struct base64 testE = encode(input, size);
	struct base64 testD = decode(testE.a, size);
	printf("ASCII:\t\t%s\nIndices\t\t", input);
	for(size_t i = 0; i < (testE.b); ++i){
		printf("%d ", testE.a[i]);
	}
	printf("\nBase64\t\t%s\n", testD.a);
	free(testE.a);
	free(testD.a);
	printf("================\n");
	return 0;
}

int main(){
	enum {A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, Z};
	char msgA[A] = "";
	char msgB[B] = "M";
	char msgC[C] = "Ma";
	char msgD[D] = "Man";
	char msgE[E] = "Many";
	char msgF[F] = "Many ";
	char msgG[G] = "Many h";
	char msgH[H] = "Many ha";
	char msgI[I] = "Many han";
	char msgJ[J] = "Many hand";
	char msgK[K] = "Many hands";
	char msgL[L] = "Many hands ";
	char msgM[M] = "Many hands m";
	char msgN[N] = "Many hands ma";
	char msgZ[Z] = "Many hands mak";
	test(msgA, A);
	test(msgB, B);
	test(msgC, C);
	test(msgD, D);
	test(msgE, E);
	test(msgF, F);
	test(msgG, G);
	test(msgH, H);
	test(msgI, I);
	test(msgJ, J);
	test(msgK, K);
	test(msgL, L);
	test(msgM, M);
	test(msgN, N);
	test(msgZ, Z);
	return 7;
} 
