#include <stdio.h>
#include <memory.h>
#include <unordered_map>
#define INF 0x3f3f3f3f
using namespace std;
struct Query
{
    int f, t;
};
typedef struct Query Query;
unordered_map <int, int> con[200001];
int co[202020];
Query q[404040];
int ans[202020];
void add(int from, int to, int c)
{
    int r = INF;
    if(con[from].find(to) != con[from].end())
        r = con[from][to];
    if(c < r)
        con[from][to] = c;
};
int get(int from, int to)
{
    if(con[from].find(to) == con[from].end()) return -1;
    return con[from][to];
};
int main(void)
{
    int n, m, Q; scanf("%d%d%d", &n, &m, &Q); memset(ans, 0x3f, sizeof(int)*202020);
    for(int i=1; i<=m; i++)
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c); add(a, b, c); add(b, a, c);
    }
    for(int i=1; i<=Q; i++)
    {
        scanf("%d%d", &(q[i].f), &(q[i].t));
        printf("%d\n", get(q[i].f, q[i].t));
    }
}