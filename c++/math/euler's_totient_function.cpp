const int MAXS = 40;

int phi[MAXS + 1];

bool notPrime[MAXS + 1];

void Euler_Totient_Function(void) {
	for (int i = 1; i <= MAXS; i++) {
		phi[i] = i;
	}
	notPrime[1] = true;
	for (int i = 2; i <= MAXS; i++) {
		if (notPrime[i] == true) {
			continue;
		}
		phi[i] = (phi[i] / i) * (i - 1);
		for (int j = i + i; j <= MAXS; j += i) {
			notPrime[j] = true;
			phi[j] = (phi[j] / i) * (i - 1);
		}
	}
}