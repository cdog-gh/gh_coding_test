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
    for(int i=0; i<n-3; i++)
    {
        f[v2[i].lo] = 1; n3 = n3 + v2[i].v;
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
                
                int ve = 0;
                if(f[i]){n3_t -= calc(i); ve++;}
                if(f[j]){n3_t -= calc(j); ve++;}
                if(f[k]){n3_t -= calc(k); ve++;}
                //n-3
                /*
                why this is wrong? wrong case sample
                i = n-2 th, j = n-1 th, k = n th
                if n is 5, i = 3, j = 4, k = 5 so
                9 7 6 <<5 4 3>> 2 .. :: <<5 4 3>> selected
                
                this logic calc
                9 + 7 + 6 + 5 + 4 + 3 right? but 5, 4, 3 is i, j, k!
                so, correct solution is, select 0 ~ x th, and calc 0 ~ xth & exclude i, j, k.
                */
                if(ve == 1)
                {
                    n3_t = n3_t + v2[n-3].v;
                }
                else if(ve == 2)
                {
                    n3_t = n3_t + v2[n-3].v + v2[n-2].v;
                }
                
                else if(ve == 3)
                {
                    n3_t = n3_t + v2[n-3].v + v2[n-2].v + v2[n-1].v;
                }
                
                ret = ret + n3_t;
                
                if(ret > mmx) mmx = ret;
            }
        }
    }
    printf("%d\n",mmx);
}