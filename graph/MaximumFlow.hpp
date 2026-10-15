// https://github.com/r05i20/tokeidai_library/blob/main/graph/MaximumFlow.hpp
struct Edge{
    int to, rev;
    long long cap;
};

class MaximumFlow
{
    public:
        int size_;
        vector<bool> used;
        vector<vector<Edge>> G;

        void init(int N){
            size_=N;
            used.resize(N);
            G.resize(N);
        }

        void add_edge(int a, int b, long long c)
        {
            int ga=G[a].size();
            int gb=G[b].size();
            G[a].push_back(Edge{b,c,(long long)gb});
            G[b].push_back(Edge{a,0,(long long)ga});
        }

        long long dfs(int pos, int goal, int F)
        {
            if(pos==goal)return F;
            used[pos]=true;
            for(int i=0; i<G[pos].size(); i++)
            {
                if(G[pos][i].cap==0)continue;
                if(used[G[pos][i].to])continue;
                long long flow=dfs(G[pos][i].to, goal, min(F,G[pos][i].cap));
                if(flow>=1)
                {
                    G[pos][i].cap-=flow;
                    G[G[pos][i].to][G[pos][i].rev].cap+=flow;
                    return flow;
                }
            }
            return 0;
        }

        long long max_flow(int s, int t)
        {
            long long total=0;
            while(true)
            {
                fill(used.begin(),used.end(),false);
                long long F=dfs(s,t,inf);
                if(F==0)break;
                total+=F;
            }
            return total;
        }
};
