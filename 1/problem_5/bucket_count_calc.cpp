#include <stdio.h>
#include <unordered_set>
using namespace std;
typedef long long ll;
unordered_set <ll> ss;
/*
execute this program.
*/
int main(void)
{
    for(ll i=1; i<=300000; i++)
    {
        ll kei = i + 1;
		
		//3*10^5 item insert.
        ss.insert(kei);
    }
	//and get the bucket number
    printf("%d\n",(int)ss.bucket_count());
    return 0;
}