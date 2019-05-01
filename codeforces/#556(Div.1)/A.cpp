#include <bits/stdc++.h>
using namespace std;

int N;
int one, two;

bool P[400005];
int prime[400005], pn;

int main() {
	for (int i = 2; i <= 400000; i++) {
		if (P[i]) continue;
		prime[++pn] = i;
		for (int j = i+i; j <= 400000; j+=i) P[j] = 1;
	}
	scanf("%d",&N);
	for (int i = 1; i <= N; i++) {
		int x; scanf("%d",&x);
		(x == 1) ? (one++) : (two++);
	}
	int cur = 0, i = 1;
	while (cur + one + 2*two >= prime[i] && i <= pn) {
		int diff = prime[i] - cur;
		int useTwo = min(two, diff / 2);
		int useOne = diff - 2*useTwo;
		if (useOne > one) break;
		two -= useTwo; one -= useOne;
		while (useTwo-- > 0) printf("2 ");
		while (useOne-- > 0) printf("1 ");
		cur = prime[i++];
	}
	while (two-- > 0) printf("2 ");
	while (one-- > 0) printf("1 ");
}