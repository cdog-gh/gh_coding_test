#include <stdio.h>
#include <string.h>
char str[303030];
int main(void)
{
    scanf("%[^\n]", str);
    char *o = strchr(str, '(');
    if(o != NULL){
        char *c = strchr(str, ')');
        *c = *o = 0;
        printf("%s\n%s", str, o+1);
    }
    else
    {
        printf("%s\n-", str);
    }
}