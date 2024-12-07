#include <stdio.h>
#define M 1000000007LL
typedef long long ll;
ll dp[201][50001];
int main(void)
{
    // dp[x][y] : x번 컴퓨터까지 고려했을 때, 총 y/8 kwh를 쓴 가짓수.
    ll n, ans = 0; scanf("%lld", &n); dp[0][0] = 1LL;
    for(ll i=1; i<=n; i++)
    {
        ll a, b, unit; scanf("%lld%lld", &a, &b);
        // 1 kwh = 16 unit
        unit = (a * b * 16)/ (60 * 1000);
        for(ll j=0; j<=50000; j++)
        {
            dp[i][j] = dp[i-1][j];
            if(j >= unit) dp[i][j] += dp[i-1][j-unit];
            dp[i][j] %= M;
        }
    }
    ll c1, c2; scanf("%lld%lld", &c1, &c2);
    for(ll i=0; i<=50000; i++)
    {
        ll cost = 6 * i;
        if(cost < c1 || cost > c2) continue;
        ans += dp[n][i]; ans %= M;
    }
    printf("%lld\n", ans);
    return 0;
}