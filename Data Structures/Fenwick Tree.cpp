
template <typename DATA>
class BIT
{
private:
    int tree_size;
    vector<DATA> tree;

public:
    BIT(int n) : tree_size{n}
    {
        tree.resize(n);
    }

    void updateNode(int i, DATA value)
    {
        while (i < tree_size)
        {
            tree[i] += value;
            i |= (i + 1);
        }
    }

    // ! Inclusive Prefix
    DATA queryPrefix(int r)
    {
        DATA sum{};
        while (r >= 0)
        {
            sum += tree[r];
            r = (r & (r + 1)) - 1;
        }
        return sum;
    }
};
