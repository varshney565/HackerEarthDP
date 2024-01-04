/**
 * author : shivam varshney
 * UIET KURUKSHETRA UNIVERSITY
 * ∑.⌣
 * */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define pbds tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#include<bits/stdc++.h>
#pragma GCC optimise("Ofast")
#pragma GCC target("avx","avx2","fma")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
#define all(x) x.begin(),x.end()
#define pi pair<int,int>
#define ff first
#define ss second

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << "\n";
#else
#define debug(x)
#endif

void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(bool t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(multimap <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
inline void read(int &n,vector<int> &v) {for(int i = 0 ; i < n ; i++) cin>>v[i];}
inline void print(int &n,vector<int> &v) {for(int i = 0 ; i < n ; i++) cout<<v[i]<<" ";cout<<"\n";}
inline void read(int &n,int &m,vector<vector<int>> &v) {for(int i = 0 ; i < n ; i++) {for(int j = 0 ; j < m ; j++){ cin>>v[i][j];}}}
inline void print(int &n,int &m,vector<vector<int>> &v) {for(int i = 0 ;i < n ; i++){for(int j = 0 ; j < m ; j++){cout<<v[i][j]<<" ";}cout<<"\n";}}
inline void consoleLog(bool ans) {cout<<(ans ? "YES\n" : "NO\n");}
inline int get(pbds &s,int ind) {return *s.find_by_order(ind);}
inline int lb(pbds &s,int val) {return s.order_of_key(val);}

/**
 * 
 * Actual code starts here.
 * 
 * */

class SegTree {
public:
    vector<int> p;
    vector<int> v;
    SegTree(vector<int> &v) {
        int n = v.size();
        p.resize(4*n,0);
        this->v.assign(v.begin(),v.end());
        this->build(0,0,n-1);
    }

private:
    int query(int l,int r,int index,int low,int high) {
        if(r < low || high < l)
            return 0;

        if(l <= low && r >= high)
            return p[index];
        int mid = low+(high-low)/2;
        int left = query(l,r,2*index+1,low,mid);
        int right = query(l,r,2*index+2,mid+1,high);
        return (left^right);
    }

    void build(int index,int low,int high) {
        if(low == high){
            p[index] = v[low];
            return;
        }

        int mid = low+(high-low)/2;
        build(2*index+1,low,mid);
        build(2*index+2,mid+1,high);
        p[index] = (p[2*index+1]^p[2*index+2]);
    }
public:
    int query(int l,int r) {
        int n = v.size();
        return query(l,r,0,0,n-1);
    }
};

void solve() {
    int n,x;
    cin>>n>>x;
    int m = n;
    string a,b;cin>>a>>b;
    int cnt = 0;
    vector<int> pending;
    for(int i = 0 ; i < n ; i++) {
        if(a[i] != b[i]) {
            pending.push_back(i);
            cnt++;
        }
    }
    if(cnt%2 == 1) {
        cout<<"-1\n";
        return;
    }

    n = pending.size();
    debug(pending);
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    function<int(int,int)> go = [&](int n,int cnt) {
        if(dp[n][cnt] != -1) return dp[n][cnt];
        if(n == 0 && cnt == 0) {
            return dp[n][cnt] = 0;
        }
        if(n == 0) {
            return dp[n][cnt] = 100000;
        }
        // go for the element that is immediatly next to it
        int op1 = 100000,op2 = 100000,op3 = 100000;
        if(n > 1) {
            op1 = min(x,pending[n-1]-pending[n-2])+go(n-2,cnt);
        }
        // make the current index as a unpaired index
        op2 = go(n-1,cnt+1);

        // pair the currert index with any other index
        if(cnt) {
            op3 = go(n-1,cnt-1)+x;
        }
        return dp[n][cnt] = min({op1,op2,op3});
    };
    cout<<go(n,0)<<"\n";
}

signed main()
{
   #ifndef ONLINE_JUDGE
        freopen("./../io/input.txt","r",stdin);
        freopen("./../io/output.txt","w",stdout);
        freopen("./../io/error.txt", "w", stderr);
    #endif

    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n";
    return 0;
} 