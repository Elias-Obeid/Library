#include <bits/stdc++.h>
using namespace std;

vector<pair<char, int>> stringCompression(const string &S)
{
    int N = (int)S.size();
    vector<pair<char, int>> compressed_string;
    for (int i = 0; i < N; ++i)
    {
        if (compressed_string.empty() || compressed_string.back().first != S[i])
        {
            compressed_string.emplace_back(S[i], 1);
        }
        else
        {
            ++compressed_string.back().second;
        }
    }
    return compressed_string;
}

int main()
{
    string S;
    cin >> S;

    for (const auto &[character, counts] : stringCompression(S))
    {
        cout << character << " " << counts << "\n";
    }
    return 0;
}