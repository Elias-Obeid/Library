#include <bits/stdc++.h>
using namespace std;

template <typename number_type, typename number_type_compare>
vector<int> getClosestLeft(const vector<number_type> &values, number_type_compare &&compare)
{
    int N = (int)values.size();

    vector<int> indices_stack;
    vector<int> closest_left(N);
    for (int i = 0; i < N; ++i)
    {
        while (!indices_stack.empty() && !compare(values[indices_stack.back()], values[i]))
        {
            indices_stack.pop_back();
        }
        closest_left[i] = (indices_stack.empty() ? -1 : indices_stack.back());
        indices_stack.emplace_back(i);
    }
    return closest_left;
}

template <typename number_type, typename number_type_compare>
vector<int> getClosestRight(const vector<number_type> &values, number_type_compare &&compare)
{
    int N = (int)values.size();

    vector<int> indices_stack;
    vector<int> closest_right(N);
    for (int i = N - 1; i >= 0; --i)
    {
        while (!indices_stack.empty() && !compare(values[indices_stack.back()], values[i]))
        {
            indices_stack.pop_back();
        }
        closest_right[i] = (indices_stack.empty() ? N : indices_stack.back());
        indices_stack.emplace_back(i);
    }
    return closest_right;
}

int main()
{
    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    vector<int> to_left = getClosestLeft(A, less<int>{});
    for (int i = 0; i < N; ++i)
    {
        cout << to_left[i] << " \n"[i == N - 1];
    }

    vector<int> to_right = getClosestRight(A, less<int>{});
    for (int i = 0; i < N; ++i)
    {
        cout << to_right[i] << " \n"[i == N - 1];
    }
    return 0;
}