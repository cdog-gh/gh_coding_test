#include <stdio.h>
#include <string.h>
char s1[50];
char s2[50];
int main(void)
{
    scanf("%s\n%s", s1, s2);
    printf("%d\n", strcmp(s1, s2) == 0?0:1550);
}