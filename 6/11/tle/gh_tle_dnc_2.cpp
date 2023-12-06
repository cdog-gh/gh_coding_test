// 5500ms
#include <stdio.h>
#include <algorithm>
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;
struct moo
{
    int lo; ll v;
};
typedef struct moo moo;
ll arr[3][3001];
//1줄만 필요하므로 [1]행에서 누적합, [0]행에서 누적합, [2]행에서 누적합등으로 관리.
ll nj_garo[4][3001];
//세로 역시 맨 밑에는 고정되어 있으므로, 1줄만 필요.
ll nj_saero[3001];
moo dq[3001];
ll dnc(ll, ll, ll, ll);
ll calc(ll, ll, ll, ll);
ll rev_dig(ll, ll);
ll dig(ll, ll);
ll process(ll, ll, ll, ll);
int main(void)
{
    ll H, W; scanf("%lld%lld", &H, &W);
    ll h1, h2, w1, w2; scanf("%lld%lld%lld%lld", &h1, &h2, &w1, &w2);
    
    ll ans = INF;
    //1번 위치 ~> h+1번 위치.
    for(ll h=1; h<=H; h++)
    {
        ll cur_h = min(2LL, h);
        for(ll j=1; j<=W; j++)
        {
            scanf("%lld", &(arr[cur_h][j]));
            nj_garo[cur_h][j] = nj_garo[cur_h][j-1] + arr[cur_h][j];
            nj_saero[j] += arr[cur_h][j];
        }
        for(ll j=1; j<=W; j++)
            nj_garo[3][j] = nj_garo[1][j] + nj_garo[2][j];
        // printf("h = %lld h1 = %lld\n", h, h1);
        if(h > H || h <= h1)
            continue;
        ll r = dnc(1, W, w1, w2);
        ans = min(ans, r);
    }
    if(ans == INF)
    {
        printf("No"); return 0;
    }
    printf("%lld\n", ans);
    return 0;
}
ll process(ll s, ll e, ll w1, ll w2)
{
    // deque <moo> dq;
    ll ret = INF;
    ll mid = (s + e)/2;
    //[s] ~ [mid] | [mid+1] ~ [e]
    //좌.
    //s에서 출발했을 때, w1 이상 w2 이하인 아이들 모두 넣기
    
    ll cur_s = s + w1;
    ll cur_e = s + w2;
    ll front = 0;
    ll back = 0;
    for(ll i=cur_s; i<=cur_e; i++)
    {
        if(i <= mid) continue;
        if(i > e) continue;
        //// add
        ll r = rev_dig(mid+1, i);
        while(front < back){
            if(dq[back-1].v < r) break;
            back--;
        }
        dq[back].v = r;
        dq[back++].lo = i;
    }
    for(ll i=s; i<=mid; i++)
    {
        /// if(cur_e > e) break;
        ll left = dig(i, mid);
        /// calc min
        while(front < back){
            if(dq[front].lo >= cur_s) break;
            front++;
        }
        if(front < back)
        {
            ll right = dq[front].v;
            ret = min(ret, left + right);
        }
        //뒤에 아이 추가.
        cur_s++; cur_e++; 
        if(mid < cur_e && cur_e <= e) {
            /// printf("add %lld\n", cur_e);
            //// add
            ll r = rev_dig(mid+1, cur_e);
            while(front < back){
                if(dq[back-1].v < r) break;
                back--;
            }
            dq[back].lo = cur_e;
            dq[back++].v = r;
        }
    }
    return ret;
}
ll dnc(ll s, ll e, ll w1, ll w2)
{   
    if(e - s < w1)
        return INF;
    ll mid = (s + e)/2;
    ll a = dnc(s, mid, w1, w2);
    ll b = dnc(mid+1, e, w1, w2);
    // [s] ~ [mid] | [mid+1] ~ [e]
    ll c = process(s, e, w1, w2);
    return min(a, min(b, c));
}
ll rev_dig(ll y1, ll y2)
{
    return (nj_garo[3][y2-1] - nj_garo[3][y1-1]) 
        + nj_saero[y2];
}
ll dig(ll y1, ll y2)
{
    return (nj_garo[3][y2] - nj_garo[3][y1])
        + nj_saero[y1];
}