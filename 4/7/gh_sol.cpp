#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <deque>
#define K 1000000001LL
typedef long long ll;
using namespace std;
struct moo
{
    int id;
    int category_id;
    int time;
};
int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char str[200];
vector <string> tokens;
unordered_map <string, int> category_map;
map <int, int> movie_map;
deque <moo> dq;
//start
int category_view[500005];
set <ll> cat_pq[500005];
set <ll> common_pq;
map <ll, ll> movie_info;

void add_common_pq(int cat_lo)
{
    ll kei = *(cat_pq[cat_lo].begin());
    ll view = K - kei/K;
    ll m_id = kei%K;
    
    ll real_kei = (K - view - category_view[cat_lo]) * K + m_id;
    common_pq.insert(real_kei);
}

void del_common_pq(int cat_lo)
{
    ll kei = *(cat_pq[cat_lo].begin());
    ll view = K - kei/K;
    ll m_id = kei%K;
    
    ll real_kei = (K - view - category_view[cat_lo]) * K + m_id;
    common_pq.erase(real_kei);
}
ll get_id()
{
    ll kei = *(common_pq.begin());
    return kei%K;
}
void del(ll m_id, ll c_id, ll view)
{
    ll kei = (K - view)*K + m_id;
    if(cat_pq[c_id].find(kei) != cat_pq[c_id].end())
        cat_pq[c_id].erase(kei);
}
void add(ll m_id, ll c_id, ll view)
{
    ll kei = (K - view)*K + m_id;
    cat_pq[c_id].insert(kei);
}
void update(int m_id, int c_id, int diff)
{
    //printf("m_id = %d\n",m_id);
    del_common_pq(c_id);
    
    //<1> m_id에 대한 정보 업데이트 하기.
    ll before_view = (ll)movie_info[m_id];
    del((ll)m_id, (ll)c_id, before_view);
    ll after_view = before_view + diff;
    add((ll)m_id, (ll)c_id, after_view);
    movie_info[m_id] = after_view;
    
    //<2> category_view도 update..
    category_view[c_id] += diff;
    
    add_common_pq(c_id);
}
//end
void tokenize();
int YYYYMMDD(string &s);
int get_category_id(string &c);
int main(void)
{
    int n, e; moo item; scanf("%d%d\n", &n, &e);
    for(int i=0; i<n; i++)
    {
        fgets(str, 200, stdin);
        int len = strlen(str);
        if(str[len-1] == '\n') str[len-1] = 0;
        
        tokenize();
        
        //뒷 token 2개 자르기.
        string category = tokens[(int)tokens.size() - 2];
        int id = stoi(tokens[(int)tokens.size() - 1]);
        
        int category_id = get_category_id(category);
        
        //(id, category)
        movie_map[id] = category_id;
        movie_info[id] = 0;
        
        add(id, category_id, 0);
    }
    
    for(int i=0; i<500005; i++)
    {
        if((int)cat_pq[i].size() == 0)
            continue;
        add_common_pq(i);
    }
    
    for(int i=0; i<e; i++)
    {
        fgets(str, 200, stdin);
        int len = strlen(str);
        if(str[len-1] == '\n') str[len-1] = 0;
        str[19] = 0;
        
        string ymd = string(str);
        int ti = YYYYMMDD(ymd);
        
        //time이 ti - 3*(24*3600) 이상인 것만 Q에 남긴다.
        while(!dq.empty())
        {
            int dq_time = dq.front().time;
            if(ti - 3 * (24 * 3600) <= dq_time)
                break;
            item = dq.front();
            dq.pop_front();
            
            update(item.id, item.category_id, -1);
        }
        if(strcmp(str+20, "R") == 0)
        {
            //common_map에서 제일 큰 놈 찾기.
            printf("%lld\n",get_id());
        }
        else
        {
            int video_id = atoi(str + 20);
            //Q에 video_id와 category에 대한 정보 넣기.
            int category_id = movie_map[video_id];
            item.id = video_id;
            item.category_id = category_id;
            item.time = ti;
            
            update(video_id, category_id, 1);
            
            dq.push_back(item);
        }
    }
}
int get_category_id(string &c)
{
    if(category_map.find(c) == category_map.end())
        category_map[c] = (int)category_map.size();
    return category_map[c];
}
void tokenize(){
    tokens.clear();
    const char *tok = strtok(str, " ");
    while(tok != NULL)
    {
        tokens.push_back(string(tok));
        tok = strtok(NULL, " ");
    }
}
int YYYYMMDD(string &s)
{
    int Y = stoi(s.substr(0, 4));
    int M = stoi(s.substr(5, 2));
    int D = stoi(s.substr(8, 2));
    int hh = stoi(s.substr(11, 2));
    int mm = stoi(s.substr(14, 2));
    int ss = stoi(s.substr(17, 2));
    int tot_days = 0;
    for(int y = 2000; y < Y; y++)
        tot_days = tot_days + 365 + (y % 4 == 0);
    for(int m = 1; m < M; m++){
        tot_days = tot_days + days[m];
        if(m == 2 && Y % 4 == 0)
            tot_days++;
    }
    tot_days = tot_days + (D - 1);
    
    int tot_s = hh * 3600 + mm * 60 + ss;
    
    return (tot_days) * (3600 * 24) + tot_s;
}