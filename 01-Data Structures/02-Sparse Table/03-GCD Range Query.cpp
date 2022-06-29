#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
number_type GCD(number_type X, number_type Y)
{
    return (X == 0 ? Y : GCD(Y % X, X));
}

template <typename number_type, bool one_indexing_mode = false>
class RGQ
{
private:
    static int getHighestBit(int X)
    {
        return (X == 0 ? -1 : 31 - __builtin_clz(X));
    }

    int table_size, table_levels;
    vector<vector<number_type>> table_values;

    number_type combineCells(number_type X, number_type Y)
    {
        return GCD(X, Y);
    }

public:
    RGQ() {}
    RGQ(int N, const vector<number_type> &A) : table_size{N + (int)one_indexing_mode},
                                               table_levels{getHighestBit(N) + 1},
                                               table_values(table_levels, vector<number_type>(table_size))
    {
        table_values[0] = A;
        buildTable();
    }

    void buildTable()
    {
        for (int level = 1; level < table_levels; ++level)
        {
            for (int i = (int)one_indexing_mode; i + (1 << level) <= table_size; ++i)
            {
                table_values[level][i] = combineCells(table_values[level - 1][i],
                                                      table_values[level - 1][i + (1 << (level - 1))]);
            }
        }
    }

    number_type queryRange(int left_bound, int right_bound)
    {
        int level = getHighestBit(right_bound - left_bound + 1);
        return combineCells(table_values[level][left_bound],
                            table_values[level][right_bound - (1 << level) + 1]);
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<long long> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    RGQ<long long> rgq(N, A);
    for (int qi = 0; qi < Q; ++qi)
    {
        int left_bound, right_bound;
        cin >> left_bound >> right_bound;
        cout << rgq.queryRange(left_bound, right_bound) << "\n";
    }
    return 0;
}