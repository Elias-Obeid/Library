
struct Edge
{
	int v, w, i;
	Edge(int _v, int _w, int _i)
	{
		v = _v;
		w = _w;
		i = _i;
	}
};

vector<ll> dist;
vector<int> prev_edge;
vector<vector<Edge>> adj;

void dijkstra_check(priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> &pq, int u, int i, ll d)
{
	if (d < dist[u])
	{
		dist[u] = d;
		prev_edge[u] = i;
		pq.push({d, u});
	}
}

void dijkstra(int s)
{
	dist.assign(n, INF);
	prev_edge.assign(n, -1);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	dijkstra_check(pq, s, -1, 0);

	while (!pq.empty())
	{
		auto [d, u] = pq.top();
		pq.pop();

		if (d > dist[u])
		{
			continue;
		}

		for (auto [v, w, i] : adj[u])
		{
			dijkstra_check(pq, v, i, d + w);
		}
	}
}

void cleanUp()
{
	adj.clear();
	dist.clear();
	prev_edge.clear();
}
