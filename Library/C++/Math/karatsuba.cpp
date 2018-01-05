typedef vector<int> VI;
VI MULTI(VI X, VI Y) {
	int N = X.size(), N2 = N / 2;
	VI R(N * 2, 0);
	if (N > 100) {
		VI X2(X.begin() + N2, X.end());
		VI Y2(Y.begin() + N2, Y.end());
		X.resize(N2); Y.resize(N2);

		VI A = MULTI(X, Y);
		VI B = MULTI(X2, Y2);
		for (int i = 0; i < N2; i++) X2[i] += X[i], Y2[i] += Y[i];
		VI C = MULTI(X2, Y2);

		for (int i = 0; i < A.size(); i++) R[i] += A[i], C[i] -= A[i];
		for (int i = 0; i < B.size(); i++) R[i + N2 * 2] += B[i], C[i] -= B[i];
		for (int i = 0; i < C.size(); i++) R[i + N2] += C[i];
	}
	else {
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) R[i + j] += X[i] * Y[j];
	}
	return R;
}