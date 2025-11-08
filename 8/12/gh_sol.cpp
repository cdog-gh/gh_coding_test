#include <stdio.h>
#include <memory.h>
#include <queue>
#include <vector>
#define M 2000001
using namespace std;
struct moo
{
    int s, e, len;
};
typedef struct moo moo;
struct comp_long
{
    bool operator()(moo &I, moo &C)
    {
        if(C.len != I.len)
            return C.len > I.len;
        return C.s < I.s;
    }
};
struct comp_short
{
    bool operator()(moo &I, moo &C)
    {
        if(C.len != I.len)
            return C.len < I.len;
        return C.s < I.s;
    }
};
//
int p_left[M]; // leftest.
int p_right[M]; // rightest.
int p_nn[M];
priority_queue <moo, vector <moo>, comp_long> pq_long;
priority_queue <moo, vector <moo>, comp_short> pq_short;
int tunnel_num;
char mapi[M + 1];
char mapi_nn[M + 1];
char str[M + 1];
int find_par(int *tar, int x)
{
    // printf("x = %d: tar[x] = %d\n", x, tar[x]);
    if(tar[x] == -1)
        return x;
    tar[x] = find_par(tar, tar[x]);
    return tar[x];
};
void upd(int);
void upd2(int);
void print();
void gc();
int find_zero(int x, int n);
int main(void)
{
    memset(p_left, -1, sizeof(int) * M);
    memset(p_right, -1, sizeof(int) * M);
    memset(p_nn, -1, sizeof(int) * M);
    memset(mapi_nn, '0', sizeof(char) * (M + 1));
    memset(mapi, '0', sizeof(char) * (M + 1));
    mapi[0] = mapi_nn[0] = '0';
    int n; scanf("%d\n%s\n", &n, str+1);
    for(int i=1; i<=n; i++)
    {
        if(str[i] != '1') {mapi[i] = str[i]; continue;}
        upd(i);
    }
    for(int i=1; mapi[i]; i++)
    {
        if(mapi[i] == '0') continue;
        upd2(i); mapi_nn[i] = '1';
    }
    int Q; scanf("%d", &Q);
    for(int i=1; i<=Q; i++)
    {
        int op, s, e; scanf("%d", &op);
        if(op == 1)
        {
            scanf("%d%d", &s, &e);
            for(int i=s; i<e; i=i+1)
            {
                i = find_zero(i, n); if(i == -1) break;
                if(i >= e) break;
                upd(i); upd2(i);
            }
        }
        else
        {
            gc(); print();
        }
    }
}
int find_zero(int x, int n)
{
    int cur = x;
    while(1)
    {
        if(mapi_nn[cur] == '0') return cur;
        cur = find_par(p_nn, cur);
        cur = cur + 1;
        if(cur > n) return -1;
    }
}
void print()
{
    if(tunnel_num == 0)
    {
        printf("-1\n"); return;
    }
    moo longest = pq_long.top();
    moo shortest = pq_short.top();
    printf("%d %d %d %d %d\n", tunnel_num, longest.s, longest.e + 1, shortest.s, shortest.e + 1);
}
void gc()
{
    while(!pq_short.empty())
    {
        moo item = pq_short.top();
        int s = item.s; int e = item.e;
        if(s == find_par(p_left, e) && e == find_par(p_right, s)) break;
        pq_short.pop();
    }
    while(!pq_long.empty())
    {
        moo item = pq_long.top();
        int s = item.s; int e = item.e;
        if(s == find_par(p_left, e) && e == find_par(p_right, s)) break;
        pq_long.pop();
    }
}
void upd(int x)
{
    moo item;
    // printf("x = %d\n", x);
    if(mapi[x-1] != '1' && mapi[x+1] != '1')
    {
        // okay. [x to x add]
        item.s = x; item.e = x; item.len = 1; pq_long.push(item); pq_short.push(item);
        tunnel_num++;
    }
    else if(mapi[x-1] == '1' && mapi[x+1] != '1')
    {
        // left <--> [x]
        int left_par = find_par(p_left, x-1);
        p_left[x] = left_par;
        int right_par = find_par(p_right, x-1);
        p_right[right_par] = x;
        item.s = left_par; item.e = x; item.len = (x + 1) - left_par; pq_long.push(item); pq_short.push(item);
    }
    else if(mapi[x-1] != '1' && mapi[x+1] == '1')
    {
        // [x] <--> right
        int left_par = find_par(p_left, x+1);
        p_left[left_par] = x;
        int right_par = find_par(p_right, x+1);
        p_right[x] = right_par;
        item.s = x; item.e = right_par; item.len = right_par + 1 - x; pq_long.push(item); pq_short.push(item);
    }
    else
    {
        // left <--> [x] <--> right
        int left_par = find_par(p_left, x-1);
        p_left[x] = p_left[x+1] = left_par;
        int right_par = find_par(p_right, x+1);
        p_right[x-1] = p_right[x] = right_par;
        item.s = left_par; item.e = right_par; item.len = right_par + 1 - left_par; pq_long.push(item); pq_short.push(item);
        tunnel_num--;
    }
    mapi[x] = '1';
}
void upd2(int x)
{
    if(mapi_nn[x-1] != '1' && mapi_nn[x+1] != '1')
        ;
    else if(mapi_nn[x-1] == '1' && mapi_nn[x+1] != '1')
    {
        // left <--> [x]
        int right_par = find_par(p_nn, x-1);
        // printf("p_nn[%d] = %d\n", right_par, x);
        p_nn[right_par] = x;
    }
    else if(mapi_nn[x-1] != '1' && mapi_nn[x+1] == '1')
    {
        // [x] <--> right
        int right_par = find_par(p_nn, x+1);
        p_nn[x] = right_par;
    }
    else
    {
        int right_par = find_par(p_right, x+1);
        p_nn[x-1] = p_nn[x] = right_par;
    }
    mapi_nn[x] = '1';
}