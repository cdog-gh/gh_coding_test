#include <stdio.h>
int arr[5];
int main(void)
{
    int ans = 0;
    for(int i=0; i<5; i++) scanf("%d", arr+i);
    for(int i=1; i<5; i++) ans += (arr[0] - arr[i] <= 1000);
    printf("%d\n", ans);
    return 0;
}
