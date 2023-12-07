#include <stdio.h>
int main(void)
{
    int n, a, b, tot = 1; scanf("%d%d", &n, &a);
    for(int i=1; i<n; i++)
    {
        scanf("%d", &b); tot += (b > a);
    }
    printf("%d\n", tot);
}
