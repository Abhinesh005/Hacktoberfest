#include <bits/stdc++.h>
     
    using namespace std;
     
    constexpr int N = 5005, INF = 1e9;
     
    int t[N];
     
    void inc(int i, int d) {
    	for (; i < N; i |= i + 1)
    		t[i] += d;
    }
     
    int sum(int r) {
    	int ans = 0;
    	for (; r >= 0; r = (r & r + 1) - 1)
    		ans += t[r];
        return ans;
    }
     
    signed main() {
    	ios::sync_with_stdio(false);
    	cin.tie(0);
    	cout.tie(0);
     
    	int n, k;
    	cin >> n >> k;
     
        vector<int> p(n), pos(n);
        for (int i = 0; i < n; i++) {
        	cin >> p[i];
        	p[i]--;
        	pos[p[i]] = i;
        }
     
        vector<vector<int>> dp(n + 1, vector<int>((1 << k), INF));
     
        dp[0][0] = 0;
     
     
        function<int(int, int, int)> inv = [&] (int mn, int mask, int x) {
            int ans = 0;
            for (int i = 0; i < k; i++)
            	if ((mask & (1 << i)) && pos[x] < pos[mn + i + 1])
            		ans++;
     
            ans += sum(N - 1) - sum(pos[x]);
            return ans;
        };
     
        for (int mn = 0; mn < n; mn++) {
        	for (int mask = 0; mask < (1 << min(k, n - mn - 1)); mask++) {
        		for (int i = 0; i < min(k, n - mn - 1); i++)
        			if ((mask & (1 << i)) == 0) {
        				dp[mn][mask + (1 << i)] = min(dp[mn][mask + (1 << i)], dp[mn][mask] + inv(mn,mask, mn + i + 1));
        			}
     
        		int mn2 = mn, mask2 = mask;
        		mn2++;
        		while (mask2 % 2) {
        			mn2++;
        			mask2 /= 2;
        		}
        		mask2 /= 2;
     
        		dp[mn2][mask2] = min(dp[mn2][mask2], dp[mn][mask] + inv(mn, mask, mn));
     
        	}
        	inc(pos[mn], 1);
        }
        cout << dp[n][0];
    }
