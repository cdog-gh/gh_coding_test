#include <stdio.h>
int main(void)
{
    int a, b; scanf("%d%d", &a, &b);
    a = a * 100; // 200 ~> 20000
    int mi = (a/100)*b;
    
    if(a - mi >= 10000)
        printf("0");
    else
        printf("1");
}