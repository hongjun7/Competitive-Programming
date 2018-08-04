#include <stdio.h>

int f(int x) {
	if (x == 0) return 0;
	if (x <= 1) return 500 * 10000;
	if (x <= 3) return 300 * 10000;
	if (x <= 6) return 200 * 10000;
	if (x <= 10) return 50 * 10000;
	if (x <= 15) return 30 * 10000;
	if (x <= 21) return 10 * 10000;
	return 0;
}

int g(int x) {
	if (x == 0) return 0;
	if (x <= 1) return 512 * 10000;
	if (x <= 3) return 256 * 10000;
	if (x <= 7) return 128 * 10000;
	if (x <= 15) return 64 * 10000;
	if (x <= 31) return 32 * 10000;
	return 0;
}

int main() {
	int T; for (scanf("%d", &T); T--; ) {
		int a, b; scanf("%d%d", &a, &b);
		printf("%d\n", f(a) + g(b));
	}
}