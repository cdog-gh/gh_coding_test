#include <stdio.h>
#include <memory.h>
#include <vector>
#define Mod 1000000007LL
using namespace std;
typedef long long ll;
struct moo
{
    ll x, y;
};
typedef struct moo moo;
vector <moo> block[4];
vector <ll> st;
ll mapi[6][2];
vector <ll> con[7][64];
ll dp4[2][64];
ll dp6[2][64];
ll pow2[1010101];
ll ans4[1010101];
ll ans6[1010101];
void work(ll s, ll r_len);
void go(ll ini, ll depth, ll r_len);
ll f();
ll chk(ll x, ll y, ll k, ll r_len);
void fill_v(ll x, ll y, ll k, ll v);
/*
0 : 이전 열과 연결
1 : 다음 열과 연결

따라서 이전 열과 연결 한다면 1 상태에 넣으면 안 됨.
그러면, 이전 열 입장에서는, 현 열이 다음 열이므로 그 부분 주의해서 구현.
*/
moo bb(ll x, ll y)
{
    moo I; I.x = x; I.y = y; return I;
};
void p()
{
    for(ll i=0; i<6; i++)
        printf("%lld%lld\n", mapi[i][0], mapi[i][1]);
    printf("----\n");
}
int main(void)
{
    dp4[0][0] = dp6[0][0] = 1LL;
    block[0].push_back(bb(0, 0));
    block[0].push_back(bb(0, -1));
    block[0].push_back(bb(1, 0));

    block[1].push_back(bb(0, 0));
    block[1].push_back(bb(1, -1));
    block[1].push_back(bb(1, 0));

    block[2].push_back(bb(0, 0));
    block[2].push_back(bb(-1, -1));
    block[2].push_back(bb(0, -1));

    block[3].push_back(bb(0, 0));
    block[3].push_back(bb(0, -1));
    block[3].push_back(bb(1, -1));
    for(ll s=0; s<16; s++) work(s, 4);
    for(ll s=0; s<64; s++) work(s, 6);
    //2
    pow2[0] = 1LL;
    for(ll i=1; i<1010101; i++)
        pow2[i] = (pow2[i-1] * 2) % Mod;
    //4
    for(ll i=1; i<=1000000; i++)
    {
        for(ll s=0; s<16; s++)
        {
            ll ret = 0;
            for(ll j=0; j<(ll)con[4][s].size(); j++) ret += dp4[(i-1) & 1][con[4][s][j]];
            dp4[i & 1][s] = ret % Mod;
        }
        ans4[i] = dp4[i & 1][0];
    }
    //6
    for(ll i=1; i<=1000000; i++)
    {
        for(ll s=0; s<64; s++)
        {
            ll ret = 0;
            for(ll j=0; j<(ll)con[6][s].size(); j++) ret += dp6[(i-1) & 1][con[6][s][j]];
            dp6[i & 1][s] = ret % Mod;
        }
        ans6[i] = dp6[i & 1][0];
    }
    ll Q, r, c; scanf("%lld", &Q);
    for(ll i=1; i<=Q; i++)
    {
        scanf("%lld%lld", &r, &c);
        if(r == 2) printf("%lld\n", (c%3 != 0)?0LL:pow2[c/3LL]);
        else if(r == 4) printf("%lld\n", ans4[c]);
        else printf("%lld\n", ans6[c]);
    }
    return 0;
}
void work(ll s, ll r_len)
{
    for(ll r=0; r<6; r++) for(ll c=0; c<2; c++) mapi[r][c] = 1;
    for(ll r=0; r<r_len; r++) for(ll c=0; c<2; c++) mapi[r][c] = 0;
    for(ll i=0; i<r_len; i++)
    {
        if(s & (1<<i)) mapi[i][1] = 1; else mapi[i][1] = 0;
    }
    go(s, 0, r_len);
}
ll f()
{
    for(ll i=0; i<6; i++)
    {
        if(mapi[i][1] == 0) return i;
    }
    return -1;
}
// 모든 경우의 수를 다 돌려봐야 하므로 backtracking이 적합함.
void go(ll ini, ll depth, ll r_len)
{
    ll lo = f();
    if(lo == -1)
    {
        ll s = 0;
        for(ll i=0; i<r_len; i++)
        {
            if(mapi[i][0]) s += (1 << i);
        }
        con[r_len][ini].push_back(s);
        // printf("%lld %lld --> %lld\n", r_len, ini, s);
        return;
    }
    for(ll i=0; i<4; i++)
    {
        if(chk(lo, 1LL, i, r_len) == 0) continue;
        fill_v(lo, 1LL, i, 1LL); st.push_back(i);
        go(ini, depth + 1LL, r_len);
        fill_v(lo, 1LL, i, 0LL); st.pop_back();
    }
}
ll chk(ll x, ll y, ll k, ll r_len)
{
    for(ll i=0; i<(ll)block[k].size(); i++)
    {
        ll tx = block[k][i].x;
        ll ty = block[k][i].y;
        ll xx = x + tx; ll yy = y + ty;
        if(xx < 0 || yy < 0 || xx >= r_len || yy >= 2) return 0;
        if(mapi[xx][yy]) return 0;
    }
    return 1;
}
void fill_v(ll x, ll y, ll k, ll v)
{
    for(ll i=0; i<(ll)block[k].size(); i++)
    {
        ll tx = block[k][i].x;
        ll ty = block[k][i].y;
        mapi[x + tx][y + ty] = v;
    }
}