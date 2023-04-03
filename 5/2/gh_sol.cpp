#include <stdio.h>
int t[86400 + 86400];
int main(void)
{
    int n, c, t1, t2, t3, ans=0; scanf("%d%d", &n, &c);
    for(int i=0; i<n+c; i++)
    {
        scanf("\n%d:%d:%d", &t1, &t2, &t3);
        int s = 3600*t1 + 60*t2 + t3;
        for(int j=s; j<s+40; j++)
            t[j] = 1;
    }
    for(int i=0; i<86400; i++)
        ans = ans + (1-t[i]);
    printf("%d\n", ans);
}
