/*
먼저 update에 등장하는 전체 키워드 수가 9개임에 착안해야 함. 2^9니까 비트를 써야겠다.
문제는 아무렇게나 구현하기에는 메모리 제한이 걸린다는 것임.
즉 어떤 키워드가 들어간 상태에 역들을 저장해 두고 bit and 연산으로 순회해야 함.
*/
#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
using namespace std;
unordered_map <string, string> con[512];
unordered_map <string, int> key;
unordered_map <string, int> last;
char str[103];
char keywords[5000001];
int add_key(char *kw)
{
    if(key.find(string(kw)) == key.end())
        key[string(kw)] = (int)key.size();
    return key[string(kw)];
}
int get_key(char *kw)
{
    if(key.find(string(kw)) == key.end())
        return -1;
    return key[string(kw)];
}
void work1(char *st, char *kw)
{
    char *cur = strtok(kw, ",");
    int res = 0;
    while(cur != NULL)
    {
        //printf("cur : %s\n",cur);
        int lo = add_key(cur);
        res |= (1<<lo);
        cur = strtok(NULL, ",");
    }
    //res = ...011 =>> 3
    //res = ...101 =>> 5
    int lo = last[string(st)];
    con[lo].erase(string(st));
    con[res][string(st)] = string("");
    last[string(st)] = res;
}
int work2(char *kw)
{
    char *cur = strtok(kw, ",");
    int res = 0;
    while(cur != NULL)
    {
        //yeah
        int lo = get_key(cur);
        if(lo == -1)
            return -1;
        res |= (1<<lo);
        cur = strtok(NULL, ",");
    }
    int ans = 0;
    for(int i=0; i<512; i++)
        if((i & res) == res)
            ans = ans + (int)con[i].size();
    return ans;
}
int main(void)
{
    int n; scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("\n%s", str);
        con[0][string(str)] = string("");
        last[string(str)] = 0;
    }
    int m; scanf("\n%d", &m);
    for(int i=0; i<m; i++)
    {
        char ch;
        //scanf("\n%c %s %s", &ch, str, keywords);
        scanf("\n%c ", &ch);
        if(ch == 'U'){
            scanf("%s %s", str, keywords);
            work1(str, keywords);
        }
        else{
            scanf("%s", keywords);
            int lo = work2(keywords);
            if(lo == -1)
                printf("0\n");
            else
                printf("%d\n", lo);
        }
    }
}