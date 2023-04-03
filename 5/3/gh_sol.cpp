#include <stdio.h>
#include <string.h>
char str[10];
int main(void)
{
    /*
    idea : 최솟 위치를 1번째 역으로 고정시켜 놓고
    최대값을 하나씩 늘려나간다.
    이런 류의 문제를 풀 때에는 극값을 생각해 보는 것도 좋은 습관 중 하나임.
    */
    int n, m; scanf("%d%d", &n, &m);
    printf("%d\n", 2*m+1);
    printf("U 1 -1\n");
    for(int i=1; i<=m; i++)
    {
        int a; scanf("%d", &a);
        printf("U %d %d\n", a+1, i+1);
        printf("P\n");
    }
}