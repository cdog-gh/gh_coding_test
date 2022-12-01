#include <stdio.h>
#include <unordered_map>
#define INF 2000000000000000000LL
using namespace std;
typedef long long ll;
unordered_map <ll, ll> dp[200002];
char ans[808080];
ll get(ll x, ll y)
{
	if(x >= 200002)
		return 0;
	if(dp[x].find(y) == dp[x].end())
		return 0;
	return dp[x][y];
}
void build_dp(ll y)
{
	ll ban = y/2;
	//(x, 0) to (ban, ban)
	if(get(ban+1, ban+1) >= INF){
		dp[ban][ban] = INF;
		return;
	}
	for(ll x=0; x<=ban; x++, y--)
	{
		if(x == 0)
			continue;
		dp[x][y] = get(x-1, y+1) + get(x+1, y+1);
		dp[x][y] = min(INF, dp[x][y]);
	}
}
void track(ll d, ll k)
{
	ll cur_x = 0; 
	ll cur_y = 0;
	ll cur_gaji = k;
	//Operation number : d
	for(ll i=0; i<d; i++)
	{
		ll up_gaji = get(cur_x + 1, cur_y + 1);
		if(cur_gaji <= up_gaji){
			ans[i] = 'A';
			cur_x = cur_x + 1;
			cur_y = cur_y + 1;
		} 			
		else{
			ans[i] = 'D';
			cur_gaji = cur_gaji - up_gaji;
			cur_x = cur_x - 1;
			cur_y = cur_y + 1;
		}
	}
	printf("%s\n",ans);
}
int main(void)
{
    ll d, k; scanf("%lld%lld", &d, &k);
	ll ban = d/2;
	/*
	Fill the dp
	if d = 200000, 599987 information made. 
	*/
	dp[0][d] = 1;
	for(ll i=d; i>=0; i=i-2)
		build_dp(i);
	dp[0][0] = dp[1][1];
	if(dp[0][0] < k){
		printf("-1\n");
		return 0;
	}
	track(d, k);
	return 0;
}