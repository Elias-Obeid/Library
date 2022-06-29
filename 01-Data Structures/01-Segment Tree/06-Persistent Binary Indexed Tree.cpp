#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false>
class BIT
{
private:
    struct Node
    {
        number_type value;
        int version;

        Node(number_type _value = 0, int _version = 0) : value{_value}, version{_version}
        {
        }

        friend bool operator<(const Node &A, const Node &B)
        {
            return A.version < B.version;
        }
    };

    int tree_size;
    vector<vector<Node>> tree;

    static int getHighestBit(int X)
    {
        return (X == 0 ? -1 : 31 - __builtin_clz(X));
    }

public:
    BIT() {}
    BIT(int N) : tree_size{N + (int)one_indexing_mode}, tree(tree_size)
    {
        for (int i = 0; i < tree_size; ++i)
        {
            tree[i].emplace_back(Node());
        }
    }

    void updateTree(int index, number_type addition, int version)
    {
        for (int i = index; i < tree_size;
             i = (one_indexing_mode ? i + (i & (-i)) : i | (i + 1)))
        {
            if (tree[i].back().version != version)
            {
                tree[i].emplace_back(Node(tree[i].back().value + addition, version));
            }
            else
            {
                tree[i].back().value += addition;
            }
        }
    }

    number_type queryPrefix(int right_bound, int version)
    {
        number_type sum{};
        for (int i = right_bound; i >= 0 + (int)one_indexing_mode;
             i = (one_indexing_mode ? i - (i & (-i)) : (i & (i + 1)) - 1))
        {
            auto it = upper_bound(tree[i].begin(), tree[i].end(), Node(0, version)) - 1;
            sum += it->value;
        }
        return sum;
    }

    number_type queryRange(int left_bound, int right_bound)
    {
        if (left_bound > right_bound)
        {
            return number_type{};
        }
        return queryPrefix(right_bound) - queryPrefix(left_bound - 1);
    }

    // ! Only works in 1-indexing mode
    // returns the first index such that prefix_sums[index] >= target_sum
    int findFirstPrefix(number_type target_sum, int version)
    {
        int index = 0;
        number_type current_sum{};
        for (int bit = getHighestBit(tree_size); bit >= 0; --bit)
        {
            int offset = (1 << bit);
            if (index + offset < tree_size)
            {
                auto it = upper_bound(tree[index + offset].begin(), tree[index + offset].end(), Node(0, version)) - 1;
                if (it->value + current_sum < target_sum)
                {
                    current_sum += it->value;
                    index += offset;
                }
            }
        }
        return index + 1;
    }
};

int main()
{
    int N, M, Q;
    cin >> N >> M >> Q;

    BIT<long long, true> ft(M);
    vector<int> last_update(N + 1, 0);
    vector<long long> values(N + 1, 0);
    for (int version = 1; version <= Q; ++version)
    {
        string operation;
        cin >> operation;
        if (operation == "add")
        {
            int left_bound, right_bound, addition;
            cin >> left_bound >> right_bound >> addition;
            ft.updateTree(left_bound, +addition, version);
            ft.updateTree(right_bound + 1, -addition, version);
        }
        else if (operation == "set")
        {
            int row, value;
            cin >> row >> value;
            values[row] = value;
            last_update[row] = version;
        }
        else if (operation == "query")
        {
            int row, column;
            cin >> row >> column;
            long long answer = values[row] +
                               ft.queryPrefix(column, version) -
                               ft.queryPrefix(column, last_update[row]);
            cout << answer << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}