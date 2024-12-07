#include <stdio.h>
int main(void)
{
    int s, a, f, b; scanf("%d%d%d%d", &s, &a, &f, &b);
    if(s <= a + f + b || s <= 240) printf("high speed rail\n");
    else printf("flight\n");
    return 0;
}