#include <stdio.h>
char ma[100][101];
char vis[100][101];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int r,c,t,mmx = 0;
void dfs(int cx,int cy,int ans,int depth)
{
    int cur_ans = ans + (ma[cx][cy] == 'S' && vis[cx][cy] == 0);
    if(depth == t)
    {
        if(mmx < cur_ans)
            mmx = cur_ans;
        return;
    }
	/*
	이동할 수 있는 거리는 t-depth이고, 이 때 마다 고구마를 먹는다면 
	고구마는 cur_ans + (t-depth)만큼 먹을 수 있다.
	
	그런데 이 값이 답보다 작거나 같다면 추가로 탐색할 필요가 없다.
	*/
    if(cur_ans + (t-depth) <= mmx)
        return;
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