#include <stdio.h>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct card
{
    int people;
    int x;
};
typedef struct card card;
int ret[20001];
vector <int> turn[20001];
vector <int> v1;
vector <int> v2;
//turn을 통해 알 수 있는 카드의 선행, 후행 관계를 저장함.
vector <int> con[20001];
vector <int> real_graph[20001];
int real_in[20001];
card ca[20001];
vector <int> two;
void input(int n, int c)
{
    //result
    char op[5] = {0};
    for(int i=1; i<=c; i++)
    {
        scanf("%d ",ret+i); v1.push_back(ret[i]);
    }
    sort(v1.begin(), v1.end());
    
    for(int i=1; i<=n; i++)
    {
        int tn, a; scanf("%d",&tn);
        //order of card
        for(int j=0;j<tn;j++)
        {
            scanf("%d",&a); turn[i].push_back(a);
            
            //a번 카드를 i번 사람이 낸다.
            ca[a].people = i;
            //printf("ca[%d] = %d\n",a,i);
        }
        for(int j=1;j<tn;j++)
        {
            int prev = turn[i][j-1]; int cur = turn[i][j];
            //prev번 카드를 내고, cur 카드를 내야 한다.
            con[prev].push_back(cur);
        }
    }
    
    for(int i=1; i<=c; i++)
    {
        int nu; scanf("\n%s %d",op,&nu);
        ca[i].x = nu; v2.push_back(nu);
    }
    sort(v2.begin(), v2.end());
}
int co[20001];
void init(int n, int c)
{
    /*
    좌표 압축 대상
    ca[i].x (카드에 적혀져 있는 수)
    ret[i] (결과에 떨어진 수)
    */
    for(int i=1; i<=c; i++)
        ret[i] = lower_bound(v1.begin(), v1.end(), ret[i]) - v1.begin();
    
    for(int i=1; i<=c; i++)
        ca[i].x = lower_bound(v2.begin(), v2.end(), ca[i].x) - v2.begin();
    
    //압축이 끝났다면 2번 이상 등장한 것들만 저장하도록 하자.
    for(int i=1; i<=c; i++)
        co[ret[i]]++;
    for(int i=1; i<=c; i++)
    {
        if(co[ca[i].x] <= 1)
            continue;
        two.push_back(i);
    }
}
queue <int> Q;
int work(int n,int c)
{
    vector <int> ans;
    for(int i=1; i<=c; i++)
    {
        if(real_in[i] == 0)
        {
            real_in[i]--; Q.push(i);
        }
    }
    while(!Q.empty())
    {
        int item = Q.front(); Q.pop();
        ans.push_back(item);
        for(int i=0;i<(int)real_graph[item].size();i++)
        {
            int ne = real_graph[item][i];
            real_in[ne]--;
            
            if(real_in[ne] == 0)
            {
                real_in[ne]--; Q.push(ne);
            }
        }
    }
    
    if((int)ans.size() != c)
        return 0;
    for(int i=0;i<(int)ans.size();i++)
    {
        printf("%d ",ca[ans[i]].people);
    }
    return 1;
}
vector <int> num_to_cn[20001];
int pos[20001];
int main(void)
{
    int n, c; scanf("%d %d",&n,&c); 
    input(n, c);
    
    //vector compare를 통해서 1차로 걸러낸다.
    if(v1 != v2)
    {
        printf("-1\n");
        return 0;
    }
    init(n, c);
    do
    {    
        memset(pos, 0, sizeof(int)*20001);
        
        //graph 및 in 초기화
        memset(real_in, 0, sizeof(int)*20001);
        for(int i=0;i<=20000;i++){
            real_graph[i].clear();
            num_to_cn[i].clear();
        }
        
        //내야 하는 카드 순서?
        //ca[i] : i번 카드에 대한 정보를 가지고 있음.
        //num_to_cn[x] : 수 x는 어떤 카드가 들고 있는가?
        for(int i=1; i<=c; i++){
            if(co[ca[i].x] > 1)
                continue;
            num_to_cn[ca[i].x].push_back(i);
        }
        
        //내야 하는 카드 순서를 가지고 graph 구축.
        for(int i=1; i<=c; i++)
        {
            for(int j=0;j<(int)con[i].size();j++)
            {
                int cur = i; int ne = con[i][j];
                real_graph[cur].push_back(ne);
                //printf("%d ->> %d\n",cur, ne);
                real_in[ne]++;
            }
        }
        
        //다음에 둘 이상 나오는 놈 가지고 ordering을 한 다음에
        for(int i=0;i<(int)two.size();i++)
        {
            int card_num = two[i];
            num_to_cn[ca[card_num].x].push_back(card_num);
        }
        
        //결과 값을 가지고 2차 구축.
        int prev = -1;
        for(int i=1; i<=c; i++)
        {
            //결과는 ret에 저장되어 있으므로
            int cur_ret = ret[i];
            int cur = num_to_cn[cur_ret][pos[cur_ret]];
            pos[cur_ret]++;
            
            if(prev != -1)
            {
                //prev와 cur를 연결시켜야 하는데
                real_graph[prev].push_back(cur);
                //printf("%d -> %d\n",prev, cur);
                real_in[cur]++;
            }
            prev = cur;
        }
        //이제 위상정렬 위잉위잉^^
        if(work(n, c))
            return 0;
    }while(next_permutation(two.begin(), two.end()));
    printf("-1\n");
    return 0;
}