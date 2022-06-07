#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int arr[6];
int flag[6];
char str1[30];
char str2[30];
int main(void)
{
    int hh, mm, curi; scanf("%s\n", str1); str1[2] = 0;
    hh = atoi(str1);
    mm = atoi(str1 + 3);
    curi = 60*hh + mm;
    for(int i=0; i<6; i++)
        scanf("%d", &(arr[i]));
    int L; scanf("\n%d", &L);
    for(int i=1; i<=L; i++)
    {
        scanf("\n%s %s", str1, str2);
        if(strcmp(str2, "^") == 0)
        {
            int yy = curi / 120;
            flag[yy] = 1;
        }
        else if(strcmp(str2, "10MIN") == 0)
        {
            curi = curi + 10;
        }
        else if(strcmp(str2, "30MIN") == 0)
        {
            curi = curi + 30;
        }
        else if(strcmp(str2, "50MIN") == 0)
        {
            curi = curi + 50;
        }
        else if(strcmp(str2, "2HOUR") == 0)
        {
            curi = curi + 60*2;
        }
        else if(strcmp(str2, "4HOUR") == 0)
        {
            curi = curi + 60*4;
        }
        else if(strcmp(str2, "9HOUR") == 0)
        {
            curi = curi + 60*9;
        }
        curi = curi % (12 * 60);
    }
    int ans = 0;
    for(int i=0; i<6; i++)
    {
        if(flag[i])
            continue;
        ans = ans + arr[i];
    }
    if(ans > 100) ans = 100;
    printf("%d\n",ans);
    return 0;
}