template <typename T>
bool default_compare(T a, T b) {
	return a < b;
}

template <typename T> void merge_sort(T* st, T* en, bool(*cmp)(T, T) = default_compare) {
	int N = en - st;
	if (N <= 1) return;

	int M = N / 2;
	merge_sort(st, st + M, cmp);
	merge_sort(st + M, en, cmp);

	T* u = new T[N + 1];

	int p1 = 0, p2 = M, p = 0;
	while (p1 < M && p2 < N) {
		if (cmp(st[p1], st[p2])) u[p++] = *(st + p1++);
		else u[p++] = *(st + p2++);
	}
	while (p1 < M) u[p++] = *(st + p1++);
	while (p2 < N) u[p++] = *(st + p2++);
	for (int i = 0; i < N; i++) *(st + i) = u[i];

	delete[] u;
	return;
}