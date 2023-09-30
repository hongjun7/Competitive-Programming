/*
Conditions
���� 1) DP ��ȭ�� ��
D[i][j]=min{i<k<j}(D[i][k]+D[k][j])+C[i][j]
���� 2) Quadrangle Inequalty (�簢�ε��)
C[a][c]+C[b][d]��C[a][d]+C[b][c],a��b��c��d
���� 3) Monotonicity (������)
C[b][c]��C[a][d],a��b��c��d
*/

for (int i = 1; i <= N; i++) D[i - 1][i] = initial_value, K[i - 1][i] = i;
for (int d = 2; d <= N; d++) {
	// d = j-i
	for (int i = 0; i + d <= N; i++) {
		int j = i + d;
		D[i][j] = inf;
		for (int k = K[i][j - 1]; k <= K[i + 1][j]; k++) {
			int v = D[i][k] + D[k][j] + C[i][j];
			if (D[i][j] > v)
				D[i][j] = v, K[i][j] = k;
		}
	}
}