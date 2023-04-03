#include <stdio.h>
#define M 1000000007LL
typedef long long ll;
ll g(ll s, ll x)
{
    if(s & (1<<x))
        return 1;
    return 0;
}
/*
지하역 B3을 선택했다고 그 다음역이 지하역 B4 선택 안 되는가? 아님.
따라서 독립 사건으로 볼 수 있고, 곱사건으로 처리할 수 있음.
층을 모두 탐색하면 최악의 경우 O(11^n)의 복잡도를 지상/지하역의 상태 관리로 O(2^n)으롲 줄여야 함.
*/
ll go(ll s, ll yeon, ll n)
{
    ll cur = 1, mmx = 1, gaji = 1;
    ll x = s;
    for(ll i=1; i<n; i++)
    {
        if(g(x, i-1) != g(x, i))
            cur++;
        else
            cur = 1;
        if(cur > mmx) mmx = cur;
    }
    if(mmx != yeon)
        return 0;
    for(ll i=0; i<n; i++)
    {
        if(g(x, i))
            gaji = gaji * 5;
        else
            gaji = gaji * 11;
        gaji %= M;
    }
    return gaji;
}
int main(void)
{
    ll n, m, ret = 0; scanf("%lld %lld", &n, &m);
    for(int i=0; i<(1<<n); i++)
    {
        ret = ret + go(i, m, n);
        ret = ret % M;
    }
    printf("%lld\n", ret);
}