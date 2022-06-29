#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
void compress(vector<number_type> &A)
{
    int N = int(A.size());
    vector<number_type> values = A;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    for (int i = 0; i < N; ++i)
    {
        A[i] = lower_bound(values.begin(), values.end(), A[i]) - values.begin();
    }
}

int main()
{
    int N;
    cin >> N;

    vector<int> X(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> X[i];
    }
    compress(X);

    for (int i = 0; i < N; ++i)
    {
        cout << X[i] << " \n"[i == N - 1];
    }
    return 0;
}