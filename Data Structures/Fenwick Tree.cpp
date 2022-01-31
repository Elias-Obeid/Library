
template <typename DATA>
class BIT
{
private:
    int m_tree_size;
    vector<DATA> m_tree;

public:
    BIT(int n, const vector<DATA> &initial)
        : m_tree_size{n}
    {
        m_tree.resize(m_tree_size);
        for (int i = 0; i < n; ++i)
        {
            this->updateNode(i, initial[i]);
        }
    }

    void updateNode(int i, DATA value)
    {
        while (i < m_tree_size)
        {
            m_tree[i] += value;
            i |= (i + 1);
        }
    }

    DATA queryPrefix(int r)
    {
        DATA sum{};
        while (r >= 0)
        {
            sum += m_tree[r];
            r = (r & (r + 1)) - 1;
        }
        return sum;
    }
};
