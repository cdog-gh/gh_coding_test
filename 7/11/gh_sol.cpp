#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int f[505050];
int in[505050];
int visit[505050]; // component 번호.
int visit2[505050];
vector <int> con[505050];
queue <int> Q;
struct moo
{
    int cc; // 사이클 요소 수.
    int jj; // 줄기
};
typedef struct moo moo;
moo arr[505050];
int nj[2020202];
int ans[2020202];
void bfs(int x, int n);
void go();
int main(void)
{
    int n, q; scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%d", f+i); in[f[i]]++;
        con[i].push_back(f[i]); con[f[i]].push_back(i);
    }
    // component 번호 매기기
    int c_num = 0;
    for(int i=1; i<=n; i++)
    {
        if(visit[i])
            continue;
        c_num++; bfs(i, c_num);
    }
    // 각 정점이 cycle 내에 속해있는지 관찰.
    // 위상 정렬
    for(int i=1; i<=n; i++)
    {
        if(in[i])
            continue;
        Q.push(i); in[i]--; visit2[i] = 1;
    }
    go();
    for(int i=1; i<=n; i++)
    {
        int cmp_no = visit[i];
        // printf("%d : %d\n", i, cmp_no);
        if(visit2[i] == 0)
            arr[cmp_no].cc++;
        else
        {
            int ne = f[i];
            if(visit2[ne] == 0)
                arr[cmp_no].jj++;
        }
    }
    ans[0] = n;
    for(int i=1; i<=c_num; i++)
    {
        int cycle = arr[i].cc;
        int julgi = arr[i].jj;
        // printf("%d == %d\n", cycle, julgi);
        nj[cycle] += cycle + julgi;
    }
    for(int i=1; i<2020202; i++)
        for(int j=i; j<2020202; j+=i)
            ans[j] += nj[i];
    // a : 1번 변환과 a번 변환이 같다. (a <= 2,000,000)
    scanf("%d", &q);
    for(int i=1; i<=q; i++)
    {
        int a; scanf("%d", &a); a--;
        printf("%d\n", ans[a]);
    }
    return 0;
}
void bfs(int s, int n)
{
    visit[s] = n; Q.push(s);
    while(!Q.empty())
    {
        int cur = Q.front(); Q.pop();
        for(int i=0; i<(int)con[cur].size(); i++)
        {
            int ne = con[cur][i];
            if(visit[ne])
                continue;
            visit[ne] = n; Q.push(ne);
        }
    }
}
void go()
{
    while(!Q.empty())
    {
        int cur = Q.front(); Q.pop();
        int ne = f[cur];
        in[ne]--;
        if(in[ne] == 0)
        {
            in[ne] = -1; visit2[ne] = 1; Q.push(ne);
        }
    }
}