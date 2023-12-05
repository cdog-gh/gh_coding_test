#include <stdio.h>
#include <vector>
using namespace std;
int arr[505050];
vector <int> ans;
int main(void)
{
    int s, k; scanf("%d%d", &s, &k);
    for(int i=s; i>0; i--)
    {
        if(arr[i+k]) continue;
        arr[i] = 1; ans.push_back(i);
    }
    printf("%d\n", (int)ans.size());
    for(int i=0; i<(int)ans.size(); i++) printf("%d\n", ans[i]);
    return 0;
}
