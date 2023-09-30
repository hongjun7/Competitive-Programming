/* find a pair (c,d) s.t. ac + bd = gcd(a,b) */
pair<long long, long long> extended_gcd(long long a, long long b) {
	if (b == 0) return make_pair(1, 0);
	pair<long long, long long> t = extended_gcd(b, a % b);
	return make_pair(t.second, t.first - t.second * (a / b));
}
/* Find x in [0,m) s.t. ax ≡ gcd(a, m) (mod m) */
long long modinverse(long long a, long long m) {
	return (extended_gcd(a, m).first % m + m) % m;
}
