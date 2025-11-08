#include <stdio.h>
int go(int g, int a, int b, int c)
{
    int cut = ((g == 1)? 100: 90);
    if(g >= 3) return 0;
    if(c < 50) return 0;
    if(3 * a < cut && 3 * b < cut) return 1;
    if(a < 19 + 3 || b < 19 + 3) return 1;
    return 0;
}
int main(void)
{
    int Q, g, a, b, c; scanf("%d", &Q);
    for(int i=1; i<=Q; i++)
    {
        scanf("%d%d%d%d", &g, &a, &b, &c);
        printf("%s\n", go(g, a, b, c)?"YES":"NO");
    }
}