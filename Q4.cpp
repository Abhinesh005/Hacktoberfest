    #include <bits/stdc++.h>
     
    using ll=long long;
    using std::cin;
     
    template<class T>
    void ckmx(T &A,T B){
    	A<B?A=B:B;
    }
     
    const int N=2e5+7;
     
    int n,m,va,vb;
    int a[N],b[N];
    int da[N],db[N];
     
    bool check(int x){
    	ll sm=0,f1=0,f2=0;
    	for(int j=m,i=0;j>=1;--j){
    		while(i<n&&a[i+1]+b[j]<=x)
    			++i;
    		db[j]=i;
    		sm+=db[j];
    	}
    	f1=f2=sm;
    	for(int i=n,j=m;i>=1;--i){
    		sm-=min(j,da[i]);
    		sm+=m-max(j,da[i]);
    		ckmx(f1,sm);
    		ckmx(f2,sm-(i<=va&&j<vb));
    		while(j&&min(db[j],i-1)<=n-max(db[j],i-1)){
    			sm-=min(db[j],i-1);
    			sm+=n-max(db[j],i-1);
    			--j;
    			ckmx(f1,sm);
    			ckmx(f2,sm-(i<=va&&j<vb));
    		}
    	}return f1==f2;
    }
     
    void Main(){
    	cin>>n>>m;
    	for(int i=1;i<=n;++i)
    		cin>>a[i];
    	for(int j=1;j<=m;++j)
    		cin>>b[j];
    	va=a[1],vb=b[1];
    	std::sort(a+1,a+n+1);
    	std::sort(b+1,b+m+1);
    	while(l<r){
    		int mid=(l+r)>>1;
    		if(check(mid))
    			r=mid;
    		else 
    			l=mid+1;
    	}cout<<l<<"\n";
    }
     
    inline void File(){
    	cin.tie(nullptr)->sync_with_stdio(false);
    #ifdef zxyoi
    	freopen("my.in","r",stdin);
    #endif
    }signed main(){File();Main();return 0;}