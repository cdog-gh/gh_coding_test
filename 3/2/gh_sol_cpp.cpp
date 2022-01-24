#include <stdio.h>
#include <algorithm>
using namespace std;
int ans[101010];
void print(int n)
{
    for(int i=1; i<=n; i++)
        printf("%d ", ans[i]);
    printf("\n");
}
int main(void)
{
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    fill(ans + 1, ans + n + 1, 1); //높이 1로 초기화
    if(a + b > n + 1)
    {
        printf("-1\n"); return 0;
    }
    if(a == 1 && b == 1)
    {
        print(n); return 0;
    }
    //코너 케이스이므로 조심!
    if(a == 1)
    {
        //b > 1임.
        //먼저 ans[1] = b
        ans[1] = b;
        for(int i=1; i<b; i++)
            ans[n + 1 - i] = i;
        print(n);
        return 0;
    }
    if(b == 1)
    {
        int pos = n + 1 - a;
        for(int i=1; i<=a; i++)
            ans[pos++] = i;
        print(n);
        return 0;
    }
    if(a <= b)
    {
        int pos = n;
        for(int i=1; i<=b; i++)
            ans[pos--] = i;
        pos = n+2 - a - b;
        for(int i=1; i<a; i++)
            ans[pos++] = i;
        print(n);
        return 0;
    }
    else
    {
        int pos = n+2 - a - b;
        for(int i=1; i<=a; i++)
            ans[pos++] = i;
        pos = n;
        for(int i=1; i<b; i++)
            ans[pos--] = i;
        print(n);
        return 0;
    }
    return 0;
}