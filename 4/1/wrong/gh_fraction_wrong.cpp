#include <stdio.h>
int main(void)
{
    double a, b; scanf("%lf%lf", &a, &b);
    double mi = a * (1-b/100);
    
    if(mi >= 100)
        printf("0");
    else
        printf("1");
}