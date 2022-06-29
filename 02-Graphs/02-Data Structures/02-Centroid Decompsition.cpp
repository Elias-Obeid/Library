#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false>
class BIT
{
private:
    int tree_size;
    vector<number_type> tree;

    static int getHighestBit(int X)
    {
        return (X == 0 ? -1 : 31 - __builtin_clz(X));
    }

public:
    BIT(int N) : tree_size{N + (int)one_indexing_mode}, tree(tree_size)
    {
    }

    void updateTree(int index, number_type addition)
    {
        for (int i = index; i < tree_size;
             i = (one_indexing_mode ? i + (i & (-i)) : i | (i + 1)))
        {
            tree[i] += addition;
        }
    }

    number_type queryPrefix(int right_bound)
    {
        number_type sum{};
        for (int i = right_bound; i >= 0 + (int)one_indexing_mode;
             i = (one_indexing_mode ? i - (i & (-i)) : (i & (i + 1)) - 1))
        {
            sum += tree[i];
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
    int findFirstPrefix(number_type target_sum)
    {
        int index = 0;
        number_type current_sum{};
        for (int bit = getHighestBit(tree_size); bit >= 0; --bit)
        {
            int offset = (1 << bit);
            if (index + offset < tree_size && current_sum + tree[index + offset] < target_sum)
            {
                current_sum += tree[index + offset];
                index += offset;
            }
        }
        return index + 1;
    }
};

class Centroid
{
private:
    int graph_size;
    BIT<int> depth_freq;
    vector<bool> processed;
    vector<vector<int>> graph;
    vector<int> parent, subtree_size;

    int getSubtreeSize(int U, int P)
    {
        subtree_size[U] = 1;
        for (int V : graph[U])
        {
            if (!processed[V] && V != P)
            {
                subtree_size[U] += getSubtreeSize(V, U);
            }
        }
        return subtree_size[U];
    }

    int findCentroid(int U, int P, int S)
    {
        do
        {
            bool done = true;
            for (int V : graph[U])
            {
                if (!processed[V] && V != P && 2 * subtree_size[V] > S)
                {
                    P = U;
                    U = V;
                    done = false;
                    break;
                }
            }

            if (done)
            {
                break;
            }
        } while (true);
        return U;
    }

    void DFS(int U, int P, int D, int A)
    {
        depth_freq.updateTree(D, A);
        for (int V : graph[U])
        {
            if (!processed[V] && V != P)
            {
                DFS(V, U, D + 1, A);
            }
        }
    }

    long long getCount(int U, int P, int D, int L, int R)
    {
        if (D > R)
        {
            return 0;
        }

        long long path_count = depth_freq.queryRange(L - D, R - D);
        for (int V : graph[U])
        {
            if (!processed[V] && V != P)
            {
                path_count += getCount(V, U, D + 1, L, R);
            }
        }
        return path_count;
    }

public:
    Centroid(int N) : graph_size{N}, processed(N, false), parent(N, -1),
                      subtree_size(N, 0), graph(N), depth_freq(N)
    {
        depth_freq.updateTree(0, +1);
    }

    void addEdge(int U, int V)
    {
        graph[U].emplace_back(V);
        graph[V].emplace_back(U);
    }

    long long decompose(int U, int P, int L, int R)
    {
        long long subtree_path_count = 0;
        int C = findCentroid(U, P, getSubtreeSize(U, P));
        for (int V : graph[C])
        {
            if (!processed[V])
            {
                subtree_path_count += getCount(V, C, 1, L, R);
                DFS(V, C, 1, +1);
            }
        }

        for (int V : graph[C])
        {
            if (!processed[V])
            {
                DFS(V, C, 1, -1);
            }
        }

        parent[C] = P;
        processed[C] = true;
        for (int V : graph[C])
        {
            if (!processed[V])
            {
                subtree_path_count += decompose(V, C, L, R);
            }
        }
        return subtree_path_count;
    }
};

int main()
{
    int N, L, R;
    cin >> N >> L >> R;

    Centroid centroid(N);
    for (int i = 1; i < N; ++i)
    {
        int U, V;
        cin >> U >> V;
        --U, --V;
        centroid.addEdge(U, V);
    }
    cout << centroid.decompose(0, -1, L, R) << "\n";
    return 0;
}