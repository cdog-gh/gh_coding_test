#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <tuple>
#include <set>
using namespace std;
vector <tuple <string, string>> files;
vector <tuple <string, int, string>> deco;
set <string> ext_set;
char str[101];
int main(void)
{
    int n,m; scanf("%d %d\n",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%s\n",str);
        int lo = strchr(str, '.') - str; str[lo] = 0;
        files.push_back(make_tuple(string(str), string(str+lo+1)));
    }
    for(int i=0;i<m;i++)
    {
        scanf("%s\n",str);
        ext_set.insert(string(str));
    }
    for(int i=0;i<n;i++)
    {
        string ext = get<1>(files[i]);
        deco.push_back(make_tuple(get<0>(files[i]), 
                                  (ext_set.find(ext) == ext_set.end())?1:0, 
                                  get<1>(files[i])));
    }
    sort(deco.begin(), deco.end());
    for(int i=0;i<n;i++)
        printf("%s.%s\n",get<0>(deco[i]).c_str(), get<2>(deco[i]).c_str());
    return 0;
}