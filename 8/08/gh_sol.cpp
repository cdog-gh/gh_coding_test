#include <stdio.h>
typedef long long ll;
ll pow2[62];
char A[2][1010101];
void f(ll r, ll c, ll x);
void f_14(ll r, ll c);
void f_23(ll r, ll c);
int main(void)
{
    ll Q, r, c, x; scanf("%lld", &Q);
    pow2[0] = 1LL;
    for(ll i=1; i<=60; i++)
        pow2[i] = (pow2[i-1] * 2);
    for(ll i=1; i<=Q; i++)
    {
        scanf("%lld%lld%lld", &r, &c, &x);
        f(r, c, x);
        // printf("---\n");
    }
}
void f(ll r, ll c, ll x)
{
    if(r == 1 || c % 3)
    {
        printf("-1\n"); return;
    }
    if(c < 61 * 3 && pow2[c/3LL] < x)
    {
        printf("-1\n"); return;
    }
    x--;
    for(ll i=0; i<r; i++)
        for(ll j=0; j<=c; j++)
            A[i][j] = 0;
    for(ll j=0; j<c; j=j+3)
        f_14(0, j);
    ll c_pos = (c / 3) * 3; c_pos -= 3;
    for(ll j=0; j<63; j++)
    {
        if(x & (1LL << j))
            f_23(0, c_pos);
        c_pos -= 3;
    }
    printf("%s\n%s\n", A[0], A[1]);
}
void f_14(ll r, ll c)
{
    A[r][c] = '1'; A[r][c+1] = '1'; A[r][c+2] = '4';
    A[r+1][c] = '1'; A[r+1][c+1] = '4'; A[r+1][c+2] = '4';
}
void f_23(ll r, ll c)
{
    A[r+0][c] = '3'; A[r+0][c+1] = '2'; A[r+0][c+2] = '2';
    A[r+1][c] = '3'; A[r+1][c+1] = '3'; A[r+1][c+2] = '2';
}