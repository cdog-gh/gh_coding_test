#include <stdio.h>
#include <vector>
#include <map>
#define INF 1010101010LL
using namespace std;
typedef long long ll;
struct moo
{
    ll s, e, k;
};
typedef struct moo moo;
moo arr[202020];
map <ll, ll> counter;
vector <moo> event_add[202020];
vector <moo> event_rm[202020];
void add(ll x)
{
    if(counter.find(x) == counter.end())
        counter[x] = 1;
    else
        counter[x] = counter[x] + 1;
}
void rm(ll x)
{
    ll before = counter[x];
    ll after = before - 1;
    if(after == 0)
        counter.erase(counter.find(x));
    else
        counter[x] = after;
}
ll process()
{
    //printf("process = %lld\n", (ll)counter.size());
    if((ll)counter.size() == 1)
        return counter.begin() -> first;
    else
        return 1;
}
ll gg(ll a, ll b)
{
    ll r = a % b;
    if(r == 0)
        return b;
    return gg(b, r);
}
ll gcd(ll a, ll b)
{
    if(a >= b)
        return gg(a, b);
    return gg(b, a);
}
ll ans[202020];
ll dp[18][202020];
int main(void)
{
    ll n, Q; scanf("%lld%lld", &n, &Q);
    for(ll i=0; i<Q; i++)
    {
        ll s, e, k;
        scanf("%lld%lld%lld", &s, &e, &k);
        arr[i].s = s-1; arr[i].e = e-1; arr[i].k = k;
        event_add[arr[i].s].push_back(arr[i]);
        event_rm[arr[i].e].push_back(arr[i]);
    }
    for(ll i=0; i<n; i++)
    {
        //printf("%lld %lld\n", (ll)event_add[i].size(), (ll)event_rm[i].size());
        for(ll j=0; j<(ll)event_add[i].size(); j++)
        {
            ll x = event_add[i][j].k;
            add(x);
        }
        ans[i] = process();
        for(ll j=0; j<(ll)event_rm[i].size(); j++)
        {
            ll x = event_rm[i][j].k;
            rm(x);
        }
    }
    //init dp table
    for(ll i=0; i<n; i++)
        dp[0][i] = ans[i];
    for(ll t=1; t<18; t++)
    {
        for(ll i=0; i<n; i++)
        {
            ll right = (1LL<<(t-1));
            ll a = dp[t-1][i];
            ll b = 1;
            if(i + right < n) b = dp[t-1][i + right];
            ll g = gcd(a, b);
            ll te = (a*b) / g;
            if(te > INF) te = INF;
            dp[t][i] = te;
        }
    }
    //validate answer
    for(ll i=0; i<Q; i++)
    {
        ll s = arr[i].s;
        ll e = arr[i].e;
        ll k = arr[i].k;
        
        ll gugan_len = e - s + 1;
        ll cur_ans = 1;
        ll cur_lo = s;
        for(ll t=17; t>=0; t--)
        {
            if(gugan_len & (1LL<<t))
            {
                ll cc = dp[t][cur_lo];
                
                //cc and cur_ans lcm
                ll g = gcd(cc, cur_ans);
                ll lcc = (cc * cur_ans) / g;
                if(lcc > INF) lcc = INF;
                cur_lo = cur_lo + (1<<t);
                
                cur_ans = lcc;
            }
        }
        if(cur_ans != k)
        {
            printf("-1\n");
            return 0;
        }
    }
    for(ll i=0; i<n; i++)
        printf("%lld ", ans[i]);
    printf("\n");
}