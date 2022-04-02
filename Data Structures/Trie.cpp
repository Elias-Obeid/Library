
const int BIT = 16;

struct TrieNode
{
    vector<int> next_node;
    vector<int> subtree_sum;

    TrieNode(int k)
    {
        next_node.resize(k, 0);
        subtree_sum.resize(k, 0);
    }
};

struct Trie
{
    int K;
    int root;
    vector<TrieNode> nodes;

    Trie(int k)
        : K{k}
    {
        fetchNode();
        root = fetchNode();
    }

    int fetchNode()
    {
        nodes.push_back(TrieNode(K));
        return int(nodes.size()) - 1;
    }

    bool hasNumber(int value)
    {
        int current_node = root;
        for (int i = BIT; i >= 0; --i)
        {
            int bit = bool(value & (1 << i));
            if (nodes[current_node].next_node[bit] == 0)
            {
                int idx = fetchNode();
                nodes[current_node].next_node[bit] = idx;
            }

            if (nodes[current_node].subtree_sum[bit] == 0)
            {
                return false;
            }
            current_node = nodes[current_node].next_node[bit];
        }
        return true;
    }

    void update(int value, int add)
    {
        int current_node = root;
        for (int i = BIT; i >= 0; --i)
        {
            int bit = bool(value & (1 << i));
            if (nodes[current_node].next_node[bit] == 0)
            {
                int idx = fetchNode();
                nodes[current_node].next_node[bit] = idx;
            }

            nodes[current_node].subtree_sum[bit] += add;
            current_node = nodes[current_node].next_node[bit];
        }
    }

    void insert(int value)
    {
        update(value, +1);
    }

    void erase(int value)
    {
        update(value, -1);
    }
};
