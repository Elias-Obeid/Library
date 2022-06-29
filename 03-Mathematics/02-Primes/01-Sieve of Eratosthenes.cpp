#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200'000;

vector<bool> is_prime;
vector<int> smallest_factor, primes;

void sieve()
{
    if (!primes.empty())
    {
        return;
    }
    is_prime.resize(MAXA + 1, true);
    smallest_factor.resize(MAXA + 1, 0);

    is_prime[0] = is_prime[1] = false;
    smallest_factor[0] = smallest_factor[1] = 1;
    for (int value = 2; value <= MAXA; ++value)
    {
        if (is_prime[value])
        {
            primes.emplace_back(value);
            smallest_factor[value] = value;
            for (int k = 2; k * value <= MAXA; ++k)
            {
                if (is_prime[k * value])
                {
                    is_prime[k * value] = false;
                    smallest_factor[k * value] = value;
                }
            }
        }
    }
}

vector<pair<int, int>> factorize(int value)
{
    if (primes.empty())
    {
        sieve();
    }

    vector<pair<int, int>> factors;
    while (value != 1)
    {
        int prime = smallest_factor[value];
        factors.emplace_back(prime, 0);
        while (value % prime == 0)
        {
            value /= prime;
            ++factors.back().second;
        }
    }
    return factors;
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        int A;
        cin >> A;

        vector<pair<int, int>> factors = factorize(A);
        for (const auto &[P, C] : factors)
        {
            for (int c = 0; c < C; ++c)
            {
                cout << P << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}