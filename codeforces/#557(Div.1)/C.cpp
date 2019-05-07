#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int N;
int A[MAXN];

int main() {
	scanf("%d",&N);
	int m = 2e9;
	for (int i = 1; i <= N; i++) {
		scanf("%d",&A[i]);
		m = min(m, A[i]);
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (m == A[i]) cnt++;
	}
	if (cnt > N/2) puts("Bob");
	else puts("Alice");
}