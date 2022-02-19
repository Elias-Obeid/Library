template <const int &MOD>
struct _m_int
{
	int val;

	_m_int(long long v = 0)
	{
		if (v < 0)
			v = v % MOD + MOD;
		if (v >= MOD)
			v %= MOD;
		val = int(v);
	}

	_m_int(unsigned long long v)
	{
		if (v >= MOD)
		{
			v %= MOD;
		}
		val = int(v);
	}

	_m_int(int v) : _m_int(static_cast<long long>(v)) {}
	_m_int(unsigned v) : _m_int(static_cast<unsigned long long>(v)) {}

	explicit operator int() const { return val; }
	explicit operator unsigned() const { return val; }
	explicit operator long long() const { return val; }
	explicit operator unsigned long long() const { return val; }
	explicit operator double() const { return val; }
	explicit operator long double() const { return val; }

	_m_int &operator+=(const _m_int &other)
	{
		val -= MOD - other.val;
		if (val < 0)
		{
			val += MOD;
		}
		return *this;
	}

	_m_int &operator-=(const _m_int &other)
	{
		val -= other.val;
		if (val < 0)
		{
			val += MOD;
		}
		return *this;
	}

	static unsigned fast_mod(unsigned long long x, unsigned m = MOD)
	{
#if !defined(_WIN32) || defined(_WIN64)
		return unsigned(x % m);
#endif
		// Optimized mod for Codeforces 32-bit machines.
		// x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
		unsigned x_high = static_cast<unsigned>(x >> 32), x_low = static_cast<unsigned>(x);
		unsigned quot, rem;
		asm("divl %4\n"
			: "=a"(quot), "=d"(rem)
			: "d"(x_high), "a"(x_low), "r"(m));
		return rem;
	}

	_m_int &operator*=(const _m_int &other)
	{
		val = fast_mod(static_cast<unsigned long long>(val) * other.val);
		return *this;
	}

	_m_int &operator/=(const _m_int &other)
	{
		return *this *= other.inv();
	}

	friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
	friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
	friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
	friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }

	_m_int &operator++()
	{
		val = (val == MOD - 1 ? 0 : val + 1);
		return *this;
	}

	_m_int &operator--()
	{
		val = (val == 0 ? MOD - 1 : val - 1);
		return *this;
	}

	_m_int operator++(int)
	{
		_m_int before = *this;
		++*this;
		return before;
	}
	_m_int operator--(int)
	{
		_m_int before = *this;
		--*this;
		return before;
	}

	_m_int operator-() const
	{
		return (val == 0 ? 0 : MOD - val);
	}

	friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
	friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
	friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
	friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
	friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
	friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }

	static const int SAVE_INV = int(1e6) + 5;
	static _m_int save_inv[SAVE_INV];

	static void prepare_inv()
	{
		// Ensures that MOD is prime, which is necessary for the inverse algorithm below.
		for (long long p = 2; p * p <= MOD; p += p % 2 + 1)
		{
			assert(MOD % p != 0);
		}

		save_inv[0] = 0;
		save_inv[1] = 1;

		for (int i = 2; i < SAVE_INV; i++)
		{
			save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
		}
	}

	_m_int inv() const
	{
		if (save_inv[1] == 0)
		{
			prepare_inv();
		}

		if (val < SAVE_INV)
		{
			return save_inv[val];
		}

		_m_int product = 1;
		int v = val;

		while (v >= SAVE_INV)
		{
			product *= MOD - MOD / v;
			v = MOD % v;
		}

		return product * save_inv[v];
	}

	_m_int pow(long long p) const
	{
		if (p < 0)
		{
			return inv().pow(-p);
		}

		_m_int a = *this, result = 1;

		while (p > 0)
		{
			if (p % 2 == 1)
			{
				result *= a;
			}

			p /= 2;

			if (p > 0)
			{
				a *= a;
			}
		}

		return result;
	}

	friend ostream &operator<<(ostream &os, const _m_int &m)
	{
		return os << m.val;
	}
};

template <const int &MOD>
_m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];

using mod_int = _m_int<MOD>;

vector<mod_int> fact;
vector<mod_int> inv_fact;

void preComputeFactorials()
{
	fact.resize(MAX);
	inv_fact.resize(MAX);

	fact.assign(MAX, 1);
	inv_fact.assign(MAX, 1);
	for (int i = 1; i < MAX; ++i)
	{
		fact[i] = fact[i - 1] * i;
		inv_fact[i] = 1 / fact[i];
	}
}

mod_int NCR(int N, int R)
{
	if (int(fact.size()) < MAX)
	{
		preComputeFactorials();
	}

	if (R > N)
	{
		return 0;
	}
	return fact[N] * inv_fact[N - R] * inv_fact[R];
}

mod_int PNR(int N, int R)
{
	if (int(fact.size()) < MAX)
	{
		preComputeFactorials();
	}

	if (R > N)
	{
		return 0;
	}
	return fact[N] * inv_fact[N - R];
}