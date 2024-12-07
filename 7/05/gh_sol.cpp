#include <stdio.h>
typedef long long ll;
int main(void){
    ll Q, a, b; scanf("%lld", &Q);
    for(int i=1; i<=Q; i++){
        scanf("%lld%lld", &a, &b);
        // 소비전력이 aW, b분 사용.
        // 요율 : 105.6 / Kwh
        
        // 60,000 = 1 unit.
        ll ans = (1056 * (a * b)) / 600000;
        printf("%lld\n", ans);
    }
    return 0;
}