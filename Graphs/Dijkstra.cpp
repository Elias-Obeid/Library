
const int N = 100'000;
vector<vector<pair<int, int>>> adj(N);

vector<int> dijkstra(int source, int n)
{
	vector<int> dist(n, INF);
	priority_queue<pair<int, int>,
				   vector<pair<int, int>>,
				   greater<pair<int, int>>>
		current_paths;

	dist[source] = 0;
	current_paths.emplace(0, source);

	while (!current_paths.empty())
	{
		int u = current_paths.top().second;
		current_paths.pop();

		for (auto &[v, w] : adj[u])
		{
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				current_paths.emplace(dist[v], v);
			}
		}
	}
	return dist;
}
