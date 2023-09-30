#define _USE_MATH_DEFINES
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
typedef complex<long double> base;
void fft(vector <base> &a, bool invert) {
	int n = sz(a);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int L = 2; L <= n; L <<= 1) {
		long double ang = 2 * M_PI / L*(invert ? -1 : 1);
		base wL(cos(ang), sin(ang));
		for (int i = 0; i < n; i += L) {
			base w(1);
			for (int j = 0; j < L / 2; j++) {
				base u = a[i + j], v = a[i + j + L / 2] * w;
				a[i + j] = u + v;
				a[i + j + L / 2] = u - v;
				w *= wL;
			}
		}
	}
	if (invert) {
		for (int i = 0; i < n; i++) a[i] /= n;
	}
}
void multiply(const vector<long double> &a, const vector<long double> &b, vector<long double> &res) {
	vector <base> fa(all(a)), fb(all(b));
	int n = 1;
	while (n < sz(a) + sz(b)) n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, 0); fft(fb, 0);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	res.resize(n);
	for (int i = 0; i < n; i++) res[i] = (fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}
