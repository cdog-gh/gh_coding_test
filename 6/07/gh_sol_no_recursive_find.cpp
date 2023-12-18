#include <stdio.h>
#include <memory.h>
#include <vector>
#include <algorithm>
#define M 202020
#define R 1010101010LL
#define INF 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef long long ll;
struct moo
{
    ll from, to, c, ti;
};
typedef struct moo moo;
vector <moo> v;
ll p[M + 1];
ll co[M + 1];
ll _find(ll x)
{
    ll cur = x;
    for(;p[cur] != -1; cur = p[cur]);
    ll root = cur, par;
    for(cur = x;p[cur] != -1;cur = par)
    {
        par = p[cur]; p[cur] = root;
    }
    return cur;
};
void _merge(ll a, ll b)
{
    ll ta = _find(a);
    ll tb = _find(b);
    if(ta == tb) return;
    p[tb] = ta;
};
ll f(ll n, ll ti);
bool cmp(moo a, moo b)
{
    return a.c < b.c;
};
int main(void)
{
    ll n, m; scanf("%lld%lld", &n, &m);
    for(ll i=0; i<m; i++)
    {
        moo I; ll a, b, c, ti; scanf("\n%lld%lld%lld%lld", &a, &b, &c, &ti);
        I.from = a; I.to = b; I.c = c; I.ti = ti; v.push_back(I);
    }
    // 선 sort
    sort(v.begin(), v.end(), cmp);
    ll le = 0, ri = R, mid;
    ll ret = f(n, R);
    if(ret == INF)
    {
        printf("-1\n"); return 0;
    }
    while(le <= ri)
    {
        mid = (le + ri) / 2;
        ll k = f(n, mid);
        if(k > ret)
            le = mid + 1;
        else
        {
            ll k2 = f(n, mid-1);
            if(k2 > ret)
            {
                printf("%lld %lld\n", mid, ret);
                return 0;
            }
            else
                ri = mid-1;
        }
    }
    return 0;
}
// ti 에 건설되는 아이까지 고려했을 때, MST calc
ll f(ll n, ll ti)
{
    if(ti <= 0)
        return INF;
    memset(p, -1, sizeof(ll)* M);
    ll sumi = 0;
    for(ll i=0; i<(ll)v.size(); i++)
    {
        ll from = v[i].from; ll to = v[i].to; ll tt = v[i].ti;
        if(tt > ti) continue;
        if(_find(from) == _find(to))
            continue;
        _merge(from, to);
        sumi += v[i].c;
    }
    for(ll i=1; i<=n; i++)
    {
        if(_find(i) != _find(1))
            return INF;
    }
    return sumi;
}