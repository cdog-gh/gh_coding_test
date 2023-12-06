#include <stdio.h>
#include <deque>
#define INF 0x3f3f3f3f3f3f3f3fLL
typedef long long ll;
using namespace std;
struct moo
{
    ll lo, v;
};
typedef struct moo moo;
ll arr[3001][3001];
ll nj[3001][3001];
/// 관리할 자료 구조
ll base = 0;
// queue <ll> Q;
deque <moo> dq;
///
ll calc(ll, ll, ll, ll);
ll rev_dig(ll, ll, ll, ll);
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
        
        //이제 역 디귿자를 채울 건데.
        //먼저 어떤 것이 들어가는가?
        //( .., W) 에서 ( .., W-w1) 이 들어갈 거임.
        base = - (arr[1][W-w1] + arr[h][W-w1]);
        // while(!Q.empty()) Q.pop();
        while(!dq.empty()) dq.pop_back();
        //현재 (1, W-w1) 지점에서, (h, w) 까지 역 디귿자 형태를 구할 거임.
        
        for(ll w=W-w1; w>=1; w--)
        {
            // printf("w = %lld\n", w);
            base += (arr[1][w] + arr[h][w]); 
            ll a = rev_dig(1, w, h, w+w1);
        
            //역 ㄷ자를 자료구조에 넣는다.
            //a - base 넣기.
            moo item; item.lo = w + w1; item.v = a - base;
            
            ////add
            while(!dq.empty())
            {
                moo te = dq.back();
                if(te.v < item.v) break;
                dq.pop_back();
            }
            dq.push_back(item);
            ////
            
            //// calc
            while(!dq.empty())
            { 
                // printf("lo = %lld cur_s = %lld\n", dq.front().lo, cur_s);
                if(dq.front().lo <= w + w2) break;
                dq.pop_front();
            }
            if(dq.empty())
                continue;
            ll mini_dig = dq.front().v;
            mini_dig += base;
            
            // 나머지 1자 빼면 됨.
            ll one = calc(1, w, h, w) - arr[1][w] - arr[h][w];
            
            // one + mini_dig
            // printf("%lld %lld\n", one, mini_dig);
            if(one + mini_dig < ans)
            {
                ans = one + mini_dig;
                // printf("h = %lld w = %lld and = %lld\n", h, w, ans);
            }
        }
    }
    if(ans == INF)
    {
        printf("No"); return 0;
    }
    printf("%lld\n", ans);
    return 0;
}
ll calc(ll x1, ll y1, ll x2, ll y2)
{
    // printf("%lld %lld ~ %lld %lld\n", x1, y1, x2, y2);
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
