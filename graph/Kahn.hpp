// https://github.com/r05i20/tokeidai_library/blob/main/graph/Kahn.hpp
template<typename T>
vector<int> topological_sort(vector<vector<T>> &g){
    int N=g.size();
    //入次数0の頂点のキュー
    queue<int> q;
    // 各頂点の入次数を記録する
    vector<int> deg_in(N);
    for(int i=0; i<N; i++)for(int to:g[i])deg_in[to]++;
    for(int i=0; i<N; i++)if(deg_in[i] == 0) q.push(i);
    
    // この配列に格納する
    vector<int> ret;
    
    // 入次数0キューが空になるまで、入次数0の頂点をretに追加していく
    while(!q.empty()){
        int i = q.front(); q.pop();
        ret.push_back(i);
        // iから行ける場所の入次数を1減らし、新しく入次数0になったらキューに追加する
        for(int to: g[i]){
            deg_in[to]--;
            if(deg_in[to] == 0) q.push(to);
        }
    }
    
    return ret;
}