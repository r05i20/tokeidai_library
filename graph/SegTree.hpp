// https://github.com/r05i20/tokeidai_library/blob/main/graph/SegTree.hpp
// SegmentTree<int> seg(N, [](int a, int b){return min(a,b);}, (1LL<<31)-1);
template <typename T>
struct SegmentTree {
  function<T(T,T)> op;
  T e;
  int n;
  vector<T> data;
  
  // 初期化
  SegmentTree(int N, function<T(T,T)> op, T e) : op(op), e(e) {
    n = 1;
    while(n < N) n *= 2;
    data = vector<T>(2*n, e); // 図からわかるように2*nのサイズの配列があればよい
  }
  
  // data[i]をvalに変更する
  void set(int i, T val) {
    i += n;　// 最下層のノード
    data[i] = val;
    while(i > 1) {
      i /= 2;
      // １つ上の左右の子に値を更新する
      data[i] = op(data[i*2], data[i*2+1]);
    }
  }
  
  // 区間[l,r)の中での最小値を出力する
  T query(int l, int r) {
    l += n;
    r += n;
    T l_val = e, r_val = e;　// 左右のすでに変更が反映されたマス全てに対しop()した値
    while(l < r) {
      if(l % 2 == 1) {
        l_val = op(l_val, data[l]);
        l++;
      }
      if(r % 2 == 1) {
        r--;
        r_val = op(data[r], r_val);
      }
      l /= 2;
      r /= 2;
    }
    return op(l_val, r_val);
  }
}