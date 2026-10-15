template<typename T>
vector<pair<T, T>> Prime_Factorize(T x) {
    vector<pair<T, long long>> ans;
    for (T i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            T count = 0;
            while (x % i == 0) {
                count++;
                x /= i;
            }
            ans.push_back(make_pair(i, count));
        }
    }
    if (x != 1) ans.push_back(make_pair(x, 1));
    return ans;
}