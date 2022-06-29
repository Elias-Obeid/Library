#include <bits/stdc++.h>
using namespace std;

class LCA
{
private:
    static int getHighestBit(int X)
    {
        return (X == 0 ? -1 : 31 - __builtin_clz(X));
    }

    int graph_size, lca_levels;
    vector<vector<int>> graph, parent;
    vector<int> depth, time_in, time_out;

    bool isAncestor(int U, int V)
    {
        return (time_in[U] <= time_in[V] && time_out[U] >= time_out[V]);
    }

    void DFS(int U, int P, int D, int &timer)
    {
        depth[U] = (P == U ? 0 : depth[P] + 1);
        parent[U][0] = P;
        for (int level = 1; level <= lca_levels; ++level)
        {
            parent[U][level] = parent[parent[U][level - 1]][level - 1];
        }

        time_in[U] = ++timer;
        for (int V : graph[U])
        {
            if (V != P)
            {
                DFS(V, U, D + 1, timer);
            }
        }
        time_out[U] = ++timer;
    }

public:
    LCA() {}
    LCA(int n) : graph_size{n}, lca_levels{getHighestBit(graph_size) + 1},
                 graph(graph_size), parent(graph_size, vector<int>(lca_levels + 1, -1)),
                 depth(graph_size, 0), time_in(graph_size, 0), time_out(graph_size, 0)
    {
    }

    void addEdge(int U, int V)
    {
        graph[U].emplace_back(V);
        graph[V].emplace_back(U);
    }

    void buildLCA(int root = 0)
    {
        int timer = 0;
        DFS(root, root, 0, timer);
    }

    int getLCA(int U, int V)
    {
        if (isAncestor(U, V))
        {
            return U;
        }
        else if (isAncestor(V, U))
        {
            return V;
        }
        else
        {
            for (int level = lca_levels; level >= 0; --level)
            {
                if (!isAncestor(parent[U][level], V))
                {
                    U = parent[U][level];
                }
            }
            return parent[U][0];
        }
    }

    int kthAncestor(int U, int K)
    {
        if (K > depth[U])
        {
            return -2;
        }

        for (int level = lca_levels; level >= 0; --level)
        {
            if (K > 0 && (1 << level) <= K)
            {
                U = parent[U][level];
                K -= (1 << level);
            }
        }
        return (K == 0 ? U : -2);
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;

    LCA graph(N);
    for (int U = 1; U < N; ++U)
    {
        int P;
        cin >> P;
        --P;
        graph.addEdge(P, U);
    }
    graph.buildLCA(0);

    for (int i = 0; i < Q; ++i)
    {
        string type;
        cin >> type;

        if (type == "common")
        {
            int U, V;
            cin >> U >> V;
            --U, --V;
            cout << graph.getLCA(U, V) + 1 << "\n";
        }
        else if (type == "kth")
        {
            int U, K;
            cin >> U >> K;
            --U;
            cout << graph.kthAncestor(U, K) << "\n";
        }
    }
    return 0;
}