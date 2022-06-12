
struct DSU
{
	int N;
	int component_count;
	vector<int> parent, comp_size;

	DSU(int n) : N{n}, component_count{n}, parent(n), comp_size(n, 1)
	{
		iota(parent.begin(), parent.end(), 0);
	}

	int getParent(int U)
	{
		while (parent[U] != U)
		{
			parent[U] = parent[parent[U]];
			U = parent[U];
		}
		return U;
	}

	bool sameComp(int U, int V)
	{
		return getParent(U) == getParent(V);
	}

	bool mergeNodes(int U, int V)
	{
		U = getParent(U);
		V = getParent(V);

		if (U == V)
		{
			return false;
		}

		if (comp_size[U] < comp_size[V])
		{
			swap(U, V);
		}
		comp_size[U] += comp_size[V];
		--component_count;
		comp_size[V] = 0;
		parent[V] = U;
		return true;
	}
};
