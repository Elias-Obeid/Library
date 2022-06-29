#include <bits/stdc++.h>
using namespace std;

class DSU
{
private:
	int component_count;
	vector<int> component_size, parent;
	vector<vector<int>> component_nodes;

public:
	DSU() {}
	DSU(int N) : component_count{N}, component_size(N, 1), parent(N), component_nodes(N)
	{
		for (int U = 0; U < N; ++U)
		{
			parent[U] = U;
			component_nodes[U].emplace_back(U);
		}
	}

	int getSize(int U)
	{
		return component_size[getParent(U)];
	}

	int getParent(int U)
	{
		while (U != parent[U])
		{
			parent[U] = parent[parent[U]];
			U = parent[U];
		}
		return U;
	}

	int getComponentCount()
	{
		return component_count;
	}

	bool sameComponent(int U, int V)
	{
		return getParent(U) == getParent(V);
	}

	bool mergeNodes(int U, int V)
	{
		U = getParent(U), V = getParent(V);
		if (U == V)
		{
			return false;
		}

		if (getSize(U) < getSize(V))
		{
			swap(U, V);
		}
		component_size[U] += component_size[V];
		component_size[V] = 0;
		--component_count;
		parent[V] = U;

		component_nodes[U].insert(component_nodes[U].end(),
								  component_nodes[V].begin(),
								  component_nodes[V].end());
		component_nodes[V].clear();
		return true;
	}
};

int main()
{
	int N, M;
	cin >> N >> M;

	DSU graph(N);
	for (int i = 0; i < M; ++i)
	{
		int U, V;
		cin >> U >> V;
		--U, --V;
		graph.mergeNodes(U, V);
	}
	cout << (graph.getComponentCount() == 1 ? "Yes" : "No") << "\n";
	return 0;
}