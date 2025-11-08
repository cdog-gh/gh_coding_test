#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct moo
{
    ll to, c;
};
typedef struct moo moo;
vector <moo> con[404040];
ll pp[404040];
ll depth[404040];
vector <ll> pv;
vector <ll> dv;
vector <ll> cc;
ll compressed[404040];
ll C[404040];
ll combi_two(ll n)
{
    return ((n * (n-1)) >> 1LL);
}
void dfs(ll cur, ll par, ll nn);
int main(void)
{
    ll n; scanf("%lld", &n); // printf("n = %lld\n", n);
    for(ll i=1; i<n; i++)
    {
        moo I; ll a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        // 1 <= c <= 10^9
        I.to = b; I.c = c; con[a].push_back(I);
        I.to = a; I.c = c; con[b].push_back(I);
    }
    // 1 <= pp[i] <= 10^9
    for(int i=1; i<=n; i++) scanf("%lld", pp + i);
    dfs(1, -1, 0);
    for(ll i=1; i<=n; i++){
        dv.push_back(depth[i]);
        pv.push_back(pp[i]);
        // printf("%lld -- %lld -- %lld\n", i, depth[i], pp[i]);
    }
    sort(dv.begin(), dv.end());  dv.erase(unique(dv.begin(), dv.end()), dv.end());
    sort(pv.begin(), pv.end());  pv.erase(unique(pv.begin(), pv.end()), pv.end());
    for(ll i=1; i<=n; i++)
    {
        ll a = lower_bound(dv.begin(), dv.end(), depth[i]) - dv.begin();
        ll b = lower_bound(pv.begin(), pv.end(), pp[i]) - pv.begin();
        compressed[i] = (1 << 20) * a + b;
        cc.push_back(compressed[i]);
    }
    sort(cc.begin(), cc.end()); cc.erase(unique(cc.begin(), cc.end()), cc.end());
    for(ll i=1; i<=n; i++)
    {
        ll lo = lower_bound(cc.begin(), cc.end(), compressed[i]) - cc.begin();
        C[lo]++;
    }
    ll ans = combi_two(n);
    for(ll i=0; i<=n; i++)
    {
        if(C[i] < 2) continue;
        ans -= combi_two(C[i]);
    }
    printf("%lld %lld\n", ans, ans);
    return 0;
}
void dfs(ll cur, ll par, ll nn)
{
    depth[cur] = nn;
    for(ll i=0; i<(ll)con[cur].size(); i++)
    {
        ll ne = con[cur][i].to;
        ll nn_cc = nn + con[cur][i].c;
        if(ne == par) continue;
        dfs(ne, cur, nn_cc);
    }
}