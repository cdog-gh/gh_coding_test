#include <stdio.h>
#include <queue>
#include <set>
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;
ll arr[3001][3001];
ll nj[3001][3001];
/// 관리할 자료 구조
ll base = 0;
queue <ll> Q;
multiset <ll> ss;
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
        while(!Q.empty()) Q.pop();
        ss.clear();
        //현재 (1, W-w1) 지점에서, (h, w) 까지 역 디귿자 형태를 구할 거임.
        
        for(ll w=W-w1; w>=1; w--)
        {
            // printf("w = %lld\n", w);
            base += (arr[1][w] + arr[h][w]); 
            ll a = rev_dig(1, w, h, w+w1);
        
            //역 ㄷ자를 자료구조에 넣는다.
            //a - base 넣기.
            Q.push(a - base);
            ss.insert(a - base);
            // printf("rev_dig %lld %lld %lld %lld :: %lld\n", 1LL, w, h, W, a);
            // printf("in = %lld a = %lld base = %lld\n", a-base, a, base);
            
            // st_size 보다 큰 경우.
            while((ll)Q.size() > st_size)
            {
                ll it = Q.front(); Q.pop();
                ss.erase(ss.find(it));
            }
            
            //실제로 자료구조에서 max를 구할 때에는 base를 더하면 됨.
            ll mini_dig = *(ss.begin());
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
