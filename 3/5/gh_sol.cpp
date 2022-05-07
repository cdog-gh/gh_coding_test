#include <stdio.h>
#include <memory.h>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <set>
#include <cassert>
#define M 1010101LL
#define inf 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef long long ll;
struct MONKEY
{
    int op;
    int skill; //L1 = 2, R1 = 1
    int priority; //FIRST = 0, LAST = 1, STRONG = 2
};
typedef struct MONKEY MONKEY;
struct MONKEY_EVENT
{
    int op; //ADD = 1, UPGRADE = 2, REMOVE = 3, CHANGEPRIORITY = 4
    int id;
    int priority;
    int skill;
};
typedef struct MONKEY_EVENT MONKEY_EVENT;
struct BALLOON_EVENT
{
    int id;
    int lv;
    int route_id;
};
typedef struct BALLOON_EVENT BALLOON_EVENT;
struct BALLOON
{
    int time_s;
    int time_e;
    int id;
    int lv;
};
typedef struct BALLOON BALLOON;
MONKEY monkeys[1001];
int route_len[11];
char str[6000];
vector <string> tokens;
vector <MONKEY_EVENT> monkey_e[300000];
vector <BALLOON_EVENT> balloon_e[300000];
set <int> mee[300001];
int bC[1000001];
//util_function
void input();
void tokenize();
int monkey_skill(string tar);
int monkey_priority(string tar);
int balloon_lv(string &b_name);
int time_parse(string &ti);
//add functions
void do_monkey(MONKEY_EVENT me)
{
    int op = me.op;
    int id = me.id;
    if(op == 1)
    {
        //ADD id
        monkeys[id % 1000].priority = monkey_priority(string("FIRST"));
        monkeys[id % 1000].skill = monkey_skill(string("-"));
    }
    else if(op == 2)
    {
        //UPGRADE
        monkeys[id % 1000].skill |= me.skill;
    }
    else if(op == 3)
    {
        //REMOVE
        monkeys[id % 1000].skill = -1;
        monkeys[id % 1000].priority = -1;
    }
    else
    {
        //CHANGEPRIORITY
        monkeys[id % 1000].priority = me.priority;
    }
}
//[0] : not camo, [1] : camo
map <ll, BALLOON> SID[2];
map <ll, BALLOON> EID[2];
map <ll, BALLOON> LVID[2];
void add(BALLOON b_item)
{
    int is_camo = (b_item.lv % 2 == 0);
    ll SID_key = b_item.time_s * M + (M - b_item.id);
    ll EID_key = b_item.time_e * M + (b_item.id);
    ll LVID_key = b_item.lv * M + (M - b_item.id);
    
    SID[is_camo][SID_key] = b_item;
    EID[is_camo][EID_key] = b_item;
    LVID[is_camo][LVID_key] = b_item;
}
void rm(BALLOON b_item)
{
    int is_camo = (b_item.lv % 2 == 0);
    ll SID_key = b_item.time_s * M + (M - b_item.id);
    ll EID_key = b_item.time_e * M + (b_item.id);
    ll LVID_key = b_item.lv * M + (M - b_item.id);
    
    SID[is_camo].erase(SID[is_camo].find(SID_key));
    EID[is_camo].erase(EID[is_camo].find(EID_key));
    LVID[is_camo].erase(LVID[is_camo].find(LVID_key));
}
void do_add_balloon(BALLOON_EVENT be,int t)
{
    BALLOON b_item;
    //id, lv, route_id
    //time_s, time_e, id, lv
    b_item.id = be.id;
    b_item.lv = be.lv;
    b_item.time_s = t;
    b_item.time_e = t + route_len[be.route_id];
    
    add(b_item);
}
void do_rm_balloon(int t)
{
    //EID[0], EID[1]
    for(int c=0; c<=1; c++)
    {
        while(!EID[c].empty())
        {
            map <ll, BALLOON>::iterator iter = EID[c].begin();
            BALLOON b_item = iter -> second;
            if(b_item.time_e > t)
                break;
            rm(b_item);
        }
    }
}
BALLOON target_first(MONKEY me)
{
    int camo_detect = ((me.skill & 2) != 0);
    BALLOON be; memset(&be, -1, sizeof(BALLOON));
    ll mn = inf;
    for(int i=0; i<=camo_detect; i++)
    {
        if(EID[i].empty())
            continue;
        ll kei = (EID[i].begin()) -> first;
        if(kei < mn)
        {
            mn = kei;
            be = (EID[i].begin()) -> second;
        }
    }
    return be;
}
BALLOON target_last(MONKEY me)
{
    int camo_detect = ((me.skill & 2) != 0);
    BALLOON be; memset(&be, -1, sizeof(BALLOON));
    ll mx = -1;
    for(int i=0; i<=camo_detect; i++)
    {
        if(SID[i].empty())
            continue;
        ll kei = (--SID[i].end()) -> first;
        if(kei > mx)
        {
            mx = kei;
            be = (--SID[i].end()) -> second;
        }
    }
    return be;
}
BALLOON target_strong(MONKEY me)
{
    int camo_detect = ((me.skill & 2) != 0);
    BALLOON be; memset(&be, -1, sizeof(BALLOON));
    ll mx = -1;
    for(int i=0; i<=camo_detect; i++)
    {
        if(LVID[i].empty())
            continue;
        ll kei = (--LVID[i].end()) -> first;
        if(kei > mx)
        {
            mx = kei;
            be = (--LVID[i].end()) -> second;
        }
    }
    return be;
}
void f(BALLOON ret, int t){
    if(ret.id == -1)
        return;
    int can_attack_lead = (monkeys[t%1000].skill % 2 != 0);
    int is_lead = (ret.lv >= 3);
    
    if((!can_attack_lead) && is_lead)
        return;
    
    int m_id = ((t%1000 == 0)?1000:t%1000);    
    printf("%d %d\n", ret.id, m_id);
    
    rm(ret);
    
    //Lead 이상인 경우 추가해야 함.
    if(ret.lv > 2)
    {
        ret.lv = ret.lv - 2;
        add(ret);
    }
}
void work(int t)
{
    //monkey event
    
    //풍선 이벤트
    for(int i=0; i<(int)balloon_e[t].size(); i++)
        do_add_balloon(balloon_e[t][i], t);
    do_rm_balloon(t);
    
    if(t != 0 && monkeys[t%1000].skill != -1){
        BALLOON ret;
        //원숭이 타겟팅
        if(monkeys[t%1000].priority == 0)
            ret = target_first(monkeys[t%1000]);//FIRST
        else if(monkeys[t%1000].priority == 1)
            ret = target_last(monkeys[t%1000]);//LAST
        else
            ret = target_strong(monkeys[t%1000]);//STRONG
        f(ret, t);
    }
    //원숭이 이벤트
    for(int i=0; i<(int)monkey_e[t].size(); i++)
        do_monkey(monkey_e[t][i]);
}
//add functions end
int main(void)
{
    input();
    for(int t=0; t<300000; t++)
        work(t);
    return 0;
}
int mk_exist[1001];
//util_function
int bbj[300001][11];
void input()
{
    memset(monkeys, -1, sizeof(MONKEY)*1001);
    int r, u, e; scanf("%d%d\n",&r, &u);
    for(int i=1; i<=r; i++){
        scanf("%d ",route_len + i);
        route_len[i] *= 100; //0.1초마다 다음 지점으로 이동하므로.
    }
    for(int i=1; i<=r; i++)
        fgets(str, 6000, stdin);
    for(int i=1; i<=u; i++)
    {
        fgets(str, 6000, stdin);
        tokenize();
        int idx = stoi(tokens[0]);
        monkeys[idx % 1000].skill = monkey_skill(tokens[1]);
        monkeys[idx % 1000].priority = monkey_priority(tokens[2]);
        assert(mk_exist[idx] == 0);
        mk_exist[idx] = 1;
    }
    scanf("%d\n", &e);
    for(int i=0; i<e; i++)
    {
        MONKEY_EVENT me;
        BALLOON_EVENT be;
        fgets(str, 6000, stdin);
        tokenize();
        int time = time_parse(tokens[0]);
        
        //ss.XXX ADD monkey_id
        if(tokens[1].compare("ADD") == 0)
        {
            me.op = 1;
            me.id = stoi(tokens[2]);
            assert(me.id % 1000 != time % 1000 || time == 0);
            me.skill = monkey_skill(string("-")); 
            me.priority = monkey_priority(string("FIRST"));
            monkey_e[time].push_back(me);
            
            assert(mee[time].find(me.id) == mee[time].end());
            mee[time].insert(me.id);
            
            assert(mk_exist[me.id] == 0);
            mk_exist[me.id] = 1;
        }
        
        //ss.XXX UPGRADE monkey_id SKILLNAME
        else if(tokens[1].compare("UPGRADE") == 0)
        {
            me.op = 2;
            me.id = stoi(tokens[2]);
            me.skill = monkey_skill(tokens[3]);
            assert(me.id % 1000 != time % 1000 || time == 0);
            monkey_e[time].push_back(me);
            
            assert(mee[time].find(me.id) == mee[time].end());
            mee[time].insert(me.id);
            
            assert(mk_exist[me.id] == 1);
            //mk_exist[me.id] = 0;
        }
        
        //ss.XXX REMOVE monkey_id
        else if(tokens[1].compare("REMOVE") == 0)
        {
            me.op = 3;
            me.id = stoi(tokens[2]);
            assert(me.id % 1000 != time % 1000 || time == 0);
            monkey_e[time].push_back(me);
            
            assert(mee[time].find(me.id) == mee[time].end());
            mee[time].insert(me.id);
            
            assert(mk_exist[me.id] == 1);
            mk_exist[me.id] = 0;
        }
        
        //ss.XXX CHANGEPRIORITY monkey_id priority
        else if(tokens[1].compare("CHANGEPRIORITY") == 0)
        {
            me.op = 4;
            me.id = stoi(tokens[2]);
            me.priority = monkey_priority(tokens[3]);
            assert(me.id % 1000 != time % 1000 || time == 0);
            monkey_e[time].push_back(me);
            
            assert(mee[time].find(me.id) == mee[time].end());
            mee[time].insert(me.id);
            
            assert(mk_exist[me.id] == 1);
            //mk_exist[me.id] = 0;
        }
        
        //ss.XXX BALLOON balloon_name balloon_id route_id
        else
        {
            int len = (int)tokens.size();
            be.id = stoi(tokens[len-2]);
            be.route_id = stoi(tokens[len-1]);
            string b_name = "";
            for(int t=2; t<len-2; t++)
                b_name = b_name + tokens[t];
            be.lv = balloon_lv(b_name);
            balloon_e[time].push_back(be);
            assert(bC[be.id] == 0);
            bC[be.id]++;
            
            assert(bbj[time][be.route_id] == 0);
            bbj[time][be.route_id]++;
        }
    }
}
void tokenize()
{
    tokens.clear();
    int len = strlen(str);
    if(str[len-1] == '\n') str[len-1] = 0;
    
    const char *p = strtok(str, " ");
    while(p != NULL)
    {
        tokens.push_back(string(p));
        p = strtok(NULL, " ");
    }
}
int monkey_skill(string stat)
{
    if(stat.compare("-") == 0) return 0;
    if(stat.compare("L1") == 0) return 2;
    if(stat.compare("R1") == 0) return 1;
    return 3;
}
int monkey_priority(string prio)
{
    if(prio.compare("FIRST") == 0) return 0;
    if(prio.compare("LAST") == 0) return 1;
    return 2;
}
int balloon_lv(string &b_name)
{
    if(b_name.compare("RedBalloon") == 0)
        return 1;
    if(b_name.compare("LeadBalloon") == 0)
        return 3;
    if(b_name.compare("CamoRedBalloon") == 0)
        return 2;
    return 4;
}
int time_parse(string &ti)
{
    const char *p = ti.c_str();
    int hi, lo;
    sscanf(p, "%d.%d", &hi, &lo);
    return 1000*hi + lo;
}