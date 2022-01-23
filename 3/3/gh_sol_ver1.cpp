#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct REF
{
    int a;
    int b;
    int weak;
};
typedef struct REF REF;
set <int> root;
set <int> visit;
vector <string> tokens;
map <int, REF> ref;
map <int, set <int>> con;
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
int bfs(int upper_bound)
{
    int ret = 0;
    /*
    upper_bound가 0인 경우, weak 수치가 0인 것까지 탐색
    upper_bound가 1인 경우, weak 수치가 1인 것까지 탐색
    */
    for(set <int>::iterator it = root.begin(); it != root.end(); it++)
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
        //printf("con[%d].size = %d\n",obj_id, (int)con[obj_id].size());
        for(set <int>::iterator it = con[obj_id].begin(); it != con[obj_id].end(); it++)
        {
            int ref_id = (*it);
            //printf("ref_id = %d\n",ref_id);
            REF ref_item = ref[ref_id];
            //printf("item = %d %d %d\n",ref_item.a, ref_item.b, ref_item.weak);
            if(ref_item.weak > upper_bound)
                continue;
            
            int b_obj_id = ref_item.b;
            if(visit.find(b_obj_id) != visit.end())
                continue;
            
            Q.push(b_obj_id); visit.insert(b_obj_id);
        }
    }
    //이제 ret는 구했고, 정보를 갱신해야 하는데 어떻게 갱신할까?
    //원본으로부터 새롭게 구축한다 생각하자!
    map <int, REF> new_ref = map <int, REF>();
    map <int, set <int>> new_con = map <int, set <int>>();
    
    //ref 새로 구축
    for(map <int, REF>::iterator iter = ref.begin(); iter != ref.end(); iter++)
    {
        int ref_id = iter->first;
        REF ref_item = iter->second;
        
        if(visit.find(ref_item.a) != visit.end() && visit.find(ref_item.b) != visit.end())
        {
            //a와 b가 살아남았으므로 a에서 b로 잇는 간선 역시 유효한 간선
            new_ref[ref_id] = ref_item;
        }
    }
    
    //con 새로 구축
    for(map <int, set <int>>::iterator iter = con.begin(); iter != con.end(); iter++)
    {
        int obj_id = iter->first;
        
        //visit에 없다면 해당 obj는 제거된 것이므로 continue 걸어버린다.
        if(visit.find(obj_id) == visit.end())
            continue;
        
        //그렇지 않으면 id가 obj_id인 object는 살아 남은 것임.
        new_con[obj_id] = set <int>();
        set <int> second = iter->second;
        for(set <int>::iterator t_iter = second.begin(); t_iter != second.end(); t_iter++)
        {
            int ref_id = (*t_iter);
            //참조가 제거되었다면 pass
            if(new_ref.find(ref_id) == new_ref.end())
                continue;
            //참조가 제거되지 않은 경우
            new_con[obj_id].insert(ref_id);
        }
    }
    
    ref = new_ref;
    con = new_con;
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
        con[obj_id] = set<int>();
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
            con[obj_id] = set<int>();
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
            
            ref[ref_id] = item;
            con[item.a].insert(ref_id);
        }
        
        //(4) REMOVE ref_id
        //연결 고리 제거
        else if(is_eq(tokens[0], "REMOVE"))
        {
            int ref_id = stoi(tokens[1]);
            REF ref_info = ref[ref_id];
            
            //ref 정보에서 제거한 다음에
            ref.erase(ref.find(ref_id));
            
            //실제 연결되어 있는 con 동기화
            int a = ref_info.a;
            int b = ref_info.b;
            
            con[a].erase(con[a].find(ref_id));
        }
        
        //(5) M (major gc)
        else if(is_eq(tokens[0], "M"))
            printf("%d\n",bfs(0));
        
        //(6) m (minor gc)
        else
            printf("%d\n",bfs(1));
    }
    return 0;
}