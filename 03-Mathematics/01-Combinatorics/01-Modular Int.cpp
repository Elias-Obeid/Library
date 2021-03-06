#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;

template <const int modulo>
struct modular_int
{
    int value;
    modular_int(int v) : modular_int(static_cast<long long>(v)) {}
    modular_int(long long v = 0)
    {
        if (v < 0)
        {
            v = v % modulo + modulo;
        }

        if (v >= modulo)
        {
            v = v % modulo;
        }
        value = static_cast<int>(v);
    }

    explicit operator int() const { return value; }
    explicit operator unsigned() const { return value; }
    explicit operator long long() const { return value; }
    explicit operator unsigned long long() const { return value; }
    explicit operator double() const { return value; }
    explicit operator long double() const { return value; }

    modular_int &operator+=(const modular_int &other)
    {
        value = (value + other.value) % modulo;
        return *this;
    }

    modular_int &operator-=(const modular_int &other)
    {
        value = ((value - other.value) % modulo + modulo) % modulo;
        return *this;
    }

    modular_int &operator*=(const modular_int &other)
    {
        value = (1LL * value * other.value) % modulo;
        return *this;
    }

    modular_int &operator/=(const modular_int &other)
    {
        *this *= other.inv();
        return *this;
    }

    friend modular_int operator+(const modular_int &a, const modular_int &b) { return modular_int(a) += b; }
    friend modular_int operator-(const modular_int &a, const modular_int &b) { return modular_int(a) -= b; }
    friend modular_int operator*(const modular_int &a, const modular_int &b) { return modular_int(a) *= b; }
    friend modular_int operator/(const modular_int &a, const modular_int &b) { return modular_int(a) /= b; }

    modular_int &operator++()
    {
        value = (value == modulo - 1 ? 0 : value + 1);
        return *this;
    }

    modular_int &operator--()
    {
        value = (value == 0 ? MOD - 1 : value - 1);
        return *this;
    }

    modular_int operator++(int)
    {
        modular_int before = *this;
        ++*this;
        return before;
    }
    modular_int operator--(int)
    {
        modular_int before = *this;
        --*this;
        return before;
    }

    modular_int operator-() const
    {
        return (value == 0 ? 0 : MOD - value);
    }

    friend bool operator==(const modular_int &a, const modular_int &b) { return a.value == b.value; }
    friend bool operator!=(const modular_int &a, const modular_int &b) { return a.value != b.value; }
    friend bool operator<(const modular_int &a, const modular_int &b) { return a.value < b.value; }
    friend bool operator>(const modular_int &a, const modular_int &b) { return a.value > b.value; }
    friend bool operator<=(const modular_int &a, const modular_int &b) { return a.value <= b.value; }
    friend bool operator>=(const modular_int &a, const modular_int &b) { return a.value >= b.value; }

    friend ostream &operator<<(ostream &os, const modular_int &m)
    {
        return os << m.value;
    }

    static const int SAVE_INV = int(1e6) + 5;
    static modular_int save_inv[SAVE_INV];

    static void prepare_inv()
    {
        save_inv[0] = 0;
        save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++)
        {
            save_inv[i] = save_inv[modulo % i] * (modulo - modulo / i);
        }
    }

    modular_int inv() const
    {
        if (save_inv[1] == 0)
        {
            prepare_inv();
        }

        if (value < SAVE_INV)
        {
            return save_inv[value];
        }
        else
        {
            int v = value;
            modular_int product = 1;
            while (v >= SAVE_INV)
            {
                product *= MOD - MOD / v;
                v = MOD % v;
            }
            return product * save_inv[v];
        }
    }

    modular_int pow(long long P) const
    {
        if (P < 0)
        {
            return inv().pow(-P);
        }
        else
        {

            modular_int result = 1;
            modular_int base = *this;
            while (P > 0)
            {
                if (P & 1)
                {
                    result *= base;
                }
                P >>= 1;

                if (P > 0)
                {
                    base *= base;
                }
            }
            return result;
        }
    }
};

template <const int modulo>
modular_int<modulo> modular_int<modulo>::save_inv[modular_int<modulo>::SAVE_INV];

using mod_int = modular_int<MOD>;

int main()
{
    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    map<int, int> last;
    vector<mod_int> dp(N + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < N; ++i)
    {
        dp[i + 1] = dp[i] * 2;
        if (last.contains(A[i]))
        {
            dp[i + 1] -= dp[last[A[i]]];
        }
        last[A[i]] = i;
    }
    cout << dp[N] << "\n";
    return 0;
}