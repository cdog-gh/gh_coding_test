#include <stdio.h>
int main(void)
{
    int p, r; scanf("%d%d", &p, &r);
    int v = (100 * p) / r;
    if(v < 20)
        printf("weak");
    else if(v < 40)
        printf("normal");
    else if(v < 60)
        printf("strong");
    else
        printf("very strong");
}
