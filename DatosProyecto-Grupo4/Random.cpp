#include "Random.h"

int Random::nextInt(int n)
{
	int valorSig = 0;
	for (int i = 0; i <= n; i++) {
		valorSig = 0 + rand() % (n);
	}
	return valorSig;
}

double Random::nextDouble(){
	double val;
	for (double i = 0.0; i <= 1.0; i++) {
		val = double(1 + rand() % (10)) / 10;
	}
	return val;
}
