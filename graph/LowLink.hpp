// https://github.com/r05i20/tokeidai_library/blob/main/graph/LowLink.hpp
struct LowLink
{
    /* Lowlink: グラフの関節点・橋を列挙する構造体
    作成: O(E+V)
    関節点の集合: vector<ll> aps
    橋の集合: vector<pair<ll,ll>> bridges
    */
    vector<vector<ll>> &G;
    // uesdは0の時偽、それ以外の時真
    vector<ll> used,ord,low,aps;
    vector<pair<ll,ll>> bridges;

    LowLink(vector<vector<ll>> &G) : G(G){
        used.assign(G.size(), 0);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        ll k = 0;
        for (int i = 0; i < (int)G.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
        sort(aps.begin(), aps.end()); // 必要ならソートする
        sort(bridges.begin(), bridges.end()); // 必要ならソートする
    }

    ll dfs(ll id, ll k, ll par){
        used[id]=true;
        ord[id]=k++;
        low[id]=ord[id];

        bool is_aps=false; // 関節点かどうか
        int count=0; //子の数
        for(auto &e : G[id]){ // id:探索中の頂点, k:dfsで何番目に探索するか, par:idの親
            if(!used[e]){
                count++;
                k=dfs(e,k,id);
                low[id]=min(low[id],low[e]);
                if(par!=-1 && ord[id]<=low[e])is_aps=true;
                if(ord[id]<low[e])bridges.emplace_back(min(id,e),max(id,e)); //条件を満たすので橋   
            }
            else if(e!=par){
                low[id]=min(low[id],ord[e]);
            }
        }
        if (par == -1 && count >= 2) is_aps = true; 
        if (is_aps) aps.push_back(id);
        return k;
    }
};