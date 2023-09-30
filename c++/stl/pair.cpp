class pii {
public:
	int a, b;
	pii() {
		*this = pii(0, 0);
	}
	pii(int a, int b) : a(a), b(b) {}
	bool operator<(const pii &y)const{
		if (a != y.a) return a < y.a;
		return b < y.b;
	}
};
