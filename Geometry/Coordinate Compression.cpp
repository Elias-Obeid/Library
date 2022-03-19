#include <bits/stdc++.h>
using namespace std;

template <typename T>
void compress(vector<T> &A)
{
    int N = int(A.size());
    vector<pair<T, int>> coordinates;
    for (int i = 0; i < N; ++i)
    {
        coordinates.emplace_back(A[i], i);
    }
    sort(A.begin(), A.end());

    A[coordinates.front().second] = 1;
    for (int i = 1; i < N; ++i)
    {
        bool is_not_equal = (coordinates[i - 1].first != coordinates[i].first);
        A[coordinates[i].second] = A[coordinates[i - 1].second] + int(is_not_equal);
    }
}
