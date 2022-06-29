#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false, bool maximum_mode = false>
class RMQ
{
private:
    static int getHighestBit(int X)
    {
        return (X == 0 ? -1 : 31 - __builtin_clz(X));
    }

    int table_size, table_levels;
    vector<number_type> values;
    vector<vector<int>> table_values;

    int combineCells(int X, int Y)
    {
        return (maximum_mode ? (values[X] > values[Y] ? X : Y) : (values[X] < values[Y] ? X : Y));
    }

public:
    RMQ() {}
    RMQ(int N, const vector<number_type> &A) : table_size{N + (int)one_indexing_mode},
                                               table_levels{getHighestBit(N) + 1},
                                               values{A},
                                               table_values(table_levels, vector<int>(table_size))
    {
        iota(table_values[0].begin(), table_values[0].end(), 0);
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

    int queryIndex(int left_bound, int right_bound)
    {
        int level = getHighestBit(right_bound - left_bound + 1);
        return combineCells(table_values[level][left_bound],
                            table_values[level][right_bound - (1 << level) + 1]);
    }

    number_type queryRange(int left_bound, int right_bound)
    {
        return values[queryIndex(left_bound, right_bound)];
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

    RMQ<long long> rmq(N, A);
    for (int qi = 0; qi < Q; ++qi)
    {
        int left_bound, right_bound;
        cin >> left_bound >> right_bound;
        cout << rmq.queryRange(left_bound, right_bound) << "\n";
    }
    return 0;
}