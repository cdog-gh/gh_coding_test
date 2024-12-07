#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int F[2020];
int ans[2020];
vector <int> v;
int main(void)
{
    int n, c, k; scanf("%d%d%d", &n, &c, &k);
    for(int i=1; i<=k; i++)
    {
        int a; scanf("%d", &a); F[a] = 1;
    }
    for(int i=1; i<=n; i++)
    {
        if(F[i] == 0) continue;
        v.push_back(i);
    }
    for(int i=1; i<=n; i++) ans[i] = i;
    if(k == 0)
    {
        ans[1] = n + 1;
    }
    else
    {
        int prev = 1;
        for(int i=0; i<(int)v.size(); i++)
        {
            int te = v[i];
            // printf("%d <-> %d\n", prev, te);
            swap(ans[prev], ans[te]);
            prev = te + 1;
        }
    }
    // 후 처리
    if(k != 0)
    {
        int b = v.back();
        if(b != n) ans[b+1] = 999999;
    }
    for(int i=1; i<c; i++)
    {
        for(int j=1; j<=n; j++)
            printf("%d ", j);
        printf("\n");
    }
    for(int i=1; i<=n; i++)
        printf("%d ", ans[i]);
}