// https://github.com/r05i20/tokeidai_library/blob/main/graph/Dijkstra.hpp
// N : 頂点数、r : 始点
vector<ll> Dijkstra(int N, int r, vector<vector<ll,int>> &G)
{
    vector<ll> cur(N,INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
    cur[r]=0;
    q.push(make_pair(cur[r],r));

    while(!q.empty()){
        auto[c, pos]=q.top(); q.pop();
        if(c > cur[pos])continue;

        for(int i=0; i<G[pos].size(); i++){
            int nex=G[pos][i].first;
            int cost=G[pos][i].second;
            if(cur[nex]>cur[pos]+cost){
                cur[nex]=cur[pos]+cost;
                q.push(make_pair(cur[nex],nex));
            }
        }
    }

    return cur;
}