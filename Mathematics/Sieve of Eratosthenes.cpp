
const int A = 200'000;

vector<bool> is_prime;
vector<int> primes, spf;

void preComputeSieve()
{
    is_prime.resize(A + 1);
    is_prime.assign(A + 1, true);

    spf.resize(A + 1);
    iota(spf.begin(), spf.end(), 0);

    is_prime[0] = false;
    is_prime[1] = false;

    for (long long i = 2; i <= A; ++i)
    {
        if (is_prime[i] == true)
        {
            spf[i] = i;
            primes.emplace_back(i);
            for (long long j = i * i; j <= A; j += i)
            {
                is_prime[j] = false;
                spf[j] = min(spf[j], spf[i]);
            }
        }
    }
}
