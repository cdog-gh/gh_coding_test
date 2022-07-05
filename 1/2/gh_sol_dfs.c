/*
시간 복잡도 : O(4^T)
*/
#include <stdio.h>
char ma[100][101];
char vis[100][101];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int r,c,t,mmx = 0;
void dfs(int cx,int cy,int ans,int depth)
{
    /*
    기존에 (cx, cy)에 방문하지 않으면서, 현재 위치에 고구마가 있으면 고구마를 하나 먹은 것이다.
    */
    int cur_ans = ans + (ma[cx][cy] == 'S' && vis[cx][cy] == 0);
    if(depth == t)
    {
        if(mmx < cur_ans)
            mmx = cur_ans;
        return;
    }
    //(cx, cy)의 방문 횟수만 하나 증가시킨다.
    vis[cx][cy]++;
    for(int i=0;i<4;i++)
    {
        int tx = cx + dx[i];
        int ty = cy + dy[i];
        if(tx < 0 || ty < 0 || tx >= r || ty >= c)
            continue;
        if(ma[tx][ty] == '#')
            continue;
        dfs(tx,ty,cur_ans,depth+1);
    }
    //원복할 때에는 당연히 (cx, cy)의 방문 횟수를 하나 감소시키면 된다.
    vis[cx][cy]--;
}
int main(void)
{
    scanf("%d%d%d\n",&r,&c,&t);
    for(int i=0;i<r;i++)
        scanf("%s\n",ma[i]);
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(ma[i][j] != 'G')
                continue;
            dfs(i,j,0,0);
        }
    }
    printf("%d\n",mmx);
}