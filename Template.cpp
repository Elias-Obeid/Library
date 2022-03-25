#include <bits/stdc++.h>

using namespace std;

void setI(string name)
{
    freopen((name + ".in").c_str(), "r", stdin);
}

void setO(string name)
{
    freopen((name + ".out").c_str(), "w", stdout);
}

typedef long long ll;
typedef long double ld;

const ld EPS = 1e-9;
const ld PIE = asin(1) * 2;

const ll MAX = 100'000;
const ll INF = 1'000'000'000LL * 2;

// const int MOD = 998'244'353;
const int MOD = 1'000'000'007;

void solve_test_case()
{

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // setI("");
    // setO("");

    int number_of_test_cases = 1;
    cin >> number_of_test_cases;

    for (int test_case_number = 1; test_case_number <= number_of_test_cases; ++test_case_number)
    {
        // cout << "Case : #" << test_case_number << "\n";
        solve_test_case();
    }

    return 0;
}
