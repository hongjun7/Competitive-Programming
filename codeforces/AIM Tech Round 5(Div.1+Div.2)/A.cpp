#include <bits/stdc++.h>
using namespace std;

int N, M;
char A[222][222];

vector <pair<int, int>> P;

int main() {
	scanf("%d%d",&N,&M);
	for (int i = 1; i <= N; i++) {
		scanf("%s",A[i]+1);
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (A[i][j] == 'B') P.push_back({i, j});
		}
	}
	int Pn = P.size();
	printf("%d %d\n", P[Pn/2].first, P[Pn/2].second);
}