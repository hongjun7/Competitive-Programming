const int MAXN = 500005;
struct SuffixArray {
	/*
	m : number of alphabet, n : string length
	sa[] : 0 ~ n-1(th) suffix sorting number (starting from 1)
	h[] : adjenct sa's lcp(starting from 2)
	rank[] : 0~n-1(th) suffix's rank (starting from 0)
	ex) banana
	*suffix number
	banana	0
	anana	1
	nana	2
	ana		3
	na		4
	a		5
	*rank[]
	banana	3
	anana	2
	nana	5
	ana		1
	na		4
	a		0
	*sa[]
	a		5
	ana		3
	anana	1
	banana	0
	na		4
	nana	2
	*/
	int n, m, i, j, k, r[MAXN], sa[MAXN], rank[MAXN], h[MAXN], A[MAXN], B[MAXN], V[MAXN], S[MAXN], T;
	void read(char* S) {
		m = 27;
		for (i = 0; S[i]; i++) r[i] = S[i]-'a'+1;
		n = i;
	}
	inline bool cmp(int a, int b, int l) { return B[a] == B[b] && B[a+l] == B[b+l]; }
	void calcSuffixArray(int n) {
		int p;
		for (i = 0; i < m; i++) S[i] = 0;
		for (i = 0; i < n; i++) S[A[i] = r[i]]++;
		for (i = 1; i < m; i++) S[i]+=S[i-1];
		for (i = n-1; i >= 0; i--) sa[--S[A[i]]] = i;
		for (j = 1, p = 1; p<n; j <<= 1, m = p) {
			for (p = 0, i = n-j; i < n; i++) B[p++] = i;
			for (i = 0; i < n; i++) if(sa[i] >= j) B[p++] = sa[i]-j;
			for (i = 0; i < m; i++) S[i] = 0;
			for (i = 0; i < n; i++) S[V[i] = A[B[i]]]++;
			for (i = 1; i < m; i++) S[i]+=S[i-1];
			for (i = n-1; i >= 0; i--) sa[--S[V[i]]] = B[i];
			for (i = 0; i < n; i++) T=A[i],A[i]=B[i],B[i]=T;
			p = 1, A[sa[0]] = 0;
			for (i = 1; i < n; i++) A[sa[i]] = cmp(sa[i-1], sa[i], j) ? p-1 : p++;
		}
	}
	void calcLCP() {
		k = 0;
		for (i = 1; i <= n; i++) rank[sa[i]] = i;
		for (i = 0; i < n; h[rank[i++]] = k) for (k?k--:0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k++);
	}
	void solve() {
		calcSuffixArray(n+1);
		calcLCP();
		for (i = 1; i <= n; i++) printf("%d ",sa[i]);
		printf("\nx ");
		for (i = 2; i <= n; i++) printf("%d ",h[i]);
	}
} A;
int main() {
	char S[MAXN];
	fgets(S, MAXN, stdin);
	A.read(S); A.solve();
}