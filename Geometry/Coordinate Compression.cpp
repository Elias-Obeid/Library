
template <typename T>
void compress(vector<T> &a)
{
    vector<pair<T, int>> coordinates;
    for (int i{0}; i < int(a.size()); ++i)
    {
        coordinates[i].first = a[i], coordinates[i].second = i;
    }
    sort(coordinates.begin(), coordinates.end());

    a[coordinates[0].second] = 0;
    for (int i{1}; i < int(a.size()); ++i)
    {
        bool is_not_equal{coordinates[i - 1].first != coordinates[i].first};
        a[coordinates[i].second] = a[coordinates[i - 1].second] + is_not_equal;
    }
}
