#include <stdio.h>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
unordered_map <string, int> gun = {
    { "C", 0 },
    { "C#", 1 },
    { "D", 2 },
    { "D#", 3 },
    { "E", 4 },
    { "F", 5 },
    { "F#", 6 },
    { "G", 7 },
    { "G#", 8 },
    { "A", 9 },
    { "A#", 10 },
    { "B", 11 }
};
string gun_num[12];
struct code
{
    string base; //C#
    string code; //C#M
    int flag;
    int um[3];
};
typedef struct code code;
code cc[48];
string addition[4] = {"M", "m", "aug", "dim"};
int dist[4][2] = {
    {4, 3},
    {3, 4},
    {4, 4},
    {3, 3}
};
//x번째 음을 어떤 코드가 저장하고 있는지 저장. (사전 순으로)
vector <int> con[12];
bool cmp(code c1, code c2)
{
    return c1.code < c2.code;
}
int add(int a, int x)
{
    return (a + x + 12) % 12;
}
vector <int> process(string s);
int co[48];
vector <int> used[48];
int last_used[48];
char str[2020202];
int chk(int from, int k, int code_num)
{
    int lo = (int)used[code_num].size();
    // printf("code_num = %d lo = %d k = %d\n",code_num, lo, k);
    if(lo - k < 0)
        return 0;
    int md = used[code_num][lo-k];
    // printf("%d : %d\n", from, md);
    if(from <= md)
        return 1;
    return 0;
}
int main(void)
{
    //C, C#, D, D#, E, F, F#, G, G#, A, A#, B
    // 4 3 > M
    // 3 4 > m
    // 4 4 > aug
    // 3 3 > dim
    for(int i=0; i<48; i++)
        last_used[i] = -1;
    int p = 0;
    for(auto& item: gun)
        gun_num[item.second] = item.first;
    for(auto& item: gun){
        for(int i=0; i<4; i++){
            string temp_code;
            temp_code.append(item.first);
            temp_code.append(addition[i]);

            int um_1 = gun[item.first];
            int um_3 = add(um_1, dist[i][0]);
            int um_5 = add(um_3, dist[i][1]);

            cc[p].base = string(item.first);
            cc[p].code = temp_code;
            cc[p].um[0] = um_1;
            cc[p].um[1] = um_3;
            cc[p].um[2] = um_5;
            cc[p++].flag = i;
        }
    }
    sort(cc, cc+48, cmp);
    for(int i=0; i<48; i++)
    {
        con[cc[i].um[0]].push_back(i);
        con[cc[i].um[1]].push_back(i);
        con[cc[i].um[2]].push_back(i);
    }
    //C8 to 0 (every madi)
    int M, P, K; scanf("%d%d%d", &M, &P, &K);
    for(int i=1; i<=M; i++)
    {
        scanf("\n%s", str);
        vector <int> ve = process(str);
        for(int j=0; j<48; j++)
            co[j] = 0;
        for(int j=0; j<(int)ve.size(); j++)
            for(int k=0; k<(int)con[ve[j]].size(); k++)
                co[con[ve[j]][k]]++;
        //get used_code
        int mmx_freq = -1;
        int used_code = -1;
        for(int j=0; j<48; j++)
        {
            if(chk(i-P, K, j))
                continue;
            if(co[j] > mmx_freq)
            {
                mmx_freq = co[j];
                used_code = j;
            }
        }
        if(used_code == -1)
        {
            int lu = 0x3f3f3f3f;
            for(int j=0; j<48; j++)
            {
                if(last_used[j] < lu)
                {
                    lu = last_used[j];
                    used_code = j;
                }
            }
        }
        //used code calc
        used[used_code].push_back(i);
        last_used[used_code] = i;
        printf("%s\n", cc[used_code].code.c_str());
        // printf("used_code = %d : %d\n",used_code, (int)used[used_code].size());
    }
}
vector <int> process(string s)
{
    const char *temp = s.c_str();
    vector <int> te;
    for(int i=0; temp[i]; i++)
    {
        int lo = (int)te.size() - 1;
        if('0' <= temp[i] && temp[i] <= '9')
            continue;
        if(temp[i] == '-')
            continue;
        if(temp[i] == '#')
            te[lo] = add(te[lo], 1);
        else if(temp[i] == '$')
            te[lo] = add(te[lo], -1);
        else{
            int kth = gun[string(1, temp[i])];
            te.push_back(kth);
        }
    }
    return te;
}
