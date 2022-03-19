
template <typename T, bool maximum_mode = false>
class RMQ
{
private:
    static getHighestBit(int x)
    {
        return (x == 0 ? -1 : 31 - __builtin_clz(x));
    }

    int table_n;
    vector<T> data;
    vector<vector<int>> table;

    int betterIndex(int x, int y)
    {
        return ((maximum_mode ? data[x] > data[y] : data[x] < data[y]) ? x : y);
    }

public:
    RMQ()
    {
    }

    RMQ(int n, const vector<T> &init)
    {
        table_n = n;
        buildTable(n, init);
    }

    void buildTable(int n, const vector<T> &init)
    {
        data = init;
        int levels = getHighestBit(n) + 1;
        table.resize(levels);

        for (int k = 0; k < levels; ++k)
        {
            table[k].resize(n - (1 << k) + 1);
        }

        for (int i = 0; i < n; ++i)
        {
            table[0][i] = i;
        }

        for (int k = 1; k < levels; ++k)
        {
            for (int i = 0; i + (1 << k) <= n; ++i)
            {
                table[k][i] = betterIndex(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    T queryIndex(int l, int r)
    {
        int k = getHighestBit(r - l + 1);
        return betterIndex(table[k][l], table[k][r - (1 << k) + 1]);
    }

    T queryValue(int l, int r)
    {
        return data[queryIndex(l, r)];
    }
};

class LCA
{
private:
    int time;
    int tree_n;
    RMQ<int> table;
    vector<vector<int>> adj;
    vector<int> depth, euler, parent, time_in, time_out, first_occurence;

    void initialize(int n)
    {
        time = 0;
        tree_n = n;
        adj.resize(n);
        depth.resize(n);
        parent.resize(n);
        time_in.resize(n);
        time_out.resize(n);
        euler.reserve(2 * n);
        first_occurence.resize(n, 2 * n + 1);
    }

public:
    LCA(int n)
    {
        initialize(n);
    }

    void buildLCA(int root = 0)
    {
        DFS(root, -1);

        int m = int(euler.size());
        vector<int> euler_depths;
        euler_depths.reserve(m);

        for (int i = 0; i < m; ++i)
        {
            euler_depths.emplace_back(depth[euler[i]]);
        }
        table.buildTable(m, euler_depths);
    }

    void addEdge(int u, int v)
    {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int degree(int u)
    {
        return int(adj[u].size());
    }

    void DFS(int u, int p)
    {
        parent[u] = p;
        depth[u] = (p < 0 ? 0 : depth[p] + 1);

        first_occurence[u] = int(euler.size());
        euler.emplace_back(u);

        time_in[u] = ++time;
        for (int v : adj[u])
        {
            if (v != p)
            {
                DFS(v, u);
                euler.emplace_back(u);
            }
        }
        time_out[u] = ++time;
    }

    bool isAncestor(int u, int v)
    {
        return time_in[u] <= time_in[v] && time_out[v] <= time_out[u];
    }

    int getLCA(int a, int b)
    {
        a = first_occurence[a];
        b = first_occurence[b];

        if (a > b)
        {
            swap(a, b);
        }
        return euler[table.queryIndex(a, b)];
    }

    int getDist(int u, int v)
    {
        return depth[u] + depth[v] - 2 * depth[getLCA(u, v)];
    }
};
