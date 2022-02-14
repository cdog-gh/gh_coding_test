#include <stdio.h>
#include <string>
#include <set>
#include <deque>
#include <bitset>
using namespace std;
struct moo
{
    int id;
    string op;
    string resource;
};
typedef struct moo moo;
//set <string> ss;
//누군가 카드를 점유하고 있는지 카드 id별로 flag를 저장한다.
bitset <2000000002> ss;
deque <moo> dummy;
moo player[500002];
int turn[500002];
char str[20];
int main(void)
{
    int n, T, id; scanf("%d %d\n",&n, &T); ss.reset();
    for(int i=1;i<=T;i++)
        scanf("%lld",turn + i);
    for(int i=1;i<=n;i++)
        player[i].id = -1;
    for(int i=1;i<=T;i++)
    {
        moo I;
        scanf("\n%d %s",&id, str);
        string temp = string(str);
        I.id = id; I.op = temp;
        if(temp.compare("next") != 0)
        {
            scanf(" %s",str);
            I.resource = string(str);
        }
        dummy.push_back(I);
    }
    for(int i=1;i<=T;i++)
    {
        int pn = turn[i];
        
        if(player[pn].id == -1)
        {
            //deck에서 카드 하나 뽑는다.
            player[pn] = dummy.front(); dummy.pop_front();
        }
        printf("%d\n",player[pn].id);
        if(player[pn].op.compare("next") == 0)
        {
            player[pn].id = -1;
        }
        else if(player[pn].op.compare("acquire") == 0)
        {
            int rr = stoi(player[pn].resource);
            if(ss[rr] == 0)
            {
                ss[rr] = 1;
                player[pn].id = -1;
            }
        }
        else
        {
            //resource 제거
            int rr = stoi(player[pn].resource);
            ss[rr] = 0;
            player[pn].id = -1;
        }    
    }
    return 0;
}