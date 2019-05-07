#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int N, K;
int A[MAXN];
bool D[MAXN], X[MAXN];

int main() {
	scanf("%d%d",&N,&K);
	for (int i = 1; i <= K; i++) {
		scanf("%d",&A[i]);
		D[A[i]] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) ans += !D[i], D[i] = 0;
	
	for (int i = 1; i <= K; i++) {
		X[A[i]] = 1;
		if (X[A[i] - 1]) D[A[i] - 1] = 1;
	}
	for (int i = 1; i < N; i++) ans += !D[i], D[i] = 0;
	memset(X, 0, sizeof(X));
	
	for (int i = 1; i <= K; i++) {
		X[A[i]] = 1;
		if (X[A[i] + 1]) D[A[i] + 1] = 1;
	}
	for (int i = 2; i <= N; i++) ans += !D[i], D[i] = 0;
	printf("%d\n", ans);
}