/*
This solution may be Time Limit Exceed (TLE)
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
struct moo
{
    int a,b,c;
};
//id, time, prio
typedef struct moo moo;
moo p[100000];
int f(int n)
{
    int prio_mmx = -1 * 0x3f3f3f3f;
    int lo = -1;
    for(int i=0;i<n;i++)
    {
        if(p[i].b <= 0)
            continue;
        if(p[i].c > prio_mmx)
        {
            lo = i;
            prio_mmx = p[i].c;
        }
    }
    p[lo].b -= 1;
    p[lo].c -= 1;
    return p[lo].a;
}
bool cmp(moo a,moo b)
{
    return a.a < b.a;
}
int main(int argc, char **argv)
{
    int T, n; scanf("%d %d\n",&T, &n);
    for(int i=0; i<n;i++)
    {
        scanf("%d %d %d\n",&(p[i].a), &(p[i].b), &(p[i].c));
    }
    sort(p, p+n, cmp);
    for(int i=0; i<T; i++)
        printf("%d\n",f(n));
}