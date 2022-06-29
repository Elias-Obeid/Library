#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
private:
    // Todo : modify based on problem requirements
    struct Segment
    {
        long long sum;
        Segment(long long _sum = 0) : sum{_sum}
        {
        }
    };

    // Todo : modify based on problem requirements
    Segment mergeSegments(const Segment &left_side, const Segment &right_side)
    {
        return Segment(left_side.sum + right_side.sum);
    }

    int tree_size;
    vector<Segment> segment_tree;

    void initialize(int N)
    {
        tree_size = 1;
        while (tree_size < N)
        {
            tree_size *= 2;
        }
        segment_tree.resize(tree_size * 2, Segment{});
    }

    void buildTree(int N, const vector<int> &A)
    {
        for (int i = 0; i < N; ++i)
        {
            segment_tree[tree_size + i] = Segment(A[i]);
        }

        for (int node = tree_size - 1; node > 0; --node)
        {
            segment_tree[node] = mergeSegments(segment_tree[node * 2], segment_tree[node * 2 + 1]);
        }
    }

    void updateTree(int index, int value, int node, int low, int high)
    {
        if (low == high)
        {
            segment_tree[node] = Segment(value);
        }
        else
        {
            int middle = (low + high) / 2;
            if (index <= middle)
            {
                updateTree(index, value, node * 2, low, middle);
            }
            else
            {
                updateTree(index, value, node * 2 + 1, middle + 1, high);
            }
            segment_tree[node] = mergeSegments(segment_tree[node * 2], segment_tree[node * 2 + 1]);
        }
    }

    Segment queryRange(int left_bound, int right_bound, int node, int low, int high)
    {
        if (right_bound < low || high < left_bound)
        {
            return Segment();
        }
        else if (left_bound <= low && high <= right_bound)
        {
            return segment_tree[node];
        }
        else
        {
            int middle = (low + high) / 2;
            return mergeSegments(queryRange(left_bound, right_bound, node * 2, low, middle),
                                 queryRange(left_bound, right_bound, node * 2 + 1, middle + 1, high));
        }
    }

public:
    SegmentTree() {}
    SegmentTree(int N)
    {
        this->initialize(N);
    }

    SegmentTree(int N, const vector<int> &A)
    {
        this->initialize(N);
        this->buildTree(N, A);
    }

    void updateTree(int index, int value)
    {
        updateTree(index, value, 1, 0, tree_size - 1);
    }

    Segment queryRange(int left_bound, int right_bound)
    {
        return queryRange(left_bound, right_bound, 1, 0, tree_size - 1);
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    SegmentTree st(N, A);
    for (int qi = 0; qi < Q; ++qi)
    {
        string operation;
        cin >> operation;
        if (operation == "set")
        {
            int index, value;
            cin >> index >> value;
            st.updateTree(index, value);
        }
        else if (operation == "query")
        {
            int left_bound, right_bound;
            cin >> left_bound >> right_bound;
            cout << st.queryRange(left_bound, right_bound).sum << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}