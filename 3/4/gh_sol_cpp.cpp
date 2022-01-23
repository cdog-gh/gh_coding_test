/*
기본적인 출제 의도
bfs나 dfs를 배우면 component 개념을 배울 텐데
component 별로 묶은 다음에 경사로를 통해서 component간 연결이 될 수 있다는 걸 의도함.
*/
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct moo
{
    int x, y;
};
typedef struct moo moo;
struct gg
{
    int a, b;
    char ch;
};
typedef struct gg gg;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char str[1001][1001];
char visit[1001][1001];
int cp[1001][1001];
queue <moo> Q;
//.PB : 0
//1 : 1
//? : 2
//# : 3
int r, c;
int end_flag[1000001] = {0};
char cv[1000001] = {0};
vector <int> cv_vector;
moo qu[20];
vector <gg> bf[20];
vector <gg> gset;
vector <int> con[1000001];
queue <int> CQ;
int get_status(char);
int get_ls(int, int, int, int);
void bfs(int, int, int, int, int);
void work(int ,int ,int, int, int);
int work_bfs(int);
int main(void)
{
    int r, c, no = 1; scanf("%d%d\n", &r, &c);
    for(int i=0; i<r; i++)
        scanf("%s\n",str[i]);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(get_status(str[i][j]) == 3)
                continue;
            if(get_status(str[i][j]) == 2)
                continue;
            if(visit[i][j])
                continue;
            bfs(i, j, r, c, no++);
        }
    }
    
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            if(strchr("PB", str[i][j]) != NULL)
                end_flag[cp[i][j]] = 1;
    //cp[x][y] : x행 y열의 component 번호
    int x1, y1; scanf("%d%d", &x1, &y1); x1--; y1--;
    int start = cp[x1][y1];
    //end_flag[end_point]가 1인 지점이 있는지 고르자!
    
    int question_mark = 0;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            if(str[i][j] != '?')
                continue;
            work(i, j, r, c, question_mark);
            qu[question_mark].x = i;
            qu[question_mark].y = j;
            question_mark++;
        }
    }
    for(int i=0; i<question_mark; i++)
    {
        int sz = (int)bf[i].size();
        if(sz == 2)
            continue;
        if(sz == 1)
        {
            bf[i].push_back(bf[i][0]);
            continue;
        }
        gg item; item.a = 0; item.b = 0; item.ch = 'N';
        bf[i].push_back(item); bf[i].push_back(item);
    }
    
    //bf 초기화 후 bfs를 돌린다.
    for(int i=0; i<(1<<question_mark); i++)
    {
        //qset : 연결할 간선들
        gset.clear();
        for(int j=0; j<question_mark; j++)
        {
            if(i & (1<<j))
                gset.push_back(bf[j][1]);
            else
                gset.push_back(bf[j][0]);
        }
        
        if(work_bfs(start))
        {
            for(int j=0; j<(int)gset.size(); j++)
            {
                str[qu[j].x][qu[j].y] = gset[j].ch;
            }
            for(int j=0;j<r;j++)
                printf("%s\n",str[j]);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
int work_bfs(int start)
{
    //qset에 나온 대로 graph build!
    for(int i=0; i<(int)gset.size(); i++)
    {
        int a = gset[i].a; int b = gset[i].b;
        //char ch = gset[i].ch;
        //printf("%d <-> %d : %c\n",a, b, ch);
        con[a].push_back(b); con[b].push_back(a);
    }
    cv_vector.push_back(start); cv[start] = 1; CQ.push(start);
    while(!CQ.empty())
    {
        int item = CQ.front(); CQ.pop();
        if(end_flag[item])
            return 1;
        for(int i=0; i<(int)con[item].size(); i++)
        {
            int ne = con[item][i];
            if(cv[ne])
                continue;
            cv[ne] = 1; cv_vector.push_back(ne); CQ.push(ne);
        }
    }
    for(int i=0; i<(int)cv_vector.size(); i++)
        cv[cv_vector[i]] = 0;
    //graph clear!
    for(int i=0; i<(int)gset.size(); i++)
    {
        int a = gset[i].a; int b = gset[i].b;
        con[a].clear(); con[b].clear();
    }
    cv_vector.clear();
    return 0;
}
void work(int x, int y, int r, int c, int pos)
{
    gg item;
    if(get_ls(x-1, y, r, c) == 1 && get_ls(x+1, y, r, c) == 0){
        item.a = cp[x-1][y]; item.b = cp[x+1][y]; item.ch = 'N'; //N
        bf[pos].push_back(item);
    }
    if(get_ls(x, y-1, r, c) == 0 && get_ls(x, y+1, r, c) == 1){
        item.a = cp[x][y-1]; item.b = cp[x][y+1]; item.ch = 'E'; //E
        bf[pos].push_back(item);
    }
    if(get_ls(x-1, y, r, c) == 0 && get_ls(x+1, y, r, c) == 1){
        item.a = cp[x-1][y]; item.b = cp[x+1][y]; item.ch = 'S'; //S
        bf[pos].push_back(item);
    }
    if(get_ls(x, y-1, r, c) == 1 && get_ls(x, y+1, r, c) == 0){
        item.a = cp[x][y-1]; item.b = cp[x][y+1]; item.ch = 'W'; //W
        bf[pos].push_back(item);
    }
}
void bfs(int x, int y, int r, int c, int no)
{
    moo I, C;
    cp[x][y] = no; 
    visit[x][y] = 1; I.x = x; I.y = y; Q.push(I);
    while(!Q.empty())
    {
        C = Q.front(); Q.pop();
        for(int i=0; i<4; i++)
        {
            int tx = C.x + dx[i];
            int ty = C.y + dy[i];
            if(tx < 0 || ty < 0 || tx >= r || ty >= c)
                continue;
            if(get_status(str[x][y]) != get_status(str[tx][ty]))
                continue;
            if(visit[tx][ty])
                continue;
            cp[tx][ty] = no;
            visit[tx][ty] = 1; I.x = tx; I.y = ty; Q.push(I);
        }
    }
}
int get_ls(int x, int y, int r, int c)
{
    if(x < 0 || y < 0 || x >= r || y >= c)
        return 3;
    return get_status(str[x][y]);
}
int get_status(char ch)
{
    if(strchr(".PB", ch) != NULL)
        return 0;
    if(ch == '1')
        return 1;
    if(ch == '?')
        return 2;
    else
        return 3;
}