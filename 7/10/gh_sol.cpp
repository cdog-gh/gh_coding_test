#include <string>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
unordered_map<string, int> station_num =
{
    {"Tokyo", 0},
    {"Tokyo station", 0},
    {"Shinagawa", 1},
    {"Shinagawa station", 1},
    {"Shin-Yokohama", 2},
    {"Shin-Yokohama station", 2},
    {"Odawara", 3},
    {"Odawara station", 3},
    {"Atami", 4},
    {"Atami station", 4},
    {"Mishima", 5},
    {"Mishima station", 5},
    {"Shin-Fuji", 6},
    {"Shin-Fuji station", 6},
    {"Shizuoka", 7},
    {"Shizuoka station", 7},
    {"Kakegawa", 8},
    {"Kakegawa station", 8},
    {"Hamamatsu", 9},
    {"Hamamatsu station", 9},
    {"Toyohashi", 10},
    {"Toyohashi station", 10},
    {"Mikawa-Anjo", 11},
    {"Mikawa-Anjo station", 11},
    {"Nagoya", 12},
    {"Nagoya station", 12},
    {"Gifu-Hashima", 13},
    {"Gifu-Hashima station", 13},
    {"Maibara", 14},
    {"Maibara station", 14},
    {"Kyoto", 15},
    {"Kyoto station", 15},
    {"Shin-Osaka", 16},
    {"Shin-Osaka station", 16},
};
char s[303];
vector <string> v;
vector <int> nu;
int process();
int is_kodama();
int check_hikari_rapid(int lo1, int lo2, int g_num);
int is_hikari();
int is_nozomi();
int non_stop_check(int, int, int *);
int main()
{
    int Q, n; scanf("%d", &Q);
    for(int q=1; q<=Q; q++)
    {
        v.clear(); nu.clear();
        scanf("\n%d", &n);
        for(int i=0; i<n; i++)
        {
            scanf("\n%[^\n]s", s);
            v.push_back(string(s));
        }
        int ret = process();
        if(ret > 0) printf("ERROR %d\n", ret);
        else if(ret == -1) printf("kodama\n");
        else if(ret == -2) printf("hikari\n");
        else printf("nozomi\n");
    }
    return 0;
}
int non_stop_check(int s, int e, int *dat)
{
    if(s > e) swap(s, e);
    for(int i=s+1; i<e; i++)
    {
        if(dat[i]) return 0;
    }
    return 1;
}
int is_kodama()
{
    int k_data[17][17] = {0};
    int s = nu.front(); int e = nu.back();
    int stop_num = abs(s - e) + 1;
    if(stop_num != (int)nu.size()) return 0;
    k_data[0][7] = k_data[0][9] = k_data[0][12] = k_data[0][16] = 1;
    k_data[1][7] = k_data[1][9] = k_data[1][12] = k_data[1][16] = 1;
    k_data[2][7] = k_data[2][9] = k_data[2][12] = k_data[2][16] = k_data[2][0] = 1;
    k_data[5][0] = 1;
    k_data[7][0] = k_data[7][12] = k_data[7][16] = 1;
    k_data[9][0] = k_data[9][16] = 1;
    k_data[12][7] = k_data[12][0] = 1;
    k_data[16][9] = k_data[16][7] = k_data[16][0] = 1;
    return k_data[s][e];
}
int check_hikari_rapid(int lo1, int lo2, int g_num)
{
    int s = lo1; int e = lo2;
    if(s > e) swap(s, e);
    int stop_num = e - s - 1;
    if(g_num == 1)
    {
        if(stop_num <= 2) return 1;
        for(int i=s+1; i<e; i++)
        {
            // if stop shizuoka, return 0:
            if(nu[i] == 7) return 0;
        }
        return 1;
    }
    else
    {
        if(stop_num == 0) return 1;
        if(stop_num == 2) return 0;
        // if only 13 (Gifu-Hashima only) stop, error
        if(nu[s+1] == 13) return -1;
        return 0;
    }
}
int is_hikari()
{
    int h_data[17][17] = {0};
    int h_must_stop[17] = {0};
    int h_select_stop[17] = {0};
    int h_loc[17] = {0}; memset(h_loc, -1, sizeof(int)*17);
    int s = nu.front(); int e = nu.back();
    h_data[0][12] = h_data[0][16] = 1;
    h_data[1][12] = h_data[1][16] = 1;
    h_data[2][12] = h_data[2][16] = 1;
    h_data[12][0] = 1;
    h_data[16][0] = 1;
    h_must_stop[0] = h_must_stop[1] = h_must_stop[2] = h_must_stop[12] = h_must_stop[15] = h_must_stop[16] = 1;
    h_select_stop[3] = h_select_stop[4] = h_select_stop[5] = h_select_stop[7] = h_select_stop[9] = h_select_stop[10] = 1;
    h_select_stop[13] = h_select_stop[14] = 1;
    for(int i=1; i<(int)nu.size(); i++)
    {
        int f = nu[i-1]; int t = nu[i];
        if(!non_stop_check(f, t, h_must_stop)) return 0;
    }
    for(int i=0; i<(int)nu.size(); i++)
    {
        if((!h_must_stop[nu[i]]) && (!h_select_stop[nu[i]])) return 0;
        h_loc[nu[i]] = i;
    }
    // 2, 12, 15 얻기.
    int s2 = h_loc[2];
    int s12 = h_loc[12];
    int s15 = h_loc[15];
    if(s15 == -1)
    {
        int f1 = check_hikari_rapid(s2, s12, 1);
        if(f1 == 1) return 0;
    }
    int f1 = check_hikari_rapid(s2, s12, 1);
    int f2 = check_hikari_rapid(s12, s15, 2);
    if(f1 == 1 && f2 == 1) return 0;
    if(f2 == -1) return 0;
    return h_data[s][e];
}
int is_nozomi()
{
    int n_data[17][17] = {0};
    int n_must_stop[17] = {0};
    int s = nu.front(); int e = nu.back();
    n_data[0][12] = n_data[0][16] = 1;
    n_data[1][12] = n_data[1][16] = 1;
    n_data[2][12] = n_data[2][16] = 1;
    n_data[12][0] = 1;
    n_data[16][0] = 1;
    n_must_stop[0] = n_must_stop[1] = n_must_stop[2] = n_must_stop[12] = n_must_stop[15] = n_must_stop[16] = 1;
    for(int i=1; i<(int)nu.size(); i++)
    {
        int f = nu[i-1]; int t = nu[i];
        if(!non_stop_check(f, t, n_must_stop)) return 0;
    }
    for(int i=0; i<(int)nu.size(); i++)
    {
        if(!n_must_stop[nu[i]]) return 0;
    }
    return n_data[s][e];
}
int process()
{
    int co[20] = {0};
    for(int i=0; i<(int)v.size(); i++)
    {
        if(station_num.find(v[i]) == station_num.end()) return 200;
        int st_number = station_num[v[i]];
        co[st_number]++;
        if(co[st_number] > 1) return 300;
        nu.push_back(st_number);
    }
    int dir = nu[1] - nu[0];
    for(int i=1; i<(int)v.size(); i++)
    {
        int dir2 = nu[i] - nu[i-1];
        if(dir * dir2 < 0) return 400;
    }
    // int s = nu[0]; int e = nu.back();
    // kodama
    if(is_kodama()) return -1;
    if(is_nozomi()) return -3;
    if(is_hikari()) return -2;
    return 500;
}