// https://github.com/r05i20/tokeidai_library/blob/main/data-structures/UnionFind.hpp
class UnionFind
{
    public:
        UnionFind() = default;
        explicit UnionFind(size_t n)
            : m_parentsOrSize(n,-1){}

	    // 頂点iの代表元を返す
        int find(int i)
        {
            if(m_parentsOrSize[i]<0)
            {
                return i;
            }
            //経路圧縮
            return (m_parentsOrSize[i]=find(m_parentsOrSize[i]));
        }
        // 頂点a,bをつなぐ
        void merge(int a, int b)
        {
            a=find(a);
            b=find(b);
            if(a!=b)
            {
                //小さいほうが子になる
                if(-m_parentsOrSize[a] < -m_parentsOrSize[b])
                {
                    swap(a,b);
                }
                m_parentsOrSize[a]+=m_parentsOrSize[b];
                m_parentsOrSize[b]=a;
            }
        }
        // ２頂点が同じグループに属しているか、つまり同じ代表元を持っているかを返す
        bool same(int a, int b)
        {
            return (find(a)==find(b));
        }
        int size(int i)
        {
            return -m_parentsOrSize[find(i)];
        }
    private:
        vector<int> m_parentsOrSize;
};