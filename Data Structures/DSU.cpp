
template <typename DATA>
class DSU
{
private:
	int connected;
	vector<DATA> parent, component_size;

public:
	DSU(int n)
	{
		this->initializeDSU(n);
	}

	void initializeDSU(int n)
	{
		parent = component_size = vector<DATA>(n + 1, 0);
		for (int i = 1; i <= n; i++)
		{
			parent[i] = i, component_size[i] = 1;
		}
		connected = n;
	}

	int getParent(int u)
	{
		while (u != parent[u])
		{
			parent[u] = parent[parent[u]];
			u = parent[u];
		}
		return u;
	}

	int getSize(int u)
	{
		return component_size[getParent(u)];
	}

	bool uniteNodes(int u, int v)
	{
		int par1 = getParent(u), par2 = getParent(v);
		if (par1 == par2)
		{
			return false;
		}

		if (component_size[par1] > component_size[par2])
		{
			swap(par1, par2);
		}

		component_size[par2] += component_size[par1];
		component_size[par1] = 0;

		connected--;
		parent[par1] = parent[par2];
		return true;
	}
};
