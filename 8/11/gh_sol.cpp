#include <stdio.h>
#include <vector>
using namespace std;
int dp[201][60001];
int cc[201];
vector <int> zz;
vector <int> oo;
void pp(vector <int> tar)
{
    for(int i=0; i<(int)tar.size(); i++)
    {
        if(i == (int)tar.size() - 1)
            printf("%d\n", tar[i]);
        else
            printf("%d ", tar[i]);
    }
};
int main(void)
{
    int n, tot=0; scanf("%d", &n); dp[0][0] = 1;
    for(int i=1; i<=n; i++)
        scanf("%d", cc+i);
    if(n == 1)
    {
        printf("-1\n"); return 0;
    }
    for(int i=1; i<=n; i++) tot += cc[i];
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<=60000; j++) dp[i][j] = dp[i-1][j];
        for(int j=cc[i]; j<=60000; j++)
        {
            if(dp[i-1][j-cc[i]] == 0) continue;
            dp[i][j] = dp[i-1][j-cc[i]];
        }
    }
    int lo = -1;
    for(int i=1; i <= tot/2; i++)
    {
        if(dp[n][i]) lo = i;
    }
    int cur = lo;
    for(int i=n; i>=1; i--)
    {
        int a = cur - cc[i];
        if(a < 0 || dp[i-1][a] == 0) zz.push_back(i);
        else {oo.push_back(i); cur = a;}
    }
    printf("%d\n", (int)zz.size());
    pp(zz);
    printf("%d\n", (int)oo.size());
    pp(oo);
}