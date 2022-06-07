#include <stdio.h>
#include <memory.h>
#include <string>
#include <map>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
char str[10];
char str2[10];
int stk[200002];
int co[200002];
map <string, int> mm;
vector <int> con[200002];
vector <int> ans[200002];
vector <int> hwan;
int get_s(char *str)
{
    if(mm.find(string(str)) == mm.end())
        mm[string(str)] = (int)mm.size() + 1;
    return mm[string(str)];
}
//data structure
int dp[200002];
int visit[200002];
queue <int> Q;
void bfs(int x)
{
    memset(dp, 0x3f, sizeof(int)*200002);
    memset(visit, 0, sizeof(int)*200002);
    dp[x] = 0; visit[x] = 1; Q.push(x); 
    while(!Q.empty())
    {
        int cur = Q.front(); Q.pop();
        for(int i=0; i<(int)con[cur].size(); i++)
        {
            int ne = con[cur][i];
            if(visit[ne])
                continue;
            dp[ne] = dp[cur] + 2;
            visit[ne] = 1;
            Q.push(ne);
        }
    }
    for(int i=0; i<200002; i++)
        ans[x].push_back(dp[i]);
}
struct moo
{
    int nosun, snum;
};
typedef struct moo moo;
moo dd[202020];
int abs(int x)
{
    if(x < 0) return -x;
    return x;
}
//data structure end
int main(void)
{
    int n, Q; scanf("%d %d", &n, &Q);
    for(int i=0; i<n; i++)
    {
        int a; scanf("%d", &a);
        for(int j=0; j<a; j++)
        {
            scanf(" %s", str);
            stk[j] = get_s(str);
        }
        for(int j=0; j<a; j++)
        {
            co[stk[j]]++;
            dd[stk[j]].nosun = i;
            dd[stk[j]].snum = j;
            if(j > 0)
            {
                con[stk[j]].push_back(stk[j-1]);
                con[stk[j-1]].push_back(stk[j]);
            }
        }
    }
    for(int i=1; i<=200000; i++)
    {
        if(co[i] <= 1)
            continue;
        hwan.push_back(i);
        bfs(i);
    }
    for(int i=0; i<Q; i++)
    {
        scanf(" %s %s", str, str2);
        int s = get_s(str);
        int e = get_s(str2);
        int mmn = inf;
        for(int k=0; k<(int)hwan.size(); k++)
        {
            int LO = hwan[k];
            int r = ans[LO][s] + ans[LO][e];
            if(r < mmn) mmn = r;
        }
        //same nosun
        if(dd[s].nosun == dd[e].nosun)
        {
            int r = 2 * abs(dd[s].snum - dd[e].snum);
            if(r < mmn) mmn = r;
        }
        if(mmn == inf) printf("-1\n");
        else printf("%d\n", mmn);
        //printf("str = %s str2 = %s\n", str, str2);
    }
    return 0;
}