#include <stdio.h>
#define M 1000000007LL
typedef long long ll;
ll co[128];
char str[1010101];
ll two[1010101];
ll nc_2(ll x)
{
    return (x*(x-1))/2;
};
int main(void)
{
    ll n; scanf("%lld\n%s", &n, str); two[0] = 1;
    for(int i=1; i<1010101; i++)
        two[i] = (two[i-1] * 2)%M;
    for(int i=0; str[i]; i++)
        co[str[i]]++;
    // 길이가 2인 가짓수.
    ll base = nc_2(n); base %= M;
    for(ll i=0; i<128; i++)
    {
        if(co[i] <= 2) continue;
        ll w = co[i];
        ll temp = two[w]; temp = (temp - 1 + M) % M;
        temp = (temp - w + M) % M;
        temp = (temp - nc_2(w) % M + M) % M;
        base = (base + temp) % M;
        // 모두 같은 것을 꺼내는 경우를 세야 하는데, 1개, 2개인 경우는 제외해야 한다.
        // 제외하는 가짓수를 빼는 게 더 빠르기 때문에 여사건으로 접근하면 된다.
        // 배반사건 (교집합이 없는 케이스)와 혼동되는 경우 주의.
    }
    printf("%lld\n", base);
    return 0;
}