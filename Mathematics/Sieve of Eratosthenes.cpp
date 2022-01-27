
vector<bool> is_prime;
vector<int> primes, spf;

void preComputeSieve(int n)
{
    is_prime.resize(n + 1);
    is_prime.assign(n + 1, true);

    spf.resize(n + 1);
    iota(spf.begin(), spf.end(), 0);

    is_prime[0] = false;
    is_prime[1] = false;

    for (long long i = 2; i <= n; ++i)
    {
        if (is_prime[i] == true)
        {
            spf[i] = i;
            primes.emplace_back(i);
            for (long long j = i * i; j <= n; j += i)
            {
                is_prime[j] = false;
                spf[j] = min(spf[j], spf[i]);
            }
        }
    }
}
