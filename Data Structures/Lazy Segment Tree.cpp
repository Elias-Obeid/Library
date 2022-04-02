
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

    void combineChanges(const SegmentChange &other)
    {
        if (other.hasSet())
        {
            *this = other;
        }
        else
        {
            to_add += other.to_add;
        }
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

    void pushUpdates(int node, int low, int high)
    {
        if (lazy[node].hasChange())
        {
            if (low != high)
            {
                lazy[node * 2 + 0].combineChanges(lazy[node]);
                lazy[node * 2 + 1].combineChanges(lazy[node]);
            }
            tree[node].pushChange(lazy[node], low, high);
            lazy[node] = SegmentChange{};
        }
    }

    Segment queryRange(int l, int r, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (r < low || high < l)
        {
            return Segment{};
        }
        else if (l <= low && high <= r)
        {
            return tree[node];
        }
        else
        {
            Segment answer{};
            int mid = (low + high) / 2;

            answer.combineSegments(queryRange(l, r, node * 2, low, mid));
            answer.combineSegments(queryRange(l, r, node * 2 + 1, mid + 1, high));
            return answer;
        }
    }

    Segment queryNode(int pos, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (low == high && pos == low)
        {
            return tree[node];
        }
        else
        {
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
    }

    void updateRange(int l, int r, const SegmentChange &change, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (r < low || high < l)
        {
            return;
        }
        else if (l <= low && high <= r)
        {
            lazy[node].combineChanges(change);
            pushUpdates(node, low, high);
        }
        else
        {
            int mid = (low + high) / 2;
            updateRange(l, r, change, node * 2, low, mid);
            updateRange(l, r, change, node * 2 + 1, mid + 1, high);
            tree[node].combineChildren(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    void updateNode(int pos, const Segment &new_val, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (low == high && pos == low)
        {
            tree[node] = new_val;
        }
        else
        {
            int mid = (low + high) / 2;
            if (pos <= mid)
            {
                updateNode(pos, new_val, node * 2, low, mid);
            }
            else
            {
                updateNode(pos, new_val, node * 2 + 1, mid + 1, high);
            }
            tree[node].combineChildren(tree[node * 2], tree[node * 2 + 1]);
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
