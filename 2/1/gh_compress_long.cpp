#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
char str[30];
char name[11];
char ext[11];
struct file
{
    ll nn, ee, flag;
};
typedef struct file file;
vector <file> v;
vector <ll> ve;
ll f[128];
char c[128];
void init()
{
    for(ll i=0;i<26;i++)
        f[i + 'a'] = i + 11;
    for(ll i=0;i<10;i++)
        f[i + '0'] = i + 1;
    for(ll i=127; i>=0; i--)
        c[f[i]] = (char)i;
}
ll foo(char *tar)
{
    ll ret = 0;
    for(ll i=0;i<10;i++)
    {
        ret = ret*64 + f[tar[i]];
    }
    return ret;
}
void conv(char *tar, ll x)
{
    ll cur = x;
    //64진법
    for(ll i=9; i>=0; i--)
    {
        tar[i] = c[cur&63LL];
        cur = (cur>>6LL);
    }
}
bool cmp(file a, file b)
{
    if(a.nn != b.nn)
        return a.nn < b.nn;
    if(a.flag != b.flag)
        return a.flag > b.flag;
    return a.ee < b.ee;
}
int main(void)
{
    ll n,m; scanf("%lld %lld\n",&n,&m); init(); file I;
    
    for(ll i=0;i<n;i++)
    {
        scanf("%s\n",str); ll lo = strchr(str, '.') - str; str[lo] = 0;
        memset(name, 0, sizeof(char)*11); memset(ext, 0, sizeof(char)*11);
        strcpy(name, str); strcpy(ext, str+lo+1);
        I.nn = foo(name); I.ee = foo(ext); I.flag = 0LL; v.push_back(I); //ve.push_back(I.ee);
    }
    for(ll i=0;i<m;i++)
    {
        memset(ext, 0, sizeof(char)*11);
        scanf("%s\n",ext);
        ve.push_back(foo(ext));
    }
    sort(ve.begin(), ve.end());
    ve.erase(unique(ve.begin(), ve.end()), ve.end());
    for(ll i=0;i<n;i++)
    {
        ll lo = lower_bound(ve.begin(), ve.end(), v[i].ee) - ve.begin();
        if(lo == (ll)ve.size())
            continue;
        if(ve[lo] == v[i].ee)
            v[i].flag = 1LL;
    }
    sort(v.begin(), v.end(), cmp);
    for(ll i=0;i<n;i++)
    {
        conv(name, v[i].nn); conv(ext, v[i].ee);
        printf("%s.%s\n",name,ext);
    }
}