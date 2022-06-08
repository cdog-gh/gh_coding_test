/*
1 3 3
1 2 3
2 1 5
3 3 3

16
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct moo
{
    int x, y;
};
typedef struct moo moo;
struct moo2
{
    int lo, v;
};
typedef struct moo2 moo2;
vector <moo> v;
vector <moo2> v2;
int arr[200][200];
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int f[200*200];
int is_injup(int lo1, int lo2)
{
    int x1 = v[lo1].x;
    int y1 = v[lo1].y;
    int x2 = v[lo2].x;
    int y2 = v[lo2].y;
    
    for(int i=0; i<8; i++)
    {
        if(x1 + dx[i] == x2 && y1 + dy[i] == y2)
            return 1;
    }
    return 0;
}
int calc(int lo1)
{
    int x1 = v[lo1].x;
    int y1 = v[lo1].y;
    
    return arr[x1][y1];
}
bool cmp(moo2 I, moo2 C)
{
    return I.v > C.v;
}
int nj_t[205];
int rr[205];
int main(void)
{
    int r, c, n; scanf("%d%d%d", &r, &c, &n);
    int a1, a2, a3; scanf("%d%d%d", &a1, &a2, &a3);
    int p12, p23, p13; scanf("%d%d%d", &p12, &p23, &p13);
    int mmx = 0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            moo I; I.x = i; I.y = j;
            scanf("%d", &(arr[i][j]));
            v.push_back(I);
        }
    }
    for(int i=0; i<(int)v.size(); i++)
    {
        moo2 I; I.lo = i; I.v = arr[v[i].x][v[i].y]; v2.push_back(I); 
    }
    sort(v2.begin(), v2.end(), cmp);
    int n3 = 0;
    for(int i=0; i<(int)v2.size(); i++)
    {
        f[v2[i].lo] = 1; n3 = n3 + v2[i].v;
        nj_t[i] = n3;
        rr[v2[i].lo] = i;
    }
    for(int i=0; i<(int)v.size(); i++)
    {
        for(int j=0; j<(int)v.size(); j++)
        {
            for(int k=0; k<(int)v.size(); k++)
            {
                
                int ret = 0;
                int n3_t = n3;
                if(i == j || j == k || i == k)
                    continue;
                if(is_injup(i, j)) ret += p12;
                if(is_injup(j, k)) ret += p23;
                if(is_injup(i, k)) ret += p13;
                
                ret = ret + calc(i);
                ret = ret + calc(j);
                ret = ret + calc(k);
                
                /*
                i, j, k를 뽑았다. 나머지 top n-3개를 뽑는다면 n-3, n-2, n-1, n 넷 중에 하나임.
                */
                int ve = 0;
                int tl = -1;
                for(int ti=n-4; ti<n; ti++)
                {
                    //0 ~ ti까지 누적합..
                    int nj = ((ti < 0)?0:nj_t[ti]);
                    
                    int an = (rr[i] <= ti) + (rr[j] <= ti) + (rr[k] <= ti);
                    //printf("ti = %d\n",ti);
                    //실제 있는 원소 수
                    int real = (ti+1) - an;
                    
                    if(real == n-3)
                    {
                        tl = ti;
                        ve = nj - (rr[i] <= ti)*calc(i) - (rr[j] <= ti)*calc(j) - (rr[k] <= ti)*calc(k);
                        break;
                    }
                }
                if(ret + ve > mmx) {
                    mmx = ret + ve;
                    //printf("[%d %d %d] : ret = %d ve = %d || %d\n", i, j, k, ret, ve, tl);
                }
                //getchar();
            }
        }
    }
    printf("%d\n",mmx);
}