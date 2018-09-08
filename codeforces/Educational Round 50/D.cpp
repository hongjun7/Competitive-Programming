#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5+5;

int N, M;
int A[MAXN], B[MAXN];

int main() {
	scanf("%d",&N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}
	scanf("%d",&M);
	for (int i = 1; i <= M; i++) {
		scanf("%d", &B[i]);
	}
	
	int ans = 0;
	int a = 1, b = 1; long long as = A[1], bs = B[1];
	while (a <= N && b <= M) {
		if (as < bs) as += A[++a];
		else if (as > bs) bs += B[++b];
		else {
			ans++;
			as = A[++a], bs = B[++b];
		}
	}
	if (a <= N || b <= M) ans = -1;
	printf("%d\n", ans);
}