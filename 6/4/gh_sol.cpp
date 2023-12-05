#include <stdio.h>
#include <string.h>
char str[10];
int main(void){
    int lv, sc = 0; scanf("%d %s", &lv, str);
    if(strcmp("miss", str) == 0)
        sc = 0;
    if(strcmp("bad", str) == 0)
        sc = 200;
    if(strcmp("cool", str) == 0)
        sc = 400;
    if(strcmp("great", str) == 0)
        sc = 600;
    if(strcmp("perfect", str) == 0)
        sc = 1000;
    printf("%d\n", sc * lv);
    return 0;
}
