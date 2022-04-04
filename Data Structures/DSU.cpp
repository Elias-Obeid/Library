
struct DSU
{
	int connected;
	vector<int> parent, comp_size;

	DSU(int n) : connected{n}, parent(n), comp_size(n, 1)
	{
		iota(parent.begin(), parent.end(), 0);
	}

	int getPar(int u)
	{
		while (parent[u] != u)
		{
			parent[u] = parent[parent[u]];
			u = parent[u];
		}
		return u;
	}

	bool sameComp(int u, int v)
	{
		return getPar(u) == getPar(v);
	}

	bool mergeNodes(int u, int v)
	{
		u = getPar(u);
		v = getPar(v);

		if (u == v)
		{
			return false;
		}

		if (comp_size[u] < comp_size[v])
		{
			swap(u, v);
		}
		comp_size[u] += comp_size[v];
		comp_size[v] = 0;
		parent[v] = u;
		--connected;
		return true;
	}
};
