
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename num_t>
using indexed_set = tree<
    num_t,
    null_type,
    less<num_t>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename num_t>
using indexed_multiset = tree<
    num_t,
    null_type,
    less_equal<num_t>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
