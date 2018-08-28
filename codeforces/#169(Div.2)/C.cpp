#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;

int N, Q, A[MAXN];
int W[MAXN];

int main() {
	scanf("%d%d",&N,&Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}
	sort(A+1,A+N+1);
	for (int i = 1; i <= Q; i++) {
		int l, r; scanf("%d%d",&l,&r);
		W[l]++; W[r+1]--;
	}
	for (int i = 1; i <= N; i++) {
		W[i] += W[i-1];
	}
	sort(W+1,W+N+1);
	long long ans = 0;
	for (int i = N; i >= 1; i--) {
		ans += 1LL*W[i]*A[i];
	}
	printf("%lld\n", ans);
}