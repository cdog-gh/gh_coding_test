// 6000ms
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
ll arr[3001][3001];
ll nj[3001][3001];
moo dq[3001];
ll dnc(ll, ll, ll, ll, ll);
ll calc(ll, ll, ll, ll);
ll rev_dig(ll, ll, ll, ll);
ll dig(ll, ll, ll, ll);
ll process(ll, ll, ll, ll, ll);
int main(void)
{
    ll H, W; scanf("%lld%lld", &H, &W);
    ll h1, h2, w1, w2; scanf("%lld%lld%lld%lld", &h1, &h2, &w1, &w2);
    ll st_size = (w2 - w1) + 1;
    for(ll i=1; i<=H; i++)
        for(ll j=1; j<=W; j++)
            scanf("%lld", &(arr[i][j]));
    for(ll i=1; i<=H; i++)
        for(ll j=1; j<=W; j++)
            nj[i][j] = nj[i-1][j] + nj[i][j-1] - nj[i-1][j-1] + arr[i][j];
    
    ll ans = INF;
    //1번 위치 ~> h+1번 위치.
    for(ll h=h1+1; h<=h2+1; h++)
    {
        //(1, ~) 부터 (h, ~)까지 자른다.
        if(h > H)
            continue;
        ll r = dnc(1, W, w1, w2, h);
        ans = min(ans, r);
    }
    if(ans == INF)
    {
        printf("No"); return 0;
    }
    printf("%lld\n", ans);
    return 0;
}
ll process(ll s, ll e, ll w1, ll w2, ll h)
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
        ll r = rev_dig(1, mid+1, h, i);
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
        ll left = dig(1, i, h, mid);
        
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
            ll r = rev_dig(1, mid+1, h, cur_e);
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
ll dnc(ll s, ll e, ll w1, ll w2, ll h)
{
    ll mid = (s + e)/2;
    if(e - s < w1)
        return INF;
    ll a = dnc(s, mid, w1, w2, h);
    ll b = dnc(mid+1, e, w1, w2, h);
    // [s] ~ [mid] | [mid+1] ~ [e]
    ll c = process(s, e, w1, w2, h);
    return min(a, min(b, c));
}
ll calc(ll x1, ll y1, ll x2, ll y2)
{
    return nj[x2][y2] - nj[x1-1][y2] - nj[x2][y1-1] + nj[x1-1][y1-1];
}
ll rev_dig(ll x1, ll y1, ll x2, ll y2)
{
    ll ret1 = calc(x1, y1, x1, y2);
    ll ret2 = calc(x2, y1, x2, y2);
    ll ret3 = calc(x1, y2, x2, y2);
    // printf("%lld %lld %lld\n", ret1, ret2, ret3);
    return ret1 + ret2 + ret3 - arr[x1][y2] - arr[x2][y2];
}
ll dig(ll x1, ll y1, ll x2, ll y2)
{
    ll ret1 = calc(x1, y1, x1, y2);
    ll ret2 = calc(x2, y1, x2, y2);
    ll ret3 = calc(x1, y1, x2, y1);
    // printf("%lld %lld %lld\n", ret1, ret2, ret3);
    return ret1 + ret2 + ret3 - arr[x1][y1] - arr[x2][y1];
}