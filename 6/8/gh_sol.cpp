#include <stdio.h>
#include <memory.h>
#define M 998244353LL
typedef long long ll;
ll dp[55000][7];
int main(void)
{
    //memset(dp, -1, sizeof(ll)*7*55000);
    ll s; dp[0][0] = 1; scanf("%lld", &s);
    for(ll i=1; i<=s; i++)
    {
        for(ll j=0; j<=6; j++)
        {
            //(i-1, j-1) ~> (i, j)
            if(j)
                dp[i][j] += dp[i-1][j-1];
            //(i-1, j) -> (i, j)
            dp[i][j] += (6 * dp[i-1][j]);
            dp[i][j] %= M;
        }
    }
    ll totari = 1;
    for(ll i=1; i<=s; i++)
    {
        totari *= 7;
        totari %= M;
    }
    ll mi = 0;
    for(ll i=0; i<=6; i++)
        mi += dp[s][i];
    mi %= M;
    ll ans = (totari - mi + M)%M; printf("%lld\n", ans);    
}
