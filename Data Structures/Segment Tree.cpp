#include <bits/stdc++.h>
using namespace std;

class Segment
{
public:
    int m_maximum;
    long long int m_sum;

    Segment(long long int sum = 0, int maximum = numeric_limits<int>::lowest())
        : m_sum{sum}, m_maximum{maximum}
    {
    }

    bool empty() const
    {
        return m_maximum != numeric_limits<int>::lowest();
    }

    void apply(long long int length, const SegmentChange &change)
    {
        if (change.has_set())
        {
            m_maximum = change.m_to_set;
            m_sum = length * change.m_to_set;
        }

        m_maximum += change.m_to_add;
        m_sum += length * change.m_to_add;
    }

    void combineNodes(const Segment &other)
    {
        if (empty())
        {
            *this = other;
        }
        else if (!other.empty())
        {
            m_maximum = max(m_maximum, other.m_maximum);
            m_sum += other.m_sum;
        }
    }

    void combineNodes(const Segment &a, const Segment &b)
    {
        *this = a;
        this->combineNodes(b);
    }
};

class SegmentChange
{
private:
    static const int SENTINEL = numeric_limits<int>::lowest();

public:
    int m_to_set, m_to_add;

    SegmentChange(int to_add = 0, int to_set = SENTINEL)
        : m_to_set{to_set}, m_to_add{to_add}
    {
    }

    bool has_set() const
    {
        return m_to_set != SENTINEL;
    }

    bool has_change() const
    {
        return has_set() || m_to_add != 0;
    }

    SegmentChange combineChanges(const SegmentChange &other)
    {
        if (other.has_set())
        {
            return other;
        }
        return SegmentChange(m_to_add + other.m_to_add, m_to_set);
    }
};

class SegmentTree
{
private:
    int tree_size;
    vector<Segment> tree;
    vector<SegmentChange> lazy;

    static int highest_bit(unsigned x)
    {
        return (x == 0 ? -1 : 31 - __builtin_clz(x));
    }

public:
    SegmentTree(const vector<Segment> &initial, int n)
    {
        initialize(initial, n);
    }

    void initialize(const vector<Segment> &initial, int n)
    {
        tree_size = 1;
        while (tree_size < n)
        {
            tree_size = (tree_size * 2);
        }

        tree.resize(2 * tree_size, Segment());
        lazy.resize(2 * tree_size, SegmentChange());
        buildTree(initial, n);
    }

    void buildTree(const vector<Segment> &initial, int n)
    {
        for (int i = 0; i < n; ++i)
        {
            tree[i + tree_size] = initial[i];
        }

        for (int node = tree_size - 1; node > 0; --node)
        {
            tree[node].combineNodes(tree[node * 2], tree[node * 2 + 1]);
        }
    }
};