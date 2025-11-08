#include <stdio.h>
typedef long long ll;
int main(void)
{
    ll Q; scanf("%lld", &Q);
    for(ll i=1; i<=Q; i++)
    {
        ll c, k; scanf("%lld%lld", &c, &k);
        printf("%lld %lld\n", c*k, c/k);
    }
    return 0;
}