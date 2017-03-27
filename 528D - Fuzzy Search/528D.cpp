#include <iostream>     
#include <complex>      
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <memory>

using namespace std;

typedef complex<double> xd;
typedef vector<double> dvec;
typedef vector<int> ivec;
typedef vector<xd> xvec;
const double PI = acos(0) * 2;
const xd J(0, 1); // sqrt(-1)

class FFT
{
public:
	static ivec convolve(const ivec &a, const ivec &b)
	{
		// degree of resulting polynomial = size of resulting array
		size_t deg = a.size() + b.size() - 1;

		// transform array size must be in power of 2 for FFT
		size_t N = 1;
		while (N < deg) N <<= 1;

		// precompute omega, if not yet done so:
		for (int i = N; i > 0; i >>= 1) {
			if (omega.find({ i, 0 }) != omega.end()) break;

			int p = i / 2;
			for (double j = 1 - p; j < p; ++j) {
				omega[{i, j}] = exp((2. * PI * J * j) / (double)i);
			}
		}

		xvec acof(N), bcof(N);
		copy(a.begin(), a.end(), acof.begin());
		copy(b.begin(), b.end(), bcof.begin());

		xvec apv, bpv, cpv(N);

		// evaluation: fft
		apv = transform(acof);
		bpv = transform(bcof);

		// point-wise multiplcation
		for (size_t i = 0; i < N; ++i) {
			cpv[i] = apv[i] * bpv[i];
		}

		// interpolation: ifft
		ivec c(deg);
		cpv = transform(cpv, true);
		for (size_t i = 0; i < deg; ++i) {
			c[i] = (int)round(cpv[i].real() / N);
		}

		return c;
	}

private:
	static map<pair<int, int>, xd> omega;

	static xvec transform(xvec &s, bool inv = false)
	{
		int N = s.size();

		if (N == 1) return s;

		int halfN = N / 2;
		xvec se, so;
		se.reserve(halfN);
		so.reserve(halfN);

		for (int i = 0; i < N; i += 2) {
			se.push_back(s[i]);     // even
			so.push_back(s[i + 1]); // odd
		}

		se = transform(se, inv);
		so = transform(so, inv);

		for (int m = 0; m < halfN; ++m) {
			xd omso = omega[{N, inv ? m : -m}] * so[m];
			s[m] = se[m] + omso;
			s[m + halfN] = se[m] - omso;
		}

		return s;
	}
};

map<pair<int, int>, xd> FFT::omega;

struct Padder 
{
	Padder(const int &n, const int &pad) 
	: Data(n, 0), pad(pad), n(n) {}

	// assumes idx is passed in ascending order
	void mark(const int &idx) 
	{
		int start = idx - pad;
		if (start < p) start = p;
		int end = idx + pad + 1;
		if (end > n) end = n;

		for (int i = start; i < end; ++i) {
			Data[i] = 1;
		}
		
		p = end;
	}

	ivec Data;
	int pad;
	int n;
	int p = 0;
};

int main()
{
	clog.setstate(ios_base::failbit); // turn off log

	const char DNA[] = { 'A', 'T', 'G', 'C' };
	map<char, unique_ptr<Padder>> A;
	map<char, ivec> B;
	
	int slen, tlen, k;
	string s, t;

	cin >> slen >> tlen >> k
		>> s    >> t;

	ivec match(slen + tlen - 1, 0);
	
	// init map:
	for (int c = 0; c < 4; c++) {
		A[DNA[c]] = make_unique<Padder>(slen, k);
		B[DNA[c]] = ivec(tlen, 0);
	}
	
	for (int i = 0; i < slen; ++i) {
		A[s[i]].get()->mark(i);
	}
	
	for (size_t i = 0; i < t.size(); ++i) {
		B[t[i]][tlen - i - 1] = 1;
	}

	for (int c = 0; c < 4; c++) {
		ivec C = FFT::convolve(A[DNA[c]].get()->Data, B[DNA[c]]);
		
		for (size_t i = 0; i < C.size(); ++i) {
			match[i] += C[i];
		}
	}

	int answer = 0;
	for (const auto &m : match) {
		if (m == tlen) ++answer;
	}
	
	cout << answer;
}
