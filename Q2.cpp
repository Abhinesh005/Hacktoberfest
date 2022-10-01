    /*  ********** fastcoder_ali ********* */
    #include <bits/stdc++.h>
    using namespace std;
    #define lli long long int
    const lli A=1e6+5;
    vector<lli> divs[A],pos[A];
    lli id[A];
     
    void solve()
    {
    	lli n;
    	cin>>n;
    	vector<lli> a(n),gl(n),gr(n),ll(n),lr(n);
    	
    	for(lli i=0;i<n;i++){
    		cin>>a[i];
    		pos[a[i]].push_back(i);
    	}
     
    	{
    		stack<lli> st;
    		for(lli i=0;i<n;i++){
    			while(!st.empty()&&a[i]>=a[st.top()])st.pop();
    			gl[i] = st.empty()?-1:st.top();
    			st.push(i);
    		}
    	}
    	
    	{
    		stack<lli> st;
    		for(lli i=n-1;i>=0;i--){
    			while(!st.empty()&&a[i]>a[st.top()])st.pop();
    			gr[i] = st.empty()?n:st.top();
    			st.push(i);
    		}
    	}
    	{
    		stack<lli> st;
    		for(lli i=n-1;i>=0;i--){
    			while(!st.empty()&&a[i]<=a[st.top()])st.pop();
    			lr[i] = st.empty()?n:st.top();
    			st.push(i);
    		}
    	}
     
    	long long ans=0;
    	for(lli i=0;i<n;i++){
    		for(auto x:divs[a[i]]){
    			if(id[x]){
    				
    				lli j = pos[x][id[x]-1];
    				// cout<<"maxp: " <<i<<' '<<" minp: "<<j<<'\n';
    				if(lr[j]>i&&gl[i]<j){
    					ans += 1ll*(j-max(ll[j],gl[i]))*(min(lr[j],gr[i])-i);
    					// cout<<"range: "<<max(ll[j],gl[i])+1<<' '<<min(lr[j],gr[i])-1<<'\n';
    				}
    			}
    			
    		}
    		id[a[i]]++;
    	}
     
    	cout<<ans<<'\n';
     
    	for(lli i=0; i<n; i++){
    		id[a[i]]=0;
    		pos[a[i]].erase(pos[a[i]].begin(),pos[a[i]].end());
    	}
    }
    int main()
    {
        #ifndef ONLINE_JUDGE
    	freopen("input.txt", "r", stdin);
    	freopen("output.txt", "w", stdout);
        #endif
        
        for(int i=1;i<A;i++)
    		for(int j=i;j<A;j+=i)
    			divs[j].push_back(i);
    	lli t;
    	cin>>t;
    	while(t--)
    	{
    	    solve();
    	}
    	
    	return 0;
    }