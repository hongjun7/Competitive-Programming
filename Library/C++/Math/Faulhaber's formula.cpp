/* 1^K + 2^K + ... + N^K */
/* O(K^2) */
long long mod = 1000000007;
long long s[55], N, c[55][55], d[55][55];
int K;
long long f(long long a, long long b) {
	if (b == 0) return 1;
	if (b == 1) return a % mod;
	long long v = f(a, b / 2);
	if (b & 1) return (((a*v) % mod)*v) % mod;
	return (v*v) % mod;
}
int main() {
	c[0][0] = c[1][0] = c[1][1] = 1;
	scanf("%lld%d", &N, &K);
	for (int i = 2; i <= K + 1; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	s[0] = N%mod;
	for (int j = 1; j <= K + 1; j++) d[0][j] = (s[0] * c[j][0]) % mod;
	for (int k = 1; k <= K; k++) {
		long long a = (N + 1);
		for (int j = 2; j <= k + 1; j++) a = (a*(N + 1)) % mod;
		a--;
		if (a < 0) a += mod;
		for (int j = 0; j < k; j++) a = (a - d[j][k + 1] + mod) % mod;
		s[k] = (a * f(c[k + 1][k], mod - 2)) % mod;
		for (int j = k; j <= K + 1; j++) d[k][j] = (s[k] * c[j][k]) % mod;
	}
	printf("%lld", s[K]);
}