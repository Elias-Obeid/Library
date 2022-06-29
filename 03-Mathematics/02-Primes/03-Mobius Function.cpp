#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200'000;

vector<bool> is_prime;
vector<int> mobius, primes;

void sieveMobius()
{
    if (!primes.empty())
    {
        return;
    }

    mobius.resize(MAXA + 1, 1);
    is_prime.resize(MAXA + 1, true);

    is_prime[0] = is_prime[1] = false;
    for (int value = 2; value <= MAXA; ++value)
    {
        if (is_prime[value])
        {
            mobius[value] = -1;
            primes.emplace_back(value);
        }

        for (int p : primes)
        {
            if (p * value > MAXA)
            {
                break;
            }
            mobius[p * value] = (value % p == 0 ? 0 : mobius[p] * mobius[value]);
            is_prime[p * value] = false;
        }
    }
}

int main()
{
    int N;
    cin >> N;
    sieveMobius();

    for (int i = 0; i < N; ++i)
    {
        int A;
        cin >> A;
        cout << mobius[A] << " \n"[i == N - 1];
    }
    return 0;
}