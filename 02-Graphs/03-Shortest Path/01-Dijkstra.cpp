#include <bits/stdc++.h>
using namespace std;

struct Path
{
    int node;
    long long weight;
    Path(int _node = 0, long long _weight = 0) : node{_node}, weight{_weight} {}

    friend bool operator<(const Path &A, const Path &B)
    {
        return A.weight < B.weight;
    }
};

vector<long long> getDijkstra(int source, int N, const vector<vector<pair<int, int>>> &graph)
{
    set<Path> paths;
    vector<long long> distance(N, INF);

    distance[source] = 0;
    paths.emplace(source, 0);

    while (!paths.empty())
    {
        auto [node, path_weight] = *paths.begin();
        paths.erase(paths.begin());

        if (path_weight > distance[node])
        {
            continue;
        }

        for (const auto &[neighbour, weight] : graph[node])
        {
            if (distance[neighbour] > weight + path_weight)
            {
                distance[neighbour] = weight + path_weight;
                paths.emplace(neighbour, distance[neighbour]);
            }
        }
    }
    return distance;
}

int main()
{
    int N, M, Q, S;
    cin >> N >> M >> Q >> S;

    vector<vector<pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int U, V, W;
        cin >> U >> V >> W;
        graph[U].emplace_back(V, W);
        graph[V].emplace_back(U, W);
    }

    vector<long long> distances = getDijkstra(S, N, graph);
    for (int i = 0; i < Q; ++i)
    {
        int T;
        cin >> T;
        cout << distances[T] << "\n";
    }
    return 0;
}