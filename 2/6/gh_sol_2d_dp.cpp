#include <stdio.h>
typedef long long ll;
/*
dp[x][h] : x위치에서 고도가 h이다.
*/
ll dp[4004][4004];
int main(void)
{
    ll d, m; scanf("%lld%lld",&d, &m); dp[0][0] = 1;
    for(int x=1; x<d; x++)
        for(int h=1; h<=x; h++)
            dp[x][h] = (dp[x-1][h-1] + dp[x-1][h+1])%m;
    dp[d][0] = dp[d-1][1];
    printf("%lld\n",dp[d][0]);
}