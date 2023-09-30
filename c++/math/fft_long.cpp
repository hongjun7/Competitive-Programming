typedef long long ll;
const double PI = 3.1415926535897932384626433832795;

namespace FFT {
	typedef complex<double> base;
	void FFT(vector <base> &v, bool inv) {
		vector<base> w(v.size());
		for (int i = 0; i < v.size(); i++) {
			int k = i&-i;
			if (i == k) {
				double ang = 2 * PI * i / v.size();
				if (inv) ang *= -1;
				w[i] = base(cos(ang), sin(ang));
			}
			else w[i] = w[i - k] * w[k];
		}
		for (int i = 1, j = 0; i < v.size(); i++) {
			int bit = v.size() >> 1;
			for (; j >= bit; bit >>= 1) j -= bit;
			j += bit;
			if (i < j) swap(v[i], v[j]);
		}
		for (int i = 2; i <= v.size(); i <<= 1) {
			for (int j = 0; j < v.size(); j += i) {
				for (int k = 0; k < i / 2; k++) {
					base a = v[j + k], b = v[j + k + i / 2] * w[k * (v.size() / i)];
					v[j + k] = a + b;
					v[j + k + i / 2] = a - b;
				}
			}
		}
		if (inv) {
			for (int i = 0; i < v.size(); i++) {
				v[i] /= v.size();
			}
		}
	}
	vector <ll> mul(vector <ll> &v, vector <ll> &w) {
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 1;
		while (n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		FFT(fv, 0);
		FFT(fw, 0);
		for (int i = 0; i < n; i++) fv[i] *= fw[i];
		FFT(fv, 1);
		vector <ll> ret(n);
		for (int i = 0; i < n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector <ll> pw(vector <ll> &v) {
		vector<base> fv(v.begin(), v.end());
		int n = 1;
		while (n < v.size()) n <<= 1;
		n <<= 1;
		fv.resize(n);
		FFT(fv, 0);
		for (int i = 0; i < n; i++) fv[i] *= fv[i];
		FFT(fv, 1);
		vector <ll> ret(n);
		for (int i = 0; i < n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector <ll> solve(vector <ll> &v, vector <ll> &w, int b) {
		int n = 1;
		while (n < v.size() || n < w.size()) n <<= 1;
		n <<= 1;
		vector<base> v1(n), v2(n), v3(n), v4(n), r1(n), r2(n), r3(n);
		for (int i = 0; i < v.size(); i++) {
			v1[i] = base(v[i] / b, 0);
			v2[i] = base(v[i] % b, 0);
		}
		for (int i = 0; i < w.size(); i++) {
			v3[i] = base(w[i] / b, 0);
			v4[i] = base(w[i] % b, 0);
		}
		FFT(v1, 0); FFT(v2, 0); FFT(v3, 0); FFT(v4, 0);
		for (int i = 0; i < n; i++) {
			r1[i] = v1[i] * v3[i];
			r2[i] = v1[i] * v4[i] + v2[i] * v3[i];
			r3[i] = v2[i] * v4[i];
		}
		FFT(r1, 1); FFT(r2, 1); FFT(r3, 1);
		vector <ll> ret(n);
		for (int i = 0; i < n; i++) {
			ret[i] = (ll)round(r1[i].real()) * b * b + (ll)round(r2[i].real()) * b + (ll)round(r3[i].real());
		}
		return ret;
	}
}
