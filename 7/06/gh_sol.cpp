#include <stdio.h>
#define M 1000000007LL
#define LV 50000
typedef long long ll;
/* dp[lv][rev] : key note의 레벨이 lv이고 역방향 키가 rev 개인 가짓수 */
ll dp[50001][7];
int main(void)
{
    ll lv; scanf("%lld", &lv);
    if(lv <= 5)
    {
        printf("%lld\n", (1LL<<(2*lv)));
        return 0;
    }
    dp[0][0] = 1LL;
    for(ll v=1; v<=LV; v++)
    {
        for(ll rev=0; rev<=6; rev++)
        {
            dp[v][rev] = 8*dp[v-1][rev];
            // v-1개까지 보았을 때 rev개인 경우와, rev-1개인 경우가 있으므로 이를 더해줘야 한다.
            // Combination dp가 채워지는 원리랑 동일함.
            if(rev)
                dp[v][rev] += (8*dp[v-1][rev-1]);
            dp[v][rev] %= M;
        }
    }
    printf("%lld\n", (dp[lv][0] + dp[lv][1] + dp[lv][2] + dp[lv][3] + dp[lv][4] + dp[lv][5] + dp[lv][6]) % M);
    return 0;
}