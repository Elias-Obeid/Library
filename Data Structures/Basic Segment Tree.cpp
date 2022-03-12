
struct Segment
{
    int maximum;

    Segment(int _maximum = numeric_limits<int>::lowest())
        : maximum{_maximum}
    {
    }

    // ! Remeber to modify based on need
    void operator+=(const Segment &other)
    {
    }

    void combineSegments(const Segment &other)
    {
        *this += other;
    }

    void combineChildren(const Segment &left, const Segment &right)
    {
        *this = left;
        *this += right;
    }
};

class SegmentTree
{
private:
    int tree_n;
    vector<Segment> tree;

    void initializeTree(int n)
    {
        tree_n = 1;
        while (tree_n < n)
        {
            tree_n *= 2;
        }
        tree.resize(2 * tree_n, Segment{});
    }

    Segment queryRange(int l, int r, int node, int low, int high)
    {
        if (r < low || high < l)
        {
            return Segment{};
        }

        if (l <= low && high <= r)
        {
            return tree[node];
        }

        int mid = (low + high) / 2;

        Segment answer{};
        answer.combineSegments(queryRange(l, r, node * 2, low, mid));
        answer.combineSegments(queryRange(l, r, node * 2 + 1, mid + 1, high));
        return answer;
    }

    void updateNode(int pos, const Segment &new_val, int node, int low, int high)
    {
        pos += tree_n;
        tree[pos] = new_val;

        while (pos > 0)
        {
            pos /= 2;
            tree[pos].combineChildren(tree[pos * 2], tree[pos * 2 + 1]);
        }
    }

public:
    SegmentTree(int n)
    {
        initializeTree(n);
    }

    void buildTree(int n, const vector<Segment> &initial)
    {
        for (int i = 0; i < n; ++i)
        {
            tree[tree_n + i] = initial[i];
        }

        for (int node = tree_n - 1; node > 0; --node)
        {
            tree[node].combineChildren(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    // ! 0 indexing
    Segment queryRange(int l, int r)
    {
        return queryRange(l, r, 1, 0, tree_n - 1);
    }

    Segment queryFull()
    {
        return tree[1];
    }

    // ! 0 indexing
    void updateNode(int pos, const Segment &new_val)
    {
        updateNode(pos, new_val, 1, 0, tree_n - 1);
    }

    void debugTree()
    {
        for (int i = 1; i < 2 * tree_n; ++i)
        {
            cerr << tree[i].sum << " " << lazy[i].to_add << " : ";
            if ((i & (i + 1)) == 0)
            {
                cerr << "\n";
            }
            else
            {
                cerr << " ";
            }
        }
        cerr << "\n";
    }
};
