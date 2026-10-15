template<class Container>
auto run_length(const Container& v) {
    using T = typename Container::value_type;
    vector<pair<T, int>> res;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && v[i] == v[j]) j++;
        res.emplace_back(v[i], j - i);
        i = j - 1;
    }
    return res;
}