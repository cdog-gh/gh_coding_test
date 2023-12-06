#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll ans[1000001];
char temp[50];
char p_ans[45000000];
int main(void)
{
    ll n, s; scanf("%lld%lld", &n, &s);
    ll filled = ((1LL<<31) - 1) - s;
    ll M = (1LL << 31);
    if(n % 4 == 0)
    {
        for(ll i=0; i<n; i++)
            ans[i] = (i+4)*M;
        ans[0] += s;
    }
    else
    {
        ll mok = n / 4;
        ll namo = n % 4;
        for(ll i=0; i<mok*4; i++)
            ans[i] = (i+4)*M;
        // printf("%lld %lld\n", filled, s);
        ans[0] += filled;
        
        ll cur = (1LL<<31) - 1;
        ll cur_bit = 30;
        // printf("cur = %lld\n", cur);
        for(ll i=0; i<namo; i++)
        {
            //4 * mok + i
            if(i == namo - 1)
                ans[4 * mok + i] = cur;
            else
            {
                cur -= (1LL << cur_bit);
                ans[4 * mok + i] = (1LL << cur_bit);
                cur_bit--;
            }
        }
    }
    // sort(ans, ans + n);
    sprintf(temp, "%lld\n", n);
    char *t_ans = p_ans;
    t_ans = stpcpy(t_ans, temp);
    for(int i=(n/4)*4-1; i>=0; i--)
    {
        sprintf(temp, "%lld\n", ans[i]);
        t_ans = stpcpy(t_ans, temp);
    }
    for(int i=(n/4)*4; i<n; i++)
    {
        sprintf(temp, "%lld\n", ans[i]);
        t_ans = stpcpy(t_ans, temp);
    }
    printf("%s", p_ans);
}