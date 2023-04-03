#include <stdio.h>
#include <unordered_map>
#include <algorithm>
#define inf 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef long long ll;
typedef struct moo moo;
ll arr[404040];
ll nj[404040];
unordered_map <ll, ll> dist;
ll calc(ll a, ll b)
{
    //printf("a = %lld b = %lld\n", a, b);
    if(a <= b)
        return nj[b] - nj[a];
    else
        return nj[401010] - nj[a] + nj[b] - nj[0];
}
int main(void)
{
    ll n, totari; scanf("%lld", &n);
    for(ll i=1; i<=4*n; i++)
    {
        ll d; scanf("%lld", &d); arr[i+1] = d;
    }
    for(ll i=1; i<404040; i++){
        nj[i] = nj[i-1] + arr[i];
        totari = nj[i];
    }
    for(ll i=1; i<=4; i++)
    {
        ll a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        ll r = min(a, min(b, c));
        dist[n*i] = r;
    }
    ll Q; scanf("%lld", &Q);
    for(ll i=1; i<=Q; i++)
    {
        ll k; scanf("%lld", &k);
    ll ans = inf;
        for(ll ji=1; ji<=4; ji++)
        {        
            //anti clockwise + a
            ll di = calc(k, n*ji);
            ll r1 = di + dist[n*ji];
            ans = min(ans, r1);
            //clockwise + a
            ll r2 = (totari - di) + dist[n*ji];
            ans = min(ans, r2);
        }
        printf("%lld\n", ans);
    }
    return 0;
}