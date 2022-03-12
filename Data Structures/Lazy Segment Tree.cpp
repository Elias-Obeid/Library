
struct SegmentChange
{
    static const int BASE = numeric_limits<int>::lowest();

    int to_add;
    int to_set;

    SegmentChange(int _to_add = 0, int _to_set = BASE)
        : to_add{_to_add}, to_set{_to_set}
    {
    }

    bool hasSet() const
    {
        return to_set != BASE;
    }

    bool hasChange() const
    {
        return to_add != 0 || hasSet();
    }

    SegmentChange combineChanges(const SegmentChange &other) const
    {
        if (other.hasSet())
        {
            return other;
        }
        return SegmentChange(to_add + other.to_add, to_set);
    }
};

struct Segment
{
    int maximum;

    Segment(int _maximum = numeric_limits<int>::lowest())
        : maximum{_maximum}
    {
    }

    void pushChange(const SegmentChange &change, int low, int high)
    {
        if (change.hasSet())
        {
            maximum = change.to_set;
        }
        maximum += change.to_add;
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
    vector<SegmentChange> lazy;

    void initializeTree(int n)
    {
        tree_n = 1;
        while (tree_n < n)
        {
            tree_n *= 2;
        }
        tree.resize(2 * tree_n, Segment{});
        lazy.resize(2 * tree_n, SegmentChange{});
    }

    void applyAndCombine(int node, int low, int high, const SegmentChange &change)
    {
        tree[node].pushChange(change, low, high);
        if (node < tree_n)
        {
            lazy[node] = lazy[node].combineChanges(change);
        }
    }

    void pushUpdates(int node, int low, int high)
    {
        if (lazy[node].hasChange())
        {
            int mid = (low + high) / 2;
            applyAndCombine(2 * node, low, mid, lazy[node]);
            applyAndCombine(2 * node + 1, mid + 1, high, lazy[node]);

            lazy[node] = SegmentChange{};
        }
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
        pushUpdates(node, low, high);

        int mid = (low + high) / 2;

        Segment answer{};
        answer.combineSegments(queryRange(l, r, node * 2, low, mid));
        answer.combineSegments(queryRange(l, r, node * 2 + 1, mid + 1, high));
        return answer;
    }

    Segment queryNode(int pos, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (low == high)
        {
            return tree[node];
        }

        int mid = (low + high) / 2;
        if (pos <= mid)
        {
            return queryNode(pos, node * 2, low, mid);
        }
        else
        {
            return queryNode(pos, node * 2 + 1, mid + 1, high);
        }
    }

    void updateRange(int l, int r, const SegmentChange &change, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (low == high)
        {
            return;
        }
        else if (r < low || high < l)
        {
            return;
        }

        int mid = (low + high) / 2;
        updateRange(l, r, change, node * 2, low, mid);
        updateRange(l, r, change, node * 2 + 1, mid + 1, high);
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

    // ! 0 indexing
    Segment queryNode(int pos)
    {
        return queryNode(pos, 1, 0, tree_n - 1);
    }

    // ! 0 indexing
    void updateRange(int l, int r, const SegmentChange &change)
    {
        updateRange(l, r, change, 1, 0, tree_n - 1);
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
