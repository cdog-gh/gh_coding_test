#include <stdio.h>
#include <string.h>
char str[10];
int main(void)
{
    int ans = 0, num;
    for(int i=0; i<4; i++)
    {
        scanf("\n%s %d", str, &num);
        if(strcmp(str, "Stair") == 0)
            ans = ans + 17 * num;
        else
            ans = ans + 21 * num;
    }
    printf("%d\n", ans);
}