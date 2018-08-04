#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 505;

int N, K;
int A[MAXN];

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}
	double ans = 1e18;
	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = i; j <= N; j++) {
			sum += A[j];
			double m = sum / (double)(j - i + 1);
			if (j - i + 1 >= K) {
				double sq = 0;
				for (int k = i; k <= j; k++) {
					sq += (double)(A[k] - m)*(double)(A[k] - m);
				}
				sq /= (j - i + 1);
				if (ans > sq)
					ans = sq;
			}
		}
	}
	printf("%.10lf\n", sqrt(ans));
}