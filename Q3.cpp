#include<bits/stdc++.h>
    #define ll long long
    #define ull unsigned long long
    #define ld long double
    #define pi pair<int,int>
    #define all(x) begin(x),end(x)
    using namespace std;
    inline ll read()
    {
     	ll x=0,f=1;char c=getchar();
     	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
     	for(;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
     	return x*f;
    }
    inline void out(ll x){if(x>9)out(x/10);putchar(x%10^48);}
    inline void print(ll x,char c='\n'){if(x<0)putchar('-'),x=-x;out(x),putchar(c);}
    const int N=2e4+10;
    int h[N],tmp[N],cnt=1;
    struct edge{int v,nxt;ll w;}e[N<<3];
    inline void add(int x,int y,int z){e[++cnt]={y,h[x],z},h[x]=cnt;}
    inline void ins(int x,int y,int z){add(x,y,z),add(y,x,0);}
    ll dinic(int s,int t,ll res=0)
    {
        vector<int> d(N,0);
        auto bfs=[&]()
        {
            queue<int>q({s});d=vector<int>(N,0),d[s]=1;
            while(q.size())
            {
                int x=q.front();q.pop();
                for(int i=h[x],y;i;i=e[i].nxt)
                    if(e[i].w>0&&!d[y=e[i].v])q.push(y),d[y]=d[x]+1;
            }
            return d[t];
        };
        function<ll(int,ll)> dfs=[&](int x,ll f)
        {
            if(x==t)return f;
            ll k,res=0;
            for(int i=h[x],y;i&&f;h[x]=i,i=e[i].nxt)
                if(e[i].w>0&&d[y=e[i].v]==d[x]+1)
                k=dfs(y,min(f,e[i].w)),!k&&(d[y]=1e9),e[i].w-=k,e[i^1].w+=k,f-=k,res+=k;
            return res;
        };
        memcpy(tmp,h,sizeof h);
        while(bfs())res+=dfs(s,1e18),memcpy(h,tmp,sizeof h);
        return res;
    }
    int a[N],s[N];
    pi q[N];
    int main()
    {
    	int n=read(),m=read(),S=n+m+1,T=n+m+2,E=n+m+3,sum=0;
    	for(int i=1;i<=n;i++)s[i]=read();
    	for(int i=1;i<=n;i++)a[i]=read();
    	for(int i=1;i<=m;i++)
    	{
    		q[i]={read(),read()};
    		auto[x,y]=q[i];
    		x=s[x]?x:E,y=s[y]?y:E;
    		a[x]++,a[y]++,ins(S,i+n,2),ins(i+n,x,2),ins(i+n,y,2);
    	}
    	for(int i=1;i<=n;i++)
    		if(s[i])
    		{
    			ins(i,T,a[i]),sum+=a[i];
    			if(a[i]<0)return puts("NO"),0;
    		}
    	if(m*2<sum)return puts("NO"),0;
    	ins(E,T,m*2-sum);
    	int tmp=dinic(S,T);
    	if(tmp!=m*2)return puts("NO"),0;
    	puts("YES");
    	for(int i=1;i<=m;i++)
    	{
    		auto[x,y]=q[i];
    		if(e[(i-1)*6+4].w)print(x,' '),print(y);
    		else print(y,' '),print(x);
    	}
    }
