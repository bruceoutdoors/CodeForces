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
		logN = 0;
		while (N < deg) {
			N <<= 1;
			++logN;
		}

		// precompute omega, if not yet done so:
		for (int i = N; i > 0; i >>= 1) {
			if (omega.find({i, 0}) != omega.end()) break;

			int p = i / 2;
			for (double j = 1 - p; j < p; ++j) {
				omega[{i, j}] = exp((2. * PI * J * j) / (double)i);
			}
		}

		xvec ax(N), bx(N);
		copy(a.begin(), a.end(), ax.begin());
		copy(b.begin(), b.end(), bx.begin());

		// evaluation: fft
		transform(ax);
		transform(bx);

		// point-wise multiplcation
		for (size_t i = 0; i < N; ++i) {
			ax[i] *= bx[i];
		}

		// interpolation: ifft
		ivec c(deg);
		transform(ax, true);
		for (size_t i = 0; i < deg; ++i) {
			c[i] = round(ax[i].real() / N);
		}

		return c;
	}

private:
	static map<pair<int, int>, xd> omega;
	static int logN;

	static void transform(xvec &s, bool inv = false)
	{
		int N = s.size();
		int i, m, u, v;
		xd fodd, feven;
		
		// swap all elements with its bit reverse:
		u = N - 1;
		for (i = 1; i < u; ++i) {
			v = reverseBits(i, logN);
			if (v > i) swap(s[i], s[v]);
		}
		
		// in-place fourier transform:
		for (int n = 2, p = 1; n <= N; n <<= 1, p <<= 1) {
			for (i = 0; i < N; i += n) {
				for (m = 0; m < p; ++m) {
					u = i + m;
					v = u + n/2;
					fodd  = omega[{n, inv ? m : -m}] * s[v];
					feven = s[u];
					s[u] = feven + fodd;
					s[v] = feven - fodd;
				}
			}
		}
	}
	
	static size_t reverseBits(const size_t &num, const size_t &bitNum)
	{
		size_t reverse_num = 0;

		for (size_t i = 0; i < bitNum; ++i)
		{
			if (num & (1 << i)) {
			   reverse_num |= 1 << ((bitNum - 1) - i); 
			}
		}
		
		return reverse_num;
	}
};

map<pair<int, int>, xd> FFT::omega;
int FFT::logN = 0;

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
