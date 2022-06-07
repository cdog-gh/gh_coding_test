#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;
struct train
{
    int id;
    int arrive_time;
};
typedef struct train train;
char str[30];
struct event1
{
    int train_id;
    int sn;
    int flag;
};
typedef struct event1 event1;
struct event2
{
    int train_id;
    int sn1;
    int sn2;
    int flag;
};
typedef struct event2 event2;
vector <event1> e1[30*60];
vector <event2> e2[30*60];
deque <int> wait[7][2];
int get_train_num(int a, int b)
{
    if((int)wait[a][b].size() == 0)
        return -1;
    return wait[a][b][0];
}
int parse()
{
    str[2] = 0;
    int hh = atoi(str);
    int mm = atoi(str+3);
    return 60*hh + mm;
}
int is_terminated(int train_id, int cur_station)
{
    if(train_id % 2 == 0)
        return (cur_station == 0);
    return (cur_station == 4);
}
int run_start_time[5001]; //운행 시작 시각
int locked[50];
int H[5] = {7, 7, 8, 10, 0};
int S[5] = {0, 7, 7, 8, 10};
struct moo
{
    int id, time;
};
typedef struct moo moo;
vector <moo> ans;
void go(int, int, int, int, int);
int select(int, int);
bool cmp(moo a, moo b)
{
    return a.id < b.id;
}
int print_t(int t)
{
    int hh = t / 60;
    int mm = t % 60;
    hh = hh % 24;
    printf("%02d:%02d\n", hh, mm);
    return 0;
}
int main(void)
{
    int B, C, pnum; scanf("%d%d", &C, &B);
    for(int i=0; i<C; i++)
    {
        scanf("\n%d %s", &pnum, str); int tt = parse();
        run_start_time[pnum] = tt;
        event1 item; 
        item.train_id = pnum; item.sn = 0; item.flag = 1; e1[tt].push_back(item); //하행
    }
    for(int i=0; i<B; i++)
    {
        scanf("\n%d %s", &pnum, str); int tt = parse();
        run_start_time[pnum] = tt;
        event1 item; 
        item.train_id = pnum; item.sn = 4; item.flag = 0; e1[tt].push_back(item); //상행
    }
    
    /*
    이 상태에서 event1에는 각 열차가 처음에 어느 역에서 출발 준비를 마치는지에 대한 정보가 담겨 있다.
    event2는 lock event인데..
    각 분마다 어떤 것을 먼저 처리할 것인지 천천히 생각해 보자.
    */
    for(int tt=0; tt<30*60; tt++)
    {
        //1. 먼저 출발 준비를 마친 얘들이 있으면 역별 대기 큐에 넣어야 함. 따라서, e1[tt]에 뭔가 있는지 파악한다.
        for(int j=0; j<(int)e1[tt].size(); j++)
        {
            event1 item = e1[tt][j];
            //이들은 각각 어떤 정보를 들고 있느냐. 어느 역에서 어느 방향으로 갈지에 대한 정보가 저장되어 있다.
            wait[item.sn][item.flag].push_back(item.train_id);
        }
        
        //2. 다음에 구간을 운행하고 있는 열차가 역에 도착하면 풀어줘야 한다. 이게 event2에 있음.
        for(int j=0; j<(int)e2[tt].size(); j++)
        {
            int from = e2[tt][j].sn1;
            int to = e2[tt][j].sn2;
            int train_id = e2[tt][j].train_id;
            int flag = e2[tt][j].flag;
            int lock_num = ((from < to)? from : to);
            
            //(1) 해당 구간을 점유하는 열차가 없으므로 lock을 해제해 버린다.
            locked[lock_num] = 0;
            
            //(2) 1분이 지난 후, 현재 역의 wait에 넣어버리기 위한 트리거를 걸어놓는다.
            //언제? 만약 종착역이 아니라면
            //printf("%d : %d = %d\n", train_id, to, is_terminated(train_id, to));
            if(!is_terminated(train_id, to))
            {
                event1 item;
                item.sn = to; item.train_id = train_id; item.flag = flag; e1[tt+1].push_back(item);
            }
            else
            {
                //train_id가 tt에 운행을 끝냈다는 정보를 어딘가에 저장한다.
                moo item;
                item.id = train_id; item.time = tt; ans.push_back(item);
                //printf("%d : %d\n",train_id, tt);
            }
        }
        
        //3. 이제 구간에 들어갈 열차를 뽑아야 겠다.
        for(int lock=0; lock<4; lock++)
        {
            //(1) 이미 구간에 열차가 운행하고 있으면 볼 필요도 없음.
            if(locked[lock])
                continue;
            //(2) 그렇지 않은 경우, 열차를 선택해야 하는데 wait[lock][1]과 wait[lock+1][0]에 해당 정보가 있음.
            int ha = get_train_num(lock, 1);
            int sa = get_train_num(lock+1, 0);
            
            //ha = 하행, sa = 상행인데 해당 구간에 갈 수 있는 열차 두 놈이 다 없다면 그냥 건너뛰고
            if(ha == -1 && sa == -1) continue;
            else if(ha == -1) go(tt, sa, lock+1, 0, lock); //상행만 있으면 상행이 간다.
            else if(sa == -1) go(tt, ha, lock, 1, lock); //하행만 있으면 하행이 간다.
            //상, 하행 두 놈 다 있으면
            else
            {
                int go_num = select(ha, sa);
                if(go_num == ha) go(tt, ha, lock, 1, lock);
                else go(tt, sa, lock+1, 0, lock);
            }
        }
    }
    sort(ans.begin(), ans.end(), cmp);
    for(int i=0; i<(int)ans.size(); i++)
        print_t(ans[i].time);
    return 0;
}
void go(int tt, int train_id, int sn, int flag, int lock_num)
{
    event2 item;
    
    int next = ((flag == 0)?sn - 1:sn + 1);
    item.train_id = train_id; item.sn1 = sn; item.sn2 = next; item.flag = flag;
    int soyo = ((flag != 0)?H[sn]:S[sn]);
    if(tt + soyo < 1800)
        e2[tt + soyo].push_back(item);
    
    wait[sn][flag].pop_front();
    locked[lock_num] = 1;
}
int select(int s1, int s2)
{
    if(run_start_time[s1] < run_start_time[s2])
        return s1;
    else if(run_start_time[s2] < run_start_time[s1])
        return s2;
    return ((s1 < s2)? s1:s2);
}