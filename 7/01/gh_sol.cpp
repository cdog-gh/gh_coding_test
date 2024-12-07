#include <stdio.h>
int main(void)
{
    int s, f; scanf("%d%d", &s, &f);
    if(s <= f) printf("high speed rail\n");
    else printf("flight\n");
    return 0;
}