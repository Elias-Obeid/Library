#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SparseTable
{
private:
    static getHighestBit(int x)
    {
        return (x == 0 ? -1 : 31 - __builtin_clz(x));
    }

    int table_n;
    vector<T> data;
    vector<vector<int>> table;

    // ! Remember to write
    T combineCells(int x, int y)
    {
    }

    void buildTable(int n, const vector<T> &init)
    {
        data = init;
        int levels = getHighestBit(n) + 1;
        table.resize(levels);

        for (int k = 0; k < levels; ++k)
        {
            table[k].resize(n);
        }

        for (int i = 0; i < n; ++i)
        {
            table[0][i] = init[i];
        }

        for (int k = 1; k < levels; ++k)
        {
            for (int i = 0; i + (1 << k) <= n; ++i)
            {
                table[k][i] = combineCells(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

public:
    SparseTable(int n, const vector<T> &init)
    {
        table_n = n;
        buildTable(n, init);
    }

    T queryValue(int l, int r)
    {
        int k = getHighestBit(r - l + 1);
        return combineCells(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
