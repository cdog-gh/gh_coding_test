/*
basic idea
(1) ver1에서 obj_id에 연결된 ref1, ref2, ... 이렇게 관리를 했음. 그런데 이 경우 ref2 삭제 명령이 떨어질 때 마다 삭제하고 M과 m 연산이 들어올 때 마다 재구축
    - 이 경우 set, map이 느리기 때문에 생각보다 효율적으로 동작하지 못함.
(2) 들어오는 쿼리는 연결 관계를 삽입하거나, 삭제하거나, 수집하는 쿼리인데 수집 쿼리에서 시간이 많이 발생하는 것이므로 이를 줄이는 게 목적임.
    -  연결 관계가 삭제된 것을 판단하는 방법이 없는가?
(3) made_time[x] 이벤트를 두자. 이건 객체가 만들어 지거나 삭제될 때 업데이트가 된다.
    - 예를 들어 id가 30인 object가 시간 10일때 추가된 경우 made_time[30] = 10이 됨. 이걸 어떻게 관리하는가?
    - 객체가 만들어 지거나 삭제되는 것은 obj_id에 대한 최신화가 언제 일어났는지를 나타낸다고 말할 수 있음.
    - 그런데, con[obj]에 추가할 때에는 추가한 시간이 저장됨. 따라서 con[obj]에서 돌면서 ref_id가 t1에 추가되었는데 made_time[ref_id]가 t2라 하자.
    - t1 < t2라 하자. 그러면 이 경우는 기존에 추가된 친구가 업데이트가 안 되어 있는 상태이기 때문에 무시해도 되는 친구임.
*/
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct REF
{
    int a;
    int b;
    int id;
    int weak;
    int made_time;
};
typedef struct REF REF;
unordered_set <int> root;
unordered_set <int> visit;
vector <string> tokens;
unordered_map <int, REF> ref;
unordered_map <int, vector <REF>> con;
unordered_map <int, int> made_time;
char str[50];
queue <int> Q;
void tokenize(){
    tokens.clear();
    const char *p = strtok(str, " ");
    while(p != NULL)
    {
        tokens.push_back(string(p));
        p = strtok(NULL, " ");
    }
}
int is_eq(string s, const char *target){
    return (strcmp(s.c_str(), target) == 0);
}
int bfs(int upper_bound, int etime)
{
    int ret = 0;
    /*
    upper_bound가 0인 경우, weak 수치가 0인 것까지 탐색
    upper_bound가 1인 경우, weak 수치가 1인 것까지 탐색
    */
    for(unordered_set <int>::iterator it = root.begin(); it != root.end(); it++)
    {
        int obj_id = (*it);
        //printf("<%d>\n",obj_id);
        Q.push(obj_id); visit.insert(obj_id);
    }
    
    while(!Q.empty())
    {
        int obj_id = Q.front(); Q.pop(); ret++;
        //printf("obj_id = %d\n",obj_id);
        if(con.find(obj_id) == con.end())
            continue;
        for(int i=0; i<(int)con[obj_id].size(); i++)
        {
            REF ref_item = con[obj_id][i];
            if(ref_item.weak > upper_bound)
                continue;
            
            //# 이 부분이 중요함. made_time[ref_item.id]는 ref_item.id인 연결 관계가 ADD 연산에 의해 추가된 시간임.
            //그런데 made_time[ref_item.id]는 ref_item.id인 연결 관계가 정보가 변한 최신 시간임.
            //그래서 if문이 걸린다는 의미는 ref_item이 최신 상태가 아니라는 의미이므로 무시해도 된다.
            if(made_time[ref_item.id] > ref_item.made_time)
                continue;
            int b_obj_id = ref_item.b;
            if(visit.find(b_obj_id) != visit.end())
                continue;
            
            Q.push(b_obj_id); visit.insert(b_obj_id);
        }
    }
    for(unordered_map <int, vector <REF>>::iterator iter = con.begin(); iter != con.end(); iter++){
        int cur = iter->first;
        vector <REF> refx = iter->second;
        //con은 REF들을 가지고 있다.
        for(int i=0; i<(int)refx.size(); i++)
        {
            //REF는 a -> b에 대한 정보를 가지고 있다.
            int a = refx[i].a;
            int b = refx[i].b;
            int id = refx[i].id;
            
            //a나 b를 찾을 수 없으면 
            if(visit.find(a) == visit.end() || visit.find(b) == visit.end())
                made_time[id] = etime;
        }
    }
    //정리 후 재구축
    visit.clear();
    return ret;
}
int main(void)
{
    int O, E; scanf("%d %d\n", &O, &E);
    for(int o=0; o<O; o++)
    {
        int obj_id; scanf("%d %s\n", &obj_id, str);
        if(strcmp(str, "ROOT") == 0)
            root.insert(obj_id);
        con[obj_id] = vector<REF>();
    }
    for(int e=0; e<E; e++)
    {
        fgets(str, 40, stdin);
        int len = strlen(str);
        if(str[len - 1] == '\n') str[len-1] = 0;
        //token 별로 자르자!
        tokenize();
        
        //(1) MADE id is_root
        //is_root는 ROOT이거나 -임.
        if(is_eq(tokens[0], "MADE"))
        {
            int obj_id = stoi(tokens[1]);
            if(is_eq(tokens[2], "ROOT"))
                root.insert(obj_id);
            con[obj_id] = vector<REF>();
        }
        //(2) ADD ref_id object_id_1 -> object_id_2
        //약연결
        
        //(3) ADD ref_id object_id_1 => object_id_2
        //강연결
        else if(is_eq(tokens[0], "ADD"))
        {
            REF item;
            item.a = stoi(tokens[2]);
            item.b = stoi(tokens[4]);
            if(is_eq(tokens[3], "->"))
                item.weak = 1;
            else
                item.weak = 0;
            int ref_id = stoi(tokens[1]);
            item.id = ref_id;
            ref[ref_id] = item;
            item.made_time = e;
            con[item.a].push_back(item);
            made_time[ref_id] = e;
        }
        
        //(4) REMOVE ref_id
        //연결 고리 제거
        else if(is_eq(tokens[0], "REMOVE"))
        {
            int ref_id = stoi(tokens[1]);
            REF ref_info = ref[ref_id];
            
            //실제 연결되어 있는 con 동기화
            int a = ref_info.a;
            int b = ref_info.b;
            made_time[ref_id] = e;
        }
        
        //(5) M (major gc)
        else if(is_eq(tokens[0], "M"))
            printf("%d\n",bfs(0, e));
        
        //(6) m (minor gc)
        else
            printf("%d\n",bfs(1, e));
    }
    return 0;
}